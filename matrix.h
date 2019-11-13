#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"

using namespace std;

template <typename T>
class Matrix {
private:
    Node<T> *root = nullptr ;
    int rows, cols;

public:
    Matrix(int rows,  int cols)
    {
        this->root = new Node<T>();
        if(cols <=0 ||  rows<= 0) throw;
        this->rows = rows;
        this->cols = cols;

        Node<T> *temp = this->root;
        for (int i = 0; i < cols; ++i) {
            auto *ptr = new Node<T>(-1,i,i);
            temp->next = ptr;
            temp = ptr;
        }

        temp = this->root;
        for (int i = 0; i < rows; ++i) {
            auto *ptr = new Node<T>(i,-1,i);
            temp->down = ptr;
            temp = ptr;
        }


    }


    void set(int x, int y, T val)
    {
        if(this->operator()(x, y) != 0) return;

        auto addedNode = new Node<T>(x, y, val);

        Node<T> *prev;
        auto search = this->root;
        for(int i = 0; i<=x; i++)
        {
            search = search->down;
        }
        prev= search;
        while(search->Y < y && search->next != nullptr)
        {
            prev= search;
            search = search->next;
        }
        if(search->Y > y)
        {
            addedNode->next = search;
            prev->next = addedNode;
        }
        else if(search->next == nullptr)
        {
            search->next = addedNode;
        }
        else
        {
            addedNode->next = search->next;
            search->next = addedNode;
        }
        search = this->root;
        for(int i = 0; i<=y; i++)
        {
            search = search->next;
        }
        while(search->X < x && search->down != nullptr)
        {
            search = search->down;
        }
        if(search->X > x)
        {
            addedNode->down = search;
            prev->down = addedNode;
        }
        else if(search->down == nullptr)
        {
            search->down = addedNode;
        }
        else
        {
            addedNode->down = search->down;
            search->down = addedNode;
        }

    }

    T operator()(int x, int y) const
    {
        auto *temp = this->root;

        while(  temp->down != nullptr && (temp->X < x || temp->X == NULL_VALUE))
        {
            temp = temp->down;
        }
        while( temp->next != nullptr && (temp->Y < y || temp->Y == NULL_VALUE))
        {
            temp = temp->next;
        }
        if(temp->X == x && temp->Y == y) return temp->data;
        else return 0;
    }

    Matrix<T> operator*(T scalar) const
    {
        Matrix<T> multipliedMatrix(rows, cols);

        for(int i = 0; i< rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                T value = this->operator()(i,j);
                if(value != 0) multipliedMatrix.set(i, j, value*scalar);
            }
        }

        return multipliedMatrix;
    }

    Matrix<T> operator*(Matrix<T> other) const
    {
        if(other.rows != this->cols ) throw ;
        Matrix<T> productMatrix(this->rows, other.cols);

        for(int i = 0; i< other.cols; i++)
        {
            for (int j = 0; j < this->rows; j++)
            {
                if(this->operator()(i,j) != 0 && other.operator()(i,j) != 0)
                {
                    T sum = 0;
                    for (int k = 0; k < this->cols; k++)
                        sum += this->operator()(j,k) * other.operator()(k,i);
                    productMatrix.set(i,j, sum);
                }
            }
        }
        return productMatrix;
    }

    Matrix<T> operator+(Matrix<T> other) const
    {
        if(this->rows != other.rows || this->cols != other.cols)
            throw;

        Matrix<T> sumMatrix(rows, cols);
        for(int i = 0; i< rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                T value_1 = this->operator()(i,j);
                T value_2 = other.operator()(i,j);
                if(value_1 != 0 && value_2 != 0) sumMatrix.set(i, j, value_1+value_2);
            }
        }
        return sumMatrix;
    }

    Matrix<T> operator-(Matrix<T> other) const
    {
        if(this->rows != other.rows || this->cols != other.cols)
            throw;
        Matrix<T> susMatrix(rows, cols);
        for(int i = 0; i< rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                T value_1 = this->operator()(i,j);
                T value_2 = other.operator()(i,j);
                if(value_1 != 0 && value_2 != 0) susMatrix.set(i, j, value_1-value_2);
            }
        }
        return susMatrix;
    }

    Matrix<T> transpose() const
    {
        Matrix<T> tranMatrix(rows, cols);
        for(int i = 0; i< rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                T value = (*this)(i,j);
                if(value != 0)tranMatrix.set(j, i, value);
            }
        }
        return tranMatrix;
    }

    void print() const
    {
        for(int i = 0; i<cols; i++){
            for(int j = 0; j<rows; j++){
                cout<<(*this)(i, j)<<" ";
            }
            cout<<endl;
        }
    }
    ~Matrix()
    {

    }
};

#endif //SPARSE_MATRIX_MATRIX_H
