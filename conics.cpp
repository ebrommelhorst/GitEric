/* 	
Name: Lab 10
Author: Eric Brommelhorst
Version: 1.0
Copyright:
Description: Conic Program
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;
class BaseConic{
	protected:
		double x;
		double y;
		double rad; 
	public:
		BaseConic(double x0 = 0, double y0 = 0){x=0;y=0;rad=1;};
		virtual ~BaseConic(){};
		void Move();
		virtual double Area() = 0;
};

class Circle : public BaseConic{
	public:
		virtual void pointCheck();
		void Resize();
		virtual void Display();
		double Area();
};

class Ellipse : public BaseConic{
	private:
		double min;
		double angle;
	public:
		Ellipse();
		void Rotate();
		virtual void Position();
		void Resize();
		virtual void Display();
		double Area();
};

void BaseConic :: Move(){
	cout << "Enter a new x coordinate: ";
	cin >> x;
	cout << "Enter a new y coordinate: ";
	cin >> y;
}


void Circle :: Display(){
	cout << "The x coordinate is " << x << endl;
	cout << "The y coordinate is " << y << endl;
	cout << "The radius of the circle is " << rad << endl;
}
void Circle :: Resize(){
	cout << "Enter the new radius: ";
	cin >> rad;
}
void Circle :: pointCheck(){
	double xc;
	double yc;
	double d;
	cout << "Enter an x coordinate: ";
	cin >> xc;
	cout << "Enter a y coordinate: ";
	cin >> yc;
	d = sqrt((xc-x)*(xc-x)+(yc-y)*(yc-y));
	if(d < rad){
		cout << "The point (" << xc << "," << yc << ") is inside the circle" << endl;
	}else{
		cout << "The point (" << xc << "," << yc << ") is outside the circle" << endl;
	}
}
double Circle :: Area(){
	double area;
	area = 3.14*(rad*rad);
	cout << "The area of the circle is " << area << endl;
}

Ellipse :: Ellipse(){
	angle = 0;
}
void Ellipse :: Rotate(){
	cout << "Enter an angle from the x axis to rotate the ellipse: ";
	cin >> angle;
}
void Ellipse :: Resize(){
	cout << "Enter a new major axis length: ";
	cin >> rad;
	cout << "Enter a new minor axis length: ";
	cin >> min;
}
void Ellipse :: Position(){
	double ma1[2];
	double ma2[2];
	double mi1[2];
	double mi2[2];
	
	ma1[0] = x + rad*cos((angle*3.14)/180);
	ma2[0] = x - rad*cos((angle*3.14)/180);
	mi1[0] = x + min*cos((angle*3.14)/180);
	mi2[0] = x - min*cos((angle*3.14)/180);
	
	ma1[1] = y + rad*sin((angle*3.14)/180);
	ma2[1] = y - rad*sin((angle*3.14)/180);
	mi1[1] = y + min*sin((angle*3.14)/180);
	mi2[1] = y - min*sin((angle*3.14)/180);
	
	cout << setprecision(3) << "The vertices of the major axis are (" << ma1[0] << "," << ma1[1] << ") and ("
	     << ma2[0] << "," << ma2[1] << ")." << endl;
	cout << setprecision(3) << "The vertices of the minor axis are (" << mi1[0] << "," << mi1[1] << ") and ("
	     << mi2[0] << "," << mi2[1] << ")." << endl;
}
void Ellipse :: Display(){
	cout << "The x coordinate is " << x << endl;
	cout << "The y coordinate is " << y << endl;
	cout << "The minor axis of the ellipse is " << min << endl;
	cout << "The major axis of the ellipse is " << rad << endl;
	cout << "The angle of the ellipse is " << angle << endl;
	
}
double Ellipse :: Area(){
	double area;
	area = 3.14*rad*min;
	cout << "The area of the ellipse is " << area << endl;
}

int main(void){
	int choice;
	int c;
	do{
		cout << "Menu: " << endl
			 << "\t1: Circle" << endl
			 << "\t2: Ellipse" << endl
			 << "\tAnything else to Exit" << endl
			 << "Enter shape choice: ";
			 
		cin >> choice;
		
		switch(choice){
			case 1:
				{Circle cir;
				do{	
					cout << "Menu: " << endl
						<< "\t1: Move" << endl
						<< "\t2: Resize" << endl
						<< "\t3: Check Point" << endl
						<< "\t4: Area" << endl
						<< "\t5: Display" << endl
						<< "\tAnything else to Exit" << endl;
					cin >> c;
					switch(c){
						case 1:
							cir.Move();
							break;
						case 2:
							cir.Resize();
							break;
						case 3:
							cir.pointCheck();
							break;
						case 4:
							cir.Area();
							break;
						case 5:
							cir.Display();
							break;
						default:
							c = 0;
							break;
					}
				}while(c != 0);
				}
				break;
			case 2:
				{
				Ellipse ell;
				do{
					cout << "Menu: " << endl
						<< "\t1: Move" << endl
						<< "\t2: Resize" << endl
						<< "\t3: Rotate" << endl
						<< "\t4: Axis Position" <<endl
						<< "\t5: Area" << endl
						<< "\t6: Display" << endl
						<< "\tAnything else to Exit" << endl;
					cin >> c;
					switch(c){
						case 1:
							ell.Move();
							break;
						case 2:
							ell.Resize();
							break;
						case 3:
							ell.Rotate();
							break;
						case 4:
							ell.Position();
							break;
						case 5:
							ell.Area();
							break;
						case 6:
							ell.Display();
							break;
						default:
							c = 0;
							break;
					}
				}while(c != 0);			
				}
				break;
			default:
				choice = 0;
				break;
		}
	}while(choice != 0);
	return 0;
}