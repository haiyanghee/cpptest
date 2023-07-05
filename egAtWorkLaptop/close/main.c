#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main()
{
	int fd = -1;
	const int ret = close(fd);
	//printf("ret = %d, errno = %d, EBADF = %d\n", ret, errno, EBADF);
    char buf[128];                         
    //char buf[3];                         

    //const int curErrno = errno;
    const int curErrno = EADDRINUSE;
    strerror_r(curErrno, buf, sizeof(buf));
    printf("strerror_r returned '%s'\n", buf);

    //printf("strerror_r returned '%s'\n", strerror_r(13, buf, sizeof(buf)));
}
