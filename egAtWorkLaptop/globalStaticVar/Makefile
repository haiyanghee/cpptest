all: other.out
	#gcc -c ./header.c
	#gcc main.c header.o -o other.out
	#gcc main.c
	#./a.out
	./other.out

header.o : header.c header.h
main.o : main.c header.h

other.out : main.o header.o
	#gcc main.o header.o -o other.out
	gcc $^ -o $@
#%.o : %.c

.PHONY: clean
clean:
	-rm *.o
