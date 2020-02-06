				//////////////TCP Server/////////
#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define PORT 8080

int main(int argc, char *argv[]) 
{
	int sockfd;
	struct sockaddr_in serverAddr;
	int i;
	socklen_t  addr_size;
	int newsocket;
	struct sockaddr_in newAddr;
	char buf[1024];
	char send_msg[1024];
	char msg[100];

	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	listen(sockfd, 5);

	addr_size = sizeof(newAddr);
	newsocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
	strcpy(msg, "Connected!!");
	send(newsocket, msg, strlen(msg), 0);
	printf("\nSend connected msg.");

	recv(newsocket, buf, strlen(buf), 0);
	
	for (i=0; buf[i] != '\0'; i++) {
		send_msg[i] = toupper(buf[i]);
	}

	send(newsocket, send_msg, strlen(send_msg), 0);
}

		
