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

//#define port 8080
#define MAX 1024
//#define MAXI 1000000

FILE *fp;
int check(); // Function to check end of file
int upperfile();// Function to convert file upper case

int main(int argc, char *argv[]) 
{
	int port1[10];

	///////////////////////////////////////////////////////////////////////
	//variables for store socket id, types of protocol, method of 
	//transmission
	///////////////////////////////////////////////////////////////////////
	int sockfd;
	struct sockaddr_in serverAddr;
	int i_loop;
	socklen_t  addr_size;
	int newsocket;
	struct sockaddr_in newAddr;
	char c_buf[MAX];
	char c_send_c_msg[MAX];
	char c_msg[100];
	pid_t pid;
	//pid = fork();

	if(argc < 3) {
		printf("\nEnter valid arguments\n\tExample => ./file PORT IP_address \n");
		exit(1);
	}
	int port;
	port= atoi(argv[1]);
	printf("\nPort number is %d", port);

	//fp = fopen("temp.txt", "w+"); // open temp file for write incoming data //new

	//while (1){	
	sockfd = socket(PF_INET, SOCK_STREAM, 0); // created new socket
	serverAddr.sin_family = AF_INET; // type of transmission
	serverAddr.sin_port = htons(port); // port number where server listen
	serverAddr.sin_addr.s_addr = inet_addr(argv[2]);
	//while (1){	
	bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)); // bind the socket
	int a;
	a=listen(sockfd, 5); // listen request from client at time 5
	printf("\nprint a is %d", a);

	addr_size = sizeof(newAddr);
	pid = fork();
	newsocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size); // accept connection request
	strcpy(c_msg, "Connected");
	int sflag;
	sflag =	send(newsocket, c_msg, strlen(c_msg), 0); // Send acknowledgment 
	
	/*********************************************//*
	*Receive from client
	************************************************/
	int flag, count, exit;
	do{
			
		flag = recv(newsocket, c_buf, MAX, 0); // receive data from client store into buf array
		if(flag < 0) {
			printf("\nnot receive any data");
			break;
		}
		printf("\nrecev flag is %d", flag);
		//fputs(c_buf, fp); // from buf to file //or
	
		exit = check(c_buf, c_send_c_msg); // if particular sign is found then exit from loop
		flag = send(newsocket, c_send_c_msg, MAX, 0); //new
	} while(exit != -1);
	/***********************************************/

	int size;
	//size = upperfile(c_send_c_msg); // transfer data from file to array with uppercase //new
	//fclose(fp); //new
	//printf("\n%d", size);
	int s1=0;
//	send(newsocket, c_send_c_msg, size, 0); // send final converted data //new
	close(sockfd); // close connection
	printf("\nfinish");
	//bzero(c_send_c_msg, MAX);
	//bzero(c_buf, MAX);
	return 0;
	

}


/***************************************************************************//*
*function for check end file
*@paramin char from[] source array
*@paramin char to[] destination array
******************************************************************************/
int check(char from[], char to[] ) {
	int i_loop;
	for(i_loop=0; i_loop< MAX; i_loop++) {
		if(from[i_loop] == '$') {
			return -1;
		}
		to[i_loop] = toupper(from[i_loop]);
		//printf("%c", to[i_loop]);
	}
	return 0;
}


/***************************************************************************//*
*function for convert file into upper case
*@paramin char from[] source array
******************************************************************************/
int upperfile(char from[]) {
	int i_loop=0, count=0;
	char c;
	fseek(fp, 0, SEEK_SET);
	c = fgetc(fp);
	while(c != EOF) {
		from[i_loop] = toupper(c);
		c = fgetc(fp);
		i_loop++;
		count++;
	}
	from[i_loop] = '\0';
	return count;
}	

/*****************************************************************************/
