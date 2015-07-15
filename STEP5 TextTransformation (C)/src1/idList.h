/*
 * idList.h
 *	Version: 1.0
 *  Created on: 2014/10/16
 *	Last Modified on: 2014/10/16
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */

#ifndef IDLIST_H_
#define IDLIST_H_

#include "fileAccess.h"

extern struct ID{
	char *name;
	int count;
	struct ID *nextp;
} *idroot;

extern void init_idtab();
extern struct ID *search_idtab(char *np);
extern void id_countup(char *np);
extern void print_idtab();
extern void release_idtab();

#endif /* IDLIST_H_ */
