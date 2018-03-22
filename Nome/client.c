#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void errore(int, char*);

int main(int argc, char* argv[]){
	int i, ret, sock_id, len, conn_id;
	struct sockaddr_in server;
	if(argc != 4){
		printf("USAGE:%s IP_ADDR PORT MESSAGE",argv[0]);
		return -1;
	}
	
	sock_id = socket(AF_INET,SOCK_STREAM,0);
	
	if(sock_id == -1) errore(-2, "socket");
	

	server.sin_family = AF_INET;
	inet_aton(argv[1],&server.sin_addr);
	server.sin_port = htons(atoi(argv[2]));
	for(i=0; i<8; i++) server.sin_zero[i] = 0;
	len  = sizeof(argv[3]+1);
	
	conn_id = connect(sock_id, (struct sockaddr*) &server,(socklen_t) sizeof(struct sockaddr_in));
	
	if(conn_id == -1) errore(-3, "connect");	
	
	ret = send(sock_id,argv[3],(socklen_t) len,0);
	if(ret<=0) errore(-4, "send");
	close(sock_id);
	return 0;
}

void errore(int retCode, char* description){
	printf("ERRORE bloccante su %s\n", description);
	printf("%d:%s\n",errno, strerror(errno));
	printf("exiting with return code %d\n", retCode);
	exit(retCode);
}
