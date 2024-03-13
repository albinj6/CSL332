#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
	int socket_desc,k=5,m=1,p;
	struct sockaddr_in server_addr;
	char buffer[1024];
	
	memset(buffer,'\0',sizeof(buffer));
	
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	
	if(socket_desc<0)
	{
		printf("Error while creating a socket\n");
		return -1;
	}
	printf("Socket created successfully\n");
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("Unable to connect\n");
		return -1;
	}
	printf("Connected with server successfully\n");
	
	while(k!=0)
	{
		if(m>0)
			printf("sending frame\n");
		if(m%2==0)
			strcpy(buffer,"frame");
		else
		{
			strcpy(buffer,"error");
			printf("packet loss\n");
			for(p=1;p<=3;p++)
			{
				printf("waiting for %d seconds\n",p);
			}
			printf("retransmitting....\n");
			strcpy(buffer,"frame");
			sleep(3);
		}
		int y=send(socket_desc,buffer, 19, 0);
		if(y<0)
		{
			printf("error while sending\n");
			exit(0);
		}
		else
			printf("message send succesfully\n");
		int z=recv(socket_desc,buffer,19, 0);
		if(z<0)
		{
			printf("error in receiving buffer\n");
			return -1;
		}
		if(strcmp(buffer,"ack")==0)
			printf("received ack for frame %d\n",m);
		k--;
		m++;
	}
	close(socket_desc);
	
	return 0;
}
