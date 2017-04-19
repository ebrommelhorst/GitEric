/* 	
Name: Lab 4
Author: Eric Brommelhorst
Version: 1.0
Copyright:
Description: Command Line Program
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Signal{
	private:						//Declare Class Object Variables
		int len;
		int mx;
		double av;
		double *a;
	public:							//Declare Class Functions
		Signal();
		Signal(int num);
		Signal(char *name);
		~Signal();
		void menu(Signal sig);
		void offset();
		void scale();
		void sig_info();
		void center();
		void normal();
		void max();
		void avg();
		void save();
};

int main(int argc, char *argv[]){
	int num = 0;
	char *name = (char *)malloc(sizeof(char)*100);

	if(argc <= 2){								//Check For Flags
		Signal sig;
		sig.menu(sig);
	}else if(!strcmp(argv[1],"-n")){			//Check for file number flag
		if(argv[2] == NULL){
			cout<<"Invalid input"<<endl;
			return 0;
		}
		num = atoi(argv[2]);
		if(1>num || num>14){
			cout<<"Invalid input"<<endl;
			return 0;
		}
		Signal sig(atoi(argv[2]));				//Use File Number class object
		sig.menu(sig);
		
	}else if(!strcmp(argv[1],"-f")){			//Check for file name flag
			if(argv[2]== NULL){
			cout<<"Invalid input"<<endl;
			return 0;
		}
		std::strcpy(name,argv[2]);				//USe file name class object
		Signal sig(name);
		sig.menu(sig);
	}
	free(name);
}

void Signal::menu(Signal sig){	
	int in;
	int i = 0;	
	while(i == 0){								//Display menu
		cout << "Menu" << endl;
		cout << "\t1. Offset" << endl;
		cout << "\t2. Scale" << endl;
		cout << "\t3. Normal" << endl;
		cout << "\t4. Center" << endl;
		cout << "\t5. Info" << endl;
		cout << "\t6. Save" << endl;
		cout << "\t7. Exit" << endl;
		cout << "Enter Selection: ";
		cin >> in;
		
		sig.avg();
		sig.max();
		switch(in){								//Make selection
			case 1:
				sig.offset();
				break;
			case 2:
				sig.scale();
				break;
			case 3:
				sig.normal();
				break;
			case 4:
				sig.center();
				break;
			case 5:
				sig.sig_info();
				break;
			case 6:
				sig.save();
				break;
			case 7:
				return;
				break;
			default:
				in = 0;
				break;
		}
	}
}

Signal::Signal(int num){
	FILE *f;									//Create object using num
	int i;
	char filename[30];
	sprintf(filename,"Raw_data_%02d.txt",num);
	f = fopen(filename, "r");
	fscanf(f,"%d %d",&len,&mx);
	a = (double *)malloc(sizeof(double)*len);
	for(i=0;i<len;i++){
		fscanf(f,"%lf",(a+i));
	}
	avg();
	max();
}

Signal::Signal(char *name){
	FILE *f;									//Create object with file name
	int i;
	char filename[100];
	sprintf(filename,"%s.txt",name);
	f = fopen(filename, "r");
	if(f == NULL){								//Exit if file doesnt exist
		printf("File does not exist.\n");
		exit(1);
	}
	fscanf(f,"%d %d",&len,&mx);
	a = (double *)malloc(sizeof(double)*len);
	for(i=0;i<len;i++){
		fscanf(f,"%lf",(a+i));
	}
	avg();
	max();
}

Signal::Signal(){
	FILE *f;									//Create default object
	int i;
	f = fopen("Default.txt", "r");
	fscanf(f,"%d %d",&len,&mx);
	a = (double *)malloc(sizeof(double)*len);
	for(i=0;i<len;i++){
		fscanf(f,"%lf",(a+i));
	}
	avg();
	max();
}

Signal::~Signal(){
	if(a != NULL){								//Deconstruct object
		free(a);
		a = NULL;
	}
}

void Signal::offset(){
	double hold;								//Offset data
	int i;
	double off;
	cout << "Enter Offset Value: ";
	cin >> off;
	for(i=0;i<len;i++){
		hold = *(a+i);
		hold += off;
		*(a+i) = hold;
	}
}

void Signal::scale(){
	double hold;								//Scale Data
	int i;
	double scl;
	cout << "Enter Scale Value: ";
	cin >> scl;
	for(i=0;i<len;i++){
		hold = *(a+i);
		hold *= scl;
		*(a+i) = hold;
	}
}

void Signal::sig_info(){
	cout << "Length: " << len << " Max: " << mx << " Average: " << av << endl;
}

void Signal::center(){								//Center data
	double hold;
	int i;
	for(i=0;i<len;i++){
		hold = *(a+i);
		hold = hold - av;
		*(a+i) = hold;
	}
}

void Signal::normal(){								//normalize data
	double hold;
	int i;
	for(i=0;i<len;i++){
		hold = *(a+i);
		hold = hold/mx;
		*(a+i) = hold;
	}
}

void Signal::max(){
	mx = 0;									//Find max
	int i;
	double hold;
	for(i=0;i<len;i++){
		hold = *(a+i);
		if(hold > mx){
			mx = hold;
		}
	}
}

void Signal::avg(){
	av = 0;								//Find Average
	int i;
	double hold;
	for(i=0;i<len;i++){
		hold = *(a+i);
		av += hold;
	}
	
	av /=len;
	
}

void Signal::save(){
	FILE *f;									//Save file
	int i;
	printf("Check\n");
	f = fopen("Saved_File.txt", "w");
	printf("Check\n");
	fprintf(f,"%d %d\n",len,mx);
	printf("Check");
	for(i=0;i<len;i++){
		fprintf(f,"%lf\n",*(a+i));
	}
}