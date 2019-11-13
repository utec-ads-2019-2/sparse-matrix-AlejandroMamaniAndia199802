#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

#define NULL_VALUE    (-1)

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
        this->posX = this->posY = NULL_VALUE;
        this->next = this->down = nullptr;
        this->data = 0;
    }
    Node(int posx, int posy, T val)
    {
        this->posX = posx;
        this->posY = posy;
        this->next = this->down = nullptr;
        this->data = val;
    }

    Node(int posx, int posy)
    {
        this->posX = posx;
        this->posY = posy;
        this->next = this->down = nullptr;
        this->data = 0;
    }



    friend class Matrix<T>;
};

#endif //SPARSE_MATRIX_NODE_H

