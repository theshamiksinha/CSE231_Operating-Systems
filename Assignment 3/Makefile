all: clean example 

example: example.c mems.h
	gcc -o example example.c

run: example
	./example

clean:
	rm -rf example