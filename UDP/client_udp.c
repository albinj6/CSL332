#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
int client_fd,new_socket,client_size;
struct sockaddr_in client_addr,server_addr;
char server_message[100],client_message[100];
int main(){

	memset(server_message, '\0',sizeof(server_message));
	memset(client_message, '\0',sizeof(client_message));

	//create a socket for client, store socket file descriptor to client_fd
	if((client_fd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))<0){
		printf("Error while creating socket\n");
		return -1;
	}
	printf("Socket created successfully!\n");
	
	//set port no, ip address, and family of addresses
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2001);              //htons - host byte order to network byte order conversion
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	//connect to server
	if(connect(client_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
		printf("Could'nt connect to server!\n");
		return -1;
	}
	printf("Connected to server!\n");

	gets(client_message);
	client_size=sizeof(client_addr);

	//send message to server
	if(sendto(client_fd,client_message,sizeof(client_message),0,(struct sockaddr*)&server_addr,client_size)<0){
		printf("Could'nt send message to server!\n");
		return -1;
	}
	//receive message from server
	if(recvfrom(client_fd,server_message,sizeof(server_message),0,(struct sockaddr*)&server_addr,&client_size)<0){
		printf("Could'nt receive message from server\n");
		return -1;
	}
	printf("Message from server: %s\n",server_message);
	
	close(client_fd);
	}
