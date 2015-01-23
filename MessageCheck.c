#include "MessageCheck.h"
#include<stdio.h> 
void socket_fdCheck(int socket_fd)
{
   if(socket_fd < 0) 
    { 
        perror("Create Socket Error"); 
        return;
    } 
}

void bindCheck(int bindflag)
{
 if(-1 ==bindflag ) 
    { 
        perror("Bind Error"); 
        return;
    } 
}

void listenCheck(int listenflag)
{
 if(-1 == listenflag) 
    { 
        perror("Server Listen Error"); 
        return; 
    } 
}

void connectCheck(int connectflag)
{
  if(connectflag<0)
  { 
    perror("Connect With Server Error"); 
        return;
  }
}

void sendCheck(int sendflag,char *file_name)
{
  if(sendflag<0)
  { 
     printf("Send File:%s Failed./n", file_name); 
        return;
  }
}


void acceptCheck(int acceptflag)
{
    if(acceptflag < 0) 
        { 
	    perror("Accept Error"); 
            return;
        } 
}

void fileOpenCheck(FILE *fp,char *file_name)
{
   if(NULL == fp) 
    { 
        printf("File:\t%s Can Not Open To Write", file_name); 
        return;
    } 
}
