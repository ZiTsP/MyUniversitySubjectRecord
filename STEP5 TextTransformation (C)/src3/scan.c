/*
 * scan.c
 *	Version: 5.0
 *  Created on: 2014/10/14
 *  Last Modified on: 2014/10/18
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */

#include "scan.h"

static int isSign(char s);
static int checkWSign(char *s);
static int checkToken(char *s);
static int isComment(char s);
static int isDefString(char s);
static int isSeparater(char s);
int num_attr;
char string_attr[MAXSTRSIZE];
int lastLineNumber=1;

int wordexist[NUMOFTOKEN]={0};
int lastToken=0;

int lineCountTrigger=RESET;

int scan(){
	memset(string_attr,'\0',strlen(string_attr));
	num_attr=-1;
	int trigger[6]={0}; //trigger of {string,number,sign,',/**/,{}}
	int wordsCount=0; //counter of words in token
	int resultToken=0;	//temp token
	int check=0;	//get "check~"function returns
	int isSep,isDef,isCom;	//get "is~"function returns
	if (lineCountTrigger==SET){	//when check some word, it feedback new line count
		lastLineNumber++;
		lineCountTrigger=RESET;
	}
	if(word==EOF){	//EOF
		return -1;
	}else if((isSep=isSeparater(word))!=0){ //line, tab or space
		word=fgetc(fp);
		return 0; //skip
	}else if(isprint(word)==0){	//leave out not printable words
		error("cannot print the word");
	}else if(islower(word)!=0||isupper(word)!=0){ //NAME
		resultToken=TNAME;
		string_attr[wordsCount++]=word;
		word=fgetc(fp);
		trigger[0]=SET;
	}else if(isdigit(word)!=0){ //Natural Number
		resultToken=TNUMBER;
		string_attr[wordsCount++]=word;
		num_attr=atoi(string_attr);
		word=fgetc(fp);
		trigger[1]=SET;
	}else if((resultToken=isSign(word))!=0){ //Sign
		string_attr[wordsCount++]=word;
		word=fgetc(fp);
		trigger[2]=SET;
	}else if((isDef=isDefString(word))!=0){ //'___' start
		resultToken=TSTRING;
		word=fgetc(fp); //next word is first count
		trigger[3]=SET;
	}else if((isCom=isComment(word))=='/'){ //comment out start /*___*/
		word=fgetc(fp); //next word is first count
		trigger[4]=SET;
	}else if((isCom=isComment(word))=='{'){ //comment out start {___}
		word=fgetc(fp); //next word is first count
		trigger[5]=SET;
	}else{ //except??
			fprintf(stderr,"Something Bug words or not define\n");
			return -2;
	}
	while(1){
		if(word==EOF){	//EOF
			if((check=checkToken(string_attr))<0){
				return resultToken;
			}
			return check;
		}else if(trigger[0]==SET){ //NAME or TOKEN
			if(wordsCount>MAXSTRSIZE-1){
				error("syntax err: too long string\n");
			}else if(islower(word)!=0||isupper(word)!=0||isdigit(word)!=0){
				string_attr[wordsCount++]=word;
				word=fgetc(fp);
			}else{
				if((check=checkToken(string_attr))<0){
					return resultToken;
				}
				return check;
			}
		}else if(trigger[1]==SET){ //NUMBER
			if(isdigit(word)!=0){
				string_attr[wordsCount++]=word;
				if((num_attr=atoi(string_attr))>32767){
					error("syntax err: number<=32767");
				}
				word=fgetc(fp);
			}else{
				return resultToken;
			}
		}else if(trigger[2]==SET){ //sign by two words
			if(isSign(word)!=0){
				string_attr[1]=word;
				check=checkWSign(string_attr);
				if(check<0){
					string_attr[1]='\0';
					return resultToken;
				}else{
					word=fgetc(fp);
					return check;
				}
			}else{
				return resultToken;
			}
		}else if(trigger[3]==SET){ //string '__'
			if(isprint(word)==0&&(isSep=isSeparater(word))==0){
				error("syntax err: about STRING start");
			}else if(isDefString(word)!=0){
				if((word=fgetc(fp))!='\''){
					return resultToken;
				}else{
					string_attr[wordsCount++]=word; //this is one before "\'"
				}
			}else if(isSep<0){
				error("not permission new line in STRING");
			}
			string_attr[wordsCount++]=word;
			word=fgetc(fp);
		}else if(trigger[4]==SET){ //comment out /**/
			if(wordsCount==0){
				if(word!='*'){
					error("syntax err: about comment out start");
				}
				word=fgetc(fp);
			}
			if(word=='*'){
				if((word=fgetc(fp))=='/'){
					word=fgetc(fp);
					return 0; //coment out end
				}
				string_attr[wordsCount++]='*';
			}
			if(isprint(word)!=0||isSeparater(word)!=0){
				string_attr[wordsCount++]=word;
				word=fgetc(fp);
			}else if(word==EOF){
				fprintf(stdout,"syntax err: comment out not END\n");
				return 0;
			}else{
				error("cannot print");
			}
		}else if(trigger[5] == SET){ //comment out {}
			if(word=='{'){
				error("comment out in comment");
			}else if(word=='}'){
				word=fgetc(fp);
				return 0; //coment out end
			}
			if(isprint(word)!=0||isSeparater(word)!=0){
				string_attr[wordsCount++]=word;
				word=fgetc(fp);
			}else if(word==EOF){
				fprintf(stdout,"syntax err: comment out not END\n");
				return 0;
			}else{
				error("cannot print");
			}
		}else{ //except??
			error("Something Bug words or not define");
			return -2;
		}
	}
	return -2;
}

int isSign(char s){
	int i;
	for(i=0;i<ASIGNSIZE;i++){
		if(s==*sign[i].keyword){
			return sign[i].keytoken;
		}
	}
	return 0;
}

int checkWSign(char *s){
	int r;
	int i;
	for(i=SIGNSIZE-ASIGNSIZE-1;i<SIGNSIZE;i++){
		r=strncmp(s,sign[i].keyword,2);
		if(r==0){
			return sign[i].keytoken;
		}
	}
	return -1;
}

int checkToken(char *s){
	int r;
	int i;
	for(i=0;i<KEYWORDSIZE;i++){
		r=strncmp(s,key[i].keyword,strlen(key[i].keyword));
		if(r==0&&strlen(s)==strlen(key[i].keyword)){
			return key[i].keytoken;
		}
	}
	return -1;
}

int isComment(char s){
	if(s=='/'){
		return '/';
	}else if(s=='{'){
		return'{';
	}
	return 0;
}

int isDefString(char s){
	if(s=='\''){
		return '\'';
	}
	return 0;
}

int isSeparater(char s){
	if(s=='\t'){
		return '\t';
	}else if(s==' '){
		return ' ';
	}else if(s=='\n'){
		lineCountTrigger=SET;
		return -'\n';
	}
	else return 0;
}

