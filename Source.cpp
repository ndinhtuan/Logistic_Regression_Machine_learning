#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#include "LinearRegression.h"
#include "Logistic.h"
#include <conio.h>

int main(){
	
	Logistic ob;
	
	ob.loadData("data3.txt");

	ob.initTheta(0);
	ob.addX0ForX();
	ob.computeCost();
	cout << ob.getJ();
	ob.updateGrad();
	cout << ob.getGrad();
	cout << "Run normal gradient descent. Theta : " << endl;
	ob.gradientDescent(400, 0.01);
	cout << ob.getTheta();
	cout << "Train Accuracy : " << ob.trainAccuracy() << " %." << endl;

	ob.initTheta(0);
	cout << "Run auto gradient descent . Theta : " << endl;
	ob.autoGradientDescent(0.01, 0.000001);
	cout << ob.getTheta();
	cout << "Train Accuracy : " << ob.trainAccuracy() << " %." << endl;
	//ob.loadData("data2.txt"); // memory leak
	//ob.initTheta();
	//cout << "Theta of using normal equations." << endl;
	//ob.addX0ForX();
	//ob.useNormalEquations();
	//cout << ob.getTheta();
	//cout << "Predict : " << (ob.getTheta() * pre1)[0][0] << endl;
	_getch();
	return 0;
}