#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>

#define S_BUFSIZE 512   /* 送信用バッファサイズ */
#define R_BUFSIZE 512   /* 受信用バッファサイズ */
#define TIMEOUT_SEC 1
#define USERNAME_LEN 15
#define DEFAULT_USER "anonimus"
#define DEFAULT_PORT 50001
#define limitedBroadcastAddress "255.255.255.255"

int callHELO();
extern int executeAsServer();
extern int executeAsClient();

void exit_errmesg(char *errmesg);
int port;
char userName[USERNAME_LEN];

static char broadcastAddress[]=limitedBroadcastAddress;
static int opt;
static struct timeval timeout;
static char Buf[10];
struct sockaddr_in from_adrs;
static int timeLim;

int main(int argc,char *argv[]) {
	port=DEFAULT_PORT;
	snprintf(userName,USERNAME_LEN,"%s",DEFAULT_USER);
	int r=0;
	timeLim=TIMEOUT_SEC;
	while(1){
		opt=getopt(argc,argv,"U:P:T:");
		if(opt<0)break;
		switch(opt){
		case'U':
			snprintf(userName,USERNAME_LEN,"%s",optarg);
			break;
		case 'P':
			port=atoi(optarg);
			break;
		case 'T':
			timeLim=atoi(optarg);
			break;
		}
	}
	printf("UserName:%s Port:%d BroadcastAddress:%s \n",userName,port,broadcastAddress);
	r=callHELO(port);
	int j;
	if(r==0){//受信なし
		fprintf(stderr,"Become Server\n");
			j=executeAsServer();
	}else if(r==1){//受信あり
		fprintf(stderr,"Become Client\n");
			j=executeAsClient();
	}else{
		exit_errmesg("HELO");
	}
	return 0;
}


int callHELO(){
	struct sockaddr_in sockAddr;
	int sock,sel;
	int optval=1;
	fd_set mask, readfds;
	if((sock = socket(PF_INET, SOCK_DGRAM, 0)) == -1){//ソケットをDGRAMモードで作成する
		exit_errmesg("socket()");
	}
	FD_ZERO(&mask);//ビットマスクの準備
	FD_SET(sock, &mask);
	sockAddr.sin_family = AF_INET;//ブロードキャストアドレスの情報をsockaddr_in構造体に格納する
	sockAddr.sin_port = htons(port);
	sockAddr.sin_addr.s_addr = inet_addr(limitedBroadcastAddress);
	if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *)&optval, sizeof(optval)) == -1){
	    exit_errmesg("setsockopt()");
	}
	int i;
	for(i=0;i<3;i++){
		sendto(sock, "HELO", 5, 0, (struct sockaddr *)&sockAddr, sizeof(sockAddr));
		readfds = mask;// 受信データの有無をチェック
//		timeout.tv_sec = TIMEOUT_SEC;
		timeout.tv_sec = timeLim;
		timeout.tv_usec = 0;
		sel=select( sock+1, &readfds, NULL, NULL, &timeout );
				if(sel==-1){
					exit_errmesg("select(HELO)");
				}else if(sel==0){
					printf("Time out[%d th].\n",i+1);
					continue;
				}else{
					int strsize;
					socklen_t from_len;
					from_len = sizeof(from_adrs);
					if((strsize=recvfrom(sock,Buf,10,0,(struct sockaddr *)&from_adrs, &from_len)) == -1){//form_adrsにIPアドレスを取得
						exit_errmesg("recvfrom()");
					}
					close(sock);
					if(strncmp(Buf,"HERE",4)==0){
						return 1;
					}
					else return 0;
				}
	}
	close(sock);
	return 0;
}

void exit_errmesg(char *errmesg)
{
  perror(errmesg);
  exit(EXIT_FAILURE);
}
