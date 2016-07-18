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
	int listenfd;
	if((listenfd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
		ERR_EXIT("socket");
	struct sockaddr_in serveraddr;
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(5188);
	/**serveradd.sin_addr.s_addr = inet_addr("127.0.0.0");**/
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(listenfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
		ERR_EXIT("bind");
	if(listen(listenfd,SOMAXCONN)<0)
		ERR_EXIT("listen");
	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);
	int conn = 0;
	if((conn= accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen))<0)
		ERR_EXIT("accpet");
	char recvbuf[1024];
	while(1){
		memset(recvbuf,0,sizeof(recvbuf));
		int ret = read(conn,recvbuf,sizeof(recvbuf));
		fputs(recvbuf,stdout);
		write(conn,recvbuf,ret);
	}
	close(conn);
	close(listenfd);
	return 0;

}
