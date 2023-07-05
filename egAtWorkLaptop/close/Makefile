CFILES=$(wildcard *.c)
OBJ=$(CFILES:.c=.out)
all: $(OBJ)
	echo $^
%out: %c
	gcc $< -o $@
