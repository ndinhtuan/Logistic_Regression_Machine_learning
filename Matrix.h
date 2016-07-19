#ifndef MATRIX_H
#define MATRIX_H
#define ALL 0
#include <iostream>

using std::ostream;

struct Size{
	int rows;
	int cols;
};

ostream& operator<<(ostream&, const Size&);
bool operator==(const Size &ob1, const Size &ob2);
bool operator!=(const Size &ob1, const Size &ob2);

class Matrix
{
	friend ostream& operator<<(ostream&, const Matrix&);
public:
	Matrix();
	Matrix(int rows, int cols, int value = 0);
	Matrix(const Matrix&);
	~Matrix();
	void setRows(int rows){
		this->size.rows = rows;
	}
	void setCols(int cols){
		this->size.cols = cols;
	}
	void setMat(long double **mat){
		this->mat = mat;
	}
	Matrix transpose();
	void createMatRand(int ker);
	void createMat(int rows, int cols, int value = 0);
	Size getSize() const;

	long double& operator()(int row, int col);
	Matrix& operator*=(long double scalar);
	Matrix operator*(long double scalar);
	Matrix operator*(const Matrix&);
	Matrix& operator=(const Matrix&);
	bool operator==(const Matrix&);
	Matrix& operator+=(long double scalar);
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	long double* operator[](int i);
	Matrix operator/(double scalar);
	Matrix operator/(const Matrix &ob2);

	Matrix operator^(double num);
	Matrix multiEachElement(const Matrix&);
	Matrix plusEachElement(const Matrix&); // NO NEED
	Matrix minusEachElement(const Matrix&); // NO NEED

	Matrix elementsOfRow(int row);
	Matrix elementsOfCol(int col);
	Matrix sum();
	// function maxInCols return Matrix 2 * size.cols. with row 1 is max value of col and row 2 is index of max value of col
	Matrix maxInCols();

	// function maxInRows return Matrix size.rows * 2, with col 1 is max value of row and col 2 is index of max value of row
	Matrix maxInRows();

	// add X0 add colum X0 = size.rows * 1 [1] at left matrix -> serve for machine learning .
	Matrix& addX0();

	// Compute average of matrix follow column
	Matrix mean();

	//standard deviation.
	Matrix STD();
private:
	long double **mat;
	Size size;

	void deleteMat();
	bool existMat(){
		if (size.rows == 0 || size.cols == 0 || mat == NULL){
			std::cout << "Need to init matrix" << std::endl;
			return false;
		}
		return true;
	}
};
#endif
