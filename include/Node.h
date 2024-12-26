#pragma once
#include "patient.h"

/**
 * @class FibHeap
 * @brief Forward declaration of FibHeap class template.
 * @tparam T The type of data stored in the node.
 */
template<typename T>
class FibHeap;

/**
 * @class DoublyCircularLinkedList
 * @brief Forward declaration of DoublyCircularLinkedList class template.
 * @tparam T The type of data stored in the node.
 */
template<typename T>
class DoublyCircularLinkedList;

/**
 * @class VisualizeFibonacciHeap
 * @brief Forward declaration of VisualizeFibonacciHeap class.
 */
class VisualizeFibonacciHeap;

/**
 * @class VisualizeTaskManager
 * @brief Forward declaration of VisualizeTaskManager class.
 */
class VisualizeTaskManager;



/**
 * @class Node
 * @brief Represents a node in a doubly linked list.
 * @tparam T The type of data stored in the node.
 */
template<typename T>
class Node {
private:
    int key; ///< The key value of the node.
    T Name; ///< The name associated with the node.
    int deg; ///< The degree of the node (number of children).
    Node *parent; ///< Pointer to the parent node.
    DoublyCircularLinkedList<T> *child; ///< Pointer to DLL of the children of that specific node.
    Node *left; ///< Pointer to the left sibling node.
    Node *right; ///< Pointer to the right sibling node.
    bool mark; ///< Mark indicating whether the node has lost a child since it became a child of its current parent.
    Patient * data = nullptr; ///< Class upholding Patient's extra data, Managed by the Hospital Task Manager

public:
    /**
     * @brief Constructor to initialize a node with a given name and key.
     * @param Name The name to be assigned to the node.
     * @param key The key value to be assigned to the node.
     */
    Node(T Name, int key);

    /**
     * @brief Default destructor.
     */
    ~Node();

    /**
     * @brief Gets the key value of the node.
     * @return The key value of the node.
     */
    int getKey() const;

    /**
     * @brief Gets the name of the node.
     * @return The name of the node.
     */
    T getName() const;

    /**
     * @brief Gets the degree of the node.
     * @return The degree of the node.
     */
    int getDeg() const;

    void setData(Patient * data);
    void setName(T Name);
    Patient *getData();

    // Friend class declarations
    friend class DoublyCircularLinkedList<T>;
    friend class VisualizeFibonacciHeap;
    friend class FibHeap<T>;
    friend class VisualizeTaskManager;
};

template<typename T>
Node<T>::Node(T Name, int key) : key(key), Name(Name), deg(0), parent(nullptr), child(nullptr),
                                 left(this), right(this), mark(false) {
}

template<typename T>
void Node<T>::setData(Patient * data) {
 this->data = data;
}
template<typename T>
void Node<T>::setName(T Name) {
 this->Name = Name;
}
template<typename T>
Patient* Node<T>::getData() {
 return this->data;
}


template<typename T>
Node<T>::~Node() = default;

template<typename T>
int Node<T>::getKey() const {
    return key;
}

template<typename T>
int Node<T>::getDeg() const {
    return deg;
}

template<typename T>
T Node<T>::getName() const {
    return Name;
}
