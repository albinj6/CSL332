#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
	int socket_desc,client_sock,client_size;
	struct sockaddr_in server_addr,client_addr;
	char server_message[2000],client_message[2000];
	
	//clean buffer
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
	
	//create socket
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	
	if(socket_desc < 0)
	{
		printf("\nError while creating socket\n");
		return -1;
	}
	printf("\nSocket created successfully\n");
	
	//set port and ip
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	//bind to the set port and ip
	if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("\nCouldn't bind to the port\n");
		return -1;
	}
	printf("\nDone with binding\n");
	
	//listen for clients
	if(listen(socket_desc,1) < 0)
	{
		printf("\nError while listening\n");
		return -1;
	}
	printf("\nListening for incoming connections...\n");
	
	//Accept an incoming connection
	client_size=sizeof(client_addr);
	client_sock=accept(socket_desc,(struct sockaddr*)&client_addr,&client_size);
	
	if(client_sock < 0)
	{
		printf("\nCan't accept\n");
		return -1;
	}
	printf("Client connected at IP:%s and port=%i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
	
	//Recieve client's message
	if(recv(client_sock,client_message,sizeof(client_message),0) < 0)
	{
		printf("\nCouldn'd recieve\n");
		return -1;
	}
	printf("\nMsg from client: %s\n",client_message);
	
	//Respond to client
	strcpy(server_message,"THIS IS THE SERVER'S MESSAGE\n");
	
	if(send(client_sock,server_message,strlen(server_message),0) < 0)
	{
		printf("\nCouldn't Send\n");
		return -1;
	}
	
	//Closing socket
	close(client_sock);
	close(socket_desc);
	
	return 0;
}

