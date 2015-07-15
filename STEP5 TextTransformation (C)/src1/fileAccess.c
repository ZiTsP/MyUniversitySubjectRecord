/*
 * fileAccess.c
 *	Version: 1.0
 *  Created on: 2014/10/09
 *  Last Modified on: 2014/10/13
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */

#include "fileAccess.h"
#include <ctype.h>

FILE *fp;

char word;


int init_scan(char *filename){
	fp=fopen(filename,"r");
	if(fp==NULL){
		return -1;
	}
	word=fgetc(fp);
	return 0;
}

void end_scan(){
	fclose(fp);
}

void error(char *mes){
	printf("\n!!!!!!!! ERROR OCCURS AT <%s> !!!!!!!!\n",mes);
	printf("!!!!!!!! WHERE $%s%c$ in line:%d> !!!!!!!!\n",string_attr,word,lastLineNumber);
	printExistToken();
	end_scan();
	printf("<<<err end\n");
	exit(0);
}

void printExistToken(){
	int i=0;
	for(i=1;i<=NUMOFTOKEN;i++){
			if(tokenCount[i]>0){
				fprintf(stdout,"\"%s\"	%d\n",tokenString[i],tokenCount[i]);
			}
		}
}
