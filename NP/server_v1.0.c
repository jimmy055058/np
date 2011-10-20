#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <string.h>
#define SERV_TCP_PORT 7000

void myshell(int);

int main(int argc,char *argv[])

{
      int   sockfd,newsockfd,clilen,childpid, n;
      struct sockaddr_in   cli_addr,serv_addr;
      
      /*open a TCP socket */
      
      if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
          fprintf(stderr, "server:can't open stream socket");
          
      /*Bind oulocal address so that the client can send to us */
      
      bzero((char *) &serv_addr, sizeof(serv_addr));
      serv_addr.sin_family = AF_INET;
      serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
      serv_addr.sin_port = htons(SERV_TCP_PORT);
      
      if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
        fprintf( stderr,"server:can't bind local address");
          
      listen(sockfd,5);
      
      for(;;)
      {
             clilen = sizeof(cli_addr);
             newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
             if(newsockfd<0)
			   fprintf(stderr, "server:accept error");
             if((childpid=fork())<0)
                 fprintf(stderr, "server:fork error");
             else if(childpid==0) /*child process*/
                 {
                     /*close original socket*/
                     close(sockfd);
                     /* process the request*/
					char* str="****************************************\n";
					if( ( n = write( newsockfd, str, strlen(str)))< 0 )
						fprintf(stderr, "ERROR writing %s failed!\n", str);
					else if(n==0)
						fprintf(stderr, "ERROR writing %s failed! No data has been written out!\n", str);
					//==============================================================================
					str = "** Welcome to the information server. **\n";
					if( ( n = write( newsockfd, str, strlen(str )))< 0 )
						fprintf(stderr, "ERROR writing %s failed!\n", str);
					else if(n==0)
						fprintf(stderr, "ERROR writing %s failed! No data has been written out!\n", str);
					//==============================================================================
					str = "****************************************\n";
					if( ( n = write( newsockfd, str, strlen(str)))< 0 )
						fprintf(stderr, "ERROR writing %s failed!\n", str);
					else if(n==0)                
						fprintf(stderr, "ERROR writing %s failed! No data has been written out!\n", str);
			
							myshell(newsockfd);

                     exit(0);
                 }
             close(newsockfd);/*parent process*/
      }
}
/*
#define MAXLINE 512
str_echo(sockfd)

  int sockfd;
{
    int n;
    char line[MAXLINE];
    for(;;)
    {
           n=readline(sockfd,line,MAXLINE);
           if(n==0)
               return;
           else if(n<0)
               err_dump("str_echo:readline error");
           if(writen(sockfd,line,n)!=n)
               err_dump("str_echo:writen error");
    }
}*/

int readline(int fd,char * ptr,int maxlen)
{
    int n,rc;
    char c;
    for(n=1;n<maxlen;n++)
    {
        if((rc=read(fd,&c,1))==1)
        {                                 
            *ptr++=c;
            if(c=='\n')
                break;
        }
        else if(rc==0)
        {
             if(n==1)
                 return(0);  /*EOF,no data read*/
             else
                 break;      /*EOF,some data was read*/
        }
        else return(-1);     /*read*/
    }
    *ptr=0;
    return(n);
}
           
void myshell(int newsockfd){

}
