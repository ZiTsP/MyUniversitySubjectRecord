/*
 *  syntaxList.h
 *  Version: 1.0
 *  Created on: 2014/10/28
 *  Last Modified on: 2014/10/30
 *  Develop on: OSX 10.9.5, GCC dumpversion 4.2.1
 *				Windows7, Mintty(Cygwin), GCC dunmversion 4.7.2
 */

#ifndef SYNTAXLIST_H_	//include Gard
#define SYNTAXLIST_H_ //include Gard

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tokenList.h"

#define MAXSTRSIZE 1024

#define SPROGRAM		1+NUMOFTOKEN//program
#define SBROCK			2+NUMOFTOKEN//brock
#define SVARDECLARE		3+NUMOFTOKEN//variable declaration
#define SVARLIST		4+NUMOFTOKEN//varibale list
#define SVARNAME		5+NUMOFTOKEN//varibale name
#define STYPE			6+NUMOFTOKEN//type
#define SSTANDARD		7+NUMOFTOKEN//
#define SARRAY			8+NUMOFTOKEN//array
#define SSUBPROGDECLARE	9+NUMOFTOKEN//sub program declaration
#define SPROCNAME		10+NUMOFTOKEN//procedure name
#define SDUMMYARGUMENT	11+NUMOFTOKEN//part of dummy argument
#define SCOMPOUNDSTATE	12+NUMOFTOKEN//compound statement
#define SSENTENCE		13+NUMOFTOKEN//sentence
#define SBRANCHI		14+NUMOFTOKEN//"if" statement
#define SLOOP			15+NUMOFTOKEN//"while" statement
#define SPROCCALL		16+NUMOFTOKEN//procedure call statement
#define SSTATELIST		17+NUMOFTOKEN//statement list
#define SRETURN			18+NUMOFTOKEN//"return" statement
#define SASSIGN			19+NUMOFTOKEN//assignment statement
#define SLEFT			20+NUMOFTOKEN//left side
#define SVAR			21+NUMOFTOKEN//variable
#define SSTATE			22+NUMOFTOKEN//statement
#define SSIMPLE			23+NUMOFTOKEN//simple statement
#define SITEM			24+NUMOFTOKEN//item
#define SFACTOR			25+NUMOFTOKEN//factor
#define SCONST			26+NUMOFTOKEN//constant number
#define SMULTIOPERATE	27+NUMOFTOKEN//multiply operator
#define SADDOPERATE		28+NUMOFTOKEN//addition operator
#define SRELATOPERATE	29+NUMOFTOKEN//relational oerator
#define SINPUT			30+NUMOFTOKEN//input sentence
#define SOUTPUT			31+NUMOFTOKEN//output sentence
#define SOUTASSIGN		32+NUMOFTOKEN//output assign
#define SEMPTY			33+NUMOFTOKEN//empty sentence

#define NUMOFSYNTAX	34

extern int *syntaxInner[NUMOFSYNTAX+1];
extern char *syntaxString[NUMOFSYNTAX+1];
extern int sprogram[];
extern int sbrock[];
extern int svardeclare[];
extern int svarlist[];
extern int svarname[];
extern int stype[];
extern int sstandard[];
extern int sarray[];
extern int ssubprogdeclare[];
extern int sprocname[];
extern int sdummyargument[];
extern int scompoundstate[];
extern int ssentence[];
extern int sbranchi[];
extern int sloop[];
extern int sproccall[];
extern int sstatelist[];
extern int sreturn[];
extern int sassign[];
extern int sleft[];
extern int svar[];
extern int sstate[];
extern int ssimple[];
extern int sitem[];
extern int sconst[];
extern int sfactor[];
extern int scont[];
extern int smultioperate[];
extern int saddoperate[];
extern int srelatoperate[];
extern int sinput[];
extern int soutput[];
extern int soutassign[];
extern int sempty[];
#endif
