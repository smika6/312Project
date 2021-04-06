Makefile:

all: Philosopher run

mutualexlusion: Philosopher.cpp
	g++ Philosopher.cpp -o Philosopher -std=c++0x

run: Philosopher
	./Philosopher 

clean:
	rm -f Philosopher
