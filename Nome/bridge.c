#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define MAX_MSG 4096
#define MYSELF_IP "0.0.0.0"

void errore(int n,char *s);

int main(int argc,char* argv[]){
    
    int sock_id;
    struct sockaddr_in myself, dets, mitt;
    char buffer[MAX_MSG + 1];
    
    int myself_port;
    char* myself_ip;
    int dest_port;
    char* dest_ip;
    
    int len_addr;
    int len_msg;    
    int i;

    if(argc!=4){
        print("USAGE:%s LISTENING_PORT dest_IP dest_PORT\n", argv[0])
        return(-1);    
    }
    
    myself_ip= MYSELF_IP;
    myself_port = atoi(argv[1]);
    dest_ip= argv[2];
    dest_port= atoi(argv[3]);

    printf("Opening a socket...")
    sock_id = socket(AF_INET,SOCK_DGRAM,0);
    if(sock_id==-1)errore(-2,"socket()");


    printf("Binding..")
    myself.sin_family=AF_INET;
    inet_aton(myself_ip;&myself.addr);  
    myself.sin_port=htons(myself_port);         
    for(int i=0;i<8;i++){ 
        myself.sin_zero[i]=0;
    }
    
    len_adr=sizeof(Struct sockaddr_in);    
        
    if(bind(sock_id, (struct sockaddr*)myself,(socklen_t)len_addr)){
        errore (-3,"bind()");
    }
    printf("DONE.");
    len_addr=sizeof(struct sockaddr_in); 
  
    ret = recvfrom(sock_id, buffer, MAX_MSG,0, (struct sockaddr*)&mitt, (socklen_t*)&len_addr);
    
    if (ret<=0){
    errore(-4,"recvfrom()");
    }
    buffer[ret]= '\0';

    dest.sin_family=AF_INET;
    inet_aton(dest_ip,&dest.addr);
    dest.sin_port= htnos(dest_port);
    for(int i=0;i<8;i++) { dest.sin_port[i]=0};
       
    len_addr = sizeof(struct sockaddr_in);
    len_msg = strlen(buffer)+1;
    ret= sendto(sock_id,buffer, len_msg,0,(struct sockaddr*)&dest,(socklen_t)len_addr);

    printf("Closing socket...")
    if(ret!=len_msg) errore(-5,"sendto()");
    if(close(sock_id)) errore(-6, "close()");
}
void errore(int n,char *s){
    printf("Errore %d:%s\n",errno,strerror(errno));
    printf("Exiting with return code %d\n",n);
    exit(n);
}
