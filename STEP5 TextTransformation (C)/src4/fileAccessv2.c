/*
 * fileAccessv2.c
 *	Version: 1.0
 *  Created on: 2014/10/09
 *  Last Modified on: 2014/11/26
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */

#include "fileAccessv2.h"
#include <ctype.h>

FILE *fp;

char word;
char *filename;
int LogCount=0;
char fName[30]={'\0'};


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

void errPrint(const char *str,...){
	va_list list;
	int length=strlen(str);
	va_start(list,str);
	int i;
	int d;
	char c;
	char* s;
	printf("ERROR;Line %d;Word %s; ",lastLineNumber,tmpString);
	for(i=0;i<=length;i++){
		if(str[i]=='%'){
			switch (str[i+1]){
				case 'd':
					d=va_arg(list,int);
					printf("%d",d);
					break;
				case 'c':
					c=va_arg(list,int);
					printf("%c",c);
					break;
				case 's':
					s=va_arg(list,char*);
					printf("%s",s);
					break;
				default:
					printf("errPrint : argument err\n");
					exit(0);
			}
			i++;
		}else{
			printf("%c",str[i]);
		}
	}
	printf("\n");
	end_scan();
	va_end(list);
	exit(0);
}

void logPutOut(const char *str,...){
	char *filename2="errTxt";
	FILE *fp;
	va_list list;
	int length=strlen(str);
	va_start(list,str);
	int i,d;
	char c;
	char* s;
	if(LogCount==0){
	    time_t timer=time(NULL);
	    struct tm *utc;
	    utc = localtime(&timer);
//	    sprintf(fName,"./log/%s_%d%d%d-%d:%d.txt",filename2,utc->tm_year+1900,utc->tm_mon + 1,utc->tm_mday,utc->tm_hour,utc->tm_min);//for debug
	    sprintf(fName,"%s.txt",filename2);
		fp=fopen(fName,"w");
		if(fp==NULL) exit(-1);
		for(i=0;i<length;i++){
			if(str[i]=='%'){
				switch (str[i+1]){
					case 'd':
						d=va_arg(list,int);
						fprintf(fp,"%d",d);
						break;
					case 'c':
						c=va_arg(list,int);
						fprintf(fp,"%c",c);
						break;
					case 's':
						s=va_arg(list,char*);
						fprintf(fp,"%s",s);
						break;
					default:
						fprintf(fp,"errPrint : argument err\n");
						exit(0);
				}
				i++;
			}else{
				fprintf(fp,"%c",str[i]);
			}
		}
		fclose(fp);
	}else{
		fp=fopen(fName,"a");
		if(fp==NULL) exit(-1);
//		fprintf(fp,"\n");
		for(i=0;i<length;i++){
			if(str[i]=='%'){
				switch (str[i+1]){
					case 'd':
						d=va_arg(list,int);
						fprintf(fp,"%d",d);
						break;
					case 'c':
						c=va_arg(list,int);
						fprintf(fp,"%c",c);
						break;
					case 's':
						s=va_arg(list,char*);
						fprintf(fp,"%s",s);
						break;
					default:
						fprintf(fp,"errPrint : argument err\n");
						exit(0);
				}
				i++;
			}else{
				fprintf(fp,"%c",str[i]);
			}
		}
		fclose(fp);
	}
	LogCount++;
}
