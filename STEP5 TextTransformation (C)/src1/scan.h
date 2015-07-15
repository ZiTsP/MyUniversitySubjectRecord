/*
 * scan.h
 *  Version: 2.0
 *  Created on: 2014/10/13
 *  Last Modified on: 2014/10/16
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */

#ifndef SCAN_H_
#define SCAN_H_
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tokenList.h"
#include "fileAccess.h"

#define SET 1
#define RESET 0

extern int init_scan(char *filename);
extern int scan(void);
extern int num_attr;
extern char string_attr[];
extern int lastLineNumber;
extern int get_linenum(void);
extern void end_scan(void);

extern int isSign(char s);
extern int checkWSign(char *s);
extern int checkToken(char *s);
extern int isComment(char s);
extern int isDefString(char s);
extern int isSeparater(char s);


#endif /* SCAN_H_ */
