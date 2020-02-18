#make file for TCP client-server
all:
	gcc -o tcp_server tcp_server.c
	gcc -o tcp_client tcp_client.c

server:
	gcc -o tcp_server tcp_server.c
	
client:
	gcc -o tcp_client tcp_client.c
clean:
	rm tcp_client tcp_server



