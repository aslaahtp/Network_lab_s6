#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
    int n1,buff[10],even[10],odd[10],e=0,o=0;
    int client_fd;
    int server_fd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in saddress;
    if(server_fd==-1)
    {
        printf("Socket creation failed");
        exit(0);    
    }
    else 
    {
       printf("Socket created\n");
    }
    saddress.sin_family=AF_INET;
    saddress.sin_addr.s_addr=inet_addr("127.0.0.1");
    saddress.sin_port=htons(8000);

    int bind_status=bind(server_fd,(struct sockaddr*)&saddress,sizeof(saddress));
    if(bind_status==-1)
	printf("Binding Failed\n");
    else
    {
    	printf("Binding Done\n");
        listen(server_fd,6);
        printf("Listening...\n");
        int addrlen=sizeof(saddress);
        client_fd=accept(server_fd,(struct sockaddr*)&saddress,(socklen_t *)&addrlen);
        if(client_fd<0)
        {
          printf("Error");
          exit(1);
        }
        recv(client_fd,&n1,1*sizeof(int),0);
        recv(client_fd,&buff,n1*sizeof(int),0);
        printf("Recieved Array size:%d\n",n1);
        printf("Array\n");
        for(int i=0;i<n1;i++)
        {
          printf("%d ",buff[i]);
        }
        printf("%d",buff[2]);
        for(int i=0;i<n1;i++)
        {
          if(buff[i] % 2 == 0)
          {
            even[e]=buff[i];
            e++;
          }
          else
          {
           odd[o]=buff[i];
           o++;
          }
        }
        printf("\nSending back..\n");
        send(client_fd,&e,1*sizeof(int),0);
        send(client_fd,&o,1*sizeof(int),0);
        send(client_fd,&even,e*sizeof(int),0);
        send(client_fd,&odd,o*sizeof(int),0);
    }
    
    //close(server_fd);
}

