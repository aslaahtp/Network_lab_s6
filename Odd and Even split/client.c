#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>


int main()
{
    int n,arr[10],even[10],odd[10],e,o;
    int client_fd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in address;
    if(client_fd==-1)
    {
        printf("Socket creation failed");
        exit(0);    
    }
    else 
    {
       printf("Socket created\n");
    }
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=inet_addr("127.0.0.1");
    address.sin_port=htons(8000);
    printf("Enter size of array\n");
    scanf("%d",&n);
    printf("Enter array Elements\n");
    for(int i=0;i<n;i++)
    {  
       scanf("%d",&arr[i]);
    }
    int con_status=connect(client_fd,(struct sockaddr*)&address,sizeof(address));
    if(con_status==-1)
	printf("Connection Failed\n");
    else
    {
        printf("Connection Established\n");
        send(client_fd,&n,1*sizeof(int),0);
        printf("Size sent=%d\n",n);
        send(client_fd,&arr,n*sizeof(int),0);
        printf("Array sent \n");
        recv(client_fd,&e,1*sizeof(int),0);
        recv(client_fd,&o,1*sizeof(int),0);
        recv(client_fd,&even,e*sizeof(int),0);
        recv(client_fd,&odd,o*sizeof(int),0);
        printf("Even numbers are:\n");
        for(int i=0;i<e;i++)
        {
            printf("%d ",even[i]);
        }
        printf("\nOdd numbers are:\n");
        for(int i=0;i<o;i++)
        {
            printf("%d ",odd[i]);
        }
    }
    close(client_fd);
}
