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
#include <vector>
#include <string>

using namespace std;

class Signal{
	private:						//Declare Class Object Variables
		int len;
		int mx;
		double av;
		vector<double> a;
	public:							//Declare Class Functions
		Signal();
		Signal(int num);
		Signal(string name) throw(int);
		~Signal();
		void offset(double num) throw(int);
		void scale(double num) throw(int,char);
		void sig_info();
		double center();
		double normal();
		void max();
		void avg();
		void save();
		void combine();
		int lcompare();
		double acompare(int i);
		double mcompare();
};
	void menu(Signal sig);

int main(int argc, char *argv[]){
	int num = 0;
	string name;

	if(argc <= 2){								//Check For Flags
		Signal sig;
		menu(sig);
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
		menu(sig);
		
	}else if(!strcmp(argv[1],"-f")){			//Check for file name flag
			if(argv[2]== NULL){
			cout<<"Invalid input"<<endl;
			return 0;
		}
		name = argv[2];				//USe file name class object
		try{
			Signal sig(name);
			menu(sig);
		}
		catch(...){
			cout << "File does not exist" << endl;
		}
		
	}
}

void menu(Signal sig){	
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
		cout << "\t7. Combine" << endl;
		cout << "\t8. Exit" << endl;
		cout << "Enter Selection: ";
		cin >> in;
		
		sig.avg();
		sig.max();
		switch(in){								//Make selection
			case 1:
				try{
					sig.offset(1);
				}
				catch(int x){
					cout << "Cannot offset empty data vector" << endl;
				}
				break;
			case 2:
				try{
					sig.scale(1);
				}
				catch(int x){
					cout << "Cannot scale empty data vector" << endl;
				}
				catch(char a){
					cout << "Cannot scale with factor of 0" << endl;
				}
				break;
			case 3:
				try{
					sig.scale(sig.normal());
				}
				catch(int x){
					cout << "Cannot normalize empty data vector" << endl;
				}
				catch(char a){
					cout << "Cannot scale with factor of 0" << endl;
				}
				break;
				break;
			case 4:
				try{
					sig.offset(sig.center());
				}
				catch(int x){
					cout << "Cannot center empty data vector" << endl;
				}
				break;
			case 5:
				sig.sig_info();
				break;
			case 6:
				sig.save();
				break;
			case 7:
				try{
					sig.combine();
				}
				catch(Signal sig){
					cout << "File does not exist" << endl;
				}
				catch(int x){
					cout << "File is not correct length" << endl;
				}
				break;
			case 8:
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
	string filename;
	filename = "Raw_data_" + std::to_string(num) + ".txt";
	f = fopen(filename.c_str(), "r");
	fscanf(f,"%d %d",&len,&mx);
	a.resize(len);
	for(i=0;i<len;i++){
		fscanf(f,"%lf",&a[i]);
	}
	avg();
	max();
	fclose(f);
}

Signal::Signal(string name) throw(int){
	FILE *f;									//Create object with file name
	int i;
	string filename;
	filename = name + ".txt";
	f = fopen(filename.c_str(), "r");
	if(f == NULL){								//Exit if file doesnt exist
		throw(1);
	}
	fscanf(f,"%d %d",&len,&mx);
	a.resize(len);
	for(i=0;i<len;i++){
		fscanf(f,"%lf",&a[i]);
	}
	avg();
	max();
	fclose(f);
}

Signal::Signal(){									//Create default object
	len = 0;
	mx = 0;
	a.resize(len);
}

Signal::~Signal(){

}

void Signal::offset(double num) throw(int){
	double hold;								//Offset data
	int i;
	if(a.empty() == 0){
		throw 1;
	}
	if(num == 1){
		cout << "Enter Offset Value: ";
		cin >> num;
	}
	for(i=0;i<len;i++){
		hold = a[i];
		hold += num;
		a[i] = hold;
	}
}

void Signal::scale(double num) throw(int,char){
	double hold;								//Scale Data
	int i;
	if(a.empty() == 0){
		throw 1;
	}
	if(num == 1){
		cout << "Enter Scale Value: ";
		cin >> num;
	}
	if(num == 0){
		throw 'A';
	}
	for(i=0;i<len;i++){
		hold = a[i];
		hold *= num;
		a[i] = hold;
	}
}

void Signal::sig_info(){
	cout << "Length: " << len << " Max: " << mx << " Average: " << av << endl;
}

double Signal::center(){								//Center data
	double i = 0;
	i -= av;
	return i;
}

double Signal::normal(){								//normalize data
	double i;
	i = 1/(double)mx;
	return i;
}

void Signal::max(){
	mx = 0;									//Find max
	int i;
	double hold;
	for(i=0;i<len;i++){
		hold = a[i];
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
		hold = a[i];
		av += hold;
	}
	
	av /=len;
	
}

void Signal::save(){
	FILE *f;									//Save file
	int i;
	f = fopen("Saved_File.txt", "w");
	fprintf(f,"%d %d\n",len,mx);
	for(i=0;i<len;i++){
		fprintf(f,"%lf\n",a[i]);
	}
	fclose(f);
}

void Signal::combine(){
	int i;
	int j;
	int hold;
	cout << "Combine: " << endl
		 << "\t1: Enter File Name" << endl
		 << "\t2: Enter File Number" << endl;
	cin >> j;
	if(j == 1){
		string name;
		cout << "Enter a filename: ";	
		cin >> name;
		try{
			Signal sig2(name);
		}
		catch(...){
			Signal sig2;
			throw sig2;
		}
		Signal sig2(name);
		if(sig2.lcompare() == len){
			if(sig2.mcompare() > mx){
				mx = sig2.mcompare();
			}
			for(i=0;i<len;i++){
				hold = sig2.acompare(i);
				a[i] += hold;
			}
		}else{
			throw(1);
		}
		
	}else if(j == 2){
		int num;
		cout << "Enter a file number: ";
		cin >> num;
		Signal sig2(num);
		if(sig2.lcompare() == len){
			if(sig2.mcompare() > mx){
				mx = sig2.mcompare();
			}
			for(i=0;i<len;i++){
				hold = sig2.acompare(i);
				a[i] += hold;
			}
		}else{
			cout << "File lengths do not match" << endl;
		}
	}else{
		cout << "Invalid Input" << endl;
	}
}

int Signal::lcompare(){
	return len;
}

double Signal::acompare(int i){
	return a[i];
}
double Signal::mcompare(){
	return mx;
}
