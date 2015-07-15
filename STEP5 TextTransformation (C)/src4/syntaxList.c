/*
 *  syntaxList.c
 *  Version: 1.0
 *  Created on: 2014/10/28
 *  Last Modified on: 2014/10/30
 *  Develop on: OSX 10.9.5, GCC dumpversion 4.2.1
 *				Windows7, Mintty(Cygwin), GCC dunmversion 4.7.2
 */

#include "syntaxList.h"

int *syntaxInner[NUMOFSYNTAX+1]={0,sprogram,sbrock,svardeclare,svarlist,svarname,stype,sstandard,sarray,
					ssubprogdeclare,sprocname,sdummyargument,scompoundstate,ssentence,
					sbranchi,sloop,sproccall,sstatelist,sreturn,sassign,sleft,svar,
					sstate,ssimple,sitem,sfactor,sconst,smultioperate,saddoperate,
					srelatoperate,sinput,soutput,soutassign,sempty};

char *syntaxString[NUMOFSYNTAX+1]={"","sprogram","sbrock","svardeclare","svarlist","sname","stype","sstandard","sarray",
					"ssubprogdeclare","sprocname","sdummyargument","scompoundstate","ssentence",
					"sbranchi","sloop","sproccall","sstatelist","sreturn","sassign","sleft","svar",
					"sstate","ssimple","sitem","sfactor","sconst","smultioperate","saddoperate",
					"srelatoperate","sinput","soutput","soutassign","sempty"};

int sprogram[6]={5,TPROGRAM,TNAME,TSEMI,SBROCK,TDOT};
int sbrock[4]={3,SVARDECLARE,SSUBPROGDECLARE,SCOMPOUNDSTATE};
int svardeclare[10]={9,TVAR,SVARLIST,TCOLON,STYPE,TSEMI,SVARLIST,TCOLON,STYPE,TSEMI};
int svarlist[]={2,SVARNAME,TCOMMA};
int svarname[]={1,TNAME};
int stype[]={2,SSTANDARD,SARRAY};
int sstandard[]={3,TINTEGER,TBOOLEAN,TCHAR};
int sarray[]={6,TARRAY,TLSQPAREN,TNUMBER,TRSQPAREN,TOF,SSTANDARD};
int ssubprogdeclare[]={7,TPROCEDURE,SPROCNAME,SDUMMYARGUMENT,TSEMI,SVARDECLARE,SCOMPOUNDSTATE,TSEMI};
int sprocname[]={1,TNAME};
int sdummyargument[]={9,TLPAREN,SVARLIST,TCOLON,STYPE,TSEMI,SVARLIST,TCOLON,STYPE,TRPAREN};
int scompoundstate[]={5,TBEGIN,SSENTENCE,TSEMI,SSENTENCE,TEND};
int ssentence[]={11,SASSIGN,SBRANCHI,SLOOP,SPROCCALL,SRETURN,SINPUT,SINPUT,SOUTPUT,SOUTPUT,SCOMPOUNDSTATE,SEMPTY};
int sbranchi[]={6,TIF,SSTATE,TTHEN,SSENTENCE,TELSE,SSENTENCE};
int sloop[]={4,TWHILE,SSTATE,TDO,SSENTENCE};
int sproccall[]={5,TCALL,SPROCNAME,TLPAREN,SSTATELIST,TRPAREN};
int sstatelist[]={3,SSTATE,TCOMMA,SSTATE};
int sreturn[]={1,TRETURN};
int sassign[]={3,SLEFT,TASSIGN,SSTATE};
int sleft[]={1,SVAR};
int svar[]={4,SVARNAME,TLSQPAREN,SSTATE,TRSQPAREN};
int sstate[]={3,SSIMPLE,SRELATOPERATE,SSIMPLE};
int ssimple[]={5,TPLUS,TMINUS,SITEM,SADDOPERATE,SITEM};
int sitem[]={3,SFACTOR,SMULTIOPERATE,SFACTOR};
int sfactor[]={11,SVAR,SCONST,TLPAREN,SSTATE,TRPAREN,TNOT,SFACTOR,SSTANDARD,TLPAREN,SSTATE,TRPAREN};
int sconst[]={4,TNUMBER,TFALSE,TTRUE,TSTRING};
int smultioperate[]={3,TSTAR,TDIV,TAND};
int saddoperate[]={3,TPLUS,TMINUS,TOR};
int srelatoperate[]={6,TEQUAL,TNOTEQ,TLE,TLEEQ,TGR,TGREQ};
int sinput[]={7,TREAD,TREADLN,TLPAREN,SVAR,TCOMMA,SVAR,TRPAREN};
int soutput[]={7,TWRITE,TWRITELN,TLPAREN,SOUTASSIGN,TCOMMA,SOUTASSIGN,TRPAREN};
int soutassign[]={4,SSTATE,TCOLON,TNUMBER,TSTRING};
int sempty[]={0};
