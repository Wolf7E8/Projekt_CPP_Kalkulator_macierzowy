#include "Matrix.h"

int Matrix::amountMatrix = 1;

Matrix::Matrix(): numberMatrix(amountMatrix)
{
	rows = 0;
	columns = 0;
	matrix = nullptr;
}

Matrix::Matrix(int rows, int columns) :rows(rows), columns(columns), numberMatrix(amountMatrix)
{
	amountMatrix++;
	//dynamiczna alokacja pamięci dla macierzy
	matrix = new double*[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new double[columns];
	}

	//domyślne wypełnienie macierzy zerami
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

Matrix::Matrix(Matrix& secMatrix) :rows(secMatrix.rows), columns(secMatrix.columns), numberMatrix(amountMatrix)
{
	amountMatrix++;
	//dynamiczna alokacja pamięci dla macierzy
	matrix = new double* [rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new double[columns];
	}

	//przepisanie macierzy
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = secMatrix.matrix[i][j];
		}
	}

}

Matrix::Matrix(Matrix&& secMatrix) noexcept : numberMatrix(secMatrix.numberMatrix), matrix(secMatrix.matrix), rows(secMatrix.rows), columns(secMatrix.columns)
{
	secMatrix.rows = 0;
	secMatrix.columns = 0;
	secMatrix.matrix = nullptr;
}

Matrix::~Matrix()
{
	rows = 0;
	columns = 0;
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

Matrix& Matrix::operator=(Matrix& secMatrix)
{
	//zwolnienie pamięci obiektu do którego przypisujemy
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;

	rows = secMatrix.rows;
	columns = secMatrix.columns;
	//ponowna alokacja
	matrix = new double* [rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new double[columns];
	}
	//przepisanie wartości
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = secMatrix.matrix[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator=(Matrix&& secMatrix) noexcept
{
	if (this != &secMatrix)
	{
		//zwolnienie pamięci obiektu do którego przypisujemy
		for (int i = 0; i < rows; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;

		rows = secMatrix.rows;
		columns = secMatrix.columns;
		matrix = secMatrix.matrix;
		secMatrix.matrix = nullptr;
	}
	return *this;
}

Matrix& Matrix::operator+(Matrix& secMatrix)
{
	if (rows != secMatrix.rows || columns != secMatrix.columns)
	{
		cerr << "ERROR: Macierze które próbowałeś dodać nie mają takich samych wymiarów!" << endl;
		cerr << "V" << numberMatrix << "<" << rows << "," << columns << "> + V" << secMatrix.numberMatrix << "<" << secMatrix.rows << "," << secMatrix.columns << "> <- operacja niemożliwa" << endl;
		exit(1);
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = matrix[i][j] + secMatrix.matrix[i][j];
		}
	}
	//delete &secMatrix;
	return *this;
}

Matrix& Matrix::operator-(Matrix& secMatrix)
{
	if (rows != secMatrix.rows || columns != secMatrix.columns)
	{
		cerr << "ERROR: Macierze które próbowałeś odjąć nie mają takich samych wymiarów!" << endl;
		cerr << "V" << numberMatrix << "<" << rows << "," << columns << "> - V" << secMatrix.numberMatrix << "<" << secMatrix.rows << "," << secMatrix.columns << "> <- operacja niemożliwa" << endl;
		exit(1);
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = matrix[i][j] - secMatrix.matrix[i][j];
		}
	}
	//delete& secMatrix;
	return *this;
}

Matrix& Matrix::operator*(double number)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = matrix[i][j] * number;
		}
	}
	return *this;
}

Matrix& Matrix::operator*(Matrix& secMatrix)
{
	if (columns != secMatrix.rows)
	{
		cerr << "ERROR: Mnożenie macierzy nie udane!\nLiczba kolumn pierwszej macierzy musi być równa liczbie wierszy drugiej macierzy" << endl;
		cerr << "V" << numberMatrix << "<" << rows << "," << columns << "> * V" << secMatrix.numberMatrix << "<" << secMatrix.rows << "," << secMatrix.columns << "> <- operacja niemożliwa" << endl;
		exit(1);
	}

	Matrix auxMatrix(rows, secMatrix.columns);
	double tempSum = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < secMatrix.columns; j++)
		{
			for (int z = 0; z < columns; z++)
			{
				tempSum += matrix[i][z] * secMatrix.matrix[z][j];
			}
			auxMatrix.matrix[i][j] = tempSum;
			tempSum = 0;
		}
	}

	*this = move(auxMatrix);
	/*for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = auxMatrix.matrix[i][j];
		}
	}*/
	//delete& secMatrix;
	return *this;
}

Matrix& Matrix::transpone()
{
	Matrix auxMatrix(columns, rows);

	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			auxMatrix.matrix[i][j] = matrix[j][i];
		}
	}

	*this = move(auxMatrix);
	/*for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = auxMatrix.matrix[i][j];
		}
	}*/

	return *this;
}

Matrix& Matrix::exponentation(int exp)
{
	Matrix auxMatrix(*this);

	/*for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			auxMatrix.matrix[i][j] = matrix[i][j];
		}
	}*/

	int counter = 1;
	while (counter < exp)
	{
		*this * auxMatrix;
		counter++;
	}
	return *this;
}

double Matrix::determinant() const
{
	if (rows != columns)
	{
		cerr << "ERROR: Macierz której próbowałeś obliczyć wyznacznik nie jest kwadratowa!" << endl;
		cerr << "Jest to macierz: V" << numberMatrix << "<" << rows << "," << columns << ">" << endl;
		exit(1);
	}

	double det;
	Eigen::MatrixXd auxMatrix(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			auxMatrix(i, j) = matrix[i][j];
		}
	}

	det = auxMatrix.determinant();
	return det;
}

Matrix Matrix::complement() const
{
	if (rows != columns)
	{
		cerr << "ERROR: Macierz której próbowałeś obliczyć macierz odwrotną nie jest kwadratowa!" << endl;
		cerr << "Jest to macierz: V" << numberMatrix << "<" << rows << "," << columns << ">" << endl;
		exit(1);
	}
	Matrix auxMatrix(rows-1, columns-1);
	Matrix complementMatrix(rows, columns);
	int k = 0;
	int m = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			k = 0;
			m = 0;
			for (int dw = 0; dw < rows; dw++)
			{
				for (int dk = 0; dk < columns; dk++)
				{
					if (dw != i && dk != j)
					{
						auxMatrix.matrix[k][m] = matrix[dw][dk];
						m++;
						if (m >= rows-1)
						{
							k++;
							m = 0;
						}
					}
				}
			}
			complementMatrix.matrix[i][j] = auxMatrix.determinant();
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			complementMatrix.matrix[i][j] = (i + j) % 2 == 0 ? complementMatrix.matrix[i][j] : -complementMatrix.matrix[i][j];
		}
	}
	return complementMatrix;
}

Matrix& Matrix::inverse()
{
	double det = determinant();
	if (det == 0)
	{
		cerr << "ERROR: Macierz którą próbowałeś odwrócić ma wyznacznik równy 0!" << endl;
		cerr << "Jest to macierz: V" << numberMatrix << "<" << rows << "," << columns << ">" << endl;
		exit(1);
	}
	Matrix complementMatrix(complement());
	complementMatrix.transpone();
	*this = complementMatrix * (1 / det);
	return *this;
}

Matrix& Matrix::operator/(Matrix& secMatrix)
{
	*this * (secMatrix.inverse());
	return *this;
}

void Matrix::enter()
{
	cout << "Podaj elementy macierzy V" << numberMatrix << "<" << rows << "," << columns << ">:" << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << "[" << i << "," << j << "] = ";
			cin >> matrix[i][j];
		}
	}
}

ostream& operator<<(ostream& wy, const Matrix& m)
{
	wy << "\nMacierz wynikowa:" << endl;
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.columns; j++)
		{
			wy << setw(8) << round(m.matrix[i][j] * 1000) / 1000;
			//wy << m.matrix[i][j] << " ";
		}
			wy << endl;
	}
	return wy;
}
