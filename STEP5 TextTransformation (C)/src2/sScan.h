/*
 * sScan.h
 *	Version: 
 *  Created on: 2014/11/16
 *	Last Modified on: 2014/11/16
 */

#ifndef SSCAN_H_
#define SSCAN_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "syntaxList.h"
#include "fileAccess.h"
#include "scan.h"
#include "tokenList.h"

#define NEWLINE 0
#define INDENT 1
#define SCAN -1
extern int ppScan();

#endif /* SSCAN_H_ */
