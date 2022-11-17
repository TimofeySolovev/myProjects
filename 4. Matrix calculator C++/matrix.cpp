#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <array>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "matrix.h"

using namespace std;

Matrix::Matrix() { // конструктор по умолчанию

	rows = 5; // по умолчанию
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

Matrix::Matrix(int matR, int matC) { // конструктор с параметрами

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

Matrix::Matrix(const Matrix& obj) { // конструктор копии

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

Matrix::~Matrix() { // деструктор

	for (int i = 0; i < rows; i++) {
		delete[] mat[i];
	}
	delete[] mat;
}

//=========================================================================== перегруженные операторы для класса Matrix

istream& operator >> (istream& in, Matrix& obj) { // ввод элементов матрицы

	cout << "Введите элементы матрицы (вектора) размера " << obj.rows << "x" << obj.cols << ":" << endl;

	for (int i = 0; i < obj.rows; i++) {
		for (int j = 0; j < obj.cols; j++) {
			in >> obj.mat[i][j];
		}
	}

	return in; // позволяет множественный ввод, типа cin >> x >> y >> z >> ...
}

ostream& operator << (ostream& out, const Matrix& obj) { // вывод элементов матрицы на экран

	cout << "Матрица (вектор):" << endl;

	for (int i = 0; i < obj.rows; i++) {
		for (int j = 0; j < obj.cols; j++) {
			if (abs(obj.mat[i][j]) > 0.00000000001) {
				out << setw(8) << setprecision(3) << obj.mat[i][j]; // под каждое число выделяется 8 позиций
			}
			else {
				out << setw(5) << 0;
			}
		}
		cout << endl;
	}
	out << endl;

	return out; // позволяет множественный вывод, типа cout << x << y << z << ...
}

double& Matrix::operator () (int matR, int matC) { // оператор взятия индекса

	if (matR < 0 || matR >= rows || matC < 0 || matC >= cols) {
		throw MatrixException("Неправильный индекс");
	}
	return *mat[matR, matC]; // возврат указателя на элемент массива
}

const Matrix& Matrix::operator = (const Matrix& obj) { // оператор присваивания

	if (&obj != this) { // чтобы не выполнялось самоприсваивание
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
	return *this; // разрешает множественное присваивание, типа x = y = z = ...
}

Matrix Matrix::operator + (const Matrix& obj) { // сложение

	if (rows != obj.rows || cols != obj.cols) {
		throw MatrixException("Матрицы разных размеров");
	}

	Matrix res(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			res.mat[i][j] = mat[i][j] + obj.mat[i][j];
		}
	}
	return (Matrix)res;
}

Matrix Matrix::operator - (const Matrix& obj) { // вычитание

	if (rows != obj.rows || cols != obj.cols) {
		throw MatrixException("Матрицы разных размеров");
	}

	Matrix res(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			res.mat[i][j] = mat[i][j] - obj.mat[i][j];
		}
	}
	return (Matrix)res;
}

Matrix Matrix::operator * (const Matrix& obj) { // умножение

	if (cols != obj.rows) {
		throw MatrixException("Матрицы нельзя перемножить");
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

Matrix Matrix::operator ^ (const Matrix& obj) { // произведение Адамара

	if (rows != obj.rows || cols != obj.cols) {
		throw MatrixException("Матрицы разных размеров");
	}

	Matrix res(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			res.mat[i][j] = mat[i][j] * obj.mat[i][j];
		}
	}
	return (Matrix)res;
}

Matrix Matrix::operator * (double a) { // умножение на число справа

	Matrix res(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			res.mat[i][j] = mat[i][j] * a;
		}
	}
	return (Matrix)res;
}

Matrix operator * (double a, Matrix obj) { // умножение на число слева

	Matrix res(obj.rows, obj.cols);
	for (int i = 0; i < obj.rows; i++) {
		for (int j = 0; j < obj.cols; j++) {
			res.mat[i][j] = obj.mat[i][j] * a;
		}
	}
	return (Matrix)res;
}

//=========================================================================== конструкторы для подклассов

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

//=========================================================================== перегруженные операторы ввода для подклассов

istream& operator >> (istream& in, Diagonalnaya& obj) {

	cout << "Введите элементы диагональной матрицы размера " << obj.cols << ":" << endl;

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

	cout << "Введите элементы симметричной матрицы размера " << obj.cols << ":" << endl;

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

	cout << "Введите элементы верхней треугольной матрицы размера " << obj.cols << ":" << endl;

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

	cout << "Введите элементы нижней треугольной матрицы размера " << obj.cols << ":" << endl;

	int k = 1;

	for (int i = 0; i < obj.rows; i++) {
		for (int j = 0; j < k; j++) {
			in >> obj.mat[i][j];
		}
		k++;
	}

	return in;
}

//=========================================================================== методы для ЛР 2

double Matrix::tr() { // след матрицы

	if (rows != cols) {
		throw MatrixException("Матрица не является квадратной");
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

double Matrix::det() { // определитель матрицы

	if (rows != cols) {
		throw MatrixException("Матрица не является квадратной");
	}

	Matrix result(rows, cols); // копируем матрицу, чтобы не менять исходную
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

		for (int j = k + 1; j < rows; j++) { // метод Гаусса
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

double Matrix::scalar(const Matrix& obj) { // скалярное произведение

	if (rows != 1 && cols != 1 || obj.rows != 1 && obj.cols != 1) {
		throw MatrixException("Не являтюся векторами");
	}

	if (rows != obj.rows || cols != obj.cols) { // !
		throw MatrixException("Векторы разных размерностей");
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

Matrix Matrix::vector(const Matrix& obj) { // векторное произведение

	if (rows != 1 && cols != 1 || obj.rows != 1 && obj.cols != 1) {
		throw MatrixException("Не являтюся векторами");
	}

	if (rows != obj.rows || cols != obj.cols) {
		throw MatrixException("Векторы разных размерностей");
	}

	if (rows != 3 && cols != 3) {
		throw MatrixException("Некорректные векторы");
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

double Matrix::euclNorm() { // евклидова норма

	if (rows != 1 && cols != 1) {
		throw MatrixException("Не является вектором");
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

double Matrix::maxNorm() { // максимальная норма

	if (rows != 1 && cols != 1) {
		throw MatrixException("Не является вектором");
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

double Matrix::frobNorm() { // норма Фробениуса

	double res = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			res += pow(mat[i][j], 2);
		}
	}
	res = pow(res, 0.5);

	return res;
}

//=========================================================================== методы для ЛР 3

double Matrix::angle(const Matrix& obj) { // угол между векторами

	if (rows != 1 && cols != 1 || obj.rows != 1 && obj.cols != 1) {
		throw MatrixException("Не являтюся векторами");
	}

	if (rows != obj.rows || cols != obj.cols) {
		throw MatrixException("Векторы разных размерностей");
	}

	Matrix result1(rows, cols); // созадаем копию матрицы, чтобы получить доступ к методам
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result1.mat[i][j] = mat[i][j];
		}
	}

	Matrix result2(rows, cols); // созадаем копию матрицы, чтобы получить доступ к методам
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result2.mat[i][j] = obj.mat[i][j];
		}
	}

	double res = 0;
	res = acos(result1.scalar(result2) / (result1.euclNorm() * result2.euclNorm())) * 180 / M_PI;

	return res;
}

double Matrix::rank() { // ранг матрицы

	int size = max(rows, cols);

	Matrix result(size, size); // созадаем 
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

	double sumv = 0; // сумма столбца
	double sumf = 0; // сумма первого столбца
	int count0 = 0; //счетчик прохода матрицы

	for (int i = 0; i < size; i++) {  // сумма первого столбца
		sumf += abs(result.mat[i][0]);
	}

	while (sumf < 0.00000000001) { // свдигаем, пока первый столбец окажется ненулевым

		if (count0 == size) { // если количество нулевых столбцов равно размеру матрицы - возвращаем 0
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

	int index = 0; // индекс максимального элемента
	int k = 0; // счетчик прохода матрицы
	double maxv = 0; // максимальный элемент столбца
	double coef = 0; // коэффициент домножения строки

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

		for (int j = k + 1; j < size; j++) { // метод Гаусса
			if (abs(result.mat[k][k]) == 0) { // если делитель равен нулю - пропускаем
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
	for (int i = size - 1; i >= 0; i--) { // "обратный" метод Гаусса
		for (int j = i - 1; j >= 0; j--) {
			if (abs(result.mat[i][i]) == 0) { // если делитель равен нулю - пропускаем
				continue;
			}
			coef = -result.mat[j][i] / result.mat[i][i];
			for (int l = j; l < size; l++) {
				result.mat[j][l] = result.mat[j][l] + coef * result.mat[i][l];
			}
		}
	}

	sumv = 0;
	double count = 0; // счетчик нулевых строк
	for (int i = 0; i < size; i++) { // подсчитываем количество нулевых строк
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

Matrix Matrix::reverse() { // обратная матрица

	if (rows != cols) {
		throw MatrixException("Матрица не является квадратной");
	}

	Matrix result0(rows, cols); // созадаем копию матрицы, чтобы получить доступ к методам
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result0.mat[i][j] = mat[i][j];
		}
	}
	if (result0.det() == 0) {
		throw MatrixException("Определитель матрицы равен нулю");
	}

	Matrix result1(rows, cols * 2); // создаем расширенную матрицу
	for (int i = 0; i < rows; i++) { // заполняем первую часть значениями исходной матрицы
		for (int j = 0; j < rows; j++) {
			result1.mat[i][j] = mat[i][j];
		}
	}
	for (int i = 0; i < rows; i++) { // заполняем вторую часть значениями единичной матрицы
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

		for (int j = k + 1; j < rows; j++) { // метод Гаусса
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

	double par = 0; // деление строки на ее первый ненулевой элемент
	for (int i = 0; i < rows; i++) {
		par = result1.mat[i][i];
		for (int j = 0; j < cols * 2; j++) {
			result1.mat[i][j] /= par;
		}
	}

	coef = 0; // "обратный" метод Гаусса
	for (int i = rows - 1; i >= 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			coef = -result1.mat[j][i] / result1.mat[i][i];
			for (int k = j; k < cols * 2; k++) {
				result1.mat[j][k] = result1.mat[j][k] + coef * result1.mat[i][k];
			}
		}
	}

	for (int i = 0; i < rows; i++) { // копируем вторую часть расширенной матрицы в копию исходной матрицы
		for (int j = 0; j < cols; j++) {
			result0.mat[i][j] = result1.mat[i][j + rows];
		}
	}

	return (Matrix)result0;
}

Matrix Matrix::transpose() { // транспонированная матрица

	Matrix res(cols, rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			res.mat[j][i] = mat[i][j];
		}
	}

	return (Matrix)res;
}
