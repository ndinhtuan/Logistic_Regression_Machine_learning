#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#include "LinearRegression.h"
#include <conio.h>

int main(){
	LinearRegression ob;

	ob.loadData("data.txt");
	ob.addX0ForX();
	//cout << ob.getY();
	ob.initTheta();
	ob.computeCost();
	ob.gradientDescent(1500, 0.01);
	//ob.updateGrad();
	cout << ob.getTheta() << ob.getJ() << endl;
	Matrix theta = ob.getTheta();
	Matrix pre1(1, 2);
	pre1[0][0] = 1; pre1[0][1] = 70000;
	cout << (pre1 * theta)[0][0];
	_getch();
	return 0;
}