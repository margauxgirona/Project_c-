#include <iostream>
#include <iomanip>
#include "BinaryTree.h"

template<typename T>
BinaryTree<T>::BinaryTree() : _depth(0) {}

template<typename T>
void BinaryTree<T>::setDepth(int d) {
    // Set new depth
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
        throw std::out_of_range("BinaryTree<T> : setNode function : indices out of range");
    _tree[n][i] = value;
}

template<typename T>
T BinaryTree<T>::getNode(int n, int i) const{
    if (n > _depth || i > n)
        throw std::out_of_range("BinaryTree<T> : setNode function : indices out of range");
    return _tree[n][i];
}

template<typename T>
void BinaryTree<T>::display() const{
    std::string type = typeid(_tree[0][0]).name();
    std::string space_slash =  "    ";
    if (type != "b" && type != "i"){
        space_slash =  "       ";
    }

    int space = _depth*3;
    for(int i = 0; i <= _depth; i++){
        // left shift
        std::string shift = "";
        for(int k = 0; k < space; k++)
            shift += " ";

        // nodes with gap of 6
        std::string slash = " ";
        std::string values = "";
        for(int j = 0; j <= i; j++){
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2) << _tree[i][j];
            values += oss.str() + "      ";
            
            if (j != i && i != 0)
                slash += std::string("/") + space_slash + std::string("\\") + " ";
            
        }
        
        std::cout << shift << slash << std::endl;
        std::cout << shift << values << std::endl;
        // reduce the shift
        space -= 3;
    }
}


// ====== Explicit instantiations ======
template class BinaryTree<double>;
template class BinaryTree<bool>;
template class BinaryTree<int>;