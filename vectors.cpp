// Lab7_vectors.cpp
// This program shows some simple vector examples, and asks for simple tasks.
// Reference: Lippman, section 3.3

// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
//                 OR: -std=c++0x
// Example:  g++ Lab7_vectors.cpp -o Lab7_vectors -std=c++11
//      or:  g++ Lab7_vectors.cpp -o Lab7_vectors -std=c++0x
// Some initialization methods and other things are not supported by the old standard.

#include <iostream>
#include <vector>

using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
	vector<int> ivec1(5), ivec2;
	vector<double> dvec1{5.1}, dvec2(5,1.5);
	vector<string> svec1 = {"hello", "world"};
	// vector<myClass> myCvec;	// you can have vectors of objects
	// in general: vector<Type> vec;	// vector is a template

	for(int i = 0; i < ivec1.size(); i++)
		cout << ivec1[i] << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:ivec1)	// This is equivalent to the above for loop
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:dvec1)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:dvec2)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:svec1)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
		
	cout << "Original size: " << ivec2.size() << endl;
	ivec2.push_back(50);
	cout << "New size: " << ivec2.size() << "\nAdded element: " << ivec2[0] << endl;
	cout << "\n------------------------------------------------------------------" << endl;
		
// ***********************************************************************
// Try all the ways to initializa a vector shown in Table 3.4. Use the
// vectors above and/or declare new vectors.
// Some of those operations have already been used, but write your
// own examples.

// Do exercises 3.14 and 3.15 from Lippman (page 102)

// Try all the vector operations shown in table 3.5. Use the vectors above
// or define new ones. Try different types.
// ***********************************************************************
	vector<int> v1;
	vector<int> v2(v1);
	vector<int> v3 = v1;
	vector<double> v4(6,1.7);
	vector<double> v5(4);
	vector<float> v6{1,1.5,2,2.5};
	vector<float> v7 = {1,2,3};
	
	vector<int> test1(5);
	int i;
	for(i = 0; i<5; i++){
		cout << "Enter an integer:" << endl;
		cin >> test1[i];
	}	
	
	vector<string> test2(5);
	for(i = 0; i<5; i++){
		cout << "Enter an string:" << endl;
		cin >> test2[i];
	}
	
	for(i = 0; i<5; i++){
	cout << "Values:" << test1[i] << " " << test2[i] << endl;	
	}
	
	if(v1.empty()){
		cout << v4.size() << endl;
		v4.push_back(7);
		cout << v4[6] << endl;
	}
	v1 = test1;
	v2 = {1,2,3,4,5};
	if(v1 == v2){
		cout << "Success" << endl;
	}else if(v1 > v2){
		cout << "Fail" << endl;	
	}
	
	return 0;
}