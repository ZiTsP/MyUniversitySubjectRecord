/*
 * list.h
 *
 *  Created on: 2014/12/06
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "syntaxList.h"
#include "tokenList.h"
#include "fileAccessv2.h"
//#define ON 1
//#define OFF 0
//
#define POSI_ARG 0
#define POSI_VAR 1
#define POSI_FUNC -1
struct occurrence{
	int use;
	struct occurrence *nextOccur;
};
struct function{
	struct variable *name; //about function
	struct variable *arg;
	struct variable *lastarg;
	struct variable *var;
	struct variable *lastvar;
	struct function *nextFunc;
};
struct variable{
	char *name;
	int num;
//	struct arrayChain *arrayElement;
	int type;
	int arrayNum;
	int def;
	struct occurrence *occur;
	struct occurrence *lastoccur;
	struct variable *nextVar;
};
struct idRoot{
	struct function *prog;
	struct variable *var;
	struct variable *lastvar;
	struct function *func;
	struct function *lastfunc;
};
struct arrayChain{
	char str;
	int num;
	struct arrayChain *next;
};
extern void initList();
extern void release();
extern void setupProgram(char *np);
struct variable *search(char *np,char *scope);
int registerList(char *np,int npType,int arrayNum,int defLine,int position,char *scope);
void printList();
struct variable *countup(char *np,int useLine,char *scope);
extern char programName[32];
//extern struct function *scope;
extern int position;
extern struct idRoot idList;

#endif /* LIST_H_ */
