
#ifndef FIBHEAP_H
#define FIBHEAP_H

#include "Node.h"

/**
 * @class FibHeap
 * @brief Represents a Fibonacci Heap data structure.
 *
 * This class provides the implementation of a Fibonacci Heap, including
 * operations such as insertion, merging, extracting the minimum, and
 * decreasing or increasing keys.
 */
class FibHeap {
private:
    Node *minimum; ///< Pointer to the node with the minimum key.
    int n; ///< Number of nodes in the heap.

public:
    /**
     * @brief Default constructor to initialize an empty Fibonacci Heap.
     * @pre None.
     * @post An empty Fibonacci Heap is created.
     */
    FibHeap() : minimum(nullptr), n(0) {
    }

    /**
     * @brief Links two trees of the same degree.
     * @param y Pointer to the first node.
     * @param x Pointer to the second node.
     * @pre Both nodes y and x must be non-null and have the same degree.
     * @post Node y is linked to node x as a child.
     */
    void link(Node *y, Node *x);

    /**
     * @brief Consolidates the heap by combining trees of the same degree.
     * @pre The heap must not be empty.
     * @post The heap is consolidated, and trees of the same degree are combined.
     */
    void consolidate();

    /**
     * @brief Cuts the link between a node and its parent, making it a root.
     * @param x Pointer to the node to be cut.
     * @param y Pointer to the parent node.
     * @pre Both nodes x and y must be non-null, and x must be a child of y.
     * @post Node x is cut from its parent y and becomes a root.
     */
    void cut(Node *x, Node *y);

    /**
     * @brief Performs a cascading cut operation.
     * @param y Pointer to the node to start the cascading cut.
     * @pre Node y must be non-null.
     * @post Cascading cut is performed starting from node y.
     */
    void cascadingCut(Node *y);

    /**
     * @brief Inserts a node into the heap.
     * @param x Pointer to the node to be inserted.
     * @pre Node x must be non-null.
     * @post Node x is inserted into the heap.
     */
    void inset(Node *x);

    /**
     * @brief Merges two Fibonacci Heaps into one.
     * @param H1 Pointer to the first heap.
     * @param H2 Pointer to the second heap.
     * @return Pointer to the merged heap.
     * @pre Both heaps H1 and H2 must be non-null.
     * @post A new heap is created by merging H1 and H2.
     */
    FibHeap *merge(FibHeap *H1, FibHeap *H2);

    /**
     * @brief Extracts the minimum node from the heap.
     * @return Pointer to the node with the minimum key.
     * @pre The heap must not be empty.
     * @post The minimum node is removed from the heap.
     */
    Node *extractMin();

    /**
     * @brief Displays the minimum node in the heap.
     * @return Pointer to the node with the minimum key.
     * @pre The heap must not be empty.
     * @post The minimum node is displayed.
     */
    Node *displayMinimum();

    /**
     * @brief Decreases the key of a node.
     * @param x Pointer to the node.
     * @param k The new key value.
     * @pre Node x must be non-null, and k must be less than the current key of x.
     * @post The key of node x is decreased to k.
     */
    void decreaseKey(Node *x, int k);

    /**
     * @brief Increases the key of a node.
     * @param x Pointer to the node.
     * @param k The new key value.
     * @pre Node x must be non-null, and k must be greater than the current key of x.
     * @post The key of node x is increased to k.
     */
    void increaseKey(Node *x, int k);

    /**
     * @brief Deletes a node from the heap.
     * @param x Pointer to the node to be deleted.
     * @pre Node x must be non-null.
     * @post Node x is deleted from the heap.
     */
    void deleteNode(Node *x);
};

#endif // FIBHEAP_H
