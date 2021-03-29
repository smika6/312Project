Makefile:

all: mutualexlusion run

mutualexlusion: mutualexlusion.c
	g++ mutualexlusion.c -o mutualexlusion -std=c++0x

run: mutualexlusion
	./mutualexlusion 

clean:
	rm -f mutualexlusion
