/*
 * tokenList.h
 *	Version: 1.0
 *  Created on: 2014/10/09
 *  Last Modified on: 2014/10/13
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */

#ifndef TOKENLIST_H_	//include Gard
#define TOKENLIST_H_ //include Gard

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXSTRSIZE 1024

/* Token */
#define	TNAME		1	/* name (alphabet and something) */
#define	TPROGRAM	2	/* program*/
#define	TVAR		3	/* var*/
#define	TARRAY		4	/* array*/
#define	TOF			5	/* of*/
#define	TBEGIN		6	/* begin*/
#define	TEND		7  	/* end*/
#define	TIF			8  	/* if*/
#define	TTHEN		9	/* then*/
#define	TELSE		10	/* else*/
#define	TPROCEDURE	11	/* procedure*/
#define	TRETURN		12	/* return*/
#define	TCALL		13	/* call*/
#define	TWHILE		14	/* while*/
#define	TDO			15 	/* do*/
#define	TNOT		16	/* not*/
#define	TOR			17	/* or*/
#define	TDIV		18 	/* div*/
#define	TAND		19 	/* and*/
#define	TCHAR		20	/* char*/
#define	TINTEGER	21	/* integer*/
#define	TBOOLEAN	22 	/* boolean*/
#define	TREADLN		23	/* readln*/
#define	TWRITELN	24	/* writeln*/
#define	TTRUE		25	/* true*/
#define	TFALSE		26	/* false*/
#define	TNUMBER		27	/* natural number */
#define	TSTRING		28	/* words string */
#define	TPLUS		29	/* + */
#define	TMINUS		30 	/* - */
#define	TSTAR		31 	/* * */
#define	TEQUAL		32 	/* = */
#define	TNOTEQ		33 	/* <> */
#define	TLE			34 	/* < */
#define	TLEEQ		35 	/* <= */
#define	TGR			36	/* > */
#define	TGREQ		37	/* >= */
#define	TLPAREN		38 	/* ( */
#define	TRPAREN		39 	/* ) */
#define	TLSQPAREN	40	/* [ */
#define	TRSQPAREN	41 	/* ] */
#define	TASSIGN		42	/* := */
#define	TDOT		43 	/* . */
#define	TCOMMA		44	/* , */
#define	TCOLON		45	/* : */
#define	TSEMI		46	/* ; */
#define	TREAD		47	/* read*/
#define	TWRITE		48	/* write*/

#define NUMOFTOKEN	48
#define KEYWORDSIZE	27 //special words in token
#define KEYSTRINGSIZE 3 //name, natural number and word string
#define SIGNSIZE NUMOFTOKEN-KEYWORDSIZE-KEYSTRINGSIZE
#define ASIGNSIZE 14 //single sine defined
#define WSIGNSIZE 4 //some of the signs by two sign words

typedef struct {
	char * keyword;
	int keytoken;
}KEY;

extern KEY key[KEYWORDSIZE];
extern KEY sign[NUMOFTOKEN-KEYWORDSIZE-KEYSTRINGSIZE];
extern char *tokenString[];
extern int tokenCount[];

#endif //include Gard
