//
// Created by Belousov Ilya on 3.02.22.
//

#pragma once

#include <vector>
#include <iostream>
#include <random>
#include <iomanip>

template <typename Type>
class Matrix
{
public:
	using secondary_matrix = std::vector<std::vector<Type>>;
	using primary_matrix = std::vector<std::vector<secondary_matrix>>;
	
private:
	primary_matrix matrix;
	
	size_t primary_matrix_size_row;
	size_t primary_matrix_size_column;
	
	size_t secondary_matrix_size_row;
	size_t secondary_matrix_size_column;

public:
	Matrix() = default;
	explicit Matrix(size_t size_primary_row, size_t size_primary_column,
	                size_t size_secondary_row, size_t size_secondary_column,
					Type min, Type max);
	
	Matrix(const Matrix &M) = default;

	Matrix &operator=(const Matrix &M) = default;
	
	template <typename type>
	friend Matrix<type> operator*(const Matrix<type> &lhs, const Matrix<type> &rhs);
//	friend Matrix MultiplicationPrimaryMatrix(const Matrix &lhs, const Matrix &rhs);
//	friend Matrix MultiplicationSecondaryMatrix(const Matrix );
	

	void Generate(Type min, Type max);
	
	template <typename type>
	friend std::ostream &operator<<(std::ostream &os, const Matrix<type> &M);

private:
	void InitMatrix();
};

template <typename Type>
Matrix<Type>::Matrix(size_t size_primary_row, size_t size_primary_column,
               size_t size_secondary_row, size_t size_secondary_column,
               Type min, Type max)
	: primary_matrix_size_row(size_primary_row), primary_matrix_size_column(size_primary_column)
	, secondary_matrix_size_row(size_secondary_row), secondary_matrix_size_column(size_secondary_column)
{
	InitMatrix();
	Generate(min, max);
}

template <typename Type>
Matrix<Type> operator*(const Matrix<Type> &lhs, const Matrix<Type> &rhs)
{
	Matrix<Type> total_matrix;
	
	
	return total_matrix;
}

template <typename Type>
void Matrix<Type>::Generate(Type min, Type max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max);

	for (auto &primary_row : matrix)
	{
		for (auto &primary_column : primary_row)
		{
			for (auto &secondary_row : primary_column)
			{
				for (auto &secondary_column : secondary_row)
				{
					secondary_column = dis(rd);
				}
			}
		}
	}
}

template <typename Type>
std::ostream &operator<<(std::ostream &os, const Matrix<Type> &M)
{
	for (auto &primary_row : M.matrix)
	{
		for (auto &primary_column : primary_row)
		{
			for (auto &secondary_row : primary_column)
			{
				for (auto &secondary_column : secondary_row)
				{
					os << std::setw(8) << secondary_column << " ";
				}
				os << std::setw(5) << os.fill(' ');
			}
			os << "\n";
		}
		os << "\n";
	}
	os << std::endl;
	return os;
}

template <typename Type>
void Matrix<Type>::InitMatrix()
{
	matrix.resize(primary_matrix_size_row);
	for (auto &primary_column : matrix)
	{
		primary_column.resize(primary_matrix_size_column);
		for (auto &secondary_row : primary_column)
		{
			secondary_row.resize(secondary_matrix_size_row);
			for (auto &secondary_column : secondary_row)
			{
				secondary_column.resize(secondary_matrix_size_column);
			}
		}
	}
}