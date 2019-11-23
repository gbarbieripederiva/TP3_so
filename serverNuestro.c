#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <time.h>
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
    printf("%s","EBADF... abrilo y verás o redirijilo ;)");
    dprintf(5,"La respuesta es pistolero");
}
void desafio5(){
    printf("respuesta=strings[250]");
}
void desafio6(){
    printf(".data .bss .comment ? .shstrtab .symtab .strtab");
}
void desafio7(){
    printf("mixed fd\n");
    char *res="la respuesta es indeterminado";
    time_t t;
    srand((unsigned)time(&t));
    int i=0,forcePrint=0;
    char buff[2];
    buff[1]=0;
    while(res[i]!=0){
        if(forcePrint<3&&rand()%10){
            buff[0]=rand()%26+'a';
            write(STDERR_FILENO,buff,2);
            forcePrint++;
        }else{
            printf("%c",res[i]);
            forcePrint=0;
            i++;
        }
    }
}
void desafio8(){
    char *retrato="                                  _______                                                                 _,,ad8888888888bba,_                                                        ,ad88888I888888888888888ba,                                                  ,88888888I88888888888888888888a,                                             ,d888888888I8888888888888888888888b,                                          d88888PP\"\"\"\" \"\"YY88888888888888888888b,                                      ,d88\"\'__,,--------,,,,.;ZZZY8888888888888,                                    ,8IIl\'\"                ;;l\"ZZZIII8888888888,                                  ,I88l;\'                  ;lZZZZZ888III8888888,                               ,II88Zl;.                  ;llZZZZZ888888I888888,                             ,II888Zl;.                .;;;;;lllZZZ888888I8888b                            ,II8888Z;;                 `;;;;;\'\'llZZ8888888I8888,                           II88888Z;\'                        .;lZZZ8888888I888b                           II88888Z; _,aaa,      .,aaaaa,__.l;llZZZ88888888I888                           II88888IZZZZZZZZZ,  .ZZZZZZZZZZZZZZ;llZZ88888888I888,                          II88888IZZ<\'(@@>Z|  |ZZZ<\'(@@>ZZZZ;;llZZ888888888I88I                         ,II88888;   `\"\"\" ;|  |ZZ; `\"\"\"     ;;llZ8888888888I888                         II888888l            `;;          .;llZZ8888888888I888,                       ,II888888Z;           ;;;        .;;llZZZ8888888888I888I                       III888888Zl;    ..,   `;;       ,;;lllZZZ88888888888I888                       II88888888Z;;...;(_    _)      ,;;;llZZZZ88888888888I888,                      II88888888Zl;;;;;\' `--\'Z;.   .,;;;;llZZZZ88888888888I888b                      ]I888888888Z;;;;\'   \";llllll;..;;;lllZZZZ88888888888I8888,                     I\'I888888888Zl.;;\"Y88bd888P\";;,..;lllZZZZZ88888888888I8888I                     II8888888888Zl;.; `\"PPP\";;;,..;lllZZZZZZZ88888888888I88888                     II888888888888Zl;;. `;;;l;;;;lllZZZZZZZZW88888888888I88888                     `II8888888888888Zl;.    ,;;lllZZZZZZZZWMZ88888888888I88888                      II8888888888888888ZbaalllZZZZZZZZZWWMZZZ8888888888I888888,                     `II88888888888888888b\"WWZZZZZWWWMMZZZZZZI888888888I888888b                      `II88888888888888888;ZZMMMMMMZZZZZZZZllI888888888I8888888                       `II8888888888888888 `;lZZZZZZZZZZZlllll888888888I8888888,                       II8888888888888888, `;lllZZZZllllll;;.Y88888888I8888888b,                     ,II8888888888888888b   .;;lllllll;;;.;..88888888I88888888b,                    II888888888888888PZI;.  .`;;;.;;;..; ...88888888I8888888888,                   II888888888888PZ;;\';;.   ;. .;.  .;. .. Y8888888I88888888888b,                ,II888888888PZ;;\'                        `8888888I8888888888888b,              II888888888\'                              888888I8888888888888888b            ,II888888888                              ,888888I88888888888888888           ,d88888888888                              d888888I8888888888ZZZZZZZ        ,ad888888888888I                              8888888I8888ZZZZZZZZZZZZZ      ,d888888888888888\'                              888888IZZZZZZZZZZZZZZZZZZ    ,d888888888888P\'8P'                               Y888ZZZZZZZZZZZZZZZZZZZZZ   ,8888888888888,  \"                                 ,ZZZZZZZZZZZZZZZZZZZZZZZZ  d888888888888888,                                ,ZZZZZZZZZZZZZZZZZZZZZZZZZZZ  888888888888888888a,      _                    ,ZZZZZZZZZZZZZZZZZZZZ888888888  888888888888888888888ba,_d\'                  ,ZZZZZZZZZZZZZZZZZ88888888888888  8888888888888888888888888888bbbaaa,,,______,ZZZZZZZZZZZZZZZ888888888888888888  88888888888888888888888888888888888888888ZZZZZZZZZZZZZZZ888888888888888888888  8888888888888888888888888888888888888888ZZZZZZZZZZZZZZ88888888888888888888888  888888888888888888888888888888888888888ZZZZZZZZZZZZZZ888888888888888888888888  8888888888888888888888888888888888888ZZZZZZZZZZZZZZ88888888888888888888888888  88888888888888888888888888888888888ZZZZZZZZZZZZZZ8888888888888888888888888888  8888888888888888888888888888888888ZZZZZZZZZZZZZZ88888888888888888888888888888  88888888888888888888888888888888ZZZZZZZZZZZZZZ8888888888888888888888888888888  8888888888888888888888888888888ZZZZZZZZZZZZZZ88888888888888888888888888888888";
    printf("%s",retrato);
}
void desafio9(){
    printf("Tango Hotel India Sierra India Sierra Alfa Whiskey Echo Sierra Oscar Mike Echo");
}
void desafio10(){
    FILE * popenFileOutput=popen("gcc quine.c -o quine && printf \"haber si el programa hace lo que debe \\n\" && (./quine | diff quine.c -) && printf \"parece que si, la respuesta es abalastro \\n\"","r");
    int c;
    while((c=fgetc(popenFileOutput))!=EOF){
        printf("%c",c);
    }
    fclose(popenFileOutput);
}

void gdbme(){
    int magicVariable=0;
    for (int i = 0; i < 5; i++)
    {
        magicVariable++;
    }
    magicVariable=0x12345;
    if(magicVariable==0x12345){
        printf("try again");
    }else{
        printf("la respuesta es gdb es la hostia");
    }
}
void desafio11(){
    printf("b gdbme y encontrá el valor mágico\n");
    gdbme();
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