#pragma once
#include <iostream>

using namespace std;

class MatrixException {

public:
	const char* problem;
	MatrixException() : problem("") {}
	MatrixException(const char* reason) : problem(reason) {}
};

class Matrix {

protected:
	double** mat; // матрица
	int rows; // количество строк в матрице
	int cols; // количество столбцов в матрице

	friend istream& operator >> (istream&, Matrix&); // перегруженный оператор ввода
	friend ostream& operator << (ostream&, const Matrix&); // перегруженный оператор вывода

public:
	Matrix();// конструктор по умолчанию
	Matrix(int, int); // конструктор с параметрами
	Matrix(const Matrix&); // конструктор копии
	~Matrix(); // деструктор

	double& operator () (int, int); // оператор взятия индекса
	const Matrix& operator = (const Matrix&); // оператор присваивания

	Matrix operator + (const Matrix&); // сложение
	Matrix operator - (const Matrix&); // вычитание
	Matrix operator * (const Matrix&); // умножение
	Matrix operator ^ (const Matrix&); // произведение Адамара
	Matrix operator * (double); // умножение на число справа
	friend Matrix operator * (double, Matrix); // умножение на число слева

	// методы для ЛР 2
	double tr(); // след матрицы
	double det(); // определитель матрицы
	double scalar(const Matrix&); // скалярное произведение
	Matrix vector(const Matrix&); // векторное произведение
	double euclNorm(); // евклидова норма
	double maxNorm(); // максимальная норма
	double frobNorm(); // норма Фробениуса

	// методы для ЛР 3
	double angle(const Matrix&); // угол между векторами
	double rank(); // ранг матрицы
	Matrix reverse(); // обратная матрица
	Matrix transpose(); // транспонированная матрица
};

class Edinichnaya : public Matrix {

public:
	Edinichnaya(const int matR);
};

class Diagonalnaya : public Matrix {

protected:
	friend istream& operator >> (istream&, Diagonalnaya&);

public:
	Diagonalnaya(const int matR);
};

class Simmetrichnaya : public Matrix {

protected:
	friend istream& operator >> (istream&, Simmetrichnaya&);

public:
	Simmetrichnaya(const int matR);
};

class VerhnayaTr : public Matrix {

protected:
	friend istream& operator >> (istream&, VerhnayaTr&);

public:
	VerhnayaTr(const int matR);
};

class NizhnayaTr : public Matrix {

protected:
	friend istream& operator >> (istream&, NizhnayaTr&);

public:
	NizhnayaTr(const int matR);
};
