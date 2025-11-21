#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <vector>
#include <cstddef>   

template<typename T>
class BinaryTree{
    private:
        int _depth;
        std::vector<std::vector<T>> _tree;
    
    public:
        BinaryTree();

        void setDepth(int d);

        void setNode(int n, int i, T value);

        T getNode(int n, int i) const;

        void display() const;
};

#endif