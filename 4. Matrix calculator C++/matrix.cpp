#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <array>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "matrix.h"

using namespace std;

Matrix::Matrix() { // ����������� �� ���������

	rows = 5; // �� ���������
	cols = 5;
	int q = -1;
	mat = new double* [rows];

	for (int i = 0; i < rows; i++) {
		mat[i] = new double[cols];
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			mat[i][j] = rand() % 10 + 0;
			q = rand() % 2 + 0;
			if (q == 1) {
				mat[i][j] = -mat[i][j];
			}
		}
	}
}

Matrix::Matrix(int matR, int matC) { // ����������� � �����������

	rows = matR;
	cols = matC;
	int q = -1;
	mat = new double* [rows];

	for (int i = 0; i < rows; i++) {
		mat[i] = new double[cols];
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			mat[i][j] = rand() % 10 + 0;
			q = rand() % 2 + 0;
			if (q == 1) {
				mat[i][j] = -mat[i][j];
			}

		}
	}
}

Matrix::Matrix(const Matrix& obj) { // ����������� �����

	rows = obj.rows;
	cols = obj.cols;
	mat = new double* [rows];

	for (int i = 0; i < rows; i++) {
		mat[i] = new double[cols];
		for (int j = 0; j < cols; j++) {
			mat[i][j] = obj.mat[i][j];
		}
	}
}

Matrix::~Matrix() { // ����������

	for (int i = 0; i < rows; i++) {
		delete[] mat[i];
	}
	delete[] mat;
}

//=========================================================================== ������������� ��������� ��� ������ Matrix

istream& operator >> (istream& in, Matrix& obj) { // ���� ��������� �������

	cout << "������� �������� ������� (�������) ������� " << obj.rows << "x" << obj.cols << ":" << endl;

	for (int i = 0; i < obj.rows; i++) {
		for (int j = 0; j < obj.cols; j++) {
			in >> obj.mat[i][j];
		}
	}

	return in; // ��������� ������������� ����, ���� cin >> x >> y >> z >> ...
}

ostream& operator << (ostream& out, const Matrix& obj) { // ����� ��������� ������� �� �����

	cout << "������� (������):" << endl;

	for (int i = 0; i < obj.rows; i++) {
		for (int j = 0; j < obj.cols; j++) {
			if (abs(obj.mat[i][j]) > 0.00000000001) {
				out << setw(8) << setprecision(3) << obj.mat[i][j]; // ��� ������ ����� ���������� 8 �������
			}
			else {
				out << setw(5) << 0;
			}
		}
		cout << endl;
	}
	out << endl;

	return out; // ��������� ������������� �����, ���� cout << x << y << z << ...
}

double& Matrix::operator () (int matR, int matC) { // �������� ������ �������

	if (matR < 0 || matR >= rows || matC < 0 || matC >= cols) {
		throw MatrixException("������������ ������");
	}
	return *mat[matR, matC]; // ������� ��������� �� ������� �������
}

const Matrix& Matrix::operator = (const Matrix& obj) { // �������� ������������

	if (&obj != this) { // ����� �� ����������� ����������������
		if (rows != obj.rows || cols != obj.cols) {

			for (int i = 0; i < rows; i++) {
				delete[] mat[i];
			}
			delete[] mat;

			rows = obj.rows;
			cols = obj.cols;

			mat = new double* [rows];
			for (int i = 0; i < rows; i++) {
				mat[i] = new double[cols];
			}
		}

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				mat[i][j] = obj.mat[i][j];
			}
		}
	}
	return *this; // ��������� ������������� ������������, ���� x = y = z = ...
}

Matrix Matrix::operator + (const Matrix& obj) { // ��������

	if (rows != obj.rows || cols != obj.cols) {
		throw MatrixException("������� ������ ��������");
	}

	Matrix res(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			res.mat[i][j] = mat[i][j] + obj.mat[i][j];
		}
	}
	return (Matrix)res;
}

Matrix Matrix::operator - (const Matrix& obj) { // ���������

	if (rows != obj.rows || cols != obj.cols) {
		throw MatrixException("������� ������ ��������");
	}

	Matrix res(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			res.mat[i][j] = mat[i][j] - obj.mat[i][j];
		}
	}
	return (Matrix)res;
}

Matrix Matrix::operator * (const Matrix& obj) { // ���������

	if (cols != obj.rows) {
		throw MatrixException("������� ������ �����������");
	}

	Matrix res(rows, obj.cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < obj.cols; j++) {
			res.mat[i][j] = 0;
			for (int k = 0; k < cols; k++) {
				res.mat[i][j] += mat[i][k] * obj.mat[k][j];
			}
		}
	}
	return (Matrix)res;
}

Matrix Matrix::operator ^ (const Matrix& obj) { // ������������ �������

	if (rows != obj.rows || cols != obj.cols) {
		throw MatrixException("������� ������ ��������");
	}

	Matrix res(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			res.mat[i][j] = mat[i][j] * obj.mat[i][j];
		}
	}
	return (Matrix)res;
}

Matrix Matrix::operator * (double a) { // ��������� �� ����� ������

	Matrix res(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			res.mat[i][j] = mat[i][j] * a;
		}
	}
	return (Matrix)res;
}

Matrix operator * (double a, Matrix obj) { // ��������� �� ����� �����

	Matrix res(obj.rows, obj.cols);
	for (int i = 0; i < obj.rows; i++) {
		for (int j = 0; j < obj.cols; j++) {
			res.mat[i][j] = obj.mat[i][j] * a;
		}
	}
	return (Matrix)res;
}

//=========================================================================== ������������ ��� ����������

Edinichnaya::Edinichnaya(const int matR) : Matrix(matR, matR) {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows; j++) {
			if (i == j) {
				mat[i][j] = 1;
			}
			else {
				mat[i][j] = 0;
			}
		}
	}
}

Diagonalnaya::Diagonalnaya(const int matR) : Matrix(matR, matR) {

	int q = -1;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows; j++) {
			if (i == j) {
				mat[i][j] = rand() % 10 + 0;
				q = rand() % 2 + 0;
				if (q == 1) {
					mat[i][j] = -mat[i][j];
				}
			}
			else {
				mat[i][j] = 0;
			}
		}
	}
}

Simmetrichnaya::Simmetrichnaya(const int matR) : Matrix(matR, matR) {

	int k = 0;
	int q = -1;

	for (int i = 0; i < rows; i++) {
		for (int j = k; j < rows; j++) {
			mat[i][j] = rand() % 10 + 0;
			q = rand() % 2 + 0;
			if (q == 1) {
				mat[i][j] = -mat[i][j];
			}
			mat[j][i] = mat[i][j];
		}
		k++;
	}
}

VerhnayaTr::VerhnayaTr(const int matR) : Matrix(matR, matR) {

	int k = 0;
	int q = -1;

	for (int i = 0; i < rows; i++) {
		for (int j = k; j < rows; j++) {
			mat[i][j] = rand() % 10 + 0;
			q = rand() % 2 + 0;
			if (q == 1) {
				mat[i][j] = -mat[i][j];
			}
			if (i != j) {
				mat[j][i] = 0;
			}
		}
		k++;
	}
}

NizhnayaTr::NizhnayaTr(const int matR) : Matrix(matR, matR) {

	int k = 0;
	int q = -1;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < k; j++) {
			mat[i][j] = rand() % 10 + 0;
			q = rand() % 2 + 0;
			if (q == 1) {
				mat[i][j] = -mat[i][j];
			}
			if (i != j) {
				mat[j][i] = 0;
			}
		}
		k++;
	}
}

//=========================================================================== ������������� ��������� ����� ��� ����������

istream& operator >> (istream& in, Diagonalnaya& obj) {

	cout << "������� �������� ������������ ������� ������� " << obj.cols << ":" << endl;

	for (int i = 0; i < obj.rows; i++) {
		for (int j = 0; j < obj.rows; j++) {
			if (i == j) {
				in >> obj.mat[i][j];
			}
		}
	}

	return in;
}

istream& operator >> (istream& in, Simmetrichnaya& obj) {

	cout << "������� �������� ������������ ������� ������� " << obj.cols << ":" << endl;

	int k = 0;

	for (int i = 0; i < obj.rows; i++) {
		for (int j = k; j < obj.rows; j++) {
			in >> obj.mat[i][j];
			obj.mat[j][i] = obj.mat[i][j];
		}
		k++;
	}

	return in;
}

istream& operator >> (istream& in, VerhnayaTr& obj) {

	cout << "������� �������� ������� ����������� ������� ������� " << obj.cols << ":" << endl;

	int k = 0;

	for (int i = 0; i < obj.rows; i++) {
		for (int j = k; j < obj.rows; j++) {
			in >> obj.mat[i][j];
		}
		k++;
	}

	return in;
}

istream& operator >> (istream& in, NizhnayaTr& obj) {

	cout << "������� �������� ������ ����������� ������� ������� " << obj.cols << ":" << endl;

	int k = 1;

	for (int i = 0; i < obj.rows; i++) {
		for (int j = 0; j < k; j++) {
			in >> obj.mat[i][j];
		}
		k++;
	}

	return in;
}

//=========================================================================== ������ ��� �� 2

double Matrix::tr() { // ���� �������

	if (rows != cols) {
		throw MatrixException("������� �� �������� ����������");
	}

	double res = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == j) {
				res += mat[i][j];
			}
		}
	}

	return res;
}

double Matrix::det() { // ������������ �������

	if (rows != cols) {
		throw MatrixException("������� �� �������� ����������");
	}

	Matrix result(rows, cols); // �������� �������, ����� �� ������ ��������
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.mat[i][j] = mat[i][j];
		}
	}

	int index = 0;
	int k = 0;
	double max;
	double coef = 0;
	int chSign = 1;

	while (k < rows) {

		max = abs(result.mat[k][k]);
		index = k;
		for (int i = k + 1; i < rows; i++) {
			if (abs(result.mat[i][k] > max)) {
				max = abs(result.mat[i][k]);
				index = i;
			}
		}

		for (int i = k; i < rows; i++) {
			swap(result.mat[k][i], result.mat[index][i]);
		}
		if (k != index) {
			chSign *= -1;
		}

		for (int j = k + 1; j < rows; j++) { // ����� ������
			if (abs(result.mat[k][k]) == 0) {
				continue;
			}
			coef = -result.mat[j][k] / result.mat[k][k];
			for (int i = k; i < cols; i++) {
				result.mat[j][i] = result.mat[j][i] + coef * result.mat[k][i];
			}
		}

		k++;
	}

	double res = 1;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == j) {
				res *= result.mat[i][j];
			}
		}
	}

	return res * chSign;
}

double Matrix::scalar(const Matrix& obj) { // ��������� ������������

	if (rows != 1 && cols != 1 || obj.rows != 1 && obj.cols != 1) {
		throw MatrixException("�� �������� ���������");
	}

	if (rows != obj.rows || cols != obj.cols) { // !
		throw MatrixException("������� ������ ������������");
	}

	double res = 0;
	if (rows == 1) {
		for (int j = 0; j < cols; j++) {
			res += mat[0][j] * obj.mat[0][j];
		}
	}
	else {
		for (int i = 0; i < rows; i++) {
			res += mat[i][0] * obj.mat[i][0];
		}
	}

	return res;
}

Matrix Matrix::vector(const Matrix& obj) { // ��������� ������������

	if (rows != 1 && cols != 1 || obj.rows != 1 && obj.cols != 1) {
		throw MatrixException("�� �������� ���������");
	}

	if (rows != obj.rows || cols != obj.cols) {
		throw MatrixException("������� ������ ������������");
	}

	if (rows != 3 && cols != 3) {
		throw MatrixException("������������ �������");
	}

	Matrix res(rows, cols);
	if (rows == 1) {
		res.mat[0][0] = mat[0][1] * obj.mat[0][2] - mat[0][2] * obj.mat[0][1];
		res.mat[0][1] = mat[0][2] * obj.mat[0][0] - mat[0][0] * obj.mat[0][2];
		res.mat[0][2] = mat[0][0] * obj.mat[0][1] - mat[0][1] * obj.mat[0][0];
	}
	else {
		res.mat[0][0] = mat[1][0] * obj.mat[2][0] - mat[2][0] * obj.mat[1][0];
		res.mat[1][0] = mat[2][0] * obj.mat[0][0] - mat[0][0] * obj.mat[2][0];
		res.mat[2][0] = mat[0][0] * obj.mat[1][0] - mat[1][0] * obj.mat[0][0];
	}

	return (Matrix)res;
}

double Matrix::euclNorm() { // ��������� �����

	if (rows != 1 && cols != 1) {
		throw MatrixException("�� �������� ��������");
	}

	double res = 0;
	if (rows == 1) {
		for (int j = 0; j < cols; j++) {
			res += pow(mat[0][j], 2);
		}
	}
	else {
		for (int i = 0; i < rows; i++) {
			res += pow(mat[i][0], 2);
		}
	}
	res = pow(res, 0.5);

	return res;
}

double Matrix::maxNorm() { // ������������ �����

	if (rows != 1 && cols != 1) {
		throw MatrixException("�� �������� ��������");
	}

	double res = 0;
	if (rows == 1) {
		for (int j = 0; j < cols; j++) {
			if (abs(mat[0][j]) >= res) {
				res = abs(mat[0][j]);
			}
		}
	}
	else {
		for (int i = 0; i < rows; i++) {
			if (abs(mat[i][0]) >= res) {
				res = abs(mat[i][0]);
			}
		}
	}

	return res;
}

double Matrix::frobNorm() { // ����� ����������

	double res = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			res += pow(mat[i][j], 2);
		}
	}
	res = pow(res, 0.5);

	return res;
}

//=========================================================================== ������ ��� �� 3

double Matrix::angle(const Matrix& obj) { // ���� ����� ���������

	if (rows != 1 && cols != 1 || obj.rows != 1 && obj.cols != 1) {
		throw MatrixException("�� �������� ���������");
	}

	if (rows != obj.rows || cols != obj.cols) {
		throw MatrixException("������� ������ ������������");
	}

	Matrix result1(rows, cols); // �������� ����� �������, ����� �������� ������ � �������
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result1.mat[i][j] = mat[i][j];
		}
	}

	Matrix result2(rows, cols); // �������� ����� �������, ����� �������� ������ � �������
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result2.mat[i][j] = obj.mat[i][j];
		}
	}

	double res = 0;
	res = acos(result1.scalar(result2) / (result1.euclNorm() * result2.euclNorm())) * 180 / M_PI;

	return res;
}

double Matrix::rank() { // ���� �������

	int size = max(rows, cols);

	Matrix result(size, size); // �������� 
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i < rows && j < cols) {
				result.mat[i][j] = mat[i][j];
			}
			else {
				result.mat[i][j] = 0;
			}
		}
	}

	double sumv = 0; // ����� �������
	double sumf = 0; // ����� ������� �������
	int count0 = 0; //������� ������� �������

	for (int i = 0; i < size; i++) {  // ����� ������� �������
		sumf += abs(result.mat[i][0]);
	}

	while (sumf < 0.00000000001) { // ��������, ���� ������ ������� �������� ���������

		if (count0 == size) { // ���� ���������� ������� �������� ����� ������� ������� - ���������� 0
			return 0;
		}

		sumf = 0;
		for (int j = 0; j < size; j++) {
			for (int i = 0; i < size; i++) {
				sumv += abs(result.mat[i][j]);
			}
			if (sumv < 0.00000000001) {
				for (int k = 0; k < size; k++) {
					if (j == size - 1) {
						break;
					}
					swap(result.mat[k][j], result.mat[k][j + 1]);
				}
			}
			sumv = 0;
		}

		for (int i = 0; i < size; i++) {
			sumf += abs(result.mat[i][0]);
		}

		count0++;
	}

	int index = 0; // ������ ������������� ��������
	int k = 0; // ������� ������� �������
	double maxv = 0; // ������������ ������� �������
	double coef = 0; // ����������� ���������� ������

	while (k < size) {

		maxv = abs(result.mat[k][k]);
		index = k;
		for (int i = k + 1; i < size; i++) {
			if (abs(result.mat[i][k] > maxv)) {
				maxv = abs(result.mat[i][k]);
				index = i;
			}
		}

		for (int i = k; i < size; i++) {
			swap(result.mat[k][i], result.mat[index][i]);
		}

		for (int j = k + 1; j < size; j++) { // ����� ������
			if (abs(result.mat[k][k]) == 0) { // ���� �������� ����� ���� - ����������
				continue;
			}
			coef = -result.mat[j][k] / result.mat[k][k];
			for (int i = k; i < size; i++) {
				result.mat[j][i] = result.mat[j][i] + coef * result.mat[k][i];
			}
		}

		k++;
	}

	coef = 0;
	for (int i = size - 1; i >= 0; i--) { // "��������" ����� ������
		for (int j = i - 1; j >= 0; j--) {
			if (abs(result.mat[i][i]) == 0) { // ���� �������� ����� ���� - ����������
				continue;
			}
			coef = -result.mat[j][i] / result.mat[i][i];
			for (int l = j; l < size; l++) {
				result.mat[j][l] = result.mat[j][l] + coef * result.mat[i][l];
			}
		}
	}

	sumv = 0;
	double count = 0; // ������� ������� �����
	for (int i = 0; i < size; i++) { // ������������ ���������� ������� �����
		for (int j = 0; j < size; j++) {
			sumv += abs(result.mat[i][j]);
		}
		if (sumv < 0.00000000001) {
			count += 1;
		}
		sumv = 0;
	}

	double res = size - count;

	return res;
}

Matrix Matrix::reverse() { // �������� �������

	if (rows != cols) {
		throw MatrixException("������� �� �������� ����������");
	}

	Matrix result0(rows, cols); // �������� ����� �������, ����� �������� ������ � �������
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result0.mat[i][j] = mat[i][j];
		}
	}
	if (result0.det() == 0) {
		throw MatrixException("������������ ������� ����� ����");
	}

	Matrix result1(rows, cols * 2); // ������� ����������� �������
	for (int i = 0; i < rows; i++) { // ��������� ������ ����� ���������� �������� �������
		for (int j = 0; j < rows; j++) {
			result1.mat[i][j] = mat[i][j];
		}
	}
	for (int i = 0; i < rows; i++) { // ��������� ������ ����� ���������� ��������� �������
		for (int j = rows; j < cols * 2; j++) {
			if (i == j - rows) {
				result1.mat[i][j] = 1;
			}
			else {
				result1.mat[i][j] = 0;
			}
		}
	}

	int index = 0;
	int k = 0;
	double max = 0;
	double coef = 0;

	while (k < rows) {

		max = abs(result1.mat[k][k]);
		index = k;
		for (int i = k + 1; i < rows; i++) {
			if (abs(result1.mat[i][k] > max)) {
				max = abs(result1.mat[i][k]);
				index = i;
			}
		}

		for (int i = k; i < cols * 2; i++) {
			swap(result1.mat[k][i], result1.mat[index][i]);
		}

		for (int j = k + 1; j < rows; j++) { // ����� ������
			if (abs(result1.mat[k][k]) == 0) {
				continue;
			}
			coef = -result1.mat[j][k] / result1.mat[k][k];
			for (int i = k; i < cols * 2; i++) {
				result1.mat[j][i] = result1.mat[j][i] + coef * result1.mat[k][i];
			}
		}

		k++;
	}

	double par = 0; // ������� ������ �� �� ������ ��������� �������
	for (int i = 0; i < rows; i++) {
		par = result1.mat[i][i];
		for (int j = 0; j < cols * 2; j++) {
			result1.mat[i][j] /= par;
		}
	}

	coef = 0; // "��������" ����� ������
	for (int i = rows - 1; i >= 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			coef = -result1.mat[j][i] / result1.mat[i][i];
			for (int k = j; k < cols * 2; k++) {
				result1.mat[j][k] = result1.mat[j][k] + coef * result1.mat[i][k];
			}
		}
	}

	for (int i = 0; i < rows; i++) { // �������� ������ ����� ����������� ������� � ����� �������� �������
		for (int j = 0; j < cols; j++) {
			result0.mat[i][j] = result1.mat[i][j + rows];
		}
	}

	return (Matrix)result0;
}

Matrix Matrix::transpose() { // ����������������� �������

	Matrix res(cols, rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			res.mat[j][i] = mat[i][j];
		}
	}

	return (Matrix)res;
}
