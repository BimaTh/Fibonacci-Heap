//
// Created by Ibrahim Ahmed
//

#include "DLL.h"

template<typename T>
DLL<T>::~DLL() {
    if (head == nullptr) return;
    Node<T> *current = head;
    do {
        Node<T> *next = current->right;
        delete current;
        current = next;
    } while (current != head);
    head = tail = nullptr;
}

template<typename T>
void DLL<T>::insert(int key, T name) {
    auto *newNode = new Node<T>(name, key);
    if (tail == nullptr) {
        head = tail = newNode;
        head->right = head;
        head->left = head;
    } else {
        tail->right = newNode;
        newNode->left = tail;
        newNode->right = head;
        head->left = newNode;
        tail = newNode;
    }
}

template<typename T>
void DLL<T>::deleteNode(Node<T> *node) {
    if (node == nullptr || head == nullptr) return;

    if (node == head && node == tail) {
        head = tail = nullptr;
    } else {
        if (node == head) {
            head = node->right;
        }
        if (node == tail) {
            tail = node->left;
        }
        node->left->right = node->right;
        node->right->left = node->left;
    }
    delete node;
}

template<typename T>
Node<T> *DLL<T>::search(int key) {
    if (head == nullptr) return nullptr;
    Node<T> *current = head;
    do {
        if (current->getKey() == key) {
            return current;
        }
        current = current->right;
    } while (current != head);
    return nullptr;
}

template<typename T>
void DLL<T>::displayForward() const {
    if (head == nullptr) return;
    Node<T> *current = head;
    do {
        std::cout << current->getName() << " ";
        current = current->right;
    } while (current != head);
    std::cout << std::endl;
}

template<typename T>
void DLL<T>::displayBackward() const {
    if (tail == nullptr) return;
    Node<T> *current = tail;
    do {
        std::cout << current->getName() << " ";
        current = current->left;
    } while (current != tail);
    std::cout << std::endl;
}

// Explicit template instantiation
template class DLL<std::string>;
template class DLL<int>;
