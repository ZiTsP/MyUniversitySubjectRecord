/*
 * main.c
 *	Version: 3.0
 *  Created on: 2014/10/13
 *  Last Modified on: 2014/10/16
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */

#include <stdio.h>
#include <stdlib.h>

#include "tokenList.h"
#include "fileAccess.h"
#include "scan.h"
#include "idList.h"

char *filename;

//#define showDetail
void debugPutOut();

int main(int argc, char *argv[]){
	if(argc!=2){	//needs filename for command line argument
		fprintf(stderr,"chose a program name\n");
		exit(0);
	}
	filename=argv[1];
	int c;
	if((c=init_scan(filename))<0){ //file open
		error("init_scan;cannot open");
	}
	printf(">>>software5 ex01 Start!! #FILE NAME : %s\n",filename);
	debugPutOut();	//when define showDetail, it works
	init_idtab();	/*FROM "idList.c*/
	int i=0;	//get scan() feedback
	while(i>=0){
		i=scan();	/*FROM scan.c*/
		if(i!=0){
			tokenCount[i]++;
			if(i==TNAME){	//when
				id_countup(string_attr);	/*FROM "idList.c*/
			}
		}
	}
	printExistToken();	/*FROM "fileAccess.c*/
	print_idtab();	/*FROM "idList.c*/
	release_idtab();	/*FROM "idList.c*/
	end_scan();	/*FROM "fileAccess.c*/
	printf("<<<end\n");
	return EXIT_SUCCESS;
}

void debugPutOut(){	//when "define showDetail", show each checking
#ifdef showDetail
	printf("@Debug \n>>>Start Detail Analyzing Mmode\n");
	int i=0;
	while(i>=0){ //if scan() return <0, it say end
		i=scan();
		if(i>0){	//if scan() return tokencode, show it's {string,tokencode,token type,its token existing count}
			tokenCount[i]++;
			printf("%s:%d	%s:%d\n",string_attr,i,tokenString[i],tokenCount[i]);
		}else if((string_attr[0]!='\0')&&i==0){ //if scan() return 0, it means separate or comment
			printf("%s:%d	comment\n",string_attr,i);
		}
	}
	printf("<<<end Detail Analyzing Mmode\n");
//	printf("<<break point<%c>in<%d>\n",word,lastLineNumber); //for print out debug
#endif
}
