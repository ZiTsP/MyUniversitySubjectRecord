/*
 * sScan.h
 *	Version: 1
 *  Created on: 2014/11/1
 *	Last Modified on: 2014/11/17
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */

#ifndef SSCAN_H_
#define SSCAN_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "syntaxList.h"
#include "fileAccessv2.h"
#include "scan.h"
#include "tokenList.h"
#include "list.h"

#define NEWLINE 0
#define INDENT 1
#define SCAN -1
extern int ppScan();
struct wordList{
	char *word;
	int token;
	struct wordList *next;
};

#endif /* SSCAN_H_ */
