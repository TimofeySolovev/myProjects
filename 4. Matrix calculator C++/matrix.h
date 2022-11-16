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
	double** mat; // �������
	int rows; // ���������� ����� � �������
	int cols; // ���������� �������� � �������

	friend istream& operator >> (istream&, Matrix&); // ������������� �������� �����
	friend ostream& operator << (ostream&, const Matrix&); // ������������� �������� ������

public:
	Matrix();// ����������� �� ���������
	Matrix(int, int); // ����������� � �����������
	Matrix(const Matrix&); // ����������� �����
	~Matrix(); // ����������

	double& operator () (int, int); // �������� ������ �������
	const Matrix& operator = (const Matrix&); // �������� ������������

	Matrix operator + (const Matrix&); // ��������
	Matrix operator - (const Matrix&); // ���������
	Matrix operator * (const Matrix&); // ���������
	Matrix operator ^ (const Matrix&); // ������������ �������
	Matrix operator * (double); // ��������� �� ����� ������
	friend Matrix operator * (double, Matrix); // ��������� �� ����� �����

	// ������ ��� �� 2
	double tr(); // ���� �������
	double det(); // ������������ �������
	double scalar(const Matrix&); // ��������� ������������
	Matrix vector(const Matrix&); // ��������� ������������
	double euclNorm(); // ��������� �����
	double maxNorm(); // ������������ �����
	double frobNorm(); // ����� ����������

	// ������ ��� �� 3
	double angle(const Matrix&); // ���� ����� ���������
	double rank(); // ���� �������
	Matrix reverse(); // �������� �������
	Matrix transpose(); // ����������������� �������
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
