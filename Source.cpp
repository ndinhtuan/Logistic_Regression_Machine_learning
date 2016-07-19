#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#include "LinearRegression.h"
#include <conio.h>

int main(){
	
	LinearRegression ob;
	ob.loadData("data2.txt");
	ob.initTheta();
	cout << "Normalizing feature ..." << endl;
	ob.setX(ob.featureNormalize());
	ob.addX0ForX();
	cout << "Gradient descent ..." << endl;
	ob.gradientDescent(400, 0.01);
	cout << ob.getTheta();

	cout << "Predicted price of a 1650, 3 br house (using gradient descent) : ";
	Matrix pre1(1, 3);
	pre1[0][0] = 1;
	pre1[0][1] = 1650;
	pre1[0][2] = 3;

	cout << (ob.getTheta() * pre1)[0][0] << endl;


	ob.loadData("data2.txt"); // memory leak
	ob.initTheta();
	cout << "Theta of using normal equations." << endl;
	ob.addX0ForX();
	ob.useNormalEquations();
	cout << ob.getTheta();
	cout << "Predict : " << (ob.getTheta() * pre1)[0][0] << endl;
	_getch();
	return 0;
}