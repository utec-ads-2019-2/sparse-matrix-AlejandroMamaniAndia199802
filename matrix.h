#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"

using namespace std;

template <typename T>
class Matrix {
private:
    Node<T> *root;
    unsigned rows{}, cols{};

public:
    Matrix(unsigned rows, unsigned cols)
    {
        this->root = new Node<T>();
        if(rows <=0 || cols <= 0) std::cerr << "Invalid size";
        this->rows = rows;
        this->cols = cols;

        auto tempPointer = this->root;
        for (int i = 0; i < cols; ++i) {
            auto ptr = new Node<T>(-1,i,i);
            tempPointer->next = ptr;
            tempPointer = ptr;
        }

        tempPointer = this->root;
        for (int i = 0; i < rows; ++i) {
            auto ptr = new Node<T>(i,-1,i);
            tempPointer->down = ptr;
            tempPointer = ptr;
        }


    }
    uint8_t getRows()
    {
        return rows;
    }
    uint8_t getCols()
    {
        return cols;
    }

    void set(int posx, int posy, T val)
    {
        if(this->operator()(posx, posy) != 0) return;

        auto newNode = new Node<T>(posx, posy, val);

        auto prevPointer = this->root;
        auto searchPointer = this->root;
        for(uint8_t i = 0; i<=posx; i++)
        {
            searchPointer = searchPointer->down;
        }
        prevPointer = searchPointer;
        while(searchPointer->posY < posy && searchPointer->next != NULL)
        {
            prevPointer = searchPointer;
            searchPointer = searchPointer->next;
        }
        if(searchPointer->posY > posy)
        {
            newNode->next = searchPointer;
            prevPointer->next = newNode;
        }
        else if(searchPointer->next == NULL)
        {
            searchPointer->next = newNode;
        }
        else
        {
            newNode->next = searchPointer->next;
            searchPointer->next = newNode;
        }
        searchPointer = this->root;
        for(uint8_t i = 0; i<=posy; i++)
        {
            searchPointer = searchPointer->next;
        }
        while(searchPointer->posX < posx && searchPointer->down != NULL)
        {
            searchPointer = searchPointer->down;
        }
        if(searchPointer->posX > posx)
        {
            newNode->down = searchPointer;
            prevPointer->down = newNode;
        }
        else if(searchPointer->down == NULL)
        {
            searchPointer->down = newNode;
        }
        else
        {
            newNode->down = searchPointer->down;
            searchPointer->down = newNode;
        }

    }

    T operator()(int posx, int posy) const
    {
        auto tempPointer = this->root;

        while((tempPointer->posX < posx || tempPointer->posX == NULL_VAL) && tempPointer->down != NULL)
        {
            tempPointer = tempPointer->down;
        }
        while((tempPointer->posY < posy || tempPointer->posY == NULL_VAL) && tempPointer->next != NULL)
        {
            tempPointer = tempPointer->next;
        }
        if(tempPointer->posX == posx && tempPointer->posY == posy)
            return tempPointer->data;
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
