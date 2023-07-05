CC=gcc
CFLAGS=-Wall -Wextra
CFILES=$(wildcard *.c)
#OFILES=$(patsubst %.c,%.o,$(CFILES))
OFILES=$(CFILES:.c=.o)

#can use `pkg-config` to get linkers required to link a library
#for openssl, it's `-lssl `-lcrypto`
LDFLAGS=$(shell pkg-config --libs openssl)

main: $(OFILES)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

