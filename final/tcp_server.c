				//////////////TCP Server/////////
///////////////////////////////////////////////////////////////////////////////
//This is code of TCP server which accept data from client by 1kB string and
//convert it into upper case than transmitt at again to client side
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#define PORT 8080
#define MAX 1024
#define MAXI 1000000

FILE *fp;
int check(); // Function to check end of file
int upperfile();// Function to convert file upper case

int main(int argc, char *argv[]) 
{
	///////////////////////////////////////////////////////////////////////
	//variables for store socket id, types of protocol, method of 
	//transmission
	///////////////////////////////////////////////////////////////////////
	int sockfd;
	struct sockaddr_in serverAddr;
	int i;
	socklen_t  addr_size;
	int newsocket;
	struct sockaddr_in newAddr;
	char buf[MAX];
	char send_msg[MAXI];
	char msg[100];
	fp = fopen("temp.txt", "w+"); // open temp file for write incoming data
	
	//while (1){	
	sockfd = socket(PF_INET, SOCK_STREAM, 0); // created new socket
	serverAddr.sin_family = AF_INET; // type of transmission
	serverAddr.sin_port = htons(PORT); // port number where server listen
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//while (1){	
	bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)); // bind the socket
	listen(sockfd, 5); // listen request from client at time 5

	addr_size = sizeof(newAddr);
	newsocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size); // accept connection request
	strcpy(msg, "Connected");
	int sflag;
	sflag =	send(newsocket, msg, strlen(msg), 0); // Send acknowledgment 
	
	/*********************************************//*
	*Receive from client
	************************************************/
	int flag, count, exit;
	do{
			
		flag = recv(newsocket, buf, MAX, 0); // receive data from client store into buf array
		printf("\nrecev flag is %d", flag);
		fputs(buf, fp); // from buf to file
		exit = check(buf, send_msg); // if particular sign is found then exit from loop
	} while(exit != -1);
	/***********************************************/

	int size;
	size = upperfile(send_msg); // transfer data from file to array with uppercase
	fclose(fp);
	printf("\n%d", size);
	int s1=0;
	send(newsocket, send_msg, size, 0); // send final converted data
	close(sockfd); // close connection
	printf("\nfinish");
	bzero(send_msg, MAXI);
	bzero(buf, MAX);
	//}
}


/***************************************************************************//*
*function for check end file
*@paramin char from[] source array
*@paramin char to[] destination array
******************************************************************************/
int check(char from[], char to[] ) {
	int i;
	for(i=0; i< MAXI; i++) {
		if(from[i] == '$') {
			return -1;
		}
	}
	return 0;
}


/***************************************************************************//*
*function for convert file into upper case
*@paramin char from[] source array
******************************************************************************/
int upperfile(char from[]) {
	int i=0, count=0;
	char c;
	fseek(fp, 0, SEEK_SET);
	c = fgetc(fp);
	while(c != EOF) {
		from[i] = toupper(c);
		c = fgetc(fp);
		i++;
		count++;
	}
	from[i] = '\0';
	return count;
}	
