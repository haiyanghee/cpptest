#include <cstdlib>
#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


void binaryToHexString(const unsigned char *binBuf, size_t binBufSize,
		       std::string &out)
{
	/*
	NOTE: This function is originally created for converting the binary
      output of sha256 to hexadecimal string. We should use the openssl API as
      much as possible, but in version 1.1.1 (the time of the code written),
      there is no OPENSSL_buf2hexstr_ex() function (which exists in
      version 3.0), but only the OPENSSL_buf2hexstr() function. In the man page
      https://www.openssl.org/docs/man3.0/man3/OPENSSL_buf2hexstr_ex.html,
      OPENSSL_buf2hexstr() uses a separator ":" for the hex output, which is not
      ideal here (technically it doesn't matter, but filling the DB with ":"
      separat       or doesn't make sense). The OPENSSL_buf2hexstr_ex() function
      give us the control of not including a separator, but it is not available
      in version 1.1.1. While we could reparse the output of
      OPENSSL_buf2hexstr(), it is not an elegant solution. After digging through
      the source code:
	  - version 1.1.1:
      https://github.com/openssl/openssl/blob/OpenSSL_1_1_1-stable/crypto/o_str.c#L191
	  - version 3.1:
      https://github.com/openssl/openssl/blob/openssl-3.1/crypto/o_str.c#L221 (I
      will be refering to the version 3.1 code, because it is more general than
      version 1.1.1.) we see the following:
	  - openssl assumes each char is exactly 8 bits. In particular, the code
      looks like:
      ```
      *q++ = hexdig[(*p >> 4) & 0xf];
      *q++ = hexdig[*p & 0xf];
      ```
	  However, the C standard only restricts the size of a char is at least
      8 bits. But if openssl assumes char = 8 bits, we can also do it here
	  - if we don't want a separator, the size of the buffer we need to
      allocate is exactly 2*SHA256_DIGEST_LENGTH+1, where the +1 is reserved for
      the null terminator. This is also true in the source code:
      ```
      size_t len = has_sep ? buflen * 3 : 1 + buflen * 2;
      ```
	  - the `hexdig` array used in openssl contains capitalized A-Z for
      hexadecimal output, however the standard command line utility `sha256` and
      `openssl dgst -sha256` outputs in lower cased a-z hexadecimal (this is
      true for git com       mit hashes when doing `git log`). This is more of a
      personal preference thing, but to make it consistent with some of the
      widely used command line utilities, our implementation below will use
      lowercased a-z.

      Our binary two hex conversion will be based on the source code of
      version 3.1.
	*/
	static const char hexdig[] = "0123456789abcdef";
	// allocate 2*SHA256_DIGEST_LENGTH+1 size buffer
	char hexOutput[2 * binBufSize + 1];
	char *q = hexOutput;
	const unsigned char *p;
	size_t i; // openssl chose size_t for the buflen

	// The loop below is copied from openssl source code. Our binary output
	// size is SHA256_DIGEST_LENGTH
	for (i = 0, p = binBuf; i < binBufSize; ++i, p++) {
		// note the post increment ++ is higher precedence than the
		// dereference operator *, so *q++ does what you think it does
		// same thing with *p >> 4, the shift right has less precedence
		// than *, so it's ok same thing with *p & 0xf, the bitwise and
		// has less precedence than *, so it's ok right shift 4 to get
		// the first 4 bits of the 8 bit char, then bitwise anding with
		// 0xf, which is all 0s except the rightmost 4 bits are 1s (for
		// safety reasons). This will extract a 4-bit index into the
		// hexdig array
		*q++ = hexdig[(*p >> 4) & 0xf];
		*q++ = hexdig[*p & 0xf];
	}
	// after the loop, q would be added 2 * SHA256_DIGEST_LENGTH + 1 times,
	// so we will add the null terminator at the end
	*q = '\0';

	// lastly, we need to copy hexOutput to the string out using operator=()
	out = hexOutput;
}


// its ok if hashSize = actual hash size + 1, since output of sha256sum will be
// more than that..
bool pipeToSha256(const char *buf, size_t bufSize, char *hashOutputBuf,
		  size_t hashOutputBufSize)
{
	// fprintf(stderr, "in pipeToSha256..\n");

	// we want to do something like
	// printf "buffer" | sha256sum -b
	// except we don't need to call the printf, we can just fwrite to the
	// pipe

	// refer to example on
	// https://stackoverflow.com/questions/33884291/pipes-dup2-and-exec
	// https://stackoverflow.com/questions/37603297/wc-standard-input-bad-file-descriptor-on-fork-pipe-execlp
	pid_t pid;
	int fd[2];

	pipe(fd);
	// write end of pipe is 1, read end is 0
	const int WRITE_END = 1, READ_END = 0;
	pid = fork(); // will fork to call the sha256sum


	/*
    "Idealized" but wrong piping flow:
    READ_END (stdout) <---- sha256sum <--- WRITE_END (stdin)

    However, we actually need 2 pipes here, because sha256sum cannot write to
    the READ_END of the pipe... so we will use popen for another pipe

    Correct piping flow:
    our pipe's READ_END  <--- our pipe's WRITE_END (stdout for sha256sum, which
    is the READ_END of popen's pipe) <---- sha256sum
    <--- popen's pipe WRITE_END
	*/

	if (pid == 0) {
		// child case

		// stdout of sha256sum goes to the write end of our pipe
		dup2(fd[WRITE_END], STDOUT_FILENO);

		// close the duplicated fd in the child
		close(fd[0]);
		close(fd[1]);

		// use popen to create a pipe that we can write to, and the
		// output of sha256sum (STDIN_FILENO) will go to the WRITE_END
		// of our pipe

		//  add -b for binary input
		FILE *fWriteToSha256 = popen("sha256sum -b ", "w");
		if (!fWriteToSha256) {
			fprintf(stderr, "child failed to execute popen!");
			exit(EXIT_FAILURE);
		}

		const char *bufP = buf;
		size_t writeSize = bufSize;
		// writes all the binary data from the buffer to popen's pipe
		while (writeSize > 0) {
			auto a = fwrite(bufP, 1, writeSize, fWriteToSha256);
			if (a < writeSize) {
				fprintf(stderr,
					"child failed to execute write!");
				exit(EXIT_FAILURE);
			}
			bufP += a;
			writeSize -= a;
		}
		pclose(fWriteToSha256);
		exit(EXIT_SUCCESS);
	} else if (pid > 0) {
		// parent case, fork succeeded

		// close because parent don't need the WRITE_END
		close(fd[WRITE_END]);
		// now parent do the reading (before the child close, since we
		// want to synchronize the write and the read with the pipe..
		// otherwise the pipe is full and nothing works)

		/*
		The sha256sum outputs the format as:
	<hash> <filename>
		we need to make sure our readbuffer have enough size..

	we know the hash output will be 2 * SHA256_DIGEST_LENGTH, and since we
	are reading from stdin, <filename> will be "-". But just to be safe, we
	allocated a bit more than we need because why not ...
		*/
		// char readBuf[2 * SHA256_DIGEST_LENGTH + 1];

		char *readP = hashOutputBuf;
		size_t readLeftoverSize = hashOutputBufSize;
		// we don't have to read all the sha256sum output here because
		// we know exactly how long the actual hash is

		// but its ok if hashSize = actual hash size + 1, since output
		// of sha256sum will be more than that..
		while (readLeftoverSize > 0) {
			auto a = read(fd[READ_END], readP, readLeftoverSize);
			if (a < 0) {
				fprintf(stderr,
					"parent failed to execute read!");
				goto returnFalseTag;
			}
			if (a == 0) // finished reading, reached EOF
				break;
			readP += a;
			readLeftoverSize -= a;
		}
		close(fd[READ_END]);
		// add the null terminator at the end
		hashOutputBuf[2 * SHA256_DIGEST_LENGTH] = '\0';

		// fprintf(stderr, "parent printing the buffer read: '%s'\n",
		// hashOutputBuf);

		// wait for the children to close
		// taken from the man page example

		while (wait(NULL) > 0)
			;
		/*
	pid_t p;
	int wstatus;
			do {
				w = waitpid(pid, &wstatus, WUNTRACED |
		   WCONTINUED); if (w == -1) { fprintf(stderr, "waitpid
		   failed"); goto returnFalseTag;
				}
			} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));

			// if child exited, check the return status
			if (WIFEXITED(wstatus)) {
				if (WEXITSTATUS(wstatus) != EXIT_SUCCESS) {
					fprintf(
					    stderr,
					    "child didn't exist successfully!
		   The exist status is %d\n", WEXITSTATUS(wstatus)); goto
		   returnFalseTag;
				}
				// else { fprintf( stderr, "child existed
		   successfully!
				// The exist status is %d\n",
		   WEXITSTATUS(wstatus)); }
			}
			// else the child didn't exit normally (i.e. not by
		   exit(3) or
			// _exit(2)), then something very wrong happend ..
			else {
				fprintf(stderr, "child exited not normall!");
				goto returnFalseTag;
			}
		*/

	} else {
		// fork failed..
		fprintf(stderr, "fork failed");
		goto returnFalseTag;
	}


	return true;

returnFalseTag:
	close(fd[0]);
	close(fd[1]);
	return false;
}

// will generate random number [0, maxInt-1]
inline int generateRandomNonNegIntStartAtZero(int maxInt)
{
	return rand() % maxInt;
}

// maxSize is the maximum size of the buffer, but we have to make the
// stringrandomStrLen null terminated :) return the length of the random string
int generateRandomStringOfMaxSize(char *buf, size_t maxSize)
{
	// a string of alphabet taken from somewhere on the internet because I'm
	// too lazy to write it myself..
	static const char alph[]
	    = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#?!";
	// need to -1 because of null terminator
	static const int alphSize = sizeof(alph) - 1;

	// make sure we don't get trolled
	if (maxSize == 0) {
		buf[0] = '\0';
		return 0;
	}
	int randomStrLen = generateRandomNonNegIntStartAtZero(maxSize);
	// don't get trolled with length 0 string
	if (randomStrLen == 0) randomStrLen = maxSize - 1;

	for (int i = 0; i < randomStrLen; ++i) {
		buf[i] = alph[generateRandomNonNegIntStartAtZero(alphSize)];
	}
	// add the null terminator
	buf[randomStrLen] = '\0';
	return randomStrLen;
}

void test()
{
	// set the random seed
	srand(time(NULL));

	char strBuf[1024];
	unsigned char hashBinBuffer[SHA256_DIGEST_LENGTH];
	char hashOutputBuf[SHA256_DIGEST_LENGTH * 2 + 1];
	memset(strBuf, 0, sizeof(strBuf));
	// const int testcases = 10000;
	const int testcases = 1000;
	std::string s;

	for (int i = 0; i < testcases; ++i) {
		const int randStrLen
		    = generateRandomStringOfMaxSize(strBuf, sizeof(strBuf));
		SHA256((const unsigned char *)strBuf, randStrLen,
		       hashBinBuffer);

		binaryToHexString(hashBinBuffer, sizeof(hashBinBuffer), s);
		pipeToSha256(strBuf, randStrLen, hashOutputBuf,
			     sizeof(hashOutputBuf));
		if (strcmp(s.c_str(), hashOutputBuf) != 0) {
			printf("sha256 calculation is wrong!\n");
			printf(
			    "expected sha256 output from the command line:\n%s\n",
			    hashOutputBuf);
			printf(
			    "actual sha256 output from our conversion:\n%s\n",
			    s.c_str());
			return;
		}
		// printf("i= %d, our sha256 conversion: \n%s\n", i, s.c_str());
	}
	printf("All %d sha256 test cases passed!\n", testcases);
}

int main()
{
	/*
	const std::string s = "iwill hash this :)";
	    unsigned char buf[SHA256_DIGEST_LENGTH];
	    auto ret = SHA256((const unsigned char *)s.c_str(), s.size(), buf);
	    printf("ret = %p, buf = %p, ret == buf = %d\n ", ret, buf, ret ==
	   buf); if (!ret) printf("ret is/should be null..\n"); printf("buf =
	   %s\n ", buf);

	    char outBuf[SHA256_DIGEST_LENGTH * 2 + 1];
	    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
		    sprintf(outBuf + (i * 2), "%02x", buf[i]);
	    }
	    outBuf[SHA256_DIGEST_LENGTH * 2] = '\0';
	    printf("outBuf = %s\n ", outBuf);
	    printf("sizeof(buf)  = %ld, sizeof(outBuf) = %ld\n ", sizeof(buf),
		   sizeof(outBuf));


	    std::string dummy;
	    binaryToHexString(buf, sizeof(buf), dummy);
	    printf("dummy string output = %s\n", dummy.c_str());

	*/


	/*
	    size_t strlen = 0;
	    auto a = OPENSSL_buf2hexstr_ex(s.c_str(), s.size(), &strlen, outBuf,
					   SHA256_DIGEST_LENGTH * 2 + 1, '\0');
	    printf("OPENSSL_buf2hexstr_ex outBuf = %s\n ", outBuf);
	*/

	/*
	    auto a = OPENSSL_buf2hexstr(buf, SHA256_DIGEST_LENGTH);
	    printf("OPENSSL_buf2hexstr = %s\n ", a);
	    OPENSSL_free(a);
	*/
	test();
}
