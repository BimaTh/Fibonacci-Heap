
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <utility>

/**
 * @class Node
 * @brief Represents a node in the Fibonacci Heap.
 *
 * This class encapsulates the properties of a node used in the Fibonacci Heap.
 */
class Node {
private:
    int key; ///< The key value of the node.
    std::string Name; ///< The name associated with the node.
    int deg = 0; ///< The degree of the node (number of children).
    Node *parent; ///< Pointer to the parent node.
    Node *child; ///< Pointer to one of the child nodes.
    Node *left; ///< Pointer to the left sibling node.
    Node *right; ///< Pointer to the right sibling node.
    bool mark; ///< Mark indicating whether the node has lost a child since it became a child of its current parent.

public:
    /**
     * @brief Constructor to initialize a node with a given name and key.
     * @param Name The name to be assigned to the node.
     * @param key The key value to be assigned to the node.
     * @pre None.
     * @post A node is created with the specified name and key.
     * @function Node
     */
    Node(std::string Name, int key): Name(std::move(Name)), key(key), deg(0), parent(nullptr), child(nullptr),
                                     left(this), right(this), mark(false) {
    };

    /**
     * @brief Default destructor.
     * @pre None.
     * @post The node is destroyed.
     * @function ~Node
     */
    ~Node() = default;

    /**
     * @brief Friend class declaration to allow FibHeap access to private members.
     * @function friend class FibHeap
     */
    friend class FibHeap;

    /**
     * @brief Gets the key value of the node.
     * @return The key value of the node.
     * @pre None.
     * @post The key value of the node is returned.
     * @function getKey
     */
    [[nodiscard]] int getKey() const;

    /**
     * @brief Gets the name of the node.
     * @return The name of the node.
     * @pre None.
     * @post The name of the node is returned.
     * @function getName
     */
    [[nodiscard]] std::string getName() const;
};

#endif //NODE_H
