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
  

#define clear() printf("\033[H\033[J")

char *answers[]={
    "entendido\n",
    "#0854780*\n",
    "morse\n",
    "pistolero\n",
    "easter_egg\n",
    ".whatAmI\n",
    "indeterminado\n",
    "la gioconda\n",
    "this is awesome\n",
    "abalastro\n",
    "gdb es la hostia\n"
};


//get connection
int holaSeniorTompson(){
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

    int enable=1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) < 0) { 
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

    return connfd;    
}

void desafio1(){
    printf("Vamos a checkear la conexion. Manda entendido\\n");
}
void desafio2(){
    printf("%s","# \\033[D \\033[A \\033[A \\033[D \\033[B \\033[C \\033[B \\033[D *");
}
void desafio3(){
    printf("%s","https://vocaroo.com/i/s1lD9m8lGzei");
}
void desafio4(){
    dprintf(5,"La respuesta es pistolero");
}
void desafio5(){
    printf("respuesta=strings[250]");
}
void desafio6(){
    printf(".data .bss .comment ? .shstrtab .symtab .strtab");
}
void desafio7(){
    printf("mixed fd");
    printf("hola");
}
void desafio8(){
    printf("es un retrato de la gioconda");
}
void desafio9(){
    printf("Tango Hotel India Sierra India Sierra Alfa Whiskey Echo Sierra Oscar Mike Echo");
}
void desafio10(){
    printf("trata compilar un quine.c");
}
void desafio11(){
    printf("b gdbme y encontrá el valor mágico\ntry again");
}

char * doYouWannaPlayAGame(int numDesafio){
    clear();
    printf("----Desafio----\n");
    switch (numDesafio)
    {
    case 1:
        desafio1();
        break;
    case 2:
        desafio2();
        break;
    case 3:
        desafio3();
        break;
    case 4:
        desafio4();
        break;
    case 5:
        desafio5();
        break;
    case 6:
        desafio6();
        break;
    case 7:
        desafio7();
        break;
    case 8:
        desafio8();
        break;
    case 9:
        desafio9();
        break;
    case 10:
        desafio10();
        break;
    case 11:
        desafio11();
        break;
    default:
        break;
    }
    printf("\n");
    return answers[numDesafio-1];
}


//communication with the client
void hableMasFuerteQueTengoUnaToalla(int sockfd) 
{ 
    char buff[MAX];
    char *answer=""; 
    int n; 
    for (int i = 1,solved; i <= 11; i++)
    {
        solved=0;
        for (;!solved;) { 
            answer=doYouWannaPlayAGame(i);
            bzero(buff, MAX);
            if(read(sockfd, buff, MAX)<=0){
                close(sockfd);
                exit(0);
            }
            printf("%s",buff);
            if(!(solved=!strncmp(buff,answer,MAX))){
                printf("Respuesta incorrecta");
            }else{
                printf("Respuesta correcta");
            }
            sleep(1);
        }
    }
    clear();
    printf("Todo perfecto");
} 
  
int main() 
{ 
    int connfd=holaSeniorTompson();
    setbuf(stdout,NULL);
    // Function for chatting between client and server 
    hableMasFuerteQueTengoUnaToalla(connfd); 
    
    close(connfd);
} 