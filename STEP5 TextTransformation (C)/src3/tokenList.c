/*
 * tokenList.c
 *	Version: 1.0
 *  Created on: 2014/10/09
 *  Last Modified on: 2014/10/13
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */

#include "tokenList.h"


KEY key[KEYWORDSIZE] = {
	{"and", 		TAND		},
	{"array",		TARRAY		},
	{"begin",		TBEGIN		},
	{"boolean",	TBOOLEAN	},
	{"call",		TCALL		},
	{"char",		TCHAR		},
	{"div",		TDIV		},
	{"do",			TDO			},
	{"else",		TELSE		},
	{"end",		TEND		},
	{"false",		TFALSE		},
	{"if",			TIF			},
	{"integer",	TINTEGER	},
	{"not",		TNOT		},
	{"of",			TOF			},
	{"or",			TOR			},
	{"procedure", TPROCEDURE	},
	{"program",	TPROGRAM	},
	{"read",		TREAD		},
	{"readln",		TREADLN	},
	{"return", 	TRETURN	},
	{"then",		TTHEN		},
	{"true",		TTRUE		},
	{"var",		TVAR		},
	{"while",		TWHILE		},
	{"write",		TWRITE  	},
	{"writeln",	TWRITELN	}
};

KEY sign[SIGNSIZE] = {
	{"+",		TPLUS		},
	{"-",		TMINUS		},
	{"*",		TSTAR		},
	{"=",		TEQUAL		},
	{"(",		TLPAREN		},
	{")",		TRPAREN		},
	{"[",		TLSQPAREN	},
	{"]",		TRSQPAREN	},
	{".",		TDOT		},
	{",",		TCOMMA		},
	{";",		TSEMI		},
	{"<",		TLE			},
	{">",		TGR			},
	{":",		TCOLON		},
	{"<>",		TNOTEQ		},
	{"<=",		TLEEQ		},
	{">=",		TGREQ		},
	{":=",		TASSIGN		}
};

char *tokenString[NUMOFTOKEN+1]={
		"",
		"NAME", "program", "var", "array", "of", "begin", "end", "if", "then", "else", "procedure", "return", "call",
		"while", "do", "not", "or", "div", "and", "char", "integer", "boolean", "readln",
		"writeln", "true", "false", "NUMBER", "STRING", "+", "-", "*", "=", "<>",
		"<", "<=", ">", ">=", "(", ")", "[", "]", ":=", ".",
		",", ":", ";", "read","write"
};

int tokenCount[NUMOFTOKEN+1]={0};

