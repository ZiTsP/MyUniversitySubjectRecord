/*
 * fileAccess.h
 *	Version: 1.0
 *  Created on: 2014/10/13
 *  Last Modified on: 2014/10/13
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */

#ifndef FILEACCESS_H_
#define FILEACCESS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scan.h"
#include "tokenList.h"

extern int init_scan(char *filename);
extern void end_scan();
extern void error(char *mes);
extern void printExistToken();
extern FILE *fp;
extern char word;
extern char *filename;

#endif /* FILEACCESS_H_ */
