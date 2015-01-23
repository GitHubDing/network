#include<stdio.h> 
void socket_fdCheck(int socket_fd);
void bindCheck(int bindflag);
void listenCheck(int listenflag);
void connectCheck(int connectflag);
void sendCheck(int sendflag,char *file_name);
void acceptCheck(int acceptflag);
void fileOpenCheck(FILE *fp,char *file_name);
