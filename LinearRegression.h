#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H
#include "Matrix.h"

class LinearRegression
{
public:
	LinearRegression();
	~LinearRegression();
	void loadData(char* fileName);
	void displayX();
	void displayY();
	void displayTheta(){
		std::cout << theta;
	}
	void displayGrad();
	int getN(){
		return n;
	}
	int getM(){
		return m;
	}
    long double getJ(){
		return J;
	}
	const Matrix& getX(){
		return X;
	}
	const Matrix& getY(){
		return y;
	}
	const Matrix& getTheta(){
		return theta;
	}
	const Matrix& getGrad(){
		return grad;
	}
	void computeCost(); // compute cost function J
	void initTheta(int value = 0);
	void createGradForTheta();
	void updateGrad(); // No use regularize term
	void addX0ForX();
	//TO-DO
	void gradientDescent(int iter, long double lambda);
private:
	Matrix X; // X of training
	Matrix y; //y of training
	int m; // numbers of examples
	int n; // number of features
	long double J; // cost function
	Matrix theta; // theta
	Matrix grad; // deriver of J with thetaj

	bool loadDataAndInitTheta(){
		if (m == 0 || n == 0){
			std::cout << "Need to load data before use this attribute." << std::endl;
			return false;
		}

		if (theta.getSize().rows == 0 || theta.getSize().cols == 0){
			std::cout << "Need to init theta before use this attribute." << std::endl;
			return false;
		}

		return true;
	}
};
#endif
