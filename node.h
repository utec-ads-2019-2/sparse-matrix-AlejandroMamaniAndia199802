#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

#define NULL_VAL    (-1)

template <typename T>
class Matrix;


template <typename T>
class Node {
private:
    int posX, posY;
    T data;

protected:
    Node<T> *next, *down;

public:
    explicit Node()
    {
        this->next = this->down = nullptr;
        this->posX = this->posY = NULL_VAL;
        this->data = 0;
    }

    Node(int posx, int posy)
    {
        this->next = this->down = nullptr;
        this->posX = posx;
        this->posY = posy;
        this->data = 0;
    }

    Node(int posx, int posy, T val)
    {
        this->next = this->down = nullptr;
        this->posX = posx;
        this->posY = posy;
        this->data = val;
    }

    friend class Matrix<T>;
};

#endif //SPARSE_MATRIX_NODE_H