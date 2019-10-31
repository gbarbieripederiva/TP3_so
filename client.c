#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAX 80 
#define ADDR "0.0.0.0"
#define PORT 23423 
#define SA struct sockaddr 
#define TIMEOUT_FOR_READ_S 5

// #define SHOULD_RECEIVE

int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	//crea el socket(ipv4,stream de bytes,el protocolo default)
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("Error en la creacion del socket\n"); 
		exit(1); 
	}else
	{
		printf("Socket creado\n");
	}
	bzero(&servaddr, sizeof(servaddr)); 
	 
	// Armamos el objeto server address al que nos queremos conectar
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr(ADDR); 
	servaddr.sin_port = htons(PORT); 

	// Trata de conectarse al server
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("Error en la conexion al servidor\n"); 
		exit(0); 
	} 
	else
		printf("Conectado al servidor\n"); 

	// Hablamos con el servidor
	char buff[MAX]; 
	
	// read con timeout
	#ifdef SHOULD_RECEIVE
	struct timeval tv;
	tv.tv_sec = TIMEOUT_FOR_READ_S;
	tv.tv_usec = 0;
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
	#endif

	for (;;) { 
		//limpiamos el buffer
		bzero(buff, sizeof(buff)); 
		printf("Enviar: "); 
		int n = 0; 
		//leemos de stdin
		while ((buff[n++] = getchar()) != '\n') 
			; 
		// escribimos al socket
		write(sockfd, buff, sizeof(buff)); 
		

		#ifdef SHOULD_RECEIVE
		//limpiamos el buffer
		bzero(buff, sizeof(buff)); 
		
		if(recv(sockfd, buff, sizeof(buff),0)>0){
			printf("\tRespueta: %s", buff); 
		}
		#endif
	} 
	// Cerramos el socket
	close(sockfd); 

	return 0;
} 
