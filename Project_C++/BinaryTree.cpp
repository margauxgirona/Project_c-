#include <iostream>
#include "BinaryTree.h"

template<typename T>
BinaryTree<T>::BinaryTree() : _depth(0) {}

template<typename T>
void BinaryTree<T>::setDepth(int d) {
    // set new depth
    _depth = d;

    // _tree is now a vector of size _depth + 1 wich represents N+1
    _tree.resize(_depth + 1);

    // each vector of the vector is resize +1 per node starting from 1
    for (int i = 0; i <= _depth; i++){
        _tree[i].resize(i+1);
    }
}

template<typename T>
void BinaryTree<T>::setNode(int n, int i, T value){
    if (n > _depth || i > n)
        throw std::out_of_range("BinaryTree<T>::setNode indices out of range");
    _tree[n][i] = value;
}

template<typename T>
T BinaryTree<T>::getNode(int n, int i) const{
    if (n > _depth || i > n)
        throw std::out_of_range("BinaryTree<T>::setNode indices out of range");
    return _tree[n][i];
}

template<typename T>
void BinaryTree<T>::display() const{
    for(int i = 0; i <= _depth; i++){
        for(int j = 0; j <= i; j++)
            std::cout << _tree[i][j] << " ";
        std::cout << "" << std::endl;
    }
}


// ====== Explicit instantiations ======
template class BinaryTree<double>;
template class BinaryTree<bool>;