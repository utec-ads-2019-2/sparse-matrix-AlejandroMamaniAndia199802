#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

#define NULL_VALUE    (-1)

template <typename T>
class Matrix;


template <typename T>
class Node {
private:
    int X{}, Y{};
    T data;

protected:
    Node<T> *next, *down;

public:
    explicit Node()
    {
        this->X = this->Y = NULL_VALUE;
        this->next = this->down = nullptr;
        this->data = 0;
    }
    Node(int x, int y, T value)
    {
        this->X = x;
        this->Y =  y;
        this->next = this->down = nullptr;
        this->data = value;
    }
    void killSelf()
    {
        if(this->next)
        {
            this->next->killSelf();
            delete this;
        }
    }

    friend class Matrix<T>;
};

#endif //SPARSE_MATRIX_NODE_H

