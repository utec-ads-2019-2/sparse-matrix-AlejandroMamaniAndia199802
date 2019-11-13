#include <iostream>

#include "tester/tester.h"

int main() {
    Tester::execute();
    Matrix<int> matrix(2, 2);
    matrix.set(0,0,7);
    matrix.set(0,1,8);
    matrix.set(1,1,5);
    matrix.set(1,0,5);

    cout << "0,0: " << matrix(0,0) << endl;
    cout << "0,1: " << matrix(0,1) << endl;
    cout << "1,1: " << matrix(1,1) << endl;
    cout << "1,0: " << matrix(1,0) << endl;

    cout << " Example matrix \n";
    matrix.print();

    Matrix<int> matrix2 = matrix*2;
    cout << "----------\n";
    cout << "Multiplication by scalar\n";
    matrix2.print();


    Matrix<int> matrix3 = matrix2.transpose();
    cout << "***********\n";
    cout << " Transpose of a matrix\n";
    matrix3.print();

    Matrix<int> matrix4 =  matrix+matrix2;
    cout << "***********\n";
    cout << " Addition of matrix\n";
    matrix4.print();

    Matrix<int> matrix5 = matrix4-matrix2;
    cout << "***********\n";
    cout << " Substraction\n";
    matrix5.print();

    Matrix<int> matrix6 = matrix5 *matrix4;
    cout << "***********\n";
    cout << " Multiplication\n";
    matrix6.print();

    return EXIT_SUCCESS;
;}

