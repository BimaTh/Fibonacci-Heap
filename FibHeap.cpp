#include "FibHeap.h"

template<typename T>
void FibHeap<T>::link(Node<T> *y, Node<T> *x) {
    // Implementation here
}

template<typename T>
void FibHeap<T>::consolidate() {
    // Implementation here
}

template<typename T>
void FibHeap<T>::cut(Node<T> *x, Node<T> *y) {
    // Implementation here
}

template<typename T>
void FibHeap<T>::cascadingCut(Node<T> *y) {
    // Implementation here
}

template<typename T>
void FibHeap<T>::inset(Node<T> *x) {
    // Implementation here
}

template<typename T>
FibHeap<T>* FibHeap<T>::merge(FibHeap<T> *H1, FibHeap<T> *H2) {
    // Implementation here
    return nullptr;
}

template<typename T>
Node<T>* FibHeap<T>::extractMin() {
    // Implementation here
    return nullptr;
}

template<typename T>
Node<T>* FibHeap<T>::displayMinimum() {
    // Implementation here
    return nullptr;
}

template<typename T>
void FibHeap<T>::decreaseKey(Node<T> *x, int k) {
    // Implementation here
}

template<typename T>
void FibHeap<T>::increaseKey(Node<T> *x, int k) {
    // Implementation here
}

template<typename T>
void FibHeap<T>::deleteNode(Node<T> *x) {
    // Implementation here
}

// Explicit template instantiation
template class FibHeap<int>;
template class FibHeap<std::string>;