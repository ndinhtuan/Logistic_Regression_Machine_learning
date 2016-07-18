#include "Matrix.h"
#include <iostream>

using std::endl;
using std::cin;
using std::cout;

#include <time.h>
#include <stdlib.h>
#include <iomanip>

using std::setw;

#include <cmath>

Matrix::Matrix()
{
	//cout << "This is default constructor." << endl;
	mat = NULL;
	size.rows = size.cols = 0;
}

Matrix::Matrix(int rows, int cols, int value){
	createMat(rows, cols, value);
}

Matrix::Matrix(const Matrix &obCopy){
	//cout << "This is copy constructor !" << endl;
	if ((obCopy.size.cols == 0 && obCopy.size.rows == 0) || obCopy.mat == NULL){
		return;
	}

	size = obCopy.size;
	mat = new long double*[size.rows];
	
	for (int i = 0; i < size.rows; i++){
		mat[i] = new long double[size.cols];
	}

	for (int i = 0; i < size.rows; i++){

		for (int j = 0; j < size.cols; j++){

			mat[i][j] = obCopy.mat[i][j];

		}

	}
}

Matrix::~Matrix()
{
	//cout << "This is destructor!" << endl;
	for (int i = 0; i < size.rows; i++){
		delete[] mat[i];
	}

	delete mat;
}

ostream& operator<<(ostream& os, const Matrix& ob){

	if (ob.mat == NULL || (ob.size.rows == 0 && ob.size.cols == 0)){
		os << "Matrix is empty. " << endl;
		return os;
	}

	os << "Matrix : " << endl;
	os << "[ " << endl;
	for (int i = 0; i < ob.size.rows; i++){
		
		os << "  ";
		for (int j = 0; j < ob.size.cols; j++){
			os << setw(5) << ob.mat[i][j] << " ";
		}
		os << endl;

	}
	os << "]" << endl;

	return os;
}

ostream& operator<<(ostream &os, const Size &ob){
	os << "Size : " << ob.rows << "  " << ob.cols << endl;

	return os;
}

Matrix& Matrix::transpose(){
	if (mat == NULL || (size.rows == 0 || size.cols == 0)){
		cout << "Matrix is empty." << endl;
		return *this;
	}

	long double **tmpMat = mat;

	int tmp = size.cols;
	size.cols = size.rows;
	size.rows = tmp;

	mat = new long double*[size.rows];
	for (int i = 0; i < size.rows; i++){
		mat[i] = new long double[size.cols];
	}

	for (int i = 0; i < size.rows; i++){

		for (int j = 0; j < size.cols; j++){

			mat[i][j] = tmpMat[j][i];

		}

	}

	return *this;
}

void Matrix::deleteMat(){

	if (mat == NULL){
		return;
	}

	for (int i = 0; i < size.rows; i++){
		delete[] mat[i];
	}

	delete mat;

	mat = NULL; // Need , because we will check mat with NULL to run deleteMat(). 

}

void Matrix::createMatRand(int ker){

	if (mat == NULL){
		createMat(size.rows, size.cols);
	}

	srand(time(0));

	for (int i = 0; i < size.rows; i++){

		for (int j = 0; j < size.cols; j++){
			mat[i][j] = rand() % ker;
		}

	}
}

void Matrix::createMat(int rows, int cols, int value){
	deleteMat();
	mat = new long double*[rows];

	for (int i = 0; i < rows; i++){

		mat[i] = new long double[cols];

	}

	size.rows = rows;
	size.cols = cols;

	for (int i = 0; i < rows; i++){

		for (int j = 0; j < cols; j++){

			mat[i][j] = value;

		}

	}
}

Size Matrix::getSize() const{
	return size;
}

long double& Matrix::operator()(int row, int col){
	return mat[row][col];
}

Matrix& Matrix::operator*=(long double scalar){
	for (int i = 0; i < size.rows; i++){

		for (int j = 0; j < size.cols; j++){
			mat[i][j] *= scalar;
		}

	}

	return *this;
}

Matrix& Matrix::operator=(const Matrix &right){
	//cout << "This is operator=" << endl;
	if (right.mat == NULL){
		cout << "Need to init value of matrix ." << endl;
		return *this;
	}
	if (*this == right){
		return *this;
	}

	if(mat != NULL) deleteMat(); // dellocate memory if mat havent dellocate. So need to assign mat for NULL after delete mat 
	size = right.size;
	createMat(size.rows, size.cols);

	for (int i = 0; i < size.rows; i++){
		for (int j = 0; j < size.cols; j++){
			mat[i][j] = right.mat[i][j];
		}
	}

	return *this;
}

bool Matrix::operator==(const Matrix &right){
	if (mat == NULL){
		return false;
	}
	if (size != right.size){
		return false;
	}

	for (int i = 0; i < size.rows; i++){
		
		for (int j = 0; j < size.cols; j++){
			if (mat[i][j] != right.mat[i][j]) return false;
		}

	}

	return true;
}

bool operator==(const Size &ob1,const Size &ob2){
	return ((ob1.cols == ob2.cols) && (ob1.rows == ob2.rows));
}

bool operator!=(const Size &ob1, const Size &ob2){
	return !(ob1 == ob2);
}

Matrix Matrix::elementsOfRow(int row){
	Matrix result;

	result.size.cols = size.cols;
	result.size.rows = 1;

	result.mat = new long double*[result.size.rows];

	if (result.mat == NULL){
		cout << "Allocate memory occur error !" << endl;
		return result;
	}

	result.mat[0] = new long double[size.cols];

	if (result.mat[0] == NULL){
		cout << "Allocate memory occur error !" << endl;
		return result;
	}

	for (int i = 0; i < size.cols; i++){
		result.mat[0][i] = mat[row][i];
	}

	return result; // This positive call copy constructor
}

Matrix& Matrix::operator+=(long double scalar){
	if ((size.rows == 0 || size.cols == 0) || mat == NULL){
		cout << "Need to init matrix before use this attribute." << endl;
		return *this;
	}
	
	for (int i = 0; i < size.rows; i++){

		for (int j = 0; j < size.cols; j++){
			mat[i][j] += scalar;
		}

	}

	return *this;
}

Matrix Matrix::operator+(const Matrix &ob2){
	if ((size.rows == 0 || size.cols == 0) || mat == NULL){
		cout << "Need to init matrix before use this attribute." << endl;
		return *this;
	}

	if ((ob2.size.rows == 0 || ob2.size.cols == 0) || ob2.mat == NULL){
		cout << "Need to init matrix before use this attribute." << endl;
		return *this;
	}

	if (size.rows != ob2.size.rows || size.cols != ob2.size.cols){
		cout << "Error : " << size << " +      " << ob2.size;
		return *this;
	}

	Matrix result(*this); 

	for (int i = 0; i < result.size.rows; i++){

		for (int j = 0; j < result.size.cols; j++){

			result.mat[i][j] += ob2.mat[i][j];

		}

	}

	return result;
}

Matrix Matrix::operator*(const Matrix &ob2){
	if ((size.rows == 0 || size.cols == 0) || mat == NULL){
		cout << "Need to init matrix before use this attribute." << endl;
		return *this;
	}

	if ((ob2.size.rows == 0 || ob2.size.cols == 0) || ob2.mat == NULL){
		cout << "Need to init matrix before use this attribute." << endl;
		return *this;
	}

	if (size.cols != ob2.size.rows){
		cout << "Error : " << size 
			<< "       *" << ob2.size;

		return *this;
	}

	Matrix result;
	result.createMat(size.rows, ob2.size.cols);

	for (int i = 0; i < result.size.rows; i++){

		for (int j = 0; j < result.size.cols; j++){
			
			for (int h = 0; h < size.cols; h++){
				result.mat[i][j] += mat[i][h] * ob2.mat[h][j];
			}

		}

	}

	return result;
}

Matrix Matrix::elementsOfCol(int col){
	Matrix result;

	result.createMat(size.rows, 1);

	if (size.rows == 0 || size.cols == 0 || mat == NULL){
		cout << "Need to init matrix" << endl;
		return result;
	}
	
	if (col < 0 || col >= size.cols){
		cout << "Value of col " << col << " is invalid." << endl;
		return result;
	}

	for (int i = 0; i < size.rows; i++){
		result.mat[i][0] = mat[i][col];
	}

	return result;
}

Matrix Matrix::operator-(const Matrix &ob2){

	if ((size.rows == 0 || size.cols == 0) || mat == NULL){
		cout << "Need to init matrix before use this attribute." << endl;
		return *this;
	}

	if ((ob2.size.rows == 0 || ob2.size.cols == 0) || ob2.mat == NULL){
		cout << "Need to init matrix before use this attribute." << endl;
		return *this;
	}

	if (size.rows != ob2.size.rows || size.cols != ob2.size.cols){
		cout << "Error : " << size << " +      " << ob2.size;
		return *this;
	}

	Matrix result(*this);

	for (int i = 0; i < result.size.rows; i++){

		for (int j = 0; j < result.size.cols; j++){
			result.mat[i][j] -= ob2.mat[i][j];
		}

	}

	return result;
}

Matrix Matrix::operator*(long double scalar){
	if ((size.rows == 0 || size.cols == 0) || mat == NULL){
		cout << "Need to init matrix before use this attribute." << endl;
		return *this;
	}

	Matrix result(*this);

	for (int i = 0; i < result.size.rows; i++){

		for (int j = 0; j < result.size.cols; j++){

			result.mat[i][j] *= scalar;

		}

	}

	return result;
}

long double* Matrix::operator[](int i){
	if (i < 0 && i >= size.rows){
		cout << "Index " << i << " out of memory of matrix." << endl;
		return mat[0];
	}

	return mat[i];
}

Matrix Matrix::multiEachElement(const Matrix &ob2){
	Matrix result(*this);

	if (size != ob2.size){
		cout << "Not use multiple each element for two different size";
		return result;
	}

	for (int i = 0; i < size.rows; i++){

		for (int j = 0; j < size.cols; j++){

			result.mat[i][j] *= ob2.mat[i][j];

		}

	}

	return result;
}

Matrix Matrix::plusEachElement(const Matrix &ob2){
	Matrix result(*this);

	if (size != ob2.size){
		cout << "Not use plus each element for two different size";
		return result;
	}

	for (int i = 0; i < size.rows; i++){

		for (int j = 0; j < size.cols; j++){

			result.mat[i][j] += ob2.mat[i][j];

		}

	}

	return result;
}

Matrix Matrix::minusEachElement(const Matrix &ob2){
	Matrix result(*this);

	if (size != ob2.size){
		cout << "Not use minus each element for two different size";
		return result;
	}

	for (int i = 0; i < size.rows; i++){

		for (int j = 0; j < size.cols; j++){

			result.mat[i][j] -= ob2.mat[i][j];

		}

	}

	return result;
}

Matrix Matrix::sum(){
	Matrix result(1, size.cols, 0);

	if (!existMat()){
		return result;
	}

	for (int col = 0; col < size.cols; col++){

		for (int row = 0; row < size.rows; row++){
			result.mat[0][col] += mat[row][col];
		}

	}

	return result;
}

Matrix Matrix::maxInCols(){
	Matrix result(2, size.cols, 0);

	if (!existMat()){
		return result;
	}

	for (int col = 0; col < size.cols; col++){
		long double max = mat[0][col];
		int index = 0;

		for (int row = 1; row < size.rows; row++){
			if (max < mat[row][col]){
				max = mat[row][col];
				index = row;
			}
		}

		result.mat[0][col] = max;
		result.mat[1][col] = index;
	}

	return result;
}

Matrix Matrix::maxInRows(){
	Matrix result(size.rows, 2, 0);

	if (!existMat()){
		return result;
	}

	for (int row = 0; row < size.rows; row++){

		long double max = mat[row][0];
		int index = 0;

		for (int col = 1; col < size.cols; col++){
			if (max < mat[row][col]){
				max = mat[row][col];
				index = col;
			}
		}

		result.mat[row][0] = max;
		result.mat[row][1] = index;

	}

	return result;
}

Matrix& Matrix::addX0(){
	if (!existMat()){
		return *this;
	}

	Matrix tmp(*this);
	deleteMat();
	createMat(tmp.size.rows, tmp.size.cols + 1);

	for (int row = 0; row < size.rows; row++){

		mat[row][0] = 1;
		for (int col = 1; col < size.cols; col++){
			mat[row][col] = tmp.mat[row][col - 1];
		}

	}

	return *this;
}

Matrix Matrix::operator^(int num){
	if (!existMat()){
		return *this;
	}

	for (int row = 0; row < size.rows; row++){

		for (int col = 0; col < size.cols; col++){

			mat[row][col] = pow(mat[row][col], 2);
			
		}

	}

	return *this;
}
































