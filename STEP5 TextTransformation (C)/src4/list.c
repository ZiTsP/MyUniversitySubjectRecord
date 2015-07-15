/*
 * list.c
 *	Version: 3.3
 *  Created on: 2014/12/06
 *  Last Modified on: 2014/12/19
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */
#include "list.h"

int wordCount;
int registerTrriger;
#define ON 1
#define OFF 0
struct idRoot idList;

void initList() {	//reset table
	struct function *f;
	if((f=(struct function *)malloc(sizeof(struct function))) == NULL) {
		printf("can not malloc in countup\n");return;
	}
	idList.prog=f;
}
void setupProgram(char *np){
	initList();
	struct variable *p;
	char *cp;
	if((p = (struct variable *)malloc(sizeof(struct variable))) == NULL) {
		printf("can not malloc in countup\n");return;
	}
	if((cp = (char *)malloc(strlen(np)+1)) == NULL) {
		printf("can not malloc-2 in countup\n");return;
	}
	strcpy(cp,np);
	p->name=cp;
	idList.prog->name=p;idList.func=NULL;idList.var=NULL;
}

struct variable *search(char *np,char *scope){	//search "np"
	struct variable *vp;	//var
	struct function *fp;	//func
	struct variable *fpArg;
	struct variable *fpVar;
	fp=idList.func;
	vp=idList.var;
	if(strcmp(scope,idList.prog->name->name)==0){//highScope
		for(vp=idList.var;vp!= NULL; vp = vp->nextVar){
			if(strcmp(np, vp->name)==0){
				return(vp);
			}
		}
		for(fp=idList.func;fp!= NULL;fp=fp->nextFunc){	//function
			if(strcmp(np, fp->name->name)==0){
				return(fp->name);
			}
		}
	}else{//low scope (function var -> hole var)
		for(fp=idList.func;fp!= NULL;fp=fp->nextFunc){	//function
			if(strcmp(scope,fp->name->name)==0){
				fpArg=fp->arg;fpVar=fp->var;
				for(;fpArg!= NULL;fpArg=fpArg->nextVar){	//function arg
					if(strcmp(np,fpArg->name)==0){
						return(fpArg);
					}
				}
				for(;fpVar!= NULL;fpVar=fpVar->nextVar){	//function var
					if(strcmp(np,fpVar->name)==0){
						return(fpVar);
					}
				}
				if(registerTrriger==ON){
					return NULL;
				}
			}
		}
		for(;vp!= NULL; vp = vp->nextVar){//hole var
			if(strcmp(np, vp->name)==0){
				return(vp);
			}
		}
		for(;fp!= NULL;fp=fp->nextFunc){//function name
			if(strcmp(np, fp->name->name)==0){
				return(fp->name);
			}
		}
	}
	return(NULL);
}

int registerList(char *np,int npType,int arrayNum,int defLine,int position,char *scope){	//add count "np"
	registerTrriger=ON;
	struct variable *vp;
	struct function *fp;
	char *cp;
	if(strcmp(scope,idList.prog->name->name)==0){//register in highScope
		if(position==POSI_FUNC){
			if(search(np,scope)!=NULL){
				errPrint("double in scope\n");
			}
			if((vp=(struct variable *)malloc(sizeof(struct variable)))==NULL) {
				printf("can not malloc variable in countup\n");return -1;
			}
			if((fp=(struct function *)malloc(sizeof(struct function)))==NULL) {
				printf("can not malloc function in countup\n");return -1;
			}
			if((cp = (char *)malloc(strlen(np)+1)) == NULL) {
				printf("can not malloc char in countup\n");return -1;
			}
			strcpy(cp,np);
			vp->name=cp;vp->type=npType;vp->arrayNum=arrayNum;vp->def=defLine;vp->nextVar=NULL;
			fp->name=vp;fp->arg=NULL;fp->var=NULL;fp->nextFunc=NULL;
			if(idList.func!=NULL){//connect function and list
				idList.lastfunc->nextFunc=fp;
			}else{
				idList.func=fp;
			}
			idList.lastfunc=fp;
		}else if(position==POSI_VAR){
			if(search(np,scope)!=NULL){
				errPrint("double in scope\n");
			}
			if((vp=(struct variable *)malloc(sizeof(struct variable)))==NULL) {
				printf("can not malloc variable in countup\n");return -1;
			}
			if((cp = (char *)malloc(strlen(np)+1)) == NULL) {
				printf("can not malloc char in countup\n");return -1;
			}
			strcpy(cp,np);
			vp->name=cp;vp->type=npType;vp->arrayNum=arrayNum;vp->def=defLine;vp->nextVar=NULL;
			if(idList.var!=NULL){//connect function and list
				idList.lastvar->nextVar=vp;
			}else{
				idList.var=vp;
			}
			idList.lastvar=vp;
		}
	}else{//register in localScope
		if(position==POSI_ARG){
			if(search(np,scope)!=NULL){
				errPrint("double in scope\n");
			}
			if((vp=(struct variable *)malloc(sizeof(struct variable)))==NULL) {
				printf("can not malloc variable in countup\n");return -1;
			}
			if((cp = (char *)malloc(strlen(np)+1)) == NULL) {
				printf("can not malloc char in countup\n");return -1;
			}
			strcpy(cp,np);
			vp->name=cp;vp->type=npType;vp->arrayNum=arrayNum;vp->def=defLine;vp->nextVar=NULL;
			for(fp=idList.func;fp!= NULL;fp=fp->nextFunc){//function name
				if(strcmp(scope, fp->name->name)==0){
					if(fp->arg!=NULL){
						fp->lastarg->nextVar=vp;
					}else{
						fp->arg=vp;
					}
					fp->lastarg=vp;
				}
			}
		}else if(position==POSI_VAR){
			if(search(np,scope)!=NULL){
				errPrint("double in scope\n");
			}
			if((vp=(struct variable *)malloc(sizeof(struct variable)))==NULL) {
				printf("can not malloc variable in countup\n");return -1;
			}
			if((cp = (char *)malloc(strlen(np)+1)) == NULL) {
				printf("can not malloc char in countup\n");return -1;
			}
			strcpy(cp,np);
			vp->name=cp;vp->type=npType;vp->arrayNum=arrayNum;vp->def=defLine;vp->nextVar=NULL;
			for(fp=idList.func;fp!= NULL;fp=fp->nextFunc){
				if(strcmp(scope, fp->name->name)==0){
					if(fp->var!=NULL){
						fp->lastvar->nextVar=vp;
					}else{
						fp->var=vp;
					}
					fp->lastvar=vp;
				}
			}
		}
	}
	registerTrriger=OFF;
	return 1;
}

struct variable *countup(char *np,int useLine,char *scope){	//add count "np"
	struct variable *p;
	struct occurrence *occur;
	if((p=search(np,scope))==NULL){ //for not first time
		errPrint("havenot dec\n");
	}else {
		if((occur=(struct occurrence *)malloc(sizeof(struct occurrence)))==NULL) {
			errPrint("can not malloc in countup\n");
		}
		occur->nextOccur=NULL;
		occur->use=useLine;
		if(p->occur==NULL){
			p->occur=occur;
		}else{
			p->lastoccur->nextOccur=occur;
		}
		p->lastoccur=occur;
	}
	return p;
}

void release() {	//free table
	struct variable *p,*q;
	struct function *f,*g;
	if(idList.prog==NULL)return;
	p=idList.prog->var;//free hole var
	for(;p!=NULL;p=q) {
		free(p->name);
		q=p->nextVar;
		free(p);
	}
	free(idList.prog->name);free(idList.prog);
	f=idList.func;
	for(;f!=NULL;f=g) {
		p=f->arg;
		for(;p!=NULL;p=q) {
			free(p->name);q=p->nextVar;free(p);
		}
		p=f->var;
		for(;p!=NULL;p=q) {
			free(p->name);q=p->nextVar;free(p);
		}
		free(f->name);g=f->nextFunc;free(f);
	}
}

void printList(){
	FILE *rp;
	struct variable *p;
	struct function *f;
	struct occurrence *o;
//	rp=fopen("resultPrint.txt","w");
	rp=stdout;
	if(rp==NULL){
		exit(0);
	}
	fprintf(rp,"**(P):ProgramName (V):VariableName (F):FunctionName\n  (Fa):ArgumentInCurrentFunction (Fv):VariavleInCurrentFunction\n\n");
	fprintf(rp,"%14s\t|%11s   |%3s|%5s%s","NAME","TYPE","DEF","USE","\n");
	fprintf(rp,"(P)%12s\t|%14s|   |",idList.prog->name->name,"PROGRAM");
	for(p=idList.var;p!=NULL;p=p->nextVar){
		if(p->arrayNum==0){
			fprintf(rp,"\n(V)%12s\t|%14s|%3d|",p->name,tokenString[p->type],p->def);
			for(o=p->occur;o!=NULL;o=o->nextOccur){
				fprintf(rp,"%d,",o->use);
			}
		}
		else{
			fprintf(rp,"\n(V)%9s[%d]\t|%7s(array)|%3d|",p->name,p->arrayNum,tokenString[p->type],p->def);
			for(o=p->occur;o!=NULL;o=o->nextOccur){
				fprintf(rp,"%d,",o->use);
			}
		}
	}
	for(f=idList.func;f!=NULL;f=f->nextFunc){
		fprintf(rp,"\n(F)%12s\t|%14s|%3d|",f->name->name,"FUNCTION",f->name->def);
		for(o=f->name->occur;o!=NULL;o=o->nextOccur){
			fprintf(rp,"%d,",o->use);
		}
		for(p=f->arg;p!=NULL;p=p->nextVar){
			fprintf(rp,"\n(Fa)%11s\t|%14s|%3d|",p->name,tokenString[p->type],p->def);
			for(o=p->occur;o!=NULL;o=o->nextOccur){
				fprintf(rp,"%d,",o->use);
			}
		}
		for(p=f->var;p!=NULL;p=p->nextVar){
			if(p->arrayNum==0){
				fprintf(rp,"\n(V)%11s\t|%14s|%3d|",p->name,tokenString[p->type],p->def);
				for(o=p->occur;o!=NULL;o=o->nextOccur){
					fprintf(rp,"%d,",o->use);
				}
			}
			else{
				fprintf(rp,"\n(V)%8s[%d]\t|%7s(array)|%3d|",p->name,p->arrayNum,tokenString[p->type],p->def);
				for(o=p->occur;o!=NULL;o=o->nextOccur){
					fprintf(rp,"%d,",o->use);
				}
			}
		}
	}
	fprintf(rp,"\n");
//	fclose(rp);
}

