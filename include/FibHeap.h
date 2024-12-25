#ifndef FIBHEAP_H
#define FIBHEAP_H

#include <functional>
#include <iostream>
#include "DoublyCircularLinkedList.h"
#include "error_handler.h"

// Forward declarations
template<typename T>
class Node;

class VisualizeFibonacciHeap;

class VisualizeTaskManager;

/**
 * @class FibHeap
 * @brief Represents a Fibonacci Heap data structure.
 *
 * This class provides the implementation of a Fibonacci Heap, including
 * operations such as insertion, merging, extracting the minimum, and
 * decreasing or increasing keys.
 *
 * @tparam T The type of data stored in the heap nodes.
 */
template<typename T>
class FibHeap {
private:
    Node<T> *min; ///< Pointer to the node with the minimum key.
    int size; ///< Number of nodes in the heap.
    DoublyCircularLinkedList<T> rootList; ///< Root linked list.
    error_handler * handler;

    /**
     * @brief Links two nodes in the heap.
     *
     * @param y The node to be linked.
     * @param x The node to which y will be linked.
     */
    void link(Node<T> *y, Node<T> *x);

    /**
     * @brief Consolidates the heap to maintain the Fibonacci heap properties.
     */
    void consolidate();

    /**
     * @brief Cuts a node from its parent and adds it to the root list.
     *
     * @param x The node to be cut.
     * @param y The parent node.
     */
    void cut(Node<T> *x, Node<T> *y);

    /**
     * @brief Performs a cascading cut operation.
     *
     * @param y The node to perform the cascading cut on.
     */
    void cascadingCut(Node<T> *y);

    /**
     * @brief Searches for a node with a specific key starting from the given node.
     *
     * @param root The starting node for the search.
     * @param key The key to search for.
     * @return Node<T>* The node with the specified key, or nullptr if not found.
     */
    Node<T> *search(Node<T> *root, int key) const;

public:
    friend class VisualizeFibonacciHeap;
    friend class VisualizeTaskManager;

    /**
     * @brief Constructs a new Fibonacci Heap object.
     */
    FibHeap(error_handler * handler);

    /**
     * @brief Inserts a node into the heap.
     *
     * @param x The node to be inserted.
     */
    void insert(Node<T> *x);

    /**
     * @brief Extracts the minimum node from the heap.
     *
     * @return Node<T>* The minimum node.
     */
    Node<T> *extractMin();

    /**
     * @brief Displays the minimum node in the heap.
     *
     * @return Node<T>* The minimum node.
     */
    Node<T> *displayMinimum();

    /**
     * @brief Modifies the key of a node.
     *
     * @param k The current key of the node.
     * @param new_k The new key to be assigned.
     */
    void modifyKey(int k, int new_k);

    /**
     * @brief Deletes a node with a specific key from the heap.
     *
     * @param k The key of the node to be deleted.
     */
    void deleteNode(int k);

    /**
     * @brief Displays the structure of the heap.
     */
    void display();

    /**
     * @brief Finds a node with a specific key in the heap.
     *
     * @param key The key to search for.
     * @return Node<T>* The node with the specified key, or nullptr if not found.
     */
    Node<T> *find(int key) const;

    /**
     * @brief Checks if the heap is empty.
     *
     * @return true If the heap is empty.
     * @return false If the heap is not empty.
     */
    bool isEmpty();

    /**
     * @brief Gets the size of the heap.
     *
     * @return int The number of nodes in the heap.
     */
    int getSize();
};

// Implementation of the FibHeap template class

template<typename T>
FibHeap<T>::FibHeap(error_handler * handler) : handler(handler), min(nullptr), size(0) {}

template<typename T>
void FibHeap<T>::insert(Node<T> *x) {
    x->deg = 0;
    x->parent = nullptr;
    x->child = nullptr;
    x->mark = false;
    rootList.insert(x);
    if (min == nullptr || x->key < min->key)
        min = x;
    ++size;

    handler->verbose_log(1, "Insert function called: " + x->getName() + "." );
}

template<typename T>
Node<T> *FibHeap<T>::extractMin() {
    Node<T> *minptr = min;
    if (minptr == nullptr) {
        handler->e_log(17);
        return nullptr;
    }
    if (minptr->child != nullptr) {
        int numChildren = minptr->child->size;
        for (int i = 0; i < numChildren; i++) {
            Node<T> *child = minptr->child->head;
            minptr->child->remove(child);
            rootList.insert(child);
            child->parent = nullptr;
        }
    }
    minptr->left->right = minptr->right;
    minptr->right->left = minptr->left;
    if (minptr == minptr->right) {
        min = nullptr;
        if (minptr->child == nullptr)
            rootList.remove(minptr);
    } else {
        min = minptr->right;
        consolidate();
    }
    size--;

    handler->verbose_log(1, "ExtractMin function called.");
    return minptr;

}

template<typename T>
bool FibHeap<T>::isEmpty() {
    handler->verbose_log(1, "Is Empty Function called.");
    return size == 0;
}

template<typename T>
void FibHeap<T>::consolidate() {

    handler->verbose_log(1,"Consolidating Fibonacci Heap...");

    const int fibsize = 45;
    Node<T> *A[fibsize];
    Node<T> *x = min;
    for (int i = 0; i < fibsize; i++)
        A[i] = nullptr;
    int iterations = rootList.size;
    for (int i = 0; i < iterations - 1; i++) {
        int d = x->deg;
        while (A[d] != nullptr) {
            Node<T> *y = A[d];
            if (x->key > y->key){
                Node <T> *temp = x;
                x = y;
                y = temp;
            }
            link(y, x);
            A[d] = nullptr;
            ++d;
        }
        A[d] = x;
        x->deg = d;
        x = x->right;
    }
    min = nullptr;
    rootList = DoublyCircularLinkedList<T>();
    for (int i = 0; i < fibsize; i++) {
        if (A[i] != nullptr){
            rootList.insert(A[i]);
            if (min == nullptr || A[i]->key < min->key)
                min = A[i];
        }
    }
}

template<typename T>
void FibHeap<T>::link(Node<T> *y, Node<T> *x) {
    rootList.remove(y);
    if (x->child == nullptr)
        x->child = new DoublyCircularLinkedList<T>();
    x->child->insert(y);
    y->parent = x;
    y->mark = false;
    handler->verbose_log(1, "link function Called.");
}

template<typename T>
Node<T> *FibHeap<T>::search(Node<T> *current, int key) const {
    if (current == nullptr) {
        handler->verbose_log(1, "Heap Empty.");
        return nullptr;
    }


    Node<T> *start = current;
    do {
        if (current->key == key) {
            return current;
        }
        if (current->child != nullptr) {
            Node<T> *result = search(current->child->head, key);
            if (result != nullptr) {
                return result;
            }
        }
        current = current->right;
    } while (current != start);
    return nullptr;
}

template<typename T>
Node<T> *FibHeap<T>::find(int key) const {
    handler->verbose_log(1, "Search function Called.");
    return search(rootList.head, key);
}

template<typename T>
void FibHeap<T>::modifyKey(int currentNodeKey, int new_k) {
    Node<T> *x = find(currentNodeKey);
    if (x == nullptr) {
        handler->e_log(17);
        return;
    }
    if (x != nullptr && new_k > x->key) { // Cut from parent and insert into root list
        modifyKey(x->key, -1);
        Node<T>* mini = extractMin();
        mini->key = new_k;
        insert(mini);
        handler->verbose_log(1, "ModifyKey function called");
        return;
    }

    x->key = new_k;
    Node<T> *y = x->parent;
    if (y != nullptr && x->key < y->key) {
        cut(x, y);
        cascadingCut(y);
    }
    if (x->key < min->key) {
        min=x;
    }
    handler->verbose_log(1, "ModifyKey function called");
}

template<typename T>
void FibHeap<T>::cut(Node<T> *x, Node<T> *y) {
    y->child->remove(x);
    rootList.insert(x);
    x->parent = nullptr;
    x->mark = false;
    handler->verbose_log(1, "Cut Function called.");
}

template<typename T>
void FibHeap<T>::cascadingCut(Node<T> *y) {
    Node<T> *z = y->parent;
    if (z != nullptr) {
        if (y->mark == false) {
            y->mark == true;
        } else {
            cut(y, z);
            cascadingCut(z);
        }
    }
    handler->verbose_log(1, "CascadingCut Function called.");
}

template<typename T>
void FibHeap<T>::deleteNode(int key) {
    Node<T> *x = find(key);
    if (x == nullptr) {
        // std::cerr << "Node with key " << key << " not found." << std::endl;
        handler->e_log(17);
        return;
    }
    modifyKey(key, min->key - 1);
    extractMin();
    handler->verbose_log(1, "DeleteNode Function called.");
}

template<typename T>
Node<T> *FibHeap<T>::displayMinimum() {
    return this->min;
}

template<typename T>
void FibHeap<T>::display() {
    handler->verbose_log(1, "Display Function called.");
    if (!rootList.head) {
        handler->e_log(18);
        return;
    }

    std::function<void(Node<T>*, int)> displayNode = [&](Node<T>* node, int level) {
        if (!node) return;
        Node<T>* start = node;
        do {
            for (int i = 0; i < level; ++i) std::cout << "  ";
            std::cout << "Key: " << node->getKey() << ", Name: " << node->getName() << ", Degree: " << node->getDeg() << std::endl;
            if (node->child) {
                displayNode(node->child->head, level + 1);
            }
            node = node->right;
        } while (node != start);
    };

    displayNode(rootList.head, 0);
}

template<typename T>
int FibHeap<T>::getSize() {
    return size;
}

#endif // FIBHEAP_H