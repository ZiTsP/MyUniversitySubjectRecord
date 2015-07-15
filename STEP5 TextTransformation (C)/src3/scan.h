/*
 * scan.h
 *  Version: 3.0
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
#include "fileAccessv2.h"

#define SET 1
#define RESET 0

extern int init_scan(char *filename);
extern int scan(void);
extern int num_attr;
extern char string_attr[];
extern int lastLineNumber;
extern int get_linenum(void);
extern void end_scan(void);



#endif /* SCAN_H_ */
