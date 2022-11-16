#include <iostream>
#include <iomanip>
#include <array>
#include <cmath>
#include <cstdlib>
#include "matrix.h"

using namespace std;

int main() {

	setlocale(LC_ALL, "Russian");
	 
	Matrix m1(3, 3), m2(2, 4);
	Matrix m3(3, 1), m4(3, 1);
	//cin >> m3 >> m4;
	//cin >> m1 >> m2; // m1 = 2 5 7 6 3 4 5 -2 -3 (������ � �������� �������)

	cout << m1 << m2 << m3 << m4;
	
	try {

		double a1 = m3.angle(m4);
		cout << "���� ����� ��������� ����� (�������):  " << a1 << endl;
		
		double a2 = m1.rank();
		cout << "���� ������� �����: " << a2 << endl;

		Matrix matr1 = m2.transpose();
		cout << "����������������� " << matr1 << endl;

		Matrix matr2 = m1.reverse(); 
		cout << "�������� " << matr2 << endl;
	}
	catch (MatrixException& c) {
		cout << "������� ����������: " << c.problem << endl;
	}
	
	system("pause");
	return 0;
}
