#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
	int socket_desc,k=5,m=1,p,client_size,client_sock;
	struct sockaddr_in server_addr,client_addr;
	char buffer[1024];
	
	memset(buffer,'\0',sizeof(buffer));
	
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	
	if(socket_desc < 0)
	{
		printf("\nError while creating socket\n");
		return -1;
	}
	printf("\nSocket created successfully\n");
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("\nCouldn't bind to the port\n");
		return -1;
	}
	printf("\nDone with binding\n");
	
	if(listen(socket_desc,1) < 0)
	{
		printf("\nError while listening\n");
		return -1;
	}
	printf("\nListening for incoming connections...\n");
	
	client_size=sizeof(client_addr);
	client_sock=accept(socket_desc,(struct sockaddr*)&client_addr,&client_size);
	
	if(client_sock < 0)
	{
		printf("\nCan't accept\n");
		return -1;
	}
	printf("Client connected at IP:%s and port=%i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
	
	while(k!=0)
	{
		int z=recv(client_sock,buffer, 19, 0);
		if(z==-1)
		{
			printf("error in receiving buffer\n");
			return -1;
		}
		if(strcmp(buffer,"frame")==0)
			printf("received frame %d succesfully\n",m);
		else
			printf("frame %d not received\n",m);
		if(m%2==0)
			strcpy(buffer,"ack");
		else
		{
			strcpy(buffer,"kca");
			printf("ack loss\n");
			for(p=1;p<=3;p++)
			{
				printf("waiting for %d seconds\n",p);
			}
			printf("retransmitting ack....\n");
			strcpy(buffer,"ack");
			sleep(3);
		}
		int y=send(client_sock,buffer, 19, 0);
		if(y<0)
		{
			printf("error while sending\n");
			exit(0);
		}
		else
			printf("ack send succesfully\n");
		k--;
		m++;
	}
	close(client_sock);
	close(socket_desc);
	
	return 0;
}

