/*
 * sScan.c
 *	Version: 5
 *  Created on: 2014/11/1
 *	Last Modified on: 2014/11/20
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */

#include "syntaxScan.h"

//static void ssLog(int num,...);	//ログ出力

struct ID *AllScope;
struct wordList *tempList,*callArgList;
int tempListCount;
char *scope;
int StateType=0;
struct arrayType{
	int type;
	int arrayNum;
}tempArray;

static int evaluateWord(int code);
static int evaluateSyntax(int scode);
static int evaluateToken(int tcode);
void clearWordList();
int currentToken;
static void exScan();
unsigned int indentCount;
char tmpString[MAXSTRSIZE];
int tmpToken;
int exceptionTrigger=0;
void refine(int num);
static void pPrint(int option,...);
static int validateTopOfSyntax(int syntaxNum);
static int notEmptySentence[]={10,TNAME,TIF,TWHILE,TCALL,TRETURN,TREAD,TREADLN,TWRITE,TWRITELN,TBEGIN};
static FILE *sFile;
#define RESETINDENT 0
#define ADDINDENT 1
#define ALLOWINDENT -1
#define SET 1
#define END 0

int ppScan(){
	refine(SET);
	if((currentToken=scan())!=TPROGRAM){
		errPrint("There is no \"program\"");//return -1;
	}
	int r=evaluateWord(SPROGRAM);
	refine(END);
	printList();
	return r;
}

void refine(int num){ //可変長には終了時の成否を代入する
	if(num==SET){
		if((sFile = fopen("refine_program.txt", "w"))==NULL){
			fprintf(stderr,"cannot open file for log\n");
			exit(-1);
		}
#ifdef Debug
		sFile=stdout;
#endif
	}else if(num==END){
		fclose(sFile);
	}else{
		exit(-1);
	}
}


int evaluateWord(int code){ //(code is correct syntax)?return>0:return<0
	logPutOut("evaluateWord(%d)",code);
	if(code>NUMOFTOKEN&&code<=NUMOFTOKEN+NUMOFSYNTAX){
		logPutOut("-evaluateSyntax\n");
		return(evaluateSyntax(code)); //return>0 is correct
	}else if(code>0&&code<=NUMOFTOKEN){
		logPutOut("-evaluateToken\n");
		return(evaluateToken(code)); //return>0 is correct
	}else{
		logPutOut("-ERR\n");
		return -1;
	}
}

int evaluateSyntax(int scode){
	char *scodeStr=syntaxString[scode-NUMOFTOKEN];
	int *temp=syntaxInner[scode-NUMOFTOKEN];
	int j=1;
	if(currentToken<0){
		printf("EOF\n");return -1;
	}
	/*evaluate SPROGRAM*/
	if(scode==SPROGRAM){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		for(j=1;j<=5;j++){
			if(evaluateWord(temp[j])<0){
				errPrint("evaluateSyntax(%s)->(%d)",scodeStr,temp[j]);
			}
			if(j==2){
				setupProgram(tmpString);
			}
		}
		return(scode);
	}
	/*evaluate SBROCK*/
	else if(scode==SBROCK){
		scope=idList.prog->name->name;
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		do{
			if(currentToken==TVAR){ //except check
				pPrint(ALLOWINDENT);
				if(evaluateWord(SVARDECLARE)<0){
					errPrint("evaluateSyntax(%s)->(%d)",scodeStr,SVARDECLARE);
				}
			}else if(currentToken==TPROCEDURE){ //except check
				pPrint(ALLOWINDENT);
				if(evaluateWord(SSUBPROGDECLARE)<0){
					errPrint("evaluateSyntax(%s)->(%d)",scodeStr,TPROCEDURE);
				}
			}else{
				j++;
			}
		}while(j==1);
        pPrint(RESETINDENT);
		if(evaluateWord(temp[3])<0){
			errPrint("evaluateSyntax(%s)->(%d)",scodeStr,temp[3]);
		}
		return(scode);
	}
	/*evaluate SVARDECLARE*/
	else if(scode==SVARDECLARE){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		int tempType;
		for(j=1;j<=3;j++){
			if(evaluateWord(temp[j])<0){
				errPrint("no var(var declaretion)\n");
			}
			if(j==1){
				pPrint(ADDINDENT,1);
			}
		}
		if((tempType=evaluateWord(temp[j++]))<0){//j=4
			errPrint("must be type\n");
		}
		int arrayNum=0;
		if(tempType==SARRAY){
			arrayNum=tempArray.arrayNum;
			tempType=tempArray.type;
		}
		int k;
		for(k=0;k<tempListCount;k++){
			if(registerList(tempList->word,tempType,arrayNum,lastLineNumber,POSI_VAR,scope)<0){
				errPrint("double variable\n");
			}
			tempList=tempList->next;
		}
		clearWordList();
		if(evaluateWord(temp[j++])<0){//j=5
			errPrint("must be ;\n");
		}
		while(1){
			int i=j=6;
				if(validateTopOfSyntax(temp[i])<0){// if there is no first word, it is correct
					break; //if nothing, its correct
				}else{
				pPrint(ALLOWINDENT);
				for(i=j;i<=temp[0];i++){
					if((tempType=evaluateWord(temp[i]))<0){// varlist
						printf("errEI1\n");return -1;
					}
					if(i==8){
						int arrayNum=0;
						if(tempType>SARRAY){
							arrayNum=tempType-SARRAY;
							tempType=SARRAY;
						}
						int k;
						for(k=0;k<tempListCount;k++){
							if(registerList(tempList->word,tempType,arrayNum,lastLineNumber,POSI_VAR,scope)<0){
								errPrint("double variable\n");
							}
							tempList=tempList->next;
						}
						clearWordList();
					}
				}
			}
		}
	}
	/*evaluate SVARLIST*/
	else if(scode==SVARLIST){//1:{2} patern
		struct wordList *p;
		char *cp;
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		if(evaluateWord(temp[j++])<0){
			printf("err9\n");return -1;
		}
		tempList=(struct wordList *)malloc(sizeof(struct wordList));
		if((cp = (char *)malloc(strlen(tmpString)+1)) == NULL) {
			printf("can not malloc char in countup\n");return -1;
		}
		strcpy(cp,tmpString);//??
		tempList->word=cp;tempList->token=tmpToken;
		tempListCount=1;
		p=tempList;
		p->next=NULL;
		while(1){
			int i=j;
			if(validateTopOfSyntax(temp[i])<0){// if there is no first word, it is correct
				break; //if nothing, its correct
			}else{
				if(evaluateWord(temp[i++])<0){ //TSEMI
					printf("errEI1\n");return -1;
				}
				if(evaluateWord(temp[i])<0){ //Next variable
					printf("err\n");return -1;
				}
				p->next=(struct wordList *)malloc(sizeof(struct wordList));
				p=p->next;
				p->next=NULL;
				if((cp = (char *)malloc(strlen(tmpString)+1)) == NULL) {
					printf("can not malloc char in countup\n");return -1;
				}
				strcpy(cp,tmpString);//??
				p->word=cp;p->token=tmpToken;
				tempListCount++;
			}
		}
		return scode;
	}
	/*evaluate SVARNAME*/
	else if(scode==SVARNAME){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		if(currentToken!=TNAME){
			errPrint("varname must be TNAME¥n");
		}
		if(evaluateWord(temp[1])<0){
				errPrint("uncorrect token");
		}
		return(scode);
	}
	/*evaluate STYPE*/
	else if(scode==STYPE){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		if(currentToken==TINTEGER||currentToken==TBOOLEAN||currentToken==TCHAR){
			evaluateWord(currentToken);
			return tmpToken;
		}else if(currentToken==TARRAY){
			return evaluateWord(SARRAY);
		}
        errPrint("evaluating : syntax Type \n");
	}
	/*evaluate SSTANDARD*/
	else if(scode==SSTANDARD){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		if(currentToken==TINTEGER||currentToken==TBOOLEAN||currentToken==TCHAR){
			evaluateWord(currentToken);
			return tmpToken;
		}
        errPrint("evaluating : syntax Type \n");
		return -1;
	}
	/*evaluate SARRAY*/
	else if(scode==SARRAY){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		for(j=1;j<=temp[0];j++){
			if(evaluateWord(temp[j])<0){
                errPrint("incorrect token\n");
			}
			if(currentToken==TNUMBER){
				tempArray.arrayNum=atoi(string_attr);
				if(tempArray.arrayNum<=0){
					errPrint("arrayNum must be over 1\n");
				}
			}
			if(j==temp[0]){
				tempArray.type=tmpToken;
			}
		}
		return(scode);
	}
	/*evaluate SSUBPROGDECLARE*/
	else if(scode==SSUBPROGDECLARE){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		int tmpIndent=indentCount;
		for(j=1;j<=temp[0];j++){
			if(j==3||j==5){
				if(validateTopOfSyntax(temp[j])>0){
					if(j==5){
						pPrint(ADDINDENT,1);
					}
					if(evaluateWord(temp[j])<0){
						printf("errEI1\n");return -1;
					}
				}
			}else{
				if(j==2){
					if(registerList(string_attr,currentToken,0,lastLineNumber,POSI_FUNC,scope)<0){
						errPrint("err : double variable\n");
					}
					scope=idList.lastfunc->name->name;
				}else if(j==6){ //SCOMPOUNDSTATE
					indentCount=tmpIndent;
					pPrint(ALLOWINDENT);
				}
				if(evaluateWord(temp[j])<0){
					printf("err13\n");return -1;
				}
			}
		}
		scope=idList.prog->name->name;
		return scode;
	}
	/*evaluate SPROCNAME*/
	else if(scode==SPROCNAME){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		if(currentToken!=TNAME){
			errPrint("varname must be TNAME¥n");
		}
		struct function *fp;
		for(fp=idList.func;fp!= NULL;fp=fp->nextFunc){	//function
			if(strcmp(string_attr, fp->name->name)==0){
				if(evaluateWord(temp[1])<0){
					errPrint("uncorrect token");
				}
				return(scode);
			}
		}
		errPrint("no function¥n");
	}
	/*evaluate SDUMMYARGUMENT*/
	else if(scode==SDUMMYARGUMENT){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		for(;j<=4;j++){
			if(evaluateWord(temp[j])<0){
				printf("err18\n");return -1;
			}
			if(j==3){
				if(currentToken!=TINTEGER&&currentToken!=TBOOLEAN&&currentToken!=TCHAR){
					errPrint("dummy arg must be SSTANDARD\n");
				}
				int i;
				for(i=0;i<tempListCount;i++){
					if(tempList->token!=TNAME){
						errPrint("need TNAME for argment dec\n");
					}
					if(registerList(tempList->word,currentToken,0,lastLineNumber,POSI_ARG,scope)<0){
						errPrint("err : double variable\n");
					}
					tempList=tempList->next;
				}
				clearWordList();
			}
		}
		while(1){
			int i=j;
			if(validateTopOfSyntax(temp[i])<0){// if there is no first word, it is correct
				break; //if nothing, its correct
			}else{
				if(evaluateWord(temp[i++])<0){// varlist
					printf("errEI1\n");return -1;
				}
				for(;i<=temp[0]-1;i++){
					if(evaluateWord(temp[i])<0){
						printf("err\n");return -1;
					}
					if(i==7){
						if(currentToken!=TINTEGER&&currentToken!=TBOOLEAN&&currentToken!=TCHAR){
							errPrint("dummy arg must be SSTANDARD\n");
						}
						int i;
						for(i=0;i<tempListCount;i++){
							if(registerList(tempList->word,currentToken,0,lastLineNumber,POSI_ARG,scope)<0){
								errPrint("err : double variable\n");
							}
							tempList=tempList->next;
							clearWordList();
						}
					}
				}
			}
		}
		j=temp[0];
		if(evaluateWord(temp[j])<0){
			printf("err20\n");return -1;
		}
		return scode;
	}
	/*evaluate SCOMPOUNDSTATE*/
	else if(scode==SCOMPOUNDSTATE){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		int tmpIndent=indentCount;
		if(evaluateWord(temp[j++])<0){//begin
            errPrint("need begin\n");
		}
		pPrint(ADDINDENT,1);
		if(evaluateWord(temp[j++])<0){//sentence
				printf("err\n");return -1;
		}
		while(1){
			int i=j;
			if(validateTopOfSyntax(temp[i])<0){// if there is no first word, it is correct
				break; //if nothing, its correct
			}else{
				if(evaluateWord(temp[i++])<0){ //TSEMI
					printf("errEI1\n");return -1;
				}
				pPrint(ALLOWINDENT);
				if(validateTopOfSyntax(temp[i])<0){
					errPrint("evaluating2 : loop part of syntax\n");
				}
				if(evaluateWord(temp[i])<0){
					printf("err\n");return -1;
				}
			}
		}
		j+=2;
		indentCount=tmpIndent;
		pPrint(ALLOWINDENT);
		if(evaluateWord(temp[j])<0){ //end
			printf("err\n");return -1;
		}
		return scode;
	}
	/*evaluate SSENTENCE*/
	else if(scode==SSENTENCE){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		for(j=1;j<=notEmptySentence[0];j++){
			if(currentToken==notEmptySentence[j]){
                if(evaluateWord(temp[j])<0){
					printf("err12\n");return -1;
				}
				return temp[j];
			}
		}
		return evaluateWord(temp[11]); //SEMPTY
	}
	/*evaluate SBRANCHI*/
	else if(scode==SBRANCHI){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		int tmpIndent=indentCount;
		for(j=1;j<=4;j++){
			if(j==2){
				int stateType;
				if((stateType=evaluateWord(temp[j]))<0){
					printf("err\n");return -1;
				}
				if(stateType!=TBOOLEAN){
					errPrint("BRANCH STATE is incorrect%d\n",stateType);
				}
			}else{
				if(evaluateWord(temp[j])<0){
					printf("err\n");return -1;
				}
				if(j==3){
		        	if(currentToken!=TBEGIN){
		            	indentCount++;
		        	}
		        	pPrint(ALLOWINDENT);
				}
			}
		}
		if(validateTopOfSyntax(temp[j])>0){// TELSE
			indentCount=tmpIndent;
			pPrint(ALLOWINDENT);
			if(evaluateWord(temp[j])<0){
				printf("err\n");return -1;
			}
	        if(currentToken!=TBEGIN){
	            indentCount++;
	        }
	        pPrint(ALLOWINDENT);
			if(evaluateWord(temp[j+1])<0){ //SSENTENCE
				printf("err\n");return -1;
			}
		}
		indentCount=tmpIndent;
		return scode;
	}
	/*evaluate SLOOP*/
	else if(scode==SLOOP){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		int tmpIndent=indentCount;
        for(j=1;j<=3;j++){
			if(j==2){
				int stateType;
				if((stateType=evaluateWord(temp[j]))<0){
					printf("err\n");return -1;
				}
				if(stateType!=TBOOLEAN){
					errPrint("LOOP STATE is incorrect\n");
				}
			}else{
	            if(evaluateWord(temp[j])<0){
	                printf("err2\n");return -1;
	            }
			}
        }
        if(currentToken!=TBEGIN){
            indentCount++;
        }
        pPrint(ALLOWINDENT);
        if(evaluateWord(temp[j])<0){
            printf("err2\n");return -1;
        }
        indentCount=tmpIndent;
		return(scode);
	}
	/*evaluate SPROCCALL*/
	else if(scode==SPROCCALL){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		for(j=1;j<=2;j++){
			if(evaluateWord(temp[j])<0){
				printf("err\n");return -1;
			}
		}
		struct function *fp;
		for(fp=idList.func;fp!=NULL;fp=fp->nextFunc){
			if(strcmp(tmpString, fp->name->name)==0){
				if(fp->arg!=NULL){
					for(j=3;j<=temp[0];j++){
						if(evaluateWord(temp[j])<0){
							printf("err\n");return -1;
						}
					}
					struct variable *ap;
					for(j=0,ap=fp->arg;(j<tempListCount)&&(ap!=NULL);j++,ap=ap->nextVar){
						if(tempList->token!=ap->type){
							errPrint("incorrect argment type\n");
						}
					}
					if(ap!=NULL||j!=tempListCount){
						errPrint("incorrect argment count\n");
					}
					clearWordList();
				}
			}
		}
		return scode;
	}
	/*evaluate SSTATELIST*/
	else if(scode==SSTATELIST){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		struct wordList *sL;
		tempList=(struct wordList *)malloc(sizeof(struct wordList));
		tempList->next=NULL;
		if((tempList->token=evaluateWord(temp[j++]))<0){
			printf("err9\n");return -1;
		}
		sL=tempList;
		tempListCount=1;
		while(1){
			int i=j;
			if(currentToken!=TCOMMA){
				return SSTATELIST;
			}
			sL->next=(struct wordList *)malloc(sizeof(struct wordList));
			sL=sL->next;sL->next=NULL;
			tempListCount++;
			if(evaluateWord(temp[i++])<0){
				printf("err9\n");return -1;
			}
			if((sL->token=evaluateWord(temp[i++]))<0){
				printf("err9\n");return -1;
			}
			if(sL->token==TNUMBER){
				sL->token=TINTEGER;
			}else if(sL->token==TFALSE||sL->token==TTRUE){
				sL->token=TBOOLEAN;
			}else if(sL->token==TSTRING){
				sL->token=TCHAR;
			}
		}
	}
	/*evaluate SRETURN*/
	else if(scode==SRETURN){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		if(evaluateWord(TRETURN)<0){
			printf("err\n");return -1;
		}
		return TRETURN;
	}
	/*evaluate SASSIGN*/
	else if(scode==SASSIGN){
		int LstateType,RstateType;
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		if((LstateType=evaluateWord(temp[j++]))<0){
            errPrint("1ncorrect token\n");
		}
		if(evaluateWord(temp[j++])<0){
            errPrint("1ncorrect token\n");
		}
		if((RstateType=evaluateWord(temp[j++]))<0){
            errPrint("1ncorrect token\n");
		}
		if(RstateType==TNUMBER){
			RstateType=TINTEGER;
		}else if(RstateType==TTRUE||RstateType==TFALSE){
			RstateType=TBOOLEAN;
		}else if(RstateType==TSTRING){
			RstateType=TCHAR;
		}
		if(LstateType!=RstateType){
			errPrint("SASSIGN : both must be same state type¥n");
		}
		return(scode);
	}
	/*evaluate SLEFT*/
	else if(scode==SLEFT){
		int LvarType;
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		if((LvarType=evaluateWord(temp[j]))<0){
				printf("err\n");return -1;
		}
		return LvarType;
	}
	/*evaluate SVAR*/
	else if(scode==SVAR){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		struct variable *tempVar;
		if((tempVar=countup(string_attr,lastLineNumber,scope))==NULL){
			errPrint("hasnt declare variable¥n");
		}
		if(evaluateWord(temp[j++])<0){
			printf("err\n");return -1;
		}
		if(currentToken!=TLSQPAREN){
			return tempVar->type;
		}
		if(tempVar->arrayNum==0){
			errPrint("SVAR-ARRAY[x],ARRAY must be array¥n");
		}
		if(evaluateWord(temp[j++])<0){//[
			printf("err\n");return -1;
		}
		int stateNum=atoi(string_attr);
		if(currentToken!=TINTEGER&&currentToken!=TNUMBER){
			stateNum=1;//とりあえず
		}
		int stateType=evaluateWord(temp[j++]);
		if(stateType==TNUMBER){
			stateType=TINTEGER;
		}
		if(stateType!=TINTEGER||stateNum<=0||stateNum>tempVar->arrayNum){
			errPrint("SVAR-ARRAY[x],x must be integer¥n");
		}
		if(evaluateWord(temp[j++])<0){//]
			printf("err\n");return -1;
		}
		return tempVar->type;
	}
	/*evaluate SSTATE*/
	else if(scode==SSTATE){//1:{2} patern
		int LstateType;
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		if((LstateType=evaluateWord(temp[j++]))<0){//j=1
			printf("err9\n");return -1;
		}
		if(LstateType==TNUMBER){
			LstateType=TINTEGER;
		}else if(LstateType==TFALSE||LstateType==TTRUE){
			LstateType=TBOOLEAN;
		}else if(LstateType==TSTRING){
			LstateType=TCHAR;
		}
		if(validateTopOfSyntax(temp[j])<0){//j=2
			return LstateType;
		}else{
			int operator,RstateType;
			if((operator=evaluateWord(temp[j++]))<0){//j=2
				printf("err9\n");return -1;
			}
			if((RstateType=evaluateWord(temp[j++]))<0){//j=3
				printf("err9\n");return -1;
			}
			if(RstateType==TNUMBER){
				RstateType=TINTEGER;
			}else if(RstateType==TFALSE||RstateType==TTRUE){
				RstateType=TBOOLEAN;
			}else if(RstateType==TSTRING){
				RstateType=TCHAR;
			}
			if(LstateType==RstateType){
				return TBOOLEAN;
			}else{
				errPrint("state relation is incorrect¥n");
			}
		}
	}
	/*evaluate SRELATOPERATE*/
	else if(scode==SRELATOPERATE){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		for(j=1;j<=temp[0];j++){
			if(validateTopOfSyntax(temp[j])>0){
				if(evaluateWord(temp[j])<0){
					printf("err11\n");return -1;
				}else{
					return temp[j];
				}
			}
		}
        errPrint("evaluating : relational operator");
	}
	/*evaluate SSIMPLE*/
	else if(scode==SSIMPLE){
		int LitemType,RitemType;
		int operator=0;
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		if(currentToken==TPLUS||currentToken==TMINUS){
			evaluateWord(currentToken);
			operator=1;
		}
		j=3;
		if((LitemType=evaluateWord(temp[j++]))<0){//j=3
			printf("err\n");return -1;
		}
		if(operator!=0&&LitemType!=TINTEGER){
			errPrint("SSIMPLE need +- & integer¥n");
		}
		if(currentToken!=TPLUS&&currentToken!=TMINUS&&currentToken!=TOR){
			return LitemType;
		}else{
			if((operator=evaluateWord(temp[j++]))<0){//j=4
				printf("err\n");return -1;
			}
			if((RitemType=evaluateWord(temp[j++]))<0){//j=5
				printf("err\n");return -1;
			}
			if(LitemType==RitemType){
				if(LitemType==TINTEGER&&operator==TPLUS){
					return TINTEGER;
				}else if(LitemType==TINTEGER&&operator==TMINUS){
					return TINTEGER;
				}else if(LitemType==TBOOLEAN&&operator==TOR){
					return TBOOLEAN;
				}else{
					errPrint("it cannot be different Type with operator¥n");
				}
			}else{
				errPrint("it cannot be different Type with operator¥n");
			}
		}
	}
	/*evaluate SADDOPERATE*/
	else if(scode==SADDOPERATE){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		int operator;
		if(currentToken==TPLUS||currentToken==TMINUS||currentToken==TOR){
			if((operator=evaluateWord(currentToken))<0){
				printf("err11\n");return -1;
			}
		}else{
			errPrint("incorrect add operator¥n");
		}
		return tmpToken;
	}
	/*evaluate SITEM*/
	else if(scode==SITEM){//1:{2} patern
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		int LitemType,operator,RitemType;
		if((LitemType=evaluateWord(temp[j++]))<0){
			printf("err9\n");return -1;
		}
		if(currentToken!=TSTAR&&currentToken!=TDIV&&currentToken!=TAND){
			return LitemType;
		}else{
			if((operator=evaluateWord(temp[j++]))<0){
				printf("err9\n");return -1;
			}
			if((RitemType=evaluateWord(temp[j++]))<0){
				printf("err9\n");return -1;
			}
			if(LitemType==RitemType){
				if(LitemType==TINTEGER&&operator==TSTAR){
					return TINTEGER;
				}else if(LitemType==TINTEGER&&operator==TDIV){
					return TINTEGER;
				}else if(LitemType==TBOOLEAN&&operator==TAND){
					return TBOOLEAN;
				}else{
					errPrint("it cannot be different Type with operator¥n");
				}
			}else{
				errPrint("it cannot be different Type with operator¥n");
			}
		}
	}
	/*evaluate SMULTIOPERATE*/
	else if(scode==SMULTIOPERATE){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		int operator;
		if(currentToken==TSTAR||currentToken==TDIV||currentToken==TAND){
			if((operator=evaluateWord(currentToken))<0){
				printf("err11\n");return -1;
			}
		}else{
			errPrint("incorrect add operator¥n");
		}
		return tmpToken;
	}
	/*evaluate SFACTOR*/
	else if(scode==SFACTOR){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		int factorType;
		if(currentToken==TNAME){
			return evaluateWord(temp[1]);
		}else if(currentToken==TNUMBER||currentToken==TFALSE||currentToken==TTRUE||currentToken==TSTRING){
			return evaluateWord(temp[2]);
		}else if(currentToken==TLPAREN){
			if(evaluateWord(temp[3])<0){
				printf("err11\n");return -1;
			}
			if((factorType=evaluateWord(temp[4]))<0){
				printf("err11\n");return -1;
			}
			if(evaluateWord(temp[5])<0){
				printf("err11\n");return -1;
			}
			return factorType;
		}else if(currentToken==TNOT){
			if(evaluateWord(temp[6])<0){
				printf("err11\n");return -1;
			}
			if((factorType=evaluateWord(temp[7]))<0){
				printf("err11\n");return -1;
			}
			if(factorType!=TBOOLEAN){
				errPrint("it must be not+TBOOLEAN¥n");
			}
			return factorType;
		}else if(currentToken==TINTEGER||currentToken==TBOOLEAN||currentToken==TCHAR){
			int tempType;
			if((factorType=evaluateWord(temp[8]))<0){
				printf("err11\n");return -1;
			}
			if(evaluateWord(temp[9])<0){
				printf("err11\n");return -1;
			}
			if((tempType=evaluateWord(temp[10]))<0){
				printf("err11\n");return -1;
			}
			if(tempType!=TINTEGER&&tempType!=TBOOLEAN&&tempType!=TCHAR){
				errPrint("state must be SSTANDARD here¥n");
			}
			if(evaluateWord(temp[11])<0){
				printf("err11\n");return -1;
			}
			return factorType;
		}else{
			errPrint("incorrect factor¥n");
		}
	}
	/*evaluate SCONST*/
	else if(scode==SCONST){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		int type;
		for(j=1;j<=temp[0];j++){
			if(validateTopOfSyntax(temp[j])>0){
				if(evaluateWord(temp[j])<0){
					printf("err11\n");return -1;
				}else{
					if(temp[j]==TNUMBER){
						type=TINTEGER;
					}else if(temp[j]==TFALSE||temp[j]==TTRUE){
						type=TBOOLEAN;
					}else if(temp[j]==TSTRING){
						type=TCHAR;
						if(strlen(tmpString)!=1){
							errPrint("String's length must be 1\n");
						}
					}
					return type;
				}
			}
		}
        error("evaluating : syntax Type or Const or Operater");
		return -1;
	}
	/*evaluate SINPUT*/
	else if(scode==SINPUT){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		int tempType;
		if(currentToken==temp[j]){//read
			evaluateWord(temp[j]);
		}else if(currentToken==temp[j+1]){//readln
			evaluateWord(temp[j+1]);
		}else{
			printf("err\n");return -1;
		}
		if(currentToken!=temp[3]){
			return scode;
		}else{ //j=3
			if(evaluateWord(temp[3])<0){
				printf("err\n");return -1;
			}
			if((tempType=evaluateWord(temp[4]))<0){
				printf("err\n");return -1;
			}
			if(tempType!=TINTEGER&&tempType!=TCHAR){
				errPrint("input to TINEGER or TCHAR¥n");
			}
			while(1){
				if(currentToken==temp[7]){
					if(evaluateWord(temp[7])<0){
						printf("err\n");return -1;
					}
					return SINPUT;
				}else if(currentToken==temp[5]){
					if(evaluateWord(temp[5])<0){
						printf("err\n");return -1;
					}
					if((tempType=evaluateWord(temp[6]))<0){
						printf("err\n");return -1;
					}
					if(tempType!=TINTEGER&&tempType!=TCHAR){
						errPrint("input to TINEGER or TCHAR¥n");
					}
				}else{
					errPrint("input incorrect¥n");
				}
			}
		}
	}
	/*evaluate SOUTPUT*/
	else if(scode==SOUTPUT){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		if(currentToken==temp[j]){
			evaluateWord(temp[j]);
		}else if(currentToken==temp[j+1]){
			evaluateWord(temp[j+1]);
		}else{
			printf("err\n");return -1;
		}
		if(currentToken==temp[3]){ //j=3
			for(j=3;j<=4;j++){
				if(evaluateWord(temp[j])<0){
					printf("err\n");return -1;
				}
			}
			while(1){
				if(currentToken==temp[7]){
					if(evaluateWord(temp[7])<0){
						printf("err\n");return -1;
					}
					return SOUTPUT;
				}else if(currentToken==temp[5]){
					for(j=5;j<=6;j++){
						if(evaluateWord(temp[j])<0){
							printf("err\n");return -1;
						}
					}
				}else{
					errPrint("input incorrect¥n");
				}
			}
		}
	}
	/*evaluate S*/
	else if(scode==SOUTASSIGN){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		int tempType;
		if(currentToken==TSTRING&&strlen(string_attr)>1){
			return evaluateWord(TSTRING);
		}else{
			if((tempType=evaluateWord(temp[j++]))<0){
				printf("err\n");return -1;
			}
			if(tempType==TNUMBER){
				tempType=TINTEGER;
			}else if(tempType==TTRUE||tempType==TFALSE){
				tempType=TBOOLEAN;
			}else if(tempType==TSTRING){
				tempType=TCHAR;
			}
			if(tempType!=TINTEGER&&tempType!=TBOOLEAN&&tempType!=TCHAR){
				errPrint("outassign-state must be SSTANDARD¥n");
			}else{
				if(currentToken!=temp[j]){
					return SOUTASSIGN;
				}else{
					for(j=2;j<=3;j++){
						if(evaluateWord(temp[j])<0){
							printf("err\n");return -1;
						}
					}
				}
			}
		}
	}
	/*evaluate SEMPTY*/
	else if (scode==SEMPTY){
		logPutOut(" evaluateSyntax(%s) line:%d\n",scodeStr,lastLineNumber);
		return scode;
	}else{
		printf("err");return(-1);
	}
	return scode;
}

int evaluateToken(int tcode){ //If not match, return -1
	if(currentToken<0){
		return -1;
	}
	if(currentToken!=tcode){
        errPrint("Token not matching:%d&:%d\n",currentToken,tcode);
	}else{
		exScan();
		return tcode;
	}
}

void exScan(){
	memset(tmpString,'\0',strlen(tmpString));
	strncpy(tmpString,string_attr,strlen(string_attr));
	tmpToken=currentToken;
	do{
		currentToken=scan(); // then, new string_attr
	}while(currentToken==0);
	if(tmpToken>=29&&tmpToken<=46){
		fprintf(sFile,"%s",tmpString);
	}else{
		fprintf(sFile,"%s ",tmpString);
	}
}

void pPrint(int option,...){ //
	va_list list;
	int r;
	va_start(list,option);
	if(option==RESETINDENT){
		indentCount=0;
	}else if(option==ALLOWINDENT){ //nothing
	}else if(option==ADDINDENT){
		r=va_arg(list,int);
		indentCount+=r;
	}else{
		error("coding>> newline and indent");
	}
	fprintf(sFile,"\n");
	int i;
	for(i=0;i<indentCount;i++){
		fprintf(sFile,"    "); //4 spaces for indent
	}
	va_end(list);
}

//validateTopOfSyntax
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

void clearWordList(){	//free table
	struct wordList *p, *q;
	return;
	for(p = tempList; p != NULL; p = q) {
		free(p->word);
		q = p->next;
		free(p);
	}
}

