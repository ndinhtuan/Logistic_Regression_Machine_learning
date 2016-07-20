#include "LinearRegression.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#include <fstream>

using std::ifstream;

#include <conio.h>

LinearRegression::LinearRegression()
{
	m = n = 0;
	J = 0;
}


LinearRegression::~LinearRegression()
{
}

void LinearRegression::loadData(char* fileName){
	ifstream input(fileName);

	if (!input.is_open()){
		cout << "Cannot access file." << endl;
		return;
	}

	input >> m >> n;
	X.createMat(m, n);
	y.createMat(m, 1);
	int row = 0;

	for (int i = 0; i < m; i++){
		
		
		// read 1 row of X
		for (int j = 0; j < n; j++){
			input >> X[row][j];
		}

		// read 1 row of y
		input >> y[row][0];

		row++;
	}
}

void LinearRegression::displayX(){
	cout << "X : ";
	cout << X;
}

void LinearRegression::displayY(){
	cout << "y : ";
	cout << y;
}

void LinearRegression::initTheta(int value){
	if (n == 0){
		cout << "Need to load data before use this attribute." << endl;
		return;
	}

	theta.createMat(n + 1, 1, value);
	createGradForTheta();
}

void LinearRegression::computeCost(){
	if (m == 0 || n == 0){
		cout << "Need to load data before use this attribute." << endl;
		return;
	}

	if (theta.getSize().rows == 0 || theta.getSize().cols == 0){
		cout << "Need to init theta before use this attribute." << endl;
		return;
	}
	J = 0;
	//X.addX0();
	Matrix tmp = X * theta;
	tmp = tmp - y;
	tmp = tmp^2;

	J = ((long double)1 / (2 * m)) * tmp.sum()[0][0];
}

void LinearRegression::createGradForTheta(){
	grad.createMat(theta.getSize().rows, 1);
}

void LinearRegression::updateGrad(){
	if (!loadDataAndInitTheta()){
		return;
	}

	grad = X * theta - y;
	Matrix tmp = (X.transpose());
	grad =  tmp * grad;
	grad = grad * (1 / (double)m);
	//X.transpose();
}

void LinearRegression::gradientDescent(int iter, long double lambda){
	//displayGrad();
	for (int i = 0; i < iter; i++){
		theta = theta - grad * lambda;
		//cout << theta << endl;
		updateGrad();
		//cout << grad.getSize() << theta;
		//_getch();
	    //_getch();
	}
	computeCost();
}

void LinearRegression::displayGrad(){
	cout << grad;
}

void LinearRegression::addX0ForX(){
	if (m == 0 || n == 0){
		cout << "You need to load data before using this attribute." << endl;
		return;
	}
	X.addX0();
}

bool LinearRegression::loadedData(){
	return (m != 0 && n != 0);
}

Matrix LinearRegression::featureNormalize(){
	if (!loadedData()){
		cout << "Need to load data before use feature normalize. " << endl;
		return X;
	}

	Matrix result(X);
	Matrix average = X.mean();
	Matrix sigma = X.STD();
	cout << average << sigma;

	result = result - average;
	result = result / sigma;
	return result;
}

void LinearRegression::useNormalEquations(){
	if (!loadedData()){
		cout << "Need to load data for using normal equations to compute theta." << endl;
		return;
	}
	theta = ((X.transpose() * X) ^ -1)*X.transpose()*y;
}

double LinearRegression::trainAccuracy(double threshold){
	int trueTrain = m;
	Matrix _y = X * theta;

	for (int i = 0; i < m; i++){

		if (_y[i][0] - y[i][0] > threshold){
			trueTrain--;
		}

	}

	return 100 * (double)trueTrain / m;
}


