/*
 * ppScan.c
 *	Version: 
 *  Created on: 2014/11/10
 *	Last Modified on: 2014/11/10
 */

#include "sScan.h"

static void ppLog(int num,...);
static int evaluateWord(int code);
static int evaluateSyntax(int scode);
static int evaluateToken(int tcode);
static int evaluateIteration(int onetime,int numc,...);
int currentToken;
static void exScan();
unsigned int indentCount;
char tmpString[MAXSTRSIZE];
int tmpToken;
int exceptionTrigger=0;
static void pPrint(int option,...);
static int validateTopOfSyntax(int syntaxNum);
static int notEmptySentence[]={10,TNAME,TIF,TWHILE,TCALL,TRETURN,TREAD,TREADLN,TWRITE,TWRITELN,TBEGIN};
static FILE *pFile;

int ppScan(){
	ppLog(0);
	indentCount=0;
	if((currentToken=scan())!=TPROGRAM){
		printf("err0\n");return -1;
	}
	indentCount++;
	int r=evaluateWord(SPROGRAM);
	ppLog(1,r);
	return r;
}

void ppLog(int num,...){
	va_list list;
	int r=0;
	va_start(list,num);
	if(num==0){
		va_end(list);
		if((pFile = fopen("Log-sScan.txt", "w"))==NULL){
			printf("cannot open file for log\n");exit(-1);
		}
//		pFile=stdout;
	}else if(num==1){
		r=va_arg(list,int);
		va_end(list);
		if(r>0){
			fprintf(pFile,"\nsScan was END!--SUCCESS\n");
		}else{
			fprintf(pFile,"\nsScan was END!--FAILED\n");
			fprintf(pFile,"LastToken was %d!\n",currentToken);
		}
		fclose(pFile);
	}else{
		exit(-1);
	}
}


int evaluateWord(int code){ //(code is correct syntax)?return>0:return<0
	fprintf(pFile,"evaluateWord(%d)",code);
	if(code>NUMOFTOKEN&&code<=NUMOFTOKEN+NUMOFSYNTAX){
		fprintf(pFile,"-evaluateSyntax\n");
		return(evaluateSyntax(code)); //return>0 is correct
	}else if(code>0&&code<=NUMOFTOKEN){
		fprintf(pFile,"-evaluateToken\n");
		return(evaluateToken(code)); //return>0 is correct
	}else{
		fprintf(pFile,"-ERR\n");
		return -1;
	}
}

int evaluateSyntax(int scode){
	int *temp=syntaxInner[scode-NUMOFTOKEN];
	int j=1;
	if(currentToken<0){
		printf("EOF\n");return -1;
	}
	if(scode==SPROGRAM){
		for(j=1;j<=5;j++){
			if(j==3){
				indentCount=1;
			}
			fprintf(pFile,"evaluateSyntax(SPROGRAM) j:%d temp[j]:%d\n",j,temp[j]);
			if(evaluateWord(temp[j])<0){
				fprintf(pFile,"err1\n");return -1;
			}
		}
		return(scode);
	}else if(scode==SBROCK){
		do{
			if(currentToken==TVAR){ //except check
				fprintf(pFile,"evaluateSyntax(SBROCK) j:%d temp[j]:%d\n",1,temp[1]);
				if(evaluateWord(SVARDECLARE)<0){
					printf("err4\n");return -1;
				}
			}else if(currentToken==TPROCEDURE){ //except check
				fprintf(pFile,"evaluateSyntax(SBROCK) j:%d temp[j]:%d\n",2,temp[2]);
				if(evaluateWord(SSUBPROGDECLARE)<0){
					printf("err5\n");return -1;
				}
			}else{
				j++;
			}
		}while(j==1);
		fprintf(pFile,"evaluateSyntax(SBROCK) j:%d temp[j]:%d\n",3,temp[3]);
		if(evaluateWord(temp[3])<0){
			printf("err6\n");return -1;
		}
		return scode;
	}else if(scode==SVARDECLARE){
		for(j=1;j<=5;j++){
			if(evaluateWord(temp[j])<0){
				printf("err7\n");return -1;
			}
		}
		if(evaluateIteration(0,4,temp[j],temp[j+1],temp[j+2],temp[j+3])<0){
			printf("err8\n");return -1;
		}
		return scode;
	}else if(scode==SVARLIST||scode==SSTATELIST||scode==SSTATE||scode==SITEM){//1:{2} patern
		if(evaluateWord(temp[j++])<0){
			printf("err9\n");return -1;
		}
		if(evaluateIteration(0,2,temp[j],temp[j+1])<0){
			printf("err10\n");return -1;
		}
		return scode;
	}else if(scode==STYPE||scode==SSTANDARD||scode==SCONST||scode==SMULTIOPERATE||scode==SADDOPERATE||scode==SRELATOPERATE){
		for(j=1;j<=temp[0];j++){
			if(validateTopOfSyntax(temp[j])>0){
				if(evaluateWord(temp[j])<0){
					printf("err11\n");return -1;
				}else{
					return temp[j];
				}
			}
		}
		return -1;
	}else if(scode==SSENTENCE){
		for(j=1;j<=notEmptySentence[0];j++){
			if(currentToken==notEmptySentence[j]){ //もし途中で切れるような場合はエラーでは？
				if(evaluateWord(temp[j])<0){
					printf("err12\n");return -1;
				}
				return temp[j];
			}
		}
		return evaluateWord(temp[11]); //SEMPTY
	}else if(scode==SSUBPROGDECLARE){
		indentCount++;
		for(j=1;j<=2;j++){
			if(evaluateWord(temp[j])<0){
				printf("err13\n");return -1;
			}
		}
		if(evaluateIteration(1,1,temp[j++])<0){ //SDUMMYARGUMENT
			printf("err14\n");return -1;
		}
		if(evaluateWord(temp[j++])<0){
			printf("err15\n");return -1;
		}
		if(evaluateIteration(1,1,temp[j++])<0){//SVARDECLARE
			printf("err16\n");return -1;
		}
		for(;j<=temp[0];j++){
			if(evaluateWord(temp[j])<0){
				printf("err17\n");return -1;
			}
		}
		return scode;
	}else if(scode==SDUMMYARGUMENT){
		for(;j<=4;j++){
			if(evaluateWord(temp[j])<0){
				printf("err18\n");return -1;
			}
		}
		if(evaluateIteration(0,4,temp[j],temp[j+1],temp[j+2],temp[j+3])<0){
			printf("err19\n");return -1;
		}
		j+=4;
		if(evaluateWord(temp[j++])<0){
			printf("err20\n");return -1;
		}
		return scode;
	}else if(scode==SCOMPOUNDSTATE){
		int dummy=0; //??? UNKNOWN: WHY DOES IT NEED?
		fprintf(pFile,"evaluateSyntax(SCOMPOUNDSTATE) j:%d temp[j]:%d\n",j,temp[j]);
		if(evaluateWord(temp[j++])<0){//begin
			printf("err21\n");return -1;
		}
		indentCount++;
		pPrint(2,NEWLINE,INDENT);
		if(evaluateWord(temp[j++])<0){//sentence
				printf("err\n");return -1;
		}
		if(evaluateIteration(0,2,temp[j],temp[j+1])<0){//loop
			printf("err\n");return -1;
		}
		j+=2;
		indentCount--;
		pPrint(2,NEWLINE,INDENT);
		if(evaluateWord(temp[j++])<0){
			printf("err\n");return -1;
		}
		if(currentToken==TSEMI){
			indentCount++;
		}
		return scode;
	}else if(scode==SBRANCHI){
		for(j=1;j<=4;j++){
			if(evaluateWord(temp[j])<0){
				printf("err\n");return -1;
			}if(j==3){
				indentCount++;
				pPrint(2,NEWLINE,INDENT);
			}
		}
//		if(evaluateIteration(1,2,temp[j],temp[j+1])<0){
//			printf("err\n");return -1;
//		}
		indentCount--;
		pPrint(2,NEWLINE,INDENT);
		if(validateTopOfSyntax(temp[j])<0){// if there is no first word, it is correct
			return scode; //if nothing, its correct
		}else{
			if(evaluateWord(temp[j])<0){
				printf("err\n");return -1;
			}
			indentCount++;
			pPrint(2,NEWLINE,INDENT);
		}
		if(validateTopOfSyntax(temp[j+1])<0){
			printf("err\n");return -1;
		}
		if(evaluateWord(temp[j+1])<0){
			printf("err\n");return -1;
		}indentCount--;
		return scode;
	}else if(scode==SVARNAME||scode==SPROCNAME||scode==SARRAY||scode==SRETURN||scode==SASSIGN||scode==SLEFT){
		for(j=1;j<=temp[0];j++){
			if(evaluateWord(temp[j])<0){
				printf("err1\n");return -1;
			}
		}
		return(scode);
	}else if(scode==SLOOP){
		for(j=1;j<=temp[0];j++){
			if(evaluateWord(temp[j])<0){
				printf("err2\n");return -1;
			}
			if(j==3){
				indentCount++;
				pPrint(2,NEWLINE,INDENT);
			}
		}
		return(scode);
	}else if(scode==SPROCCALL){
		for(j=1;j<=2;j++){
			if(evaluateWord(temp[j])<0){
				printf("err\n");return -1;
			}
		}
		if(evaluateIteration(1,3,temp[j],temp[j+1],temp[j+2])<0){
			printf("err\n");return -1;
		}
		return scode;
	}else if(scode==SVAR){
		if(evaluateWord(temp[j++])<0){
			printf("err\n");return -1;
		}
		if(evaluateIteration(1,3,temp[j],temp[j+1],temp[j+2])<0){
			printf("err\n");return -1;
		}
		j+=3;
		return scode;
	}else if(scode==SSIMPLE){
		if(currentToken==TPLUS||currentToken==TMINUS){
			evaluateWord(currentToken);
		}
		j=3;
		if(evaluateWord(temp[j++])<0){
			printf("err\n");return -1;
		}
		if(evaluateIteration(0,2,temp[j],temp[j+1])<0){
			printf("err\n");return -1;
		}
		return scode;
	}else if(scode==SFACTOR){
		int r;
		if((r=validateTopOfSyntax(scode))>0){
			for(j=1;j<=2;j++){
				if(r==temp[j]){
					return evaluateWord(temp[j]);
				}
			}
			if(r==temp[3]){
				for(j=3;j<=5;j++){
					if(evaluateWord(temp[j])<0){
						printf("err\n");return -1;
					}
				}
				return scode;
			}else if(r==temp[6]){
				for(j=6;j<=7;j++){
					if(evaluateWord(temp[j])<0){
						printf("err\n");return -1;
					}
				}
				return scode;
			}else if(r==temp[8]){
				for(j=8;j<=temp[0];j++){
					if(evaluateWord(temp[j])<0){
						printf("err\n");return -1;
					}
				}
				return scode;
			}
		}
		printf("err\n");return -1;
	}else if(scode==SINPUT||scode==SOUTPUT){
		if(currentToken==temp[j]){
			evaluateWord(temp[j]);
		}else if(currentToken==temp[j+1]){
			evaluateWord(temp[j+1]);
		}else{
			printf("err\n");return -1;
		}
		j+=2;
		if(currentToken==temp[j]){ //j=3
			for(;j<=4;j++){
				if(evaluateWord(temp[j])<0){
					printf("err\n");return -1;
				}
			}
//			printf("IE %d:%s\n",scode,syntaxString[scode-NUMOFTOKEN]);
			if(evaluateIteration(0,2,temp[j],temp[j+1])<0){ //j=5
				printf("ERRX %d:%d\n",temp[j],temp[j+1]);return -1;
			}
			j+=2;
			if(evaluateWord(temp[j])<0){
				printf("err\n");return -1;
			}
		}
		return scode;
	}else if(scode==SOUTASSIGN){
		if(currentToken==TSTRING&&strlen(string_attr)>1){
			return evaluateWord(TSTRING);
		}else{
			if(evaluateWord(temp[j++])<0){
				printf("err\n");return -1;
			}
			if(evaluateIteration(1,2,temp[j],temp[j+1])<0){
				printf("err\n");return -1;
			}
			return scode;
		}
	}else if(scode==SVARNAME||scode==SPROCNAME||scode==SRETURN||scode==SLEFT){
		for(j=1;j<temp[0];j++){
			if(evaluateWord(temp[j])<0){
				printf("err\n");return -1;
			}
		}
		return scode;
	}else if (scode==SEMPTY){
		fprintf(pFile,"evaluateSyntax(SEMPTY) j:- temp[j]:-\n");
//		if(tmpToken==TSEMI&&currentToken==TEND) indentCount--;
//		printf("<<empty sentence>> %d",tmpToken);
		return scode;
	}else{
		printf("err");return(-1);
	}
	return scode;
}

// tcode is Token Code
int evaluateToken(int tcode){ //If not match, return -1
	if(currentToken<0){
		fprintf(pFile,"\t-Token EOF\n");
		return -1;
	}
	if(currentToken!=tcode){
		fprintf(pFile,"\t-Token not match:%d\n",currentToken);
		exScan(); //define as empty sentence
		return -1;
	}else{
		fprintf(pFile,"\t-Token match at currentToken:%d\n",currentToken);
		exScan();
		return tcode;
	}
}


int evaluateIteration(int onetime,int numc,...){
	fprintf(pFile,"\tevaluateIteration\n");
	if(currentToken<0){
		return -1;
	}
	va_list list;
	int i,r;
	int temp[numc];
	va_start(list,numc);
	for(i=0;i<numc;i++){
		temp[i]=va_arg(list,int);
//		printf("\t%d\n",temp[i]);
	}
	va_end(list);
	while(1){
		i=0;
		if(validateTopOfSyntax(temp[i])<0){// if there is no first word, it is correct
			return 1; //if nothing, its correct
		}else{
			if(evaluateWord(temp[i])<0){
				printf("errEI1\n");return -1;
			}
		}
//		printf("\t%d\n",temp[i]);
		for(i=1;i<numc;i++){
			if(validateTopOfSyntax(temp[i])<0){
				printf("err\n");return -1;
			}
			if(evaluateWord(temp[i])<0){
				printf("err\n");return -1;
			}
		}
		if(onetime==1){
			return 1;
		}
	}
	return -1;
}

void exScan(){
	if(tmpToken==TEND){
		exceptionTrigger=1;
	}
	memset(tmpString,'\0',strlen(tmpString));
	strncpy(tmpString,string_attr,strlen(string_attr));
	tmpToken=currentToken;
	do{
		currentToken=scan(); // then, new string_attr
	}while(currentToken==0);
	printf("%s ",tmpString);
	if(tmpToken==TSEMI){
		fprintf(pFile,"TSEMI\n");
		pPrint(1,SCAN);
//		if(currentToken==TBEGIN){
//			pPrint(1,NEWLINE);
//		}
//		pPrint(2,NEWLINE,INDENT);
	}
	exceptionTrigger=0;
}
	// it works
//	printf("%s ",string_attr);
//	if(currentToken==TSEMI){
//		pPrint(1,NEWLINE);
//	}
//	do{
//		currentToken=scan();
//	}while(currentToken==0);
//}

//void pPrint(int option,...){ //
//	va_list list;
//	int r;
//	va_start(list,option);
//	int i,j;
//	for(i=0;i<option;i++){
//		r=va_arg(list,int);
//		if(r==NEWLINE){
//			printf("\n");
//		}else if(r==INDENT){
//			for(j=0;j<indentCount;j++){
//				printf("\t");
//			}
//		}
//	}
//	va_end(list);
//}

void pPrint(int option,...){ //
	va_list list;
	int r;
	va_start(list,option);
	int i,j;
	for(i=0;i<option;i++){
		r=va_arg(list,int);
		if(r==NEWLINE){
			printf("\n");
		}else if(r==INDENT){
			for(j=0;j<indentCount;j++){
				printf("\t");
			}
		}else if (r == SCAN){
			if(exceptionTrigger==1&&currentToken!=TBEGIN){
				indentCount--;
				pPrint(2,NEWLINE,INDENT);
			}
			if(currentToken==TELSE){
				fprintf(pFile,"\tSEMI1\n");
				indentCount--;
				pPrint(2,NEWLINE,INDENT);
				indentCount++;
			}else if(currentToken==TBEGIN){
				fprintf(pFile,"\tSEMI2\n");
				indentCount--;
				pPrint(2,NEWLINE,INDENT);
			}else{
				fprintf(pFile,"\tSEMI3\n");
				pPrint(2,NEWLINE,INDENT);
			}
		}
	}
	va_end(list);
}

//varidateTopOfSyntax
int validateTopOfSyntax(int syntaxNum){
	if(syntaxNum<NUMOFTOKEN){
		if(currentToken==syntaxNum){ //finally reach here
			return syntaxNum;
		}
		return -1;
	}
	int *temp=syntaxInner[syntaxNum-NUMOFTOKEN];
	int i;
	if(syntaxNum==SRELATOPERATE||syntaxNum==SADDOPERATE||syntaxNum==SMULTIOPERATE){
		for(i=1;i<=temp[0];i++){
			if(validateTopOfSyntax(temp[i])>0){
				return syntaxNum;
			}
		}
		return -1;
	}else if(syntaxNum==SSENTENCE){
		for(i=1;i<=temp[0]-1;i++){
			if(validateTopOfSyntax(temp[i])>0){
				return syntaxNum;
			}
		}
		return temp[i]; //empty
	}else if(syntaxNum==SBROCK||syntaxNum==SSIMPLE){
		for(i=1;i<=2;i++){
			if(validateTopOfSyntax(temp[i])>0){
				return syntaxNum;
			}
		}
		if(validateTopOfSyntax(temp[3])>0){
			return syntaxNum;
		}
		return -1;
	}else if(syntaxNum==SFACTOR){
		for(i=1;i<=3;i++){
			if(validateTopOfSyntax(temp[i])>0){
				return temp[i];
			}
		}
		if(validateTopOfSyntax(temp[6])>0){ //TNOT
			return temp[6];
		}
		if(validateTopOfSyntax(temp[8])>0){ //SSTANDARD
			return temp[8];
		}
		return -1;
	}else if(syntaxNum==SCONST){
		for(i=1;i<=temp[0];i++){
			if(validateTopOfSyntax(temp[i])>0){
				return temp[i];
			}
		}
		return -1;
	}else if(syntaxNum==SINPUT||syntaxNum==SOUTPUT){
		for(i=1;i<=2;i++){
			if(validateTopOfSyntax(temp[i])>0){
				return temp[i];
			}
		}
		return -1;
	}else if(syntaxNum==SOUTASSIGN){
		if(validateTopOfSyntax(temp[1])>0){
			return (temp[1]);
		}else if(validateTopOfSyntax(temp[4])>0){
			return (temp[4]);
		}
	}else if(syntaxNum==SSTANDARD){
		if(currentToken==TINTEGER||currentToken==TBOOLEAN||currentToken==TCHAR){
			return STYPE;
		}return -1;
	}else if(syntaxNum==STYPE){
		if(currentToken==TINTEGER||currentToken==TBOOLEAN||currentToken==TCHAR||currentToken==TARRAY){
			return STYPE;
		}return -1;
	}else if(syntaxNum>NUMOFTOKEN){
		if(validateTopOfSyntax(temp[1])>0){
			return (temp[1]);
		}
		return -1;
	}
	return -1;
}
