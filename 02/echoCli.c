#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)
	
	
int main(void){
	int sock;
	if((sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
		ERR_EXIT("socket");
	struct sockaddr_in serveraddr;
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(5188);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(connect(sock,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
		ERR_EXIT("connect");
	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};
	while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL){
	write(sock,sendbuf,strlen(sendbuf));
	read(sock,recvbuf,sizeof(recvbuf));
	fputs(recvbuf,stdout);
	memset(sendbuf,0,sizeof(sendbuf));
	}
	close(sock);
	return 0;
}
