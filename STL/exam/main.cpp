#include <iostream>
using namespace std;
//написать класс матрица

class Matrix {
	int rows;//stroka
	int cols;//kolonka
	int** matx;
	int deg;
public:
	int get_deg()
	{
		return this->deg;
	}
	int set_deg(const int deg)
	{
		this->deg = deg;
	}
	int get_rows() const
	{
		return this->rows;
	}
	int get_cols() const
	{
		return this->cols;
	}

	void set_rows(const int rows)
	{
		this->rows = rows;
	}
	void set_cols(const int cols)
	{
		this->cols = cols;
	}

	Matrix(int Row, int Col)
	{
		this->rows = Row;
		this->cols = Col;
		matx = new int* [rows];
		for (int i = 0; i < rows; i++)
		{
			matx[i] = new int[cols] {};
		}
		//std::cout << "Constructor:\t" << this << std::endl;
	}
	Matrix(const Matrix& other) :Matrix(other.cols, other.rows)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				matx[i][j] = other.matx[i][j];
			}
		}
		//std::cout << "CopyConstructor:" << this << std::endl;
	}
	~Matrix()
	{
		//cout << "MATRIX_Destructor" << endl;
		for (int i = 0; i < rows; i++)
			delete[] matx[i];
		delete[] matx;
	}
	void SetMatrix()
	{
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				matx[i][j] = rand() % 30;
			}
		}
	}
	void printMatrix()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << matx[i][j] << "\t";
			}
			cout << endl;
			cout << endl;

		}
	}

	Matrix operator+(const Matrix other)
	{
		if (this->rows != other.rows || this->cols != other.cols)throw std::exception("Bad matrix size in operator +");
		Matrix result(rows, cols);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				result.matx[i][j] = this->matx[i][j] + other.matx[i][j];
			}
		}
		return result;
	}
	Matrix operator-(const Matrix other)
	{
		if (this->rows != other.rows || this->cols != other.cols)throw std::exception("Bad matrix size in operator -");
		Matrix result(rows, cols);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				result.matx[i][j] = this->matx[i][j] - other.matx[i][j];
			}
		}
		return result;
	}
	Matrix operator*(const Matrix& other)
	{
		if (this->rows != other.rows || this->cols != other.cols)throw std::exception("Bad matrix size in operator *");
		Matrix result(rows, cols);

		/*for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				result.matx[i][j] = this->matx[i][j] * other.matx[i][j];
			}
		}*/
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++) 
			{
				result.matx[i][j] = 0;
				for (int k = 0; k < rows; k++)
					result.matx[i][j] += this->matx[i][k] * other.matx[k][j];
			}
		}
		return result;
	}


	void transponed()
	{
		int buffer;
		int start = 0;
		for (int i = start; i < rows; i++)
		{
			for (int j = start; j < cols; j++)
			{
				/*buffer = matx[i][j];
				matx[i][j] = matx[j][i];
				matx[j][i] = buffer;*/
				swap(matx[i][j], matx[j][i]);
			}
			start++;
		}
	}

	void obrat()
	{

	}
	int determinant_2x2()
	{
		int det;
		det = matx[0][0] * matx[1][1] - matx[0][1] * matx[1][0];
		return det;
	}

	int determinant_3x3()
	{
		int det;
		//det = matx[0][0] * matx[1][1] * matx[2][2] + matx[0][1] * matx[1][2] * matx[2][0] +
		//	  matx[0][2] * matx[1][0] * matx[2][1] - matx[0][2] * matx[1][1] * matx[2][0] -
		//		matx[0][0] * matx[1][2] * matx[2][1] - matx[0][1] * matx[1][0] * matx[2][2];

		return det;
	}
	Matrix& operator^(const int deg)
	{
		if (this->cols != this->rows)throw std::exception("Bad matrix size in operator ^");
		Matrix result(rows, cols);
		this->deg = deg;

		/*for (int d = 0; d < deg; d++)
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					  this->matx[i][j] = this->matx[i][j] * this->matx[i][j];
				}

			}

		}*/

		for (int i = 0; i < deg; i++)
		{
			result = result * *this;
		}

		return *this;
	} 
	Matrix& operator*=(const Matrix& other)
	{
		*this = *this * other;
		return *this;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int det;
	int Row, Col;
	cout << "Введите размер массива: ";
	cout << "\nКолонки?:"; cin >> Row;
	cout << "\nСтроки ?:"; cin >> Col;


	Matrix mat(Row, Col);
	mat.SetMatrix();
	mat.printMatrix();
	//mat.transponed();
	//mat.printMatrix();
	cout << "\n-------------------------------------\n";
	Matrix mat2(Row, Col);
	mat2.SetMatrix();
	mat2.printMatrix();
	//cout << "\n-------------------------------------\n";
	//cout << "Результат сложения: " << endl;
	////Matrix mat3;
	//Matrix mat3 = mat + mat2;
	//mat3.printMatrix();
	//
	//вычитание
	/*
	cout << "\n-------------------------------------\n";
	cout << "Результат вычитания: " << endl;
	Matrix mat4 = mat - mat2;
	mat4.printMatrix();
	*/

	//умножение
	/*
	cout << "\n-------------------------------------\n";
	cout << "Результат умножения: " << endl;
	Matrix mat5 = mat * mat2;
	mat5.printMatrix();*/

	//Умножение на число
	/*cout << "\n-------------------------------------\n";
	int num;
	cout << "Введите число, на которые хотите умножит матрицу: "; cin >> num;
	cout << "Результат умножения на число: " << endl;
	Matrix mat6 = mat * num;
	mat6.printMatrix();*/

	//транспонирование матрицы
	/*
	cout << "\n-------------------------------------\n";
	cout << "Результат транспонирования матрицы: " << endl;
	mat.transponed();
	mat.printMatrix();
	*/

	//возведение матрицы в степень 
	cout << "\n-------------------------------------\n";
	int deg;
	cout << "Введите степень, к которой хотите вознести матрицу: "; cin >> deg;
	cout << "Результат вознесения в степень: " << endl;
	Matrix mat7 = mat ^ deg;
	mat7.printMatrix();

	//determinant_2x2
	/*
	cout << "\n-------------------------------------\n";
	det = mat.determinant_2x2();
	cout << "Детерминант матрицы 2х2 равен " << det;
	cout << "\n-------------------------------------\n";
	*/

	//determinant_3x3
	/*cout << "\n-------------------------------------\n";
	det = mat.determinant_3x3();
	cout << "Детерминант матрицы 3х3 равен " << det;
	cout << "\n-------------------------------------\n";*/

	/*cout << "\n-------------------------------------\n";
	//обратная матрица
	mat.obrat();
	mat.printMatrix();*/
}