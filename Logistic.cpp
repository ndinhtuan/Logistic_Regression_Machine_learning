#include "Logistic.h"
#include "MatrixLib.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#include <fstream>

using std::ifstream;
using std::ofstream;

#include <conio.h>
#include <cassert>

Logistic::Logistic()
{
	m = n = 0;
	J = 0;
}


Logistic::~Logistic()
{
}

void Logistic::loadData(const char *fileName){
	ifstream input(fileName);

	if (!input.is_open()){
		cout << "Cannot access file training." << endl;
		return;
	}

	input >> m >> n;

	X.createMat(m, n);
	y.createMat(m, 1);

	for (int row = 0; row < m; row++){

		//read for X's row
		for (int i = 0; i < n; i++){
			input >> X[row][i];
		}

		// read for y;
		input >> y[row][0];
	}
}

Matrix Logistic::sigmoid(Matrix &ob){

	if (!ob.existMat()){
		return ob;
	}

	Matrix result(ob);

	for (int row = 0; row < ob.getSize().rows; row++){

		for (int col = 0; col < ob.getSize().cols; col++){
			result[row][col] = 1 / (1 + exp(-result[row][col]));
		}

	}

	return result;

}

bool Logistic::loadedData(){
	return (m != 0 && n != 0);
}

void Logistic::computeCost(){
	if (!loadDataAndInitTheta()){
		return;
	}

	Matrix h = sigmoid(X * theta);
	Matrix tmp = y.multiEachElement(log(h)) + (1 - y).multiEachElement(log(1 - h));

	J = (-1 / (double)m) * tmp.sum()[0][0];
}

void Logistic::createGradForTheta(){
	if (!loadedData()){
		cout << "Need to load data before creating gradient for each theta." << endl;
		return;
	}

	grad.createMat(theta.getSize().rows, 1);
}

void Logistic::initTheta(double value){
	if (!loadedData()){
		cout << "Need to load data before initing value for theta." << endl;
		return;
	}

	theta.createMat(n + 1, 1, value);
	createGradForTheta();
}

bool Logistic::loadDataAndInitTheta(){
	if (m == 0 || n == 0){
		cout << "Need to load data before using this attribute." << endl;
		return false;
	}

	if (theta.getSize().rows == 0 || theta.getSize().cols == 0){
		cout << "Need to init theta before using this attribute." << endl;
		return false;
	}

	return true;
}

void Logistic::addX0ForX(){

	if (!loadedData()){
		cout << "Need to load data before adding column 1 for X." << endl;
		return;
	}
	X.addX0();
}

void Logistic::updateGrad(){
	
	if (!loadDataAndInitTheta()){
		return;
	}

	Matrix h = sigmoid(X * theta);
	Matrix tmp = h - y;
	grad = X.transpose() * tmp * ((double)1 / m);
}

void Logistic::gradientDescent(int iter, double alpha){

	for (int i = 0; i < iter; i++){

		theta = theta - grad * alpha;
		updateGrad();
	}

	computeCost();
}

double Logistic::trainAccuracy(){
	if (!loadDataAndInitTheta()){
		return 0;
	}

	int trainTrue = m;
	Matrix _y = sigmoid(X * theta);

	for (int row = 0; row < y.getSize().rows; row++){
		if (_y[row][0] >= 0.5) _y[row][0] = 1;
		else{
			_y[row][0] = 0;
		}

		if (y[row][0] != _y[row][0]){
			trainTrue--;
		}

	}
	return (double)trainTrue * 100 / m;
}

void Logistic::autoGradientDescent(double alpha, double threshold){
	if (!loadDataAndInitTheta()){
		return;
	}

	double prevJ = 0;
	computeCost();
	
	while (abs(J - prevJ) >= threshold){
		updateGrad();
		theta = theta - grad * alpha;
		prevJ = J;
		computeCost();
	}

}

void Logistic::loadForPredict(const char* fileName){
	ifstream input(fileName);
	input >> m >> n;

	X.createMat(m, n);

	for (int row = 0; row < m; row++){

		for (int col = 0; col < n; col++){
			input >> X[row][col];
		}

	}

	cout << "Load data success !" << endl;
}

void Logistic::getThetaFromFile(const char *fileName){
	if (!loadedData()){
		cout << "Need to load data before using get theta from file." << endl;
		return;
	}

	ifstream input(fileName);

	if (!input.is_open()){
		cout << "Cannot access file " << fileName << " to get data." << endl;
		return;
	}

	theta.createMat(n + 1, 1);

	for (int i = 0; i < n + 1; i++){
		input >> theta[i][0];
	}
}

void Logistic::predict(){
	if (!loadDataAndInitTheta()){
		cout << "Need to load data and get data before predict. " << endl;
		return;
	}

	X.addX0();
	y = X * theta;
	y = sigmoid(y);

	for (int row = 0; row < y.getSize().rows; row++){
		if (y[row][0] >= 0.5){
			y[row][0] = 1;
		}
		else{
			y[row][0] = 0;
		}
	}
	cout << y;
	ofstream output("y.txt");
	output << y;
}