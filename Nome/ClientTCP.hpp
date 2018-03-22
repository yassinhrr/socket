
class ClientTCP{
	private:int sock_id;
	public: ClientTCP();
		disClientTCP();
		boolean connetti (Address server);
		boolean invia(char* msg);
		char* ricevi();
		boolean inviaRaw(void* msg,int lenght);
		void* riceviRaw(int* lenght);
		boolean broadcast(boolean state);
};

ClientTCP::ClientTCP(){

	int sock_id=socket(AF_INET,SOCK_STREAM,0);
	if(sock_id==-1) errore("socket()", -1);

}

ClientTCP::disClientTCP(){

	close(sock_id);

}

boolean ClientTCP::connetti(Address server){
	return (connect(sock_id,(struct sockaddr*)&server,(socklen_t) sizeof(struct sockaddr_in))==0);
}

boolean ClientTCP::inviaRaw(void* msg,int lenght){
	
	return (send(sock_id,msg,(size_t)len,0)>0)

}





void errore(int retCode, char* description){
	printf("ERRORE bloccante su %s\n", description);
	printf("%d:%s\n",errno, strerror(errno));
	printf("exiting with return code %d\n", retCode);
	exit(retCode);
}
