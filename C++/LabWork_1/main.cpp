#include <iostream>

#include "matrix/matrix.hpp"

int main()
{
	Matrix<int> matrix1(5, 5, 5, 5, 0, 100);
	std::cout << matrix1;
	
	Matrix<int> matrix2(5, 5, 5, 5, 0, 100);
	std::cout << matrix2;
	
	Matrix<int> matrix3;
	matrix3 = matrix1 * matrix2;

//	Matrix<float> matrix1(5, 5, 5, 5, 0.0, 100.0);
//	std::cout << matrix1;
//
//	Matrix<double> matrix2(5, 5, 5, 5, 0, 100);
//	std::cout << matrix2;


//	std::cout << "Hello world!" << std::endl;
	return 0;
}
