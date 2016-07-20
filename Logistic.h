#ifndef LOGISTIC_H
#define LOGISTIC_H
#include "Matrix.h"

class Logistic
{
public:
	Logistic();
	~Logistic();
	void loadData(const char*);
	Matrix sigmoid(Matrix&);
	void computeCost();
	bool loadedData();
	bool loadDataAndInitTheta();
	void initTheta(double value = 0);
	void createGradForTheta();
	void addX0ForX();
	void updateGrad();
	void gradientDescent(int iter, double alpha);
	void autoGradientDescent(double alpha, double threshold = 0.01); // base on cost function J to stop
	double trainAccuracy();

	const Matrix& getX(){
		return X;
	}
	const Matrix& getY(){
		return y;
	}
	long double getJ(){
		return J;
	}
	const Matrix& getGrad(){
		return grad;
	}
	Matrix getTheta(){
		return theta;
	}
private:
	Matrix X;
	Matrix y;
	int m;
	int n;
	long double J;
	Matrix grad;
	Matrix theta;
};
#endif
