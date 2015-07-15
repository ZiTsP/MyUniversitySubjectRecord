/*
 * CodingScan.h
 *
 *  Created on: 2015/01/22
 */

#ifndef CODINGSCAN_H_
#define CODINGSCAN_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "syntaxList.h"
#include "fileAccessv2.h"
#include "scan.h"
#include "tokenList.h"
#include "list.h"

#define FILETYPE "csl"
#define CSL

FILE *cFile; //out put code file
// *filename (global)
char cLabel[5];

#define LD(tag,str) fprintf(cFile,"%s\tLD\t%s\n",tag,str)
#define LD2(tag,str1,str2) fprintf(cFile,"%s\tLD\t%s,%s\n",tag,str1,str2)
#define ST(tag,str) fprintf(cFile,"%s\tST\t%s\n",tag,str)
#define ST2(tag,str1,str2) fprintf(cFile,"%s\tST\t%s,%s\n",tag,str1,str2)
#define LAD(tag,str1,str2) fprintf(cFile,"%s\tLAD\t%s,%s\n",tag,str1,str2)
#define ADDA(tag,str) fprintf(cFile,"%s\tADDA\t%s\n",tag,str)
#define ADDL(tag,str) fprintf(cFile,"%s\tADDL\t%s\n",tag,str)
#define SUBA(tag,str) fprintf(cFile,"%s\tSUBA\t%s\n",tag,str)
#define SUBL(tag,str) fprintf(cFile,"%s\tSUBL\t%s\n",tag,str)
#define OR(tag,str) fprintf(cFile,"%s\tOR\t%s\n",tag,str)
#define XOR(tag,str) fprintf(cFile,"%s\tXOR\t%s\n",tag,str)
#define CPA(tag,str) fprintf(cFile,"%s\tCPA\t%s\n",tag,str)
#define CPL(tag,str) fprintf(cFile,"%s\tCPL\t%s\n",tag,str)
#define SLA(tag,str) fprintf(cFile,"%s\tSLA\t%s\n",tag,str)
#define SRA(tag,str) fprintf(cFile,"%s\tSRA\t%s\n",tag,str)
#define SLL(tag,str) fprintf(cFile,"%s\tSLL\t%s\n",tag,str)
#define SRL(tag,str) fprintf(cFile,"%s\tSRL\t%s\n",tag,str)
#define JPL(tag,str) fprintf(cFile,"%s\tJPL\t%s\n",tag,str)
#define JMI(tag,str) fprintf(cFile,"%s\tJMI\t%s\n",tag,str)
#define JNZ(tag,str) fprintf(cFile,"%s\tJNZ\t%s\n",tag,str)
#define JZE(tag,str) fprintf(cFile,"%s\tJZE\t%s\n",tag,str)
#define JOV(tag,str) fprintf(cFile,"%s\tJOV\t%s\n",tag,str)
#define JUMP(tag,str) fprintf(cFile,"%s\tJUMP\t%s\n",tag,str)
#define PUSH(tag,str) fprintf(cFile,"%s\tPUSH\t%s\n",tag,str)
#define POP(tag,str) fprintf(cFile,"%s\tPOP\t%s\n",tag,str)
#define CALL(tag,str) fprintf(cFile,"%s\tCALL\t%s\n",tag,str)
#define RET(tag) fprintf(cFile,"%s\tRET\n",tag)
#define SVC(tag,str) fprintf(cFile,"%s\tSVC\t%s\n",tag,str)
#define NOP(tag) fprintf(cFile,"%s\tNOP\n",tag)
#define START(tag) fprintf(cFile,"%s\tSATRT\n",tag)
#define END(tag) fprintf(cFile,"%s\tEND\n",tag)
#define DS(tag,str) fprintf(cFile,"%s\tDS\t%s\n",tag,str)
#define DC(tag,str) fprintf(cFile,"%s\tDC\t%s\n",tag,str)//
#define IN(tag,str) fprintf(cFile,"%s\tIN\t%s\n",tag,str)
#define OUT(tag,str) fprintf(cFile,"%s\tOUT\t%s\n",tag,str)
#define RPUSH(tag,str) fprintf(cFile,"%s\tRPUSH\t%s\n",tag,str)
#define RPOP(tag,str) fprintf(cFile,"%s\tRPOP\t%s\n",tag,str)
#define MULA(tag,str) fprintf(cFile,"%s\tMULA\t%s\n",tag,str)
#define MULL(tag,str) fprintf(cFile,"%s\tMULL\t%s\n",tag,str)
#define DIVA(tag,str) fprintf(cFile,"%s\tDIVA\t%s\n",tag,str)
#define DIVL(tag,str) fprintf(cFile,"%s\tDIVL\t%s\n",tag,str)
#define TAGPRINT(str) fprintf(cFile,"%s\n",str)

#define COMBTAG(str1,str2) str1##str2


#define NEWLINE 0
#define INDENT 1
#define SCAN -1
extern int ppScan();
extern char tmpString[MAXSTRSIZE];
struct wordList{
	char *word;
	int token;
	struct wordList *next;
	struct wordList *before;
};
#endif /* CODINGSCAN_H_ */
