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
void growBSTree(studentRecord *root,studentRecord **p,char *argv[]);
void output(studentRecord *head,char *argv[]);

studentRecord* sortBSTreeToList(studentRecord *p,studentRecord **t);
int comp_gpa(const void *a,const void *b);
int comp_cre(const void *a,const void *b);
int comp_name(const void *a,const void *b);



int main(int argc,char *argv[]) {
	if(argc!=4){
		fprintf(stderr,"argument error.");
		exit (0);
	}
	studentRecord *head=(studentRecord*)malloc(sizeof(studentRecord)*1);;
	studentRecord **t,**p;
	studentRecord *tail=(studentRecord*)malloc(sizeof(studentRecord)*1);
	t=&tail;
	head->next=input(argv);
	p=&head->next;
	studentRecord *sortedHead=(studentRecord*)malloc(sizeof(studentRecord)*1);
	clock_t clockStart,clockEnd;
	clockStart =clock();
	growBSTree(head->next,p,argv);
	sortedHead=sortBSTreeToList(head->next,t);
	(*t)->next=NULL;
	clockEnd =clock();

	output(sortedHead,argv);
	free(sortedHead); free(head); free(tail);
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
		p->left=NULL;
		p->right=NULL;
		studentRecord *temp;
		temp=(studentRecord*)malloc(sizeof(studentRecord)*1);
		p->next=temp;
		q=p;
		p=temp;
	}
	q->next=NULL;
	fclose(fo);
	p=f;
	return (p);
}

void growBSTree(studentRecord *root,studentRecord **p,char *argv[]){
	int (*compare)(const void*, const void*);
	if(*argv[1]=='g')compare=&comp_gpa;
	else if (*argv[1]=='c')compare=&comp_cre;
	else compare=&comp_name;
	studentRecord *q;
	q=(*p)->next;
	while(q!=NULL){
		while(q!=NULL){
			if(compare(*p,q)>=0){
				if((*p)->left==NULL){
					(*p)->left=q;
					break;
				}
				else{
					p=&(*p)->left;
				}
			}
			else if(compare(*p,q)<0){
				if((*p)->right==NULL){
					(*p)->right=q;
					break;
				}
				else{
					p=&(*p)->right;
				}
			}
		}
		q=q->next;
		p=&root;
	}
}

studentRecord* sortBSTreeToList(studentRecord *p,studentRecord **t){
	studentRecord *h=(studentRecord*)malloc(sizeof(studentRecord)*1);

	if(p->left==NULL&&p->right==NULL){
		h=p;
		(*t)=p;
	}
	else if(p->left==NULL){
		h=p;
		h->next=sortBSTreeToList(p->right,t);
	}
	else if(p->right==NULL){
		h=sortBSTreeToList(p->left,t);
		(*t)->next=p;
		(*t)=p;
	}
	else{
		h=sortBSTreeToList(p->left,t);
		(*t)->next=p;
		p->next=sortBSTreeToList(p->right,t);
	}

	return h;
}

void output(studentRecord *p,char *argv[]){
	FILE *fc;
	if(	(fc=fopen(argv[3],"w"))==NULL){
		fprintf(stderr,"error.cant open %s",argv[3]);
		exit (0);
	}
	while(p!=NULL){
		fprintf(fc,"%f %d %s\n",p->gpa,p->credit,p->name);
	p=p->next;
	};
	fclose(fc);
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

