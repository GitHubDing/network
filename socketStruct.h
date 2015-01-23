#include<netinet/in.h>
#include<sys/socket.h>  
struct sockaddr_in InitSocketStruct(struct sockaddr_in addr,int int_arg);
struct sockaddr_in InitSocket(struct sockaddr_in addr,int port);
