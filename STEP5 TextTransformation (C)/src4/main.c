/*
 * main.c
 *	Version: 1.0
 *  Created on: 2014/11/16
 *  Last Modified on: 2014/11/16
 *  Develop on:Ubuntu 14.04LTE , GCC dumpversion 4.8
 */
#include <stdio.h>
#include <stdlib.h>

#include "tokenList.h"
#include "fileAccessv2.h"
#include "scan.h"
#include "list.h"
#include "CodingScan.h"

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
//	printf("\nEND");
	return EXIT_SUCCESS;
}
