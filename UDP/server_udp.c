#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
int server_fd,new_socket,client_size;
struct sockaddr_in client_addr,server_addr;
char server_message[100],client_message[100];
int main(){

	memset(server_message, '\0',sizeof(server_message));
	memset(client_message, '\0',sizeof(client_message));

	//create a socket for client, store socket file descriptor to client_fd
	if((server_fd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))<0){
		printf("Error while creating socket\n");
		return -1;
	}
	printf("Socket created successfully!\n");
	
	//set port no, ip address, and family of addresses
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2001);              //htons - host byte order to network byte order conversion
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	//bind ip address and port to server socket
	if(bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
		printf("Couldn't bind to the port\n");
		return -1;
	}
	printf("Binding done successfully!\n");
	
	client_size=sizeof(client_addr);
	//receive message from client
	if(recvfrom(server_fd,client_message,sizeof(client_message),0,(struct sockaddr*)&client_addr,&client_size)<0){
		printf("Could'nt receive message from client\n");
		return -1;
	}
	printf("Message from client: %s\n",client_message);
	
	strcpy(server_message,"Recieved!");

	//send response to client
	if(sendto(server_fd,server_message,sizeof(server_message),0,(struct sockaddr*)&client_addr,client_size)<0){
		printf("Could'nt send response to client\n");
		return -1;
	}
	printf("Response sent!\n");
	
	close(new_socket);
	close(server_fd);
	}
