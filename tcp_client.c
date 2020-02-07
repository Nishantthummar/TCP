				//////TCP_Client/////////
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char *argv[])
{
	if (argc <2) {
		printf("\nEnter argument too");
		printf("\nFor example ./name ip_address port_no argument");
		exit(1);
	}
	
	int clientSocket, serverSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	socklen_t addr_size;
	char reciv[100];
	char buf[1024];

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(clientSocket < 2) {
		printf("\nError creating socket");
		clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	}
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	addr_size = sizeof(serverAddr);
	if(connect(clientSocket, (struct sockaddr*)&serverAddr, addr_size) < 0) {
		printf("\nConnection faild");
	}
	
	int flag;
	flag = recv(clientSocket, reciv, 9, 0);
	printf("\nflag is %d", flag);
	//printf("\nFrom server %s", reciv);

	send(clientSocket, argv[1], 1024, 0);
	printf("\nsending.....");

	int rflag;
	rflag = recv(clientSocket, buf, 1024, 0);
	printf("\nrflag is %d", rflag);
	printf("\nIn upper case %s", buf);
}

