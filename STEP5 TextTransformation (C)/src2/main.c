/*
 * main.c
 *	Version: 
 *  Created on: 2014/11/16
 *	Last Modified on: 2014/11/16
 */

#include <stdio.h>
#include <stdlib.h>

#include "tokenList.h"
#include "fileAccess.h"
#include "scan.h"
#include "idList.h"
#include "sScan.h"

int main(int argc, char *argv[]){
	if(argc!=2){	//needs filename for command line argument
		fprintf(stderr,"chose a program name\n");
		exit(0);
	}
	filename=argv[1];
	int c;
	if((c=init_scan(filename))<0){ //file open
		error("init_scan;cannot open");
	}
	if(ppScan()<0){ //file open
		printf("ERROR END\n");
	}
	end_scan();	/*FROM "fileAccess.c*/
	printf("END\n");
	return EXIT_SUCCESS;
}
