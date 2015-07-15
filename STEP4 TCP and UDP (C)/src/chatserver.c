#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define S_BUFSIZE 512   /* 送信用バッファサイズ */
#define R_BUFSIZE 512   /* 受信用バッファサイズ */
#define TIMEOUT_SEC 10
#define USERNAME_LEN 15
#define MEM_MAX 10

extern void exit_errmesg(char *errmesg);

typedef struct{
	int  sock;
	char name[USERNAME_LEN];
} client_info;//（各クライアント情報）
typedef struct{
	char head[5];
	int mesLen;
	char message[488];
}messagePacket;

extern int port;

static int UDPsock;
static client_info memInfo[MEM_MAX];
static int	members,strsize;
static char sBuf[S_BUFSIZE],rBuf[R_BUFSIZE];
static char *acceptMes;
static char *sendMes;
static char *quitMes;
static messagePacket *pack;
static int largestSock;

int executeAsServer();//server main
int typeCheck();
int setMessage();
int joinClient(int number);
int sendPOST(int number);
int memQuit(int number);
int checkHELO();
int sendMESG();
int sendAllMem(char *message);


int executeAsServer(){
	memset(sBuf,0,S_BUFSIZE);
	memset(rBuf,0,R_BUFSIZE);
	fprintf(stdout,"SERVER port:%d\n",port);
	members=0;
	pack=(messagePacket*)malloc(sizeof(messagePacket)*1);
	struct sockaddr_in my_adrs,from_adrs;
	int sock,sock_listen,sock_accepted,strsize,res;
//	in_port_t port_number;
	socklen_t from_len;
//	port_number = port;
	fd_set mask,readfds;

// setupTCPserver
	memset(&my_adrs, 0, sizeof(my_adrs));//サーバ(自分自身)の情報をsockaddr_in構造体に格納する
	my_adrs.sin_family = AF_INET;
	my_adrs.sin_port = htons(port);
	my_adrs.sin_addr.s_addr = htonl(INADDR_ANY);
	if((sock_listen = socket(PF_INET, SOCK_STREAM, 0)) == -1){//待ち受け用ソケットをSTREAMモードで作成する
		exit_errmesg("socket()");
	}
	if(bind(sock_listen, (struct sockaddr *)&my_adrs, sizeof(my_adrs)) == -1 ){//待ち受け用のソケットに自分自身のアドレス情報を結びつける
		exit_errmesg("bind()");
	}
	if(listen(sock_listen, MEM_MAX) == -1){//クライアントからの接続を受け付ける準備をする
		exit_errmesg("listen()");
	}
	fprintf(stdout,"Built TCP_listen Server [%d]\n",sock_listen);

// setupUDPserver
	memset(&my_adrs, 0, sizeof(my_adrs));//サーバ(自分自身)の情報をsockaddr_in構造体に格納する
	my_adrs.sin_family = AF_INET;
	my_adrs.sin_port = htons(port);
	my_adrs.sin_addr.s_addr = htonl(INADDR_ANY);
	if((sock = socket(PF_INET, SOCK_DGRAM, 0)) == -1){//ソケットをDGRAMモードで作成する
	  exit_errmesg("socket()");
	}
	if(bind(sock, (struct sockaddr *)&my_adrs, sizeof(my_adrs)) == -1 ){//ソケットに自分自身のアドレス情報を結びつける
	  exit_errmesg("bind()");
	}
	UDPsock=sock;
	fprintf(stdout,"Built UDP Server [%d]\n",UDPsock);

// select
	FD_ZERO(&mask);
	FD_SET(0,&mask);
	FD_SET(sock_listen,&mask);
	FD_SET(UDPsock,&mask);
	largestSock=sock_listen;
	if(UDPsock>sock_listen){
		largestSock=UDPsock;
	}
	fprintf(stderr,"READY UDP&TCP&Key\n");
	for(;;){
		memcpy(&readfds, &mask, sizeof(fd_set));
		select(largestSock+1,&readfds,NULL,NULL,NULL);
		if(FD_ISSET(0,&readfds)){//キーボード入力
			sendMESG();
		}
		if(FD_ISSET(UDPsock,&readfds)){
//			fprintf(stderr,"get UDP connect UDPsock[%d]\n",UDPsock);
			from_len = sizeof(from_adrs);
			if((strsize=recvfrom(UDPsock, rBuf, R_BUFSIZE, 0,(struct sockaddr *)&from_adrs, &from_len)) == -1){
				exit_errmesg("recvfrom()");
			}
			int res=checkHELO();
			strncpy(sBuf,"HERE",4);
			sBuf[4]='\n';
			if(res==0){
				if(sendto(UDPsock,sBuf,S_BUFSIZE,0,(struct sockaddr *)&from_adrs,sizeof(from_adrs)) == -1 ){
					exit_errmesg("send(HERE)");
				}
//				fprintf(stderr,"collect to send HERE\n");
			}
			memset(sBuf,0,S_BUFSIZE);
		}
		if(FD_ISSET(sock_listen,&readfds)){
			if((sock_accepted=accept(sock_listen,NULL,NULL))== -1){
				exit_errmesg("accept()");
			}
			if(sock_accepted>largestSock)largestSock=sock_accepted;
			memInfo[members].sock=sock_accepted;
			memInfo[members].name[0]='\0';
			FD_SET(memInfo[members].sock,&mask);
			members++;
			fprintf(stderr,"get new TCP connect TCPsock[%d]&member[%d]\n",memInfo[members-1].sock,members-1);
		}
		int i;
		for(i=0;i<members;i++){
			if(FD_ISSET(memInfo[i].sock,&readfds)){
				if((strsize=recvfrom(memInfo[i].sock, rBuf, R_BUFSIZE, 0,(struct sockaddr *)&from_adrs, &from_len)) == -1){
					exit_errmesg("recvfrom()");
				}
//				fprintf(stderr,"get TCPInfo[%d] connect\n",i);
				from_len = sizeof(from_adrs);
				rBuf[strsize]='\0';
				res=typeCheck(rBuf);
				memset(rBuf,0,S_BUFSIZE);
				if(res==0){//POST
					res=sendPOST(i);
					res=2;//break
				}else if(res==1){//JOIN
					if(memInfo[i].name[0]=='\0'){
						fprintf(stderr,"join new one\n");
						res=joinClient(i);
					}
					res=2;//break
				}else if(res==-1){//QUIT
					FD_CLR(memInfo[i].sock,&mask);
					res=memQuit(i);
					res=2;//break
		}}
			memset(pack->message,0,strlen(pack->message));
		}
	}

  return 0;
}

int typeCheck(){
	if(setMessage(rBuf)!=0){
		exit_errmesg("packing");
	}
	fprintf(stderr,"head->%s $$ meslen->%d $$ message->[%s]\n",pack->head,pack->mesLen,pack->message);
	if(strncmp(pack->head,"POST",4)==0){
		return(0);
	}else if(strncmp(pack->head,"JOIN",4)==0){
		return(1);
	}else if(strncmp(pack->head,"QUIT",4)==0){
		return(-1);
	}else{
		return(-2);
	}
}

int setMessage(){
	int m;
	for(m=0;m<4;m++){
		pack->head[m]=rBuf[m];
	}
	pack->head[4]='\0';
	if(rBuf[m]=='\n')return 0;
	do{
		m++;
		pack->message[m-5]=rBuf[m];
		if(pack->message[m-5]=='\0'){
			break;
		}
	}while(rBuf[m+1]!='\n');
	pack->mesLen=strlen(pack->message);
	return 0;
}

int joinClient(int number){
	strncpy(memInfo[number].name,pack->message,pack->mesLen);
	memset(pack->message,0,pack->mesLen);
	acceptMes=(char*)malloc(sizeof(char)*50);
	snprintf(acceptMes,45,"MESG Accept new commit <%s>",memInfo[number].name);
	sendAllMem(acceptMes);
	free(acceptMes);
	return 0;
}

int sendPOST(int number){
	int mesLen=5+strlen(memInfo[number].name)+1+pack->mesLen+1;
	sendMes=(char*)malloc(sizeof(char)*mesLen);
	snprintf(sendMes,mesLen,"MESG %s$%s",memInfo[number].name,pack->message);
	sendMes[mesLen-1]='\n';
	sendAllMem(sendMes);
	memset(sendMes,0,strlen(sendMes));
	free(sendMes);
	return 0;
}

int memQuit(int number){
	fprintf(stderr,"QUIT: memInfo[%d] sock:<<%d>> name:<<%s>>\n",number,memInfo[number].sock,memInfo[number].name);
	client_info quitClient=memInfo[number];
	int i;
	for(i=number;i<members-1;i++){
		memInfo[i]=memInfo[i+1];
	}
	members--;
	int mesLen=5+strlen(quitClient.name)+1+7+1;
	quitMes=(char*)malloc(sizeof(char)*mesLen);
	snprintf(quitMes,45,"MESG %s$Log out\n",quitClient.name);
	sendAllMem(quitMes);
	memset(quitMes,0,mesLen);
	free(quitMes);
//	int j; //現在のメンバー表示
//	fprintf(stderr,"Now members::\n");
//	for(j=0;j<members;j++){
//		fprintf(stderr,"memInfo[%d] sock:<<%d>> name:<<%s>>\n",j,memInfo[j].sock,memInfo[j].name);
//	}
	return 0;
}

int checkHELO(){
	int m;
	for(m=0;m<4;m++){
		pack->head[m]=rBuf[m];
	}
	memset(rBuf,0,S_BUFSIZE);
	fprintf(stderr,"head->%s\n",pack->head);
	if(strncmp(pack->head,"HELO",4)==0){
		return 0;
	}
	return -1;
}

int sendMESG(){
	fgets(sBuf, S_BUFSIZE-1, stdin);
	strsize = strlen(sBuf);
	sBuf[strsize] = '\0'; /* 文字列の最後に終了コードを入れておく */
	int mesLen=5+strlen(sBuf)+1;
	sendMes=(char*)malloc(sizeof(char)*mesLen);
	snprintf(sendMes,mesLen,"MESG %s",sBuf);
	sendMes[mesLen-1]='\n';
	sendAllMem(sendMes);
	memset(sBuf,0,S_BUFSIZE);
	memset(sendMes,0,mesLen);
	free(sendMes);
	return 0;
}

int sendAllMem(char *message){
	int i;
	for(i=0;i<members;i++){
		if(send(memInfo[i].sock, message, strlen(message)+1, 0) == -1 ){
			exit_errmesg("send()");
		  }
//		fprintf(stderr,"sent->%d:[%s]\n",memInfo[i].sock,message);
	}
	return 0;
}

