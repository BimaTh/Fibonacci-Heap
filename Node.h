//
// Created by Ibrahim Abdelfattah
//

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <utility>

template<typename T>
class DLL; // Forward declaration of DLL class

/**
 * @class Node
 * @brief Represents a node in a doubly linked list.
 */
template<typename T>
class Node {
private:
    int key; ///< The key value of the node.
    T Name; ///< The name associated with the node.
    int deg = 0; ///< The degree of the node (number of children).
    Node *parent; ///< Pointer to the parent node.
    DLL<T> *child; ///< Pointer to DLL of the children of that specific node.
    Node *left; ///< Pointer to the left sibling node.
    Node *right; ///< Pointer to the right sibling node.
    bool mark; ///< Mark indicating whether the node has lost a child since it became a child of its current parent.

public:
    /**
     * @brief Constructor to initialize a node with a given name and key.
     * @param Name The name to be assigned to the node.
     * @param key The key value to be assigned to the node.
     */
    Node(T Name, int key) : key(key), Name(std::move(Name)), deg(0), parent(nullptr), child(nullptr),
                            left(this), right(this), mark(false) {
    }

    /**
     * @brief Default destructor.
     */
    ~Node() = default;

    /**
     * @brief Friend class declaration to allow DLL access to private members.
     */
    friend class DLL<T>;

    /**
     * @brief Gets the key value of the node.
     * @return The key value of the node.
     */
    [[nodiscard]] int getKey() const;

    /**
     * @brief Gets the name of the node.
     * @return The name of the node.
     */
    [[nodiscard]] T getName() const;
};

#endif // NODE_H
