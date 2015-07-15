/*
 * idList.h
 *	Version: 1.0
 *  Created on: 2014/10/16
 *	Last Modified on: 2014/10/16
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */

#include "idList.h"

struct ID *idroot;

void init_idtab() {	//reset table
	idroot = NULL;
}

struct ID *search_idtab(char *np) {	//search "np"
	struct ID *p;
	for(p = idroot; p != NULL; p = p->nextp) {
		if(strcmp(np, p->name) == 0){
			return(p);
		}
	}
	return(NULL);
}

void id_countup(char *np) {	//add count "np"
	struct ID *p;
	char *cp;
	if((p = search_idtab(np)) != NULL){ //for the first time
		p->count++;
	}else {
		if((p = (struct ID *)malloc(sizeof(struct ID))) == NULL) {
			printf("can not malloc in id_countup\n");
			return;
		}
		if((cp = (char *)malloc(strlen(np)+1)) == NULL) {
			printf("can not malloc-2 in id_countup\n");
			return;
		}
		strcpy(cp, np);
		p->name = cp;
		p->count = 1;
		p->nextp = idroot;
		idroot = p;
	}
}

void print_idtab() {	//out put table
	struct ID *p;
	for(p = idroot; p != NULL; p = p->nextp) {
		if(p->count != 0)
			printf("\t\"NAME\" \"%s\"\t%d\n", p->name, p->count);
	}
}

void release_idtab() {	//free table
	struct ID *p, *q;
	for(p = idroot; p != NULL; p = q) {
		free(p->name);
		q = p->nextp;
		free(p);
	}
}

