all: server client
server:server.o
	g++ -g server.o -o server
client:client.o
	g++ -g client.o -o client
server.o:server.cpp
	g++ -c server.cpp -o server.o
client.o:client.cpp
	g++ -c client.cpp -o client.o
.PHONY:clean
clean:
	rm server client *.o
