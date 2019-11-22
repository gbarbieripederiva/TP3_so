#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdio.h>
#include <unistd.h>

#define MAX 200 
#define PORT 23423 
#define SA struct sockaddr 
  
void hableMasFuerteQueTengoUnaToalla(int sockfd) 
{ 
    char buff[MAX]; 
    int n,i=0; 
    for (;i<2;i++) { 
        bzero(buff, MAX); 
        read(sockfd, buff, sizeof(buff));
        write(STDIN_FILENO,buff,MAX);
    } 
    close(sockfd);
} 
  
int main() 
{ 
    //setup variables
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("Error en la creacion del socket\n"); 
        exit(0); 
    }
  
    bzero(&servaddr, sizeof(servaddr)); 
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("Error en el binding del socker\n"); 
        exit(0); 
    }
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 1)) != 0) { 
        printf("Falló listen\n"); 
        exit(0); 
    }
    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("Fallo accept\n"); 
        exit(0); 
    }
    close(sockfd); 

    // Function for chatting between client and server 
    hableMasFuerteQueTengoUnaToalla(connfd); 
  
    // After chatting close the socket 
} 