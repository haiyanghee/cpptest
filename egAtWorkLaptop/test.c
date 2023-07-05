#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>


/*
int main()
{
	struct sockaddr_in local;
	int x;
	printf("x = %d\n", x);
	printf("port = %d\n", local.sin_port + x);
	printf("family = %d\n", local.sin_family);

	typedef int asdf;
	struct Hi {
		asdf a;
	};
}
*/

/*
int main(){
    const char* cert = "-----BEGIN CERTIFICATE-----\n"
                         "MIIEEjCCAvqgAwIBAgIJANAEUoutQc8YMA0GCSqGSIb3DQEBCwUAMIGiMQswCQYD\n"
                         "VQQGEwJVUzETMBEGA1UECAwKQ2FsaWZvcm5pYTERMA8GA1UEBwwITWlscGl0YXMx\n"
                         "DDAKBgNVBAoMA1NTODEUMBIGA1UECwwLRW5naW5lZXJpbmcxIzAhBgNVBAMMGmh0\n"
                         "dHBzOi8vMTAuMC4xNDYuMTk2OjQ0NDY2MSIwIAYJKoZIhvcNAQkBFhN4cmVzdEBk\n"
                         "aXNjb3ZlcnkuY29tMB4XDTE5MDMyODAxMjUxNVoXDTQ2MDgxMzAxMjUxNVowgaIx\n"
                         "CzAJBgNVBAYTAlVTMRMwEQYDVQQIDApDYWxpZm9ybmlhMREwDwYDVQQHDAhNaWxw\n"
                         "aXRhczEMMAoGA1UECgwDU1M4MRQwEgYDVQQLDAtFbmdpbmVlcmluZzEjMCEGA1UE\n"
                         "AwwaaHR0cHM6Ly8xMC4wLjE0Ni4xOTY6NDQ0NjYxIjAgBgkqhkiG9w0BCQEWE3hy\n"
                         "ZXN0QGRpc2NvdmVyeS5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIB\n"
                         "AQCoTRS4Va4Wcj9ZzOChQ1i+qYmc09BGxUBj405v65iCWywN0CaizI+Dz2l35Yz0\n"
                         "lw0Y9KE/QY0vu1U1+GhN7swJZsqmf2s41sRBWEQ+tQvSnWTwz/6eJ39PlS7Sv8zA\n"
                         "yW7I3ZeWPdFTnAbMse+9YjegdSnodFXgP8W9aKy8ISxrWgmreA4pnap+2P/QZVMk\n"
                         "aMvOWGnC3pXiukr4oN7E4OmcUYBgAtHYw18og0vaC+SijiQIEHdfag4fjdqUEqFf\n"
                         "d4ZsSDr13mLxW/nCSVgMDgeniP1ed/xiX4JMr8RzkJxJWAlNEJ2vJi0jyzPs9SlU\n"
                         "SWT6hBSVhdXk4LCkwBnbJbTVAgMBAAGjSTBHMEUGA1UdEQQ+MDyCGmh0dHBzOi8v\n"
                         "MTAuMC4xNDYuMTk2OjQ0NDY2ggh4Y3ZtczE5NoIOeGN2bXMxOTY6NDQ0NjaHBAoA\n"
                         "ksQwDQYJKoZIhvcNAQELBQADggEBAGeAqbKEsb9Ulj8HvO1rNa80frivZB/ddGsi\n"
                         "KD9wV/yxTGvHG7mNLYS4jzF8Mvrqv4KDg0A7XDaz9R1nHEjm7B2raytKn+RrtgmW\n"
                         "iIkvsayAbiuFOpSeLOR9wu01b2og5sI6IWvsGqHVBB+3pTM65B7ke5D5GYR1VIgz\n"
                         "cM1k+1Q4PRJVH99ugT/VZdPof6gbmH0t0nE3f3KCztji9LGnMCcWasw9ndeBRdcs\n"
                         "SCmXRmX0c74MLfbVIr4Guv0PdF7SBzQ97SY8UqywWE4EbppVKwCtN6rxpfztBy17\n"
                         "y5l7l6IMMMPdyPncKn5V+Cxg4kfi3JvwyYdeIg7DyZparyzR9to=\n"
                         "-----END CERTIFICATE-----\n";

const char* key = "-----BEGIN PRIVATE KEY-----\n"
                        "MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQCoTRS4Va4Wcj9Z\n"
                        "zOChQ1i+qYmc09BGxUBj405v65iCWywN0CaizI+Dz2l35Yz0lw0Y9KE/QY0vu1U1\n"
                        "+GhN7swJZsqmf2s41sRBWEQ+tQvSnWTwz/6eJ39PlS7Sv8zAyW7I3ZeWPdFTnAbM\n"
                        "se+9YjegdSnodFXgP8W9aKy8ISxrWgmreA4pnap+2P/QZVMkaMvOWGnC3pXiukr4\n"
                        "oN7E4OmcUYBgAtHYw18og0vaC+SijiQIEHdfag4fjdqUEqFfd4ZsSDr13mLxW/nC\n"
                        "SVgMDgeniP1ed/xiX4JMr8RzkJxJWAlNEJ2vJi0jyzPs9SlUSWT6hBSVhdXk4LCk\n"
                        "wBnbJbTVAgMBAAECggEAEm7u2Am6WYcF3UYNTFxd+fQDuIOSik3McaRR0PxS5eQq\n"
                        "fRDRSn9xMJSlDpa7y4ZHzvXsO0totVOlT5X3hqGjA1yY0YefLMiJEkciomOd+eF3\n"
                        "TtDZKGVXElZanIaZXHwzgBiVI8V9idTLAdxzT6DUSuTKREWJqlgRxl8SnEBd5xv1\n"
                        "7zGLDdgmOQ1P7KMSsbT+nLeIx6Af4dErWlyFWClefb69gGge9G9oQATvyQfngNXz\n"
                        "BgX4NxdfAz9Byji2uH4iiyPGKuPUO4iZ91Ih4gd7k0aNyvIkrRVOYGbDu9qWPJht\n"
                        "CE3C/f0kbSAsciLX2rlNQ+9p7JYYZz2tzutTrUFHAQKBgQDash5FUqama45ywJL0\n"
                        "wEe8EpkWW2JIajvcbPO1BV7ynbsTVZlcB5t080rdihb5SsoY1fEI43C5lXhR/Pu4\n"
                        "o86rait/vZ2i9yvd+1zpzU8COnf71ukn74Z45ATpY6DV3jX8v9oYJNZD6r29/VEB\n"
                        "80wGXb4Soz7BsdaSD7JHwXX8dQKBgQDFAltYTeYbyPugUozYw5QalfAPvjB/VO87\n"
                        "j+OrQd8rKukNRrLPLCis0GPglSgvlA7xu3eV9nXwOornefgh953nuw6iBFNTprQD\n"
                        "hybgprH7abWYaIg1sp3aV5Q9VOZ/wrOS1pUOyUp5p5da5C6/HHj7tMmB+2g2LPk/\n"
                        "lhVcPnVK4QKBgQDLsi/DvfH+/BtYAspeMWIfaOsyCbgHXvuWmdx89R20uPlwTsBj\n"
                        "GarQSXOn2WEAnYqTi2HQN5fdI71IEGydU+XBf0g42PIkwjgXsHKgSlyW5MKwzUGp\n"
                        "ss37d9ajU+qQiUKbwk5vQpBX/iLw/Ssgt+5N166cSXTAkNYcgYY6k5VDqQKBgQCX\n"
                        "eeZuEQc6meAPNymgiVBY2KxKDnwPi2ieLVZqGS3UbRvf31ogvN1RcrE4vra1Tmvn\n"
                        "JbMfFO89lGW08Sz+QPuib0si+5xuFyEWDVaxKLp0iqTb2JPSZdHFTc1nEt5foX6d\n"
                        "Cmx1gAPJYjiX5BalTuke77R4Qquv7AiBAY7O7B8XQQKBgQCZ/PK1UDI4rW/ynif9\n"
                        "rnpdoUvWlbWama8YDcfwxJEeQd9zipjECQkuZFZLBgnoqzS1cDyEApaDT7kWkcgB\n"
                        "wZIY+1lzLh6iD2wbWpt2X8ELQX+k01/RmPScohZiAKpd0i5rf4a+ssqe00BuDXoO\n"
                        "ksjbGNbEmTd4GJhiPZvsPL5m5w==\n"
                        "-----END PRIVATE KEY-----\n";

printf("cert:\n %s", cert);
printf("key:\n %s", key);

}
*/

int main(){
    int i=1,j=0;
    //int i=0,j=1;
    for (int k=1;k<20;++k){
        printf("======== k = %d\n", k);
        printf("before loop: i = %d, j = %d\n", i, j);
        //j = j + i;
        //i = j - i;
        j = j + i;
        i = j - i;
        printf("after loop: i = %d, j = %d\n", i, j);
    }
    
}
