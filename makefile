Makefile:

all: server client run

server: philServer.cpp
	g++ philServer.cpp -o server

client: philClient.cpp
	g++ philClient.cpp -o client

run: server
	./server

clean:
	rm -f server
	rm -f client