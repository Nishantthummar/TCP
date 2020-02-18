						/////TCP_Client Code//////
///////////////////////////////////////////////////////////////////////////////
//This is code of TCP Client which send data to the server by 1kB string and
//receive the converted data back from server
//////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define MAX 1024
#define MAXI 1000000
int check();
int main(int argc, char *argv[])
{	
	///////////////////////////////////////////////////////////////////////
	//variables for store socket id, types of protocol, method of 
	//transmission
	///////////////////////////////////////////////////////////////////////
	int clientSocket, serverSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	socklen_t addr_size;
	char reciv[100];
	char buf[MAXI];
	char fbuf[MAX];
	FILE *fin, *fout;
	char c;
	int i=0;

	clientSocket = socket(PF_INET, SOCK_STREAM, 0); // create new socket
	if(clientSocket < 0) {
		printf("\nError creating socket");
		clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	}
	serverAddr.sin_family = AF_INET; // types of transmission
	serverAddr.sin_port = htons(PORT); // port number
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ip address

	addr_size = sizeof(serverAddr);
	// connect to server with specify parameter
	if(connect(clientSocket, (struct sockaddr*)&serverAddr, addr_size) < 0) {
		printf("\nConnection failed");
	}
	
	int flag;
	flag = recv(clientSocket, reciv, 9, 0); // receive acknowlegment from server
	if(flag < 0) {
		printf("\nnot receive any response from server");
		exit(1);
	}
	printf("\nflag is %d", flag);


	fin = fopen("input.txt", "r"); // open input file for readonly
	fout = fopen("output.txt", "w+"); // open output file for write
	// to check if input file is opened or not
	if(fin == NULL) {
		printf("\nfile is not open");
		exit(1);
	}
	int size;
	fseek(fin, 0, SEEK_END); // to set a cursor at end of file
	size = ftell(fin); // to find out size of file in Bytes
	printf("\nSize of file is %d", size);
	fseek(fin, 0, SEEK_SET); // to set cursor at begin of file

	c = fgetc(fin); // get character from file
	while(c != EOF) {
		fbuf[i] = c;
		c = fgetc(fin);
		if(i == MAX) {
			flag = send(clientSocket, fbuf, MAX, 0); // send 1024 kB data 
			if(flag < 0) {
				printf("\nunable to send any data");
				exit(1);
			}
			bzero(fbuf, MAX); // to clear fbuf array with zero or NULL
			i=-1;
		}
	i++;
	}
	send(clientSocket, fbuf, MAX, 0); // send data if remaining data which is not equal to 1024 kB
	if(flag < 0) {
		printf("\nunable to send any data");
		exit(1);
	}
	fclose(fin);
	bzero(buf, MAXI);
	int bit;
	bzero(buf, MAXI);
	flag = recv(clientSocket, buf, MAXI, 0);
	//bit = check(buf);
	close(serverSocket);
	printf("\nreceived data of %d bytes", flag);
	fputs(buf, fout);
	fclose(fout);
}
/***************************************************************************//*
*function to check end of file
*@paramin char from[] source array
******************************************************************************/
int check(char a[]) {
	int i;
	for(i=0; i<MAX; i++) {
		if(a[i] == '$') {
			a[i] = '\0';
			return -1;
		}
	}
	return 0;
}


