all: client server

client: client.o
	gcc -Wall -o $@ $^

server: server.o
	gcc -Wall -o $@ $^

%.o: %.c
	gcc -Wall -c $<

clean:
	rm -f client server *.o *~

