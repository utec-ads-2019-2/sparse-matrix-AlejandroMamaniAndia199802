#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"

using namespace std;

template <typename T>
class Matrix {
private:
    Node<T> *root = nullptr ;
    unsigned rows, cols;

public:
    Matrix(unsigned rows, unsigned cols)
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
    int getRows()
    {
        return rows;
    }
    int  getCols()
    {
        return cols;
    }

    void set(int posx, int posy, T val)
    {
        if(this->operator()(posx, posy) != 0) return;

        auto newNode = new Node<T>(posx, posy, val);

        Node<T> *prev;
        auto search = this->root;
        for(int i = 0; i<=posx; i++)
        {
            search = search->down;
        }
        prev= search;
        while(search->posY < posy && search->next != nullptr)
        {
            prev= search;
            search = search->next;
        }
        if(search->posY > posy)
        {
            newNode->next = search;
            prev->next = newNode;
        }
        else if(search->next == nullptr)
        {
            search->next = newNode;
        }
        else
        {
            newNode->next = search->next;
            search->next = newNode;
        }
        search = this->root;
        for(int i = 0; i<=posy; i++)
        {
            search = search->next;
        }
        while(search->posX < posx && search->down != nullptr)
        {
            search = search->down;
        }
        if(search->posX > posx)
        {
            newNode->down = search;
            prev->down = newNode;
        }
        else if(search->down == nullptr)
        {
            search->down = newNode;
        }
        else
        {
            newNode->down = search->down;
            search->down = newNode;
        }

    }

    T operator()(int posx, int posy) const
    {
        auto *temp = this->root;

        while((temp->posX < posx || temp->posX == NULL_VALUE) && temp->down != nullptr)
        {
            temp = temp->down;
        }
        while((temp->posY < posy || temp->posY == NULL_VALUE) && temp->next != nullptr)
        {
            temp = temp->next;
        }
        if(temp->posX == posx && temp->posY == posy)
            return temp->data;
        else
            return 0;
    }

    Matrix<T> operator*(T scalar) const
    {
        Matrix<T> newMatrix(rows, cols);

        for(int i = 0; i< rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                T val = this->operator()(i,j);
                if(val != 0) newMatrix.set(i, j, val*scalar);
            }
        }

        return newMatrix;
    }

    Matrix<T> operator*(Matrix<T> other) const
    {
        if(this->cols != other.rows)
            std::cerr << "Wrong size";

        Matrix<T> newMatrix(this->rows, other.cols);
        for(int i = 0; i< other.cols; i++)
        {
            for (int j = 0; j < this->rows; j++)
            {
                if(this->operator()(i,j) != 0 && other.operator()(i,j) != 0)
                {
                    T cumSum = 0;
                    for (int k = 0; k < this->cols; k++)
                        cumSum += this->operator()(j,k) + other.operator()(k,i);
                    newMatrix.set(i,j,cumSum);
                }

            }
        }

        return newMatrix;
    }

    Matrix<T> operator+(Matrix<T> other) const
    {
        if(this->rows != other.rows || this->cols != other.cols)
            std::cerr << "Different size";

        Matrix<T> newMatrix(rows, cols);
        for(int i = 0; i< rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                T val1 = this->operator()(i,j);
                T val2 = other.operator()(i,j);
                if(val1 != 0 && val2 != 0) newMatrix.set(i, j, val1+val2);
            }
        }

        return newMatrix;
    }

    Matrix<T> operator-(Matrix<T> other) const
    {
        if(this->rows != other.rows || this->cols != other.cols)
            std::cerr << "Different size";

        Matrix<T> newMatrix(rows, cols);
        for(int i = 0; i< rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                T val1 = this->operator()(i,j);
                T val2 = other.operator()(i,j);
                if(val1 != 0 && val2 != 0) newMatrix.set(i, j, val1-val2);
            }
        }

        return newMatrix;
    }
    Matrix<T> transpose() const
    {
        Matrix<T> newMatrix(rows, cols);

        for(int i = 0; i< rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                T val = this->operator()(i,j);
                if(val != 0) newMatrix.set(j, i, val);
            }
        }

        return newMatrix;
    }

    void print() const
    {
        for (int i = 0; i < cols; ++i)
        {
            for(int j = 0; j < rows; ++j)
            {
                T value = this->operator()(i,j);
                if(value != 0) printf("(%d, %d)[%d]\t->\t", i, j, value);
            }

        }

    }

    ~Matrix()
    {

    }
};

#endif //SPARSE_MATRIX_MATRIX_H
