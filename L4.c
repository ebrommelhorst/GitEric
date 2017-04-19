/* 	
Name: Lab 4
Author: Eric Brommelhorst
Version: 1.0
Copyright:
Description: Command Line Program
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fnum(int num);
void offset(int off, int num, FILE *f);
void scale(int scl, int num, FILE *f);
void ren(char *name, FILE *f);
void help(void);
void stat(FILE *f, int num);
void center(FILE *f, int num);
void normal(FILE *f, int num);
int max(FILE *f);
double avg(FILE *f);

int main(int argc, char *argv[]){
	int num = 0;
	int off;
	int scl;
	FILE *f;
	char *name;
	int i;
	for(i=1; i<argc; i++){
		if(!strcmp(argv[i],"-n")){
			if(argv[i+1]== NULL){
				printf("Invalid input\n");
				return 0;
			}
			num = atoi(argv[i+1]);
			if(1>num && num>11){
				printf("Invalid input\n");
				return 0;
			}
			f = fnum(num);
		}else if(!strcmp(argv[i],"-h")){
			help();
			return 0;
		}
		
	}
	if(1>num || num>11){
		printf("Invalid input\n");
		return 0;
	}
	for(i=1; i<argc; i++){
		if(!strcmp(argv[i],"-o")){
			if(argv[i+1]== NULL){
				printf("Invalid input\n");
				return 0;
			}
			off = atoi(argv[i+1]);
			if(off == 0){
				printf("Invalid input\n");
				return 0;
			}
			offset(off,num,f);
		}else if(!strcmp(argv[i],"-s")){
			if(argv[i+1]== NULL){
				printf("Invalid input\n");
				return 0;
			}
			scl = atoi(argv[i+1]);
			if(scl==0){
				printf("Invalid input\n");
				return 0;
			}
			scale(scl,num,f);
		}else if(!strcmp(argv[i],"-r")){
			if(argv[i+1]== NULL){
				printf("Invalid input\n");
				return 0;
			}
			name = argv[i+1];
			ren(name,f);
		}else if(!strcmp(argv[i],"-S")){
			stat(f, num);
		}else if(!strcmp(argv[i],"-C")){
			center(f, num);
		}else if(!strcmp(argv[i],"-N")){
			normal(f, num);
		}
	}	
	fclose(f);	
	return 0;	
}

FILE *fnum(int num){
	FILE *f;
	char filename[20];
	if(num < 10){
		sprintf(filename,"Raw_data_0%d.txt",num);
	}else{
		sprintf(filename,"Raw_data_%d.txt",num);
	}
	f = fopen(filename, "r");
	return f;
}

void offset(int off, int num, FILE *f){
	int len;
	int m;
	int hold;
	int i;
	FILE *g;
	char filename[20];
	if(num < 10){
		sprintf(filename,"Offset_data_0%d.txt",num);
	}else{
		sprintf(filename,"Offset_data_%d.txt",num);
	}
	g = fopen(filename, "w");
	fscanf(f,"%d %d",&len,&m);
	fprintf(g,"%d %d\n",len,off);
	for(i=0;i<len;i++){
		fscanf(f,"%d",&hold);
		hold += off;
		fprintf(g,"%d\n",hold);
	}
	fclose(g);
}
void scale(int scl, int num, FILE *f){
	int len;
	int m;
	int hold;
	int i;
	FILE *g;
	char filename[20];
	if(num < 10){
		sprintf(filename,"Scaled_data_0%d.txt",num);
	}else{
		sprintf(filename,"Scaled_data_%d.txt",num);
	}
	g = fopen(filename, "w");
	fscanf(f,"%d %d",&len,&m);
	fprintf(g,"%d %d\n",len,scl);
	for(i=0;i<len;i++){
		fscanf(f,"%d",&hold);
		hold *= scl;
		fprintf(g,"%d\n",hold);
	}
	fclose(g);
}
void ren(char *name, FILE *f){
	int len;
	int m;
	int hold;
	int i;
	FILE *g;
	char filename[50];
	strcpy(filename,name);
	strcat(filename,".txt");
	g = fopen(filename, "w");
	fscanf(f,"%d %d",&len,&m);
	fprintf(g,"%d %d\n",len,m);
	for(i=0;i<len;i++){
		fscanf(f,"%d",&hold);
		fprintf(g,"%d\n",hold);
	}
	fclose(g);
}
void help(void){
	printf("\n\t-n ""File Number"" Open file\n");
	printf("\t-o ""Offset Value"" Add offset to values in file\n");
	printf("\t-s ""Scale Value"" Multiply values in file by scaling value\n");
	printf("\t-r ""File Name"" Create copy of file\n");
	printf("\t-h Open help display\n");
	printf("\t-S Save statistics of file\n");
	printf("\t-C Center values in file\n");
	printf("\t-N Naturalize values in file\n");
}
void stat(FILE *f, int num){
	int m;
	double a;
	FILE *g;
	char filename[20];
	if(num < 10){
		sprintf(filename,"Statistics_data_0%d.txt",num);
	}else{
		sprintf(filename,"Statistics_data_%d.txt",num);
	}
	g = fopen(filename,"w");
	m = max(f);
	a = avg(f);
	fprintf(g,"%d %lf",m,a);
	fclose(g);
}
void center(FILE *f, int num){
	double a;
	double hold;
	int len;
	int m;
	int i;
	FILE *g;
	char filename[20];
	if(num < 10){
		sprintf(filename,"Center_data_0%d.txt",num);
	}else{
		sprintf(filename,"Center_data_%d.txt",num);
	}
	g = fopen(filename,"w");
	a = avg(f);
	rewind(f);
	fscanf(f,"%d %d",&len,&m);
	fprintf(g,"%d %d\n",len,m);
	for(i=0;i<len;i++){
		fscanf(f,"%lf",&hold);
		hold = hold - a;
		fprintf(g,"%lf\n",hold);
	}
	fclose(g);
}
void normal(FILE *f, int num){
	int a;
	double hold;
	int len;
	int m;
	int i;
	FILE *g;
	char filename[20];
	if(num < 10){
		sprintf(filename,"Normal_data_0%d.txt",num);
	}else{
		sprintf(filename,"Normal_data_%d.txt",num);
	}
	g = fopen(filename,"w");
	m = max(f);
	rewind(f);
	fscanf(f,"%d %d",&len,&a);
	fprintf(g,"%d %d\n",len,a);
	for(i=0;i<len;i++){
		fscanf(f,"%lf",&hold);
		hold = hold /(double)m;
		fprintf(g,"%lf\n",hold);
	}
	fclose(g);
}
int max(FILE *f){
	int m = 0;
	int n;
	int len;
	int i;
	int hold;
	fscanf(f,"%d %d",&len,&n);
	for(i=0;i<len;i++){
		fscanf(f,"%d",&hold);
		if(hold > m){
			m = hold;
		}
	}
	return m;
}
double avg(FILE *f){
	double a = 0;
	int n;
	int len;
	int i;
	int hold;
	rewind(f);
	fscanf(f,"%d %d",&len,&n);
	for(i=0;i<len;i++){
		fscanf(f,"%d",&hold);
		a += hold;
	}
	
	a /=(double)len;
	return a;
}