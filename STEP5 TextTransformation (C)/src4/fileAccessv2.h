/*
 * fileAccessv2.h
 *	Version: 1.2
 *  Created on: 2014/11/26
 *  Last Modified on: 2014/12/6
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */

#ifndef FILEACCESS_H_
#define FILEACCESS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "scan.h"
#include "CodingScan.h"
#include "tokenList.h"

extern int init_scan(char *filename);
extern void end_scan();
extern void error(char *mes);
extern void printExistToken();
extern void logPutOut(const char *str,...);
void errPrint(const char *str,...);
extern FILE *fp;
extern char word;
extern char *filename;

#endif /* FILEACCESS_H_ */
