#include<netinet/in.h>
#include<sys/types.h> 
#include<sys/socket.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
	
#include"dbtime.h"

#define SERVER_PORT 8080 
#define BUFFER_SIZE 1024 
#define FILE_NAME_lENGTH 64 
 
void main() 
{ 
    struct sockaddr_in client_addr; 
    bzero(&client_addr, sizeof(client_addr)); 
    client_addr.sin_family = AF_INET; 
    client_addr.sin_addr.s_addr = htons(INADDR_ANY); 
    client_addr.sin_port = htons(0); 
 
    int client_socket_fd = socket(AF_INET, SOCK_STREAM, 0); 
  
    if(client_socket_fd < 0) 
    { 
        perror("Create Socket Error"); 
        return;
    } 
 
    if(-1 == (bind(client_socket_fd, (struct sockaddr*)&client_addr, sizeof(client_addr)))) 
    { 
        perror("Client Bind Error"); 
        return;
    } 
 
    struct sockaddr_in server_addr; 
  
    bzero(&server_addr, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET; 
    if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) == 0) 
    { 
         perror("Server IP Address Error"); 
          return;
    } 
  
    server_addr.sin_port = htons(SERVER_PORT); 
    socklen_t server_addr_length = sizeof(server_addr); 
 
    if(connect(client_socket_fd, (struct sockaddr*)&server_addr, server_addr_length) < 0) 
    { 
        perror("Connect With Server Error"); 
        return;
    } 
 
    char file_name[FILE_NAME_lENGTH+1]; 
    
    bzero(file_name, FILE_NAME_lENGTH+1); 
    printf("Input File Name Which You Want To Get From The Server:\n  "); 
    scanf("%s", file_name); 

 
    if(send(client_socket_fd, file_name, FILE_NAME_lENGTH, 0) < 0) 
    { 
        perror("Send File Name Failed:"); 
         return;
    } 
  
    FILE *fp = fopen("HiImage", "w"); 
    if(NULL == fp) 
    { 
        printf("File:\t%s Can Not Open To Write", file_name); 
        return;
    } 
 
    char buffer[BUFFER_SIZE]; 
    bzero(buffer, BUFFER_SIZE); 
  
    int length = 0;
    dbtime_startTest("recv File Start");

    while((length = recv(client_socket_fd, buffer, BUFFER_SIZE, 0)) > 0) 
    { 
         if(fwrite(buffer, sizeof(char), length, fp) < length) 
         { 
              printf("File: %s Write Failed", file_name); 
              break; 
         } 
         bzero(buffer, BUFFER_SIZE); 
     } 
    dbtime_endAndShow (); 
    printf("Receive File: %s Finished!", file_name); 
    dbtime_finalize (); 
    close(fp); 
    close(client_socket_fd); 
    return; 
} 
