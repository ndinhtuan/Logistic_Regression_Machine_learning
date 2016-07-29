#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#include "LinearRegression.h"
#include "Logistic.h"
#include <conio.h>

#include <fstream>

using std::ofstream;

void findTheta(){ // train
	Logistic ob;

	// Find Theta

	ob.loadData("C:/Users/9470m/Documents/Visual Studio 2013/Projects/CreateData/CreateData/finalData.txt");

	ob.initTheta(0);
	ob.addX0ForX();
	ob.computeCost();
	cout << ob.getJ();
	ob.updateGrad();
	cout << ob.getGrad();
	cout << "Run normal gradient descent. Theta : " << endl;
	ob.gradientDescent(1000, 0.01); // iteration : 1000, lambda = 0.01
	cout << ob.getTheta();

	ofstream out("Theta.txt");
	out << ob.getTheta();

	cout << "Accurate : " << ob.trainAccuracy() << " %." << endl;
	_getch();
}

void predict(){
	Logistic ob;

	ob.loadForPredict("C:/Users/9470m/Documents/Visual Studio 2013/Projects/CreateData/CreateData/data_test.txt");
	ob.getThetaFromFile("Theta.txt");
	ob.predict();
}

int main(){
	//findTheta();
	predict();
	_getch();
	return 0;
}