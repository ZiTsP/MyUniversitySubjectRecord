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
#define limitedBroadcastAddress "255.255.255.255"

extern void exit_errmesg(char *errmesg);
extern struct sockaddr_in from_adrs;
extern char userName[USERNAME_LEN];

int executeAsClient();
static char *joinMes;

int executeAsClient(){
	struct sockaddr_in server_adrs;
	int sock;
	char sBuf[S_BUFSIZE], rBuf[R_BUFSIZE],Buf[S_BUFSIZE-5];
	memset(sBuf,0,S_BUFSIZE);
	memset(rBuf,0,R_BUFSIZE);
	memset(Buf,0,S_BUFSIZE-5);
	int strsize;
	fd_set mask,readfds;
	memset(&server_adrs, 0, sizeof(server_adrs));//サーバの情報をsockaddr_in構造体に格納する
	server_adrs.sin_family = AF_INET;
	server_adrs.sin_port = from_adrs.sin_port;
	server_adrs.sin_addr=from_adrs.sin_addr;
	if((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1){//ソケットをSTREAMモードで作成する
	  exit_errmesg("socket()");
	}
	if(connect(sock, (struct sockaddr *)&server_adrs, sizeof(server_adrs))== -1){//ソケットにサーバの情報を対応づけてサーバに接続する
	  exit_errmesg("connect");
	}
	int namelen=strlen(userName);
	joinMes=(char*)malloc(sizeof(char)*(5+namelen+1));
	snprintf(joinMes,5+namelen+1,"JOIN %s",userName);
	joinMes[strlen(joinMes)]='\n';
	fprintf(stderr,"	%s\n",joinMes);
	if(send(sock,joinMes, strlen(joinMes)+1, 0) == -1 ){
		exit_errmesg("send()");
	}
	free(joinMes);
	FD_ZERO(&mask);
	FD_SET(0,&mask);
	FD_SET(sock,&mask);
	for(;;){
	  memcpy(&readfds, &mask, sizeof(fd_set));
	  select(sock+1,&readfds,NULL,NULL,NULL);
	  if(FD_ISSET(0,&readfds)){//キーボード入力
		  fgets(Buf, S_BUFSIZE-6, stdin);
		  strsize = strlen(Buf);
		  if(strncmp(Buf,"QUIT",4)==0){
			  if(send(sock, Buf, strsize+1, 0) == -1 ){
				  exit_errmesg("send()");
			  }
			  memset(Buf,0,S_BUFSIZE-5);
			  exit(EXIT_SUCCESS);
		  }
		  snprintf(sBuf,5+strlen(Buf),"POST %s",Buf);
		  sBuf[strlen(sBuf)]='\n';
		  fprintf(stderr,"	%s\n",sBuf);
		  if(send(sock, sBuf, strlen(sBuf)+1, 0) == -1 ){
			  exit_errmesg("send()");
		  }
		  memset(Buf,0,S_BUFSIZE-5);
		  memset(sBuf,0,S_BUFSIZE);
		}
	  if(FD_ISSET(sock,&readfds)){
		  if((strsize=recv(sock, rBuf, R_BUFSIZE-1, 0)) == -1){
			  exit_errmesg("recv()");
		  }
		  if(rBuf[strsize-1]=='\n'){
		  rBuf[strsize-1] = '\0';
		  }
		  if(strncmp(rBuf,"MESG",4)==0){
			  fprintf(stdout,">>>%s\n",rBuf+5);
		  }
		  else{
			  fprintf(stdout,"???%s\n",rBuf);
		  }
		  memset(rBuf,0,R_BUFSIZE);
	  }
	}
	close(sock);             /* ソケットを閉じる */
	exit(EXIT_SUCCESS);
	}
