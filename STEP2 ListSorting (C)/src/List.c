#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct StRec studentRecord;
struct StRec{
	float gpa;
	int credit;
	char name[200];
	studentRecord *next;
	studentRecord *left;
	studentRecord *right;
};

studentRecord* input(char *argv[]);
void output(studentRecord *head,char *argv[]);

void sort(studentRecord *listHead,char *argv[]);
int comp_gpa(const void *a,const void *b);
int comp_cre(const void *a,const void *b);
int comp_name(const void *a,const void *b);
void oSort(studentRecord *student,int compareType(const void*, const void*));


int main(int argc,char *argv[]) {
	if(argc!=4){
		fprintf(stderr,"argument error.");
		exit (0);
	}
	studentRecord *head=(studentRecord*)malloc(sizeof(studentRecord)*1);
	head->next=input(argv);

	clock_t clockStart,clockEnd;
	clockStart =clock();
	sort(head,argv);
	clockEnd =clock();

	output(head,argv);
    free(head);
	printf("run time : %f",(double)(clockEnd-clockStart)/CLOCKS_PER_SEC);
	return 0;
}

studentRecord* input(char *argv[]){
	FILE *fo;
	if((fo=fopen(argv[2],"r"))==NULL){
		fprintf(stderr,"error.cant open %s",argv[2]);
		exit (0);
	}
	studentRecord *p,*q,*f;
	f=(studentRecord*)malloc(sizeof(studentRecord)*1);
	p=f;
	int ret;
	while((ret=fscanf(fo,"%f %d %s",&p->gpa,&p->credit,p->name))!=EOF){
		studentRecord *temp=(studentRecord*)malloc(sizeof(studentRecord)*1);
		p->next=temp;
		q=p;
		p=temp;
	}
	q->next=NULL;
	fclose(fo);
	return (f);
}

void output(studentRecord *p,char *argv[]){
	FILE *fc;
	if(	(fc=fopen(argv[3],"w"))==NULL){
		fprintf(stderr,"error.cant open %s",argv[3]);
		exit (0);
	}
	p=p->next;
	while(p!=NULL){
		fprintf(fc,"%f %d %s\n",p->gpa,p->credit,p->name);
		p=p->next;
	}
	fclose(fc);
}

void sort(studentRecord *listHead,char *argv[]){
	int (*compare)(const void*, const void*);
	if(*argv[1]=='g')compare=&comp_gpa;
	else if (*argv[1]=='c')compare=&comp_cre;
	else compare=&comp_name;

	oSort(listHead,compare);
}

int comp_gpa(const void *a,const void *b){
	int s=0;
	studentRecord temp1=*(studentRecord*)a;
	studentRecord temp2=*(studentRecord*)b;
	if ((temp1.gpa-temp2.gpa)<0){
		s=-1;
	}
	else if((temp1.gpa-temp2.gpa)>0){
		s=1;
	}
	return s;
}
int comp_cre(const void *a,const void *b){
	studentRecord temp1=*(studentRecord*)a;
	studentRecord temp2=*(studentRecord*)b;
	return temp1.credit-temp2.credit;
}
int comp_name(const void *a,const void *b){
	studentRecord temp1=*(studentRecord*)a;
	studentRecord temp2=*(studentRecord*)b;
	return strcmp(temp1.name,temp2.name);
}

void oSort(studentRecord *dumH,int compareType(const void*, const void*)){
	studentRecord *p,*q,*r,*bp;
	bp=dumH->next;
	p=bp->next;
	while(bp!=NULL&&p!=NULL){
		q=dumH->next;
		r=dumH;
		while(q!=p){
			if(compareType((studentRecord*)p,(studentRecord*)q)<0){
				bp->next=p->next;
				r->next=p;
				p->next=q;
				p=bp;
				break;
			}
			else{
			q=q->next;
			r=r->next;
			}
		}
		bp=p;
		p=p->next;
	}
}


