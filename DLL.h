//
// Created by Ibrahim Ahmed
//

#ifndef DLL_H
#define DLL_H

#include "Node.h"
#include <iostream>

template<typename T>
class DLL {
private:
    Node<T> *head; ///< Pointer to the head node of the list.
    Node<T> *tail; ///< Pointer to the tail node of the list.

public:
    /**
     * @brief Constructor to initialize an empty list.
     */
    DLL() : head(nullptr), tail(nullptr) {
    }

    /**
     * @brief Destructor to delete all nodes in the list.
     */
    ~DLL();

    /**
     * @brief Inserts a new node at the end of the list.
     * @param key The key of the node to be inserted.
     * @param name The name of the node to be inserted.
     */
    void insert(int key, T name);

    /**
     * @brief Deletes a node from the list.
     * @param node The node to be deleted.
     */
    void deleteNode(Node<T> *node);

    /**
     * @brief Searches for a node with the given key.
     * @param key The key to search for.
     * @return Pointer to the node with the given key, or nullptr if not found.
     */
    Node<T> *search(int key);

    /**
     * @brief Displays the list from head to tail.
     */
    void displayForward() const;

    /**
     * @brief Displays the list from tail to head.
     */
    void displayBackward() const;
};

#endif // DLL_H
