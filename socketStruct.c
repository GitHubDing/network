#include "socketStruct.h"
#include<netinet/in.h>
#include<sys/socket.h>  
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 


struct sockaddr_in InitSocketStruct(struct sockaddr_in addr,int int_arg)
{
    bzero(&addr, sizeof(addr)); 
    addr.sin_family = AF_INET; 
    addr.sin_addr.s_addr = htons(INADDR_ANY); 
    addr.sin_port = htons(int_arg); 
    return addr;
}


struct sockaddr_in InitSocket(struct sockaddr_in addr,int port)
{
   bzero(&addr, sizeof(addr)); 
    addr.sin_family = AF_INET; 
    if(inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) == 0) 
    { 
         perror("Server IP Address Error"); 
          return;
    } 
    addr.sin_port = htons(port); 
    return addr;
}
