#include<netinet/in.h> 
#include<sys/types.h>  
#include<sys/socket.h>  
#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  

#define SERVER_PORT 8080 
#define LENGTH_OF_LISTEN_QUEUE 20 
#define BUFFER_SIZE 1024 
#define FILE_NAME_lENGTH 64 

void main() 
{ 
    struct sockaddr_in server_addr;
  
    bzero(&server_addr, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = htons(INADDR_ANY); 
    server_addr.sin_port = htons(SERVER_PORT); 

    int server_socket_fd = socket(PF_INET, SOCK_STREAM, 0); 
  
    if(server_socket_fd < 0) 
    { 
        perror("Create Socket Error"); 
        return;
    } 
  
    int opt = 1; 
    
    setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); 
 
    if(-1 == (bind(server_socket_fd,(struct sockaddr*)&server_addr, sizeof(server_addr)))) 
    { 
        perror("Bind Error"); 
        return;
    } 


    if(-1 == (listen(server_socket_fd, LENGTH_OF_LISTEN_QUEUE))) 
    { 
        perror("Server Listen Error"); 
        return; 
    } 
  
    while(1) 
    { 
        struct sockaddr_in client_addr; 
        socklen_t client_addr_length = sizeof(client_addr); 
 
        int new_server_socket_fd = accept(server_socket_fd, (struct sockaddr*)&client_addr, &client_addr_length); 

        if(new_server_socket_fd < 0) 
        { 
	    perror("Server Accept Error"); 
            break; 
        } 

        char file_name[FILE_NAME_lENGTH+1]; 
        bzero(file_name, FILE_NAME_lENGTH+1); 
        if(recv(new_server_socket_fd, file_name, FILE_NAME_lENGTH, 0) < 0) 
        { 
            perror("Server Recieve Data Failed:"); 
            break; 
        } 
    
        printf("%s\n", file_name); 
        FILE *fp = fopen(file_name, "r"); 
  
        if(NULL == fp) 
        { 
            printf("File:%s Not Found Or Read Error\n", file_name); 
        } 
        else
        { 
            int length = 0; 
 char buffer[BUFFER_SIZE]; 
 bzero(buffer, BUFFER_SIZE); 
            while((length = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0)
            { 
                if(send(new_server_socket_fd, buffer, length, 0) < 0) 
                { 
                    printf("Send File:%s Failed./n", file_name); 
                    break; 
                } 
                bzero(buffer, BUFFER_SIZE); 
             } 

             fclose(fp); 
             printf("File:%s Transfer Successful!\n", file_name); 
        } 
        close(new_server_socket_fd); 
    } 
    close(server_socket_fd); 
    return; 
} 
