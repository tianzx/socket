#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)
struct packet{
        int len;
	char buf[1024];
	}

ssize_t readn(int fd,void *buf,size_t count){
        size_t nleft =count;
        ssize_t nread;
        char *bufp=(char*)buf;
        while(nleft > 0){
                if((nread = read(fd,bufp,nleft))<0){
                        if(errno == EINTR)
                                continue;
                        return -1;
                }else if(nread==0){
                        return count-nleft;
                }else{
                        bufp +=nread;
                        nleft -=nread;
                }
                return count;
        }
}
ssize_t writen(int fd,const void *bufp,size_t count) {
        size_t nleft = count;
        ssize_t nwritten;
        while(nleft>0){
                if((nwritten = write(fd,bufp,nleft))<0){
                        if(errno==EINTR)
                                continue;
                        return -1;
                }else if(nwritten ==0){
                        continue;
                }
                bufp +=nwritten;
                nleft -= nwritten;
        }
}

int main(void)
{
	int sock;
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		ERR_EXIT("socket");

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("connect");
	struct packet sendbuf;
	struct packet recvbuf;
	memset(&sendbuf,0,sizeof(sendbuf));
	memset(&recvbuf,0,sizeof(recvbuf));
	int n;
	while (fgets(sendbuf, sizeof(sendbuf.buf), stdin) != NULL)
	{
		n = strlen(sendbuf.buf);
		sendbuf.len = htonl(n);
		writen(sock, &sendbuf, 4+n);
		readn(sock, recvbuf, sizeof(recvbuf));
		
		fputs(recvbuf, stdout);
		memset(sendbuf, 0, sizeof(sendbuf));
		memset(recvbuf, 0, sizeof(recvbuf));
	}

	close(sock);
	
	return 0;
}
