/* 	
Name: Lab 8
Author: Eric Brommelhorst
Version: 1.0
Copyright:
Description: Morse Code Translator
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

char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u'
				  ,'v','w','x','y','z'};
string morse[] = {".-","-..","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.",
				  "---",".--.","--.-",".-.","...","-","..-","..-","...-",".--","-..-","-.--","--.."};
class Message{
	protected:
		string msg;
	public:
		Message();
		Message(string input);
		~Message();
		void printMessage(void);
};

class morseCodeMessage: public Message{
	private:
		string* mmsg;
	public:
		morseCodeMessage(string word);
		~morseCodeMessage();
		void translate(string word);
		void printMorse(string word);
		
};

class messageStack{
	private:
		string* smsg;
		string *stack[10];
	public:
		messageStack();
		~messageStack();
		void pushStack(string *smsg, int c);
		void popStack(int c);
		void printStack(int c);
};

Message :: Message(){
}
Message :: Message(string input){
	msg = input;
}
void Message :: printMessage(void){
	cout << "The untranslated string is " << msg << endl;
}
Message :: ~Message(){
}

morseCodeMessage :: morseCodeMessage(string word){
	mmsg = new string[word.length()];
	translate(word);
	
}
void morseCodeMessage :: translate(string word){
	int i;
	int j;
	locale loc;
	for(i=0;i<word.length();i++){
		for(j=0;j<26;j++){
			word[i] = tolower(word[i],loc);		
			if(letters[j] == word[i]){
				mmsg[i] = morse[j];
			}
		}
	}
}
void morseCodeMessage :: printMorse(string word){
	int i;
	cout << "The translated message is ";
	for(i=0;i< word.length();i++){
		cout << mmsg[i] << " ";
	}
	cout << endl;
}
morseCodeMessage :: ~morseCodeMessage(){
}

messageStack :: messageStack(){
	smsg = new string;
}
void messageStack :: pushStack(string *smsg, int c){
	stack[c] = new string;
	*stack[c] = *smsg;
}
void messageStack :: popStack(int c){
	cout << "Element " << c << " was popped from the stack" << endl;
}
void messageStack :: printStack(int c){
	int i;
	cout << "Printing Stack: " << endl;
	for(i=0;i<c;i++){
		cout << "Element " << (i+1) << ": " << *stack[i] << endl;
	}
}
messageStack :: ~messageStack(){
}

int main(void){
	int loop = 1;
	int c = 0;
	string word;
	while(loop != 0){
		cout << "Please enter a word: " << endl;
		cin >> word;
		Message msg1(word);
		msg1.printMessage();
		morseCodeMessage mmsg1(word);
		mmsg1.printMorse(word);
		cout << "Press 0 to Exit. Anything else to continue." << endl;
		cin >> loop;
	}
	loop = 1;
	messageStack st;
	while(loop != 0){
		
		if(c == 10){
			cout << "Stack is full: Printing out" << endl;
			st.printStack(c);
			return 0;
		}
		cout << "Stack Menu: " << endl
			 << "\t (1) Push Message" << endl
			 << "\t (2) Pop Message" << endl
			 << "\t (3) Print Stack" << endl
			 << "\t Anything else to Exit" << endl;
		cin >> loop;
		if(loop == 1){
			cout << "Enter word to push: ";
			cin >> word;
			st.pushStack(&word, c);
			c++;
		}else if(loop == 2){
			if(c == 0){
				cout << "Stack is Empty" << endl;
			}else{
				st.popStack(c);
				c--;
			}
		}else if(loop == 3){
			st.printStack(c);
		}else{
			loop = 0;
		}
	}
	return 0;
}