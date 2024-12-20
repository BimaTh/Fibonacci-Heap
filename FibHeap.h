#ifndef FIBHEAP_H
#define FIBHEAP_H
#include <functional>

template<typename T>
class Node;

template<typename T>
class DoublyCircularLinkedList;


/**
 * @class FibHeap
 * @brief Represents a Fibonacci Heap data structure.
 *
 * This class provides the implementation of a Fibonacci Heap, including
 * operations such as insertion, merging, extracting the minimum, and
 * decreasing or increasing keys.
 */
template<typename T>
class FibHeap {
private:
    Node<T> *min; ///< Pointer to the node with the minimum key.
    int size; ///< Number of nodes in the heap.
    DoublyCircularLinkedList<T> rootList; ///< Root linked list.


    /**
   * @brief Links two trees of the same degree.
   * @param y Pointer to the first node.
   * @param x Pointer to the second node.
   * @pre Both nodes y and x must be non-null and have the same degree.
   * @post Node y is linked to node x as a child.
   */
    void link(Node<T> *y, Node<T> *x);

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
    void cut(Node<T> *x, Node<T> *y);

    /**
     * @brief Performs a cascading cut operation.
     * @param y Pointer to the node to start the cascading cut.
     * @pre Node y must be non-null.
     * @post Cascading cut is performed starting from node y.
     */
    void cascadingCut(Node<T> *y);

    /**
    * @brief Searches for a node with a specific key in the heap.
    * @param root Pointer to the root node to start the search.
    * @param key The key value to search for.
    * @return Pointer to the node with the specified key, or nullptr if not found.
    * @pre The heap must not be empty.
    * @post The node with the specified key is returned if found, otherwise nullptr.
    */
    Node<T> *search(Node<T> *root, int key) const;

public:
    /**
     * @brief Default constructor to initialize an empty Fibonacci Heap.
     * @pre None.
     * @post An empty Fibonacci Heap is created.
     */
    FibHeap() : min(nullptr), size(0) {
    }

    /**
     * @brief Inserts a node into the heap.
     * @param x Pointer to the node to be inserted.
     * @pre Node x must be non-null.
     * @post Node x is inserted into the heap.
     */
    void insert(Node<T> *x);

    /**
     * @brief Extracts the minimum node from the heap.
     * @return Pointer to the node with the minimum key.
     * @pre The heap must not be empty.
     * @post The minimum node is removed from the heap.
     */
    Node<T> *extractMin();

    /**
     * @brief Displays the minimum node in the heap.
     * @return Pointer to the node with the minimum key.
     * @pre The heap must not be empty.
     * @post The minimum node is displayed.
     */
    Node<T> *displayMinimum();

    /**
     * @brief Decreases the key of a node.
     * @param x Pointer to the node.
     * @param k The new key value.
     * @pre Node x must be non-null, and k must be less than the current key of x.
     * @post The key of node x is decreased to k.
     */
    void modifyKey(int k, int new_k);

    /**
     * @brief Deletes a node from the heap.
     * @param x Pointer to the node to be deleted.
     * @pre Node x must be non-null.
     * @post Node x is deleted from the heap.
     */
    void deleteNode(int k);

    void display();

    /**
   * @brief Finds a node with a specific key in the heap.
   * @param key The key value to search for.
   * @return Pointer to the node with the specified key, or nullptr if not found.
   * @pre The heap must not be empty.
   * @post The node with the specified key is returned if found, otherwise nullptr.
   */
    Node<T> *find(int key) const;
};

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
}

template<typename T>
Node<T> *FibHeap<T>::extractMin() {
    Node<T> *minptr = min;
    if (minptr == nullptr) {
        return minptr;
    }
    if (minptr->child != nullptr) {
        int numChildren = minptr->child->size;
        for (int i = 0; i < numChildren; i++) {
            // Add children of minptr to the root list
            Node<T> *child = minptr->child->head;
            minptr->child->remove(child);
            rootList.insert(child);
            child->parent = nullptr;
        }
    }
    minptr->left->right = minptr->right; // Remove minptr from the root list
    minptr->right->left = minptr->left;
    if (minptr == minptr->right) {
        min = nullptr;
    } else {
        min = minptr->right;
        consolidate();
    }
    size--;

    return minptr;
}

template<typename T>
void FibHeap<T>::consolidate() {
    const int fibsize = 45; // Maximum degree of a node in a Fibonacci heap
    Node<T> *A[fibsize];
    Node<T> *x = min;
    int iterations = rootList.size;
    for (int i = 0; i < fibsize; i++)
        A[i] = nullptr;
    while (--iterations) {
        int d = x->deg;
        while (A[d] != nullptr) {
            Node<T> *y = A[d];
            if (x->key > y->key)
                std::swap(x, y);
            link(y, x);
            A[d] = nullptr;
            ++d;
        }
        A[d] = x;
        x->deg = d;
        x = x->right;
    }
    min = nullptr;
    rootList = DoublyCircularLinkedList<T>(); // Initialize new root list to be filled with the consolidated nodes
    for (int i = 0; i < fibsize; i++) {
        if (A[i] == nullptr) continue;
        rootList.insert(A[i]);
        if (min == nullptr || A[i]->key < min->key)
            min = A[i];
    }
}

template<typename T>
void FibHeap<T>::link(Node<T> *y, Node<T> *x) {
    Node<T> *temp = this->rootList.remove(y);
    if (x->child == nullptr)
        x->child = new DoublyCircularLinkedList<T>();
    x->child->insert(temp);
    temp->parent = x;
    temp->mark = false;
    std::cout << "Link node successful: " << y->key << " -> " << x->key << std::endl;
}

template<typename T>
Node<T> *FibHeap<T>::search(Node<T> *current, int key) const {
    if (current == nullptr) {
        return nullptr;
    }

    Node<T> *result = nullptr;
    Node<T> *start = current;
    do {
        if (current->key == key) {
            result = current;
            break;
        }
        if (current->child != nullptr) {
            result = search(current->child->head, key); // Start search from the head of the child list
            if (result != nullptr) {
                break;
            }
        }
        current = current->right;
    } while (current != start);

    return result;
}

template<typename T>
Node<T> *FibHeap<T>::find(int key) const {
    return search(this->rootList.head, key);
}

template<typename T>
void FibHeap<T>::modifyKey(int currentNodeKey, int new_k) {
    Node<T> *x = find(currentNodeKey);

    if (x != nullptr && new_k > x->key) {
        std::cerr << "New key is greater than the current key." << std::endl;
    }

    x->key = new_k;
    Node<T> *y = x->parent;
    if (y != nullptr && x->key < y->key) {
        cut(x, y);
        cascadingCut(y);
    }
    if (x->key < min->key) {
        min = x;
    }
}

template<typename T>
void FibHeap<T>::cut(Node<T> *x, Node<T> *y) {
    if (x->parent != y) {
        std::cerr << "Calling Cut function while provided wrong child and parent.";
    }

    Node<T> *temp = y->child->remove(x);
    rootList.insert(temp);
    temp->parent = nullptr;
    temp->mark = false;
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
}


template<typename T>
void FibHeap<T>::deleteNode(int k) {
    Node<T> *x = find(k);

    if (x->parent) {
        Node<T> *temp = x->parent;
        temp->child->deleteNode(x);
    } else {
        this->rootList.deleteNode(x);
    }
    std::cout << "Deleted node x successfully";
}


template<typename T>
Node<T> *FibHeap<T>::displayMinimum() {
    return this->min;
}


template<typename T>
void FibHeap<T>::display() {
    if (!rootList.head) {
        std::cout << "The Fibonacci heap is empty." << std::endl;
        return;
    }

    Node<T> *current = rootList.head;
    do {
        std::cout << "Key: " << current->getKey() << ", Name: " << current->getName() << ", Degree: " << current->
                getDeg() << std::endl; // Print the current node

        current = current->right;
    } while (current != rootList.head);
}

#endif // FIBHEAP_H
