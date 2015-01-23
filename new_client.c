#include<netinet/in.h>
#include<sys/types.h> 
#include<sys/socket.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<time.h>
#include "MessageCheck.h" 
#include "socketStruct.h"

#define SERVER_PORT 8080 
#define BUFFER_SIZE 1024*80
#define FILE_NAME_lENGTH 20 

  time_t t_start,t_end;
  struct sockaddr_in client_addr,server_addr; 
  char fileName[FILE_NAME_lENGTH]; 
  char buffer[BUFFER_SIZE]; 
 
void ReciveFile(int client_socket_fd,FILE *fp)
{
    int int_length = 0;
    t_start=time(NULL);
    while((int_length = recv(client_socket_fd, buffer, BUFFER_SIZE, 0)) > 0) 
    { 
         if(fwrite(buffer, sizeof(char), int_length, fp) < int_length) 
         { 
              printf("File: %s Write Failed", fileName); 
              break; 
         } 
         bzero(buffer, BUFFER_SIZE); 
     } 

    t_end=time(NULL);
    printf("The sum of the time is %.0fs\n",difftime(t_end,t_start));
}


void main() 
{ 
    client_addr=InitSocketStruct(client_addr,0);
    int client_socket_fd = socket(AF_INET, SOCK_STREAM, 0); 
    socket_fdCheck(client_socket_fd);
    bindCheck(bind(client_socket_fd, (struct sockaddr*)&client_addr, sizeof(client_addr)));
  
    server_addr=InitSocketStruct(client_addr,SERVER_PORT);
    socklen_t server_addr_length = sizeof(server_addr); 
    connectCheck(connect(client_socket_fd, (struct sockaddr*)&server_addr, server_addr_length));

    bzero(fileName, FILE_NAME_lENGTH);
    printf("Input File Name Which You Want To Get:\n  "); 
    scanf("%s", fileName); 

    sendCheck(send(client_socket_fd, fileName, FILE_NAME_lENGTH, 0),fileName); 
   
    FILE *fp = fopen(fileName, "w"); 
    fileOpenCheck(fp,fileName);
   
    bzero(buffer, BUFFER_SIZE);
    
    printf("Recive start.....\n");
    ReciveFile(client_socket_fd,fp);

    printf("Receive File: %s Finished!", fileName); 
    close(fp); 
    close(client_socket_fd); 
    return; 
} 
