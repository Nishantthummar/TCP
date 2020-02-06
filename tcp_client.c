				//////TCP_Client/////////
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char *argv[])
{
	int clientSocket, serverSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	socklen_t addr_size;
	char reciv[100];
	char buf[1024];

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	
	addr_size = sizeof(serverAddr);
	serverSocket = 	accept(clientSocket, (struct sockaddr*)&clientAddr, &addr_size);

	recv(clientSocket, reciv, strlen(reciv), 0);
	printf("\nFrom server %s", reciv);
	send(serverSocket, argv[1], strlen(argv[1]), 0);
	printf("\nsending.....");
	sleep(1);

	recv(clientSocket, buf, strlen(buf), 0);
	printf("\nIn upper case %s", buf);
}

