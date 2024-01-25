#pragma once
#include <iostream>
#include <Eigen/Dense>
#include <iomanip>

using namespace std;

class Matrix
{
private:
	int rows;
	int columns;
	double** matrix;
	const int numberMatrix;


public:
	static int amountMatrix;
	Matrix();
	Matrix(int rows, int columns);
	Matrix(Matrix& secMatrix);
	Matrix(Matrix&& secMatrix) noexcept;
	~Matrix();
	Matrix& operator=(Matrix& secMatrix);
	Matrix& operator=(Matrix&& secMatrix) noexcept;
	Matrix& operator+(Matrix& secMatrix);
	Matrix& operator-(Matrix& secMatrix);
	Matrix& operator*(double number);
	Matrix& operator*(Matrix& secMatrix);
	Matrix& transpone();
	Matrix& exponentation(int exp);
	double determinant() const;
	Matrix complement() const;
	Matrix& inverse();
	Matrix& operator/(Matrix& secMatrix);
	void enter();
	friend ostream& operator<<(ostream& wy, const Matrix& m);
};

ostream& operator<<(ostream& wy, const Matrix& m);
