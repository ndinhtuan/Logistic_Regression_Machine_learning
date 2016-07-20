#include "MatrixLib.h"


Matrix eyes(int dim){
	Matrix result;
	long double **tmp = new long double*[dim];

	for (int i = 0; i < dim; i++){
		tmp[i] = new long double[dim];
	}

	for (int i = 0; i < dim; i++){
		for (int j = 0; j < dim; j++){

			if (i == j){
				tmp[i][j] = 1;
			}
			else{
				tmp[i][j] = 0;
			}

		}
	}
	
	result.setMat(tmp);
	result.setCols(dim);
	result.setRows(dim);

	return result;
}


Matrix zeros(int rows, int cols){
	Matrix result;
	long double **tmp = new long double*[rows];

	for (int i = 0; i < rows; i++){
		tmp[i] = new long double[cols];
	}

	for (int i = 0; i < rows; i++){

		for (int j = 0; j < cols; j++){
			tmp[i][j] = 0;
		}

	}

	result.setRows(rows);
	result.setCols(cols);
	result.setMat(tmp);

	return result;
}

Matrix log(Matrix &ob){
	if (!ob.existMat()){
		return ob;
	}

	Matrix result(ob.getSize().rows, ob.getSize().cols);

	for (int row = 0; row < result.getSize().rows; row++){

		for (int col = 0; col < result.getSize().cols; col++){

			result[row][col] = log(ob[row][col]);

		}

	}

	return result;
}