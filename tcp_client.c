				//////TCP_Client/////////
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 100000

int main(int argc, char *argv[])
{
/*	if (argc <2) {
		printf("\nEnter argument too");
		printf("\nFor example ./name argument");
		exit(1);
	}*/
	
	int clientSocket, serverSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	socklen_t addr_size;
	char reciv[100];
	char buf[MAX];
	char fbuf[MAX];
	FILE *fin, *fout;
	char c;
	int i=0;

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


	fin = fopen("input.txt", "r");
	int size;
	fseek(fin, 0, SEEK_END);
	size = ftell(fin);
	printf("\nSize of file is %d", size);
	fseek(fin, 0, SEEK_SET);\

	c = fgetc(fin);
	while(c != EOF) {
	//fgets(fbuf, 1024, fin);
	fbuf[i] = c;
	c = fgetc(fin);
	//printf("%c", fbuf[i]);
	//if(i == size) {
	//	send(clientSocket, fbuf, size, 0);
	//	i=-1;
//	}
	i++;
	//send(clientSocket, fbuf, 1024, 0);
	}
	send(clientSocket, fbuf, size, 0);
	//printf("\n I is %d", i);
	printf("\nsending.....");
	fclose(fin);

	int rflag;
	rflag = recv(clientSocket, buf, size, 0);
	printf("\nrflag is %d", rflag);
	//printf("\nIn upper case %s", buf);
	fout = fopen("output.txt", "w");
	fputs(buf, fout);
	fclose(fout);
}

