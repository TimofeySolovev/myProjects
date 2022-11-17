#pragma once
#include <iostream>

using namespace std;

class MatrixException {

public:
	const char* problem;
	MatrixException() : problem("") {}
	MatrixException(const char* reason) : problem(reason) {}
};
а
class Matrix {

protected:
	double** mat; // ìàòðèöà
	int rows; // êîëè÷åñòâî ñòðîê â ìàòðèöå
	int cols; // êîëè÷åñòâî ñòîëáöîâ â ìàòðèöå

	friend istream& operator >> (istream&, Matrix&); // ïåðåãðóæåííûé îïåðàòîð ââîäà
	friend ostream& operator << (ostream&, const Matrix&); // ïåðåãðóæåííûé îïåðàòîð âûâîäà

public:
	Matrix();// êîíñòðóêòîð ïî óìîë÷àíèþ
	Matrix(int, int); // êîíñòðóêòîð ñ ïàðàìåòðàìè
	Matrix(const Matrix&); // êîíñòðóêòîð êîïèè
	~Matrix(); // äåñòðóêòîð

	double& operator () (int, int); // îïåðàòîð âçÿòèÿ èíäåêñà
	const Matrix& operator = (const Matrix&); // îïåðàòîð ïðèñâàèâàíèÿ

	Matrix operator + (const Matrix&); // ñëîæåíèå
	Matrix operator - (const Matrix&); // âû÷èòàíèå
	Matrix operator * (const Matrix&); // óìíîæåíèå
	Matrix operator ^ (const Matrix&); // ïðîèçâåäåíèå Àäàìàðà
	Matrix operator * (double); // óìíîæåíèå íà ÷èñëî ñïðàâà
	friend Matrix operator * (double, Matrix); // óìíîæåíèå íà ÷èñëî ñëåâà

	// ìåòîäû äëÿ ËÐ 2
	double tr(); // ñëåä ìàòðèöû
	double det(); // îïðåäåëèòåëü ìàòðèöû
	double scalar(const Matrix&); // ñêàëÿðíîå ïðîèçâåäåíèå
	Matrix vector(const Matrix&); // âåêòîðíîå ïðîèçâåäåíèå
	double euclNorm(); // åâêëèäîâà íîðìà
	double maxNorm(); // ìàêñèìàëüíàÿ íîðìà
	double frobNorm(); // íîðìà Ôðîáåíèóñà

	// ìåòîäû äëÿ ËÐ 3
	double angle(const Matrix&); // óãîë ìåæäó âåêòîðàìè
	double rank(); // ðàíã ìàòðèöû
	Matrix reverse(); // îáðàòíàÿ ìàòðèöà
	Matrix transpose(); // òðàíñïîíèðîâàííàÿ ìàòðèöà
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
