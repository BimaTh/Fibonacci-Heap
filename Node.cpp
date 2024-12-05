//
// Created by Ibrahim Abdelfattah
//

#include "Node.h"

// Template function implementations
template<typename T>
int Node<T>::getKey() const {
    return key;
}

template<typename T>
T Node<T>::getName() const {
    return Name;
}

// Explicit template instantiation
template class Node<std::string>;
template class Node<int>;
