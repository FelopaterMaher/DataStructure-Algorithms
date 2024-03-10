#include <iostream>
#include <queue>
#include <stack>
using namespace std;

enum Color { RED, BLACK }; // Enum for defining colors

template <class T>
class Node {
public:
    T data; // Data stored in the node
    Color color; // Color of the node in Red-Black Tree
    Node<T>* left, *right, *parent; // Pointers to left child, right child, and parent

    Node(T data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {} // Constructor for Node
};

template <class T>
class RedBlackTree {
private:
    Node<T>* root; // Root of the Red-Black Tree

    // Private helper functions
    void rotateLeft(Node<T>*&); // Left rotation operation
    void rotateRight(Node<T>*&); // Right rotation operation
    void fixInsertRBTree(Node<T>*&); // Fix-up operation after insertion
    void fixDeleteRBTree(Node<T>*&); // Fix-up operation after deletion
    void inOrderHelper(Node<T>*); // Helper function for in-order traversal
    void preOrderHelper(Node<T>*); // Helper function for pre-order traversal
    void postOrderHelper(Node<T>*); // Helper function for post-order traversal
    Node<T>* findSuccessor(Node<T>*); // Find successor of a node
    Node<T>* findPredecessor(Node<T>*); // Find predecessor of a node
    Node<T>* searchHelper(Node<T>*, T); // Helper function for searching a key
    bool isSubtree(Node<T>*, Node<T>*); // Helper function to check if one tree is subtree of another
    void deleteNode(Node<T>*); // Delete a node from the tree
    void transplant(Node<T>*, Node<T>*); // Replace a node with another in the tree

public:
    RedBlackTree() : root(nullptr) {} // Constructor for Red-Black Tree

    // Traversal methods
    void inOrderTraversal(); // In-order traversal of the tree
    void preOrderTraversal(); // Pre-order traversal of the tree
    void postOrderTraversal(); // Post-order traversal of the tree

    // Insertion, deletion, and searching methods
    void insert(T); // Insert a key into the tree
    void remove(T); // Remove a key from the tree
    Node<T>* search(T); // Search for a key in the tree

    // Function to detect if one tree is a subtree of another tree
    bool isSubtreeOf(RedBlackTree<T>&); // Check if this tree is subtree of another tree
};

// Implementation of member functions

// Left rotation operation
template <class T>
void RedBlackTree<T>::rotateLeft(Node<T>*& root) {
    // Implementation of left rotation
    Node<T>* newRoot = root->right;
    root->right = newRoot->left;
    if (root->right != nullptr)
        root->right->parent = root;
    newRoot->parent = root->parent;
    if (root->parent == nullptr)
        this->root = newRoot;
    else if (root == root->parent->left)
        root->parent->left = newRoot;
    else
        root->parent->right = newRoot;
    newRoot->left = root;
    root->parent = newRoot;
}

// Right rotation operation
template <class T>
void RedBlackTree<T>::rotateRight(Node<T>*& root) {
    // Implementation of right rotation
    Node<T>* newRoot = root->left;
    root->left = newRoot->right;
    if (root->left != nullptr)
        root->left->parent = root;
    newRoot->parent = root->parent;
    if (root->parent == nullptr)
        this->root = newRoot;
    else if (root == root->parent->left)
        root->parent->left = newRoot;
    else
        root->parent->right = newRoot;
    newRoot->right = root;
    root->parent = newRoot;
}

// Fix-up operation after insertion
template <class T>
void RedBlackTree<T>::fixInsertRBTree(Node<T>*& node) {
    // Implementation of fix-up after insertion
    while (node != root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            Node<T>* uncle = node->parent->parent->right;
            if (uncle != nullptr && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotateLeft(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateRight(node->parent->parent);
            }
        } else {
            Node<T>* uncle = node->parent->parent->left;
            if (uncle != nullptr && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateLeft(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// Fix-up operation after deletion
template <class T>
void RedBlackTree<T>::fixDeleteRBTree(Node<T>*& node) {
    // Implementation of fix-up after deletion
    while (node != root && (node == nullptr || node->color == BLACK)) {
        if (node == node->parent->left) {
            Node<T>* sibling = node->parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateLeft(node->parent);
                sibling = node->parent->right;
            }
            if ((sibling->left == nullptr || sibling->left->color == BLACK) && 
                (sibling->right == nullptr || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = node->parent;
            } else {
                if (sibling->right == nullptr || sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->right->color = BLACK;
                rotateLeft(node->parent);
                node = root;
            }
        } else {
            Node<T>* sibling = node->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateRight(node->parent);
                sibling = node->parent->left;
            }
            if ((sibling->right == nullptr || sibling->right->color == BLACK) && 
                (sibling->left == nullptr || sibling->left->color == BLACK)) {
                sibling->color = RED;
                node = node->parent;
            } else {
                if (sibling->left == nullptr || sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->left->color = BLACK;
                rotateRight(node->parent);
                node = root;
            }
        }
    }
    if (node != nullptr)
        node->color = BLACK;
}

// Helper function for in-order traversal
template <class T>
void RedBlackTree<T>::inOrderHelper(Node<T>* node) {
    if (node == nullptr)
        return;
    inOrderHelper(node->left);
    cout << node->data << " ";
    inOrderHelper(node->right);
}

// Helper function for pre-order traversal
template <class T>
void RedBlackTree<T>::preOrderHelper(Node<T>* node) {
    if (node == nullptr)
        return;
    cout << node->data << " ";
    preOrderHelper(node->left);
    preOrderHelper(node->right);
}

// Helper function for post-order traversal
template <class T>
void RedBlackTree<T>::postOrderHelper(Node<T>* node) {
    if (node == nullptr)
        return;
    postOrderHelper(node->left);
    postOrderHelper(node->right);
    cout << node->data << " ";
}

// Find successor of a node
template <class T>
Node<T>* RedBlackTree<T>::findSuccessor(Node<T>* node) {
    if (node == nullptr)
        return nullptr;
    if (node->right != nullptr) {
        node = node->right;
        while (node->left != nullptr)
            node = node->left;
        return node;
    }
    Node<T>* parent = node->parent;
    while (parent != nullptr && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

// Find predecessor of a node
template <class T>
Node<T>* RedBlackTree<T>::findPredecessor(Node<T>* node) {
    if (node == nullptr)
        return nullptr;
    if (node->left != nullptr) {
        node = node->left;
        while (node->right != nullptr)
            node = node->right;
        return node;
    }
    Node<T>* parent = node->parent;
    while (parent != nullptr && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

// Helper function for searching a key
template <class T>
Node<T>* RedBlackTree<T>::searchHelper(Node<T>* root, T key) {
    if (root == nullptr || root->data == key)
        return root;
    if (key < root->data)
        return searchHelper(root->left, key);
    return searchHelper(root->right, key);
}

// In-order traversal of the tree
template <class T>
void RedBlackTree<T>::inOrderTraversal() {
    inOrderHelper(root);
}

// Pre-order traversal of the tree
template <class T>
void RedBlackTree<T>::preOrderTraversal() {
    preOrderHelper(root);
}

// Post-order traversal of the tree
template <class T>
void RedBlackTree<T>::postOrderTraversal() {
    postOrderHelper(root);
}

// Insert a key into the tree
template <class T>
void RedBlackTree<T>::insert(T key) {
    Node<T>* newNode = new Node<T>(key);
    Node<T>* parent = nullptr;
    Node<T>* current = root;
    while (current != nullptr) {
        parent = current;
        if (newNode->data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    newNode->parent = parent;
    if (parent == nullptr)
        root = newNode;
    else if (newNode->data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;
    fixInsertRBTree(newNode);
}

// Delete a node from the tree
template <class T>
void RedBlackTree<T>::deleteNode(Node<T>* node) {
    if (node == nullptr)
        return;
    Node<T>* child = nullptr;
    Node<T>* toDelete = node;
    Color originalColor = toDelete->color;
    if (node->left == nullptr) {
        child = node->right;
        if (child == nullptr) {
            child = new Node<T>(T());
            child->parent = node;
            node->right = child;
        }
        transplant(node, node->right);
    } else if (node->right == nullptr) {
        child = node->left;
        if (child == nullptr) {
            child = new Node<T>(T());
            child->parent = node;
            node->left = child;
        }
        transplant(node, node->left);
    } else {
        toDelete = findSuccessor(node);
        originalColor = toDelete->color;
        child = toDelete->right;
        if (child == nullptr) {
            child = new Node<T>(T());
            child->parent = toDelete;
            toDelete->right = child;
        }
        if (toDelete->parent == node)
            child->parent = toDelete;
        else {
            transplant(toDelete, toDelete->right);
            toDelete->right = node->right;
            toDelete->right->parent = toDelete;
        }
        transplant(node, toDelete);
        toDelete->left = node->left;
        toDelete->left->parent = toDelete;
        toDelete->color = node->color;
    }
    delete child;
    if (originalColor == BLACK)
        fixDeleteRBTree(child);
    delete node;
}

// Replace a node with another in the tree
template <class T>
void RedBlackTree<T>::transplant(Node<T>* u, Node<T>* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

// Remove a key from the tree
template <class T>
void RedBlackTree<T>::remove(T key) {
    Node<T>* node = search(key);
    deleteNode(node);
}

// Search for a key in the tree
template <class T>
Node<T>* RedBlackTree<T>::search(T key) {
    return searchHelper(root, key);
}

// Helper function to check if one tree is subtree of another
template <class T>
bool RedBlackTree<T>::isSubtree(Node<T>* root1, Node<T>* root2) {
    if (root2 == nullptr)
        return true;
    if (root1 == nullptr)
        return false;
    if (root1->data == root2->data) {
        return isSubtree(root1->left, root2->left) && isSubtree(root1->right, root2->right);
    }
    return isSubtree(root1->left, root2) || isSubtree(root1->right, root2);
}

// Check if this tree is subtree of another tree
template <class T>
bool RedBlackTree<T>::isSubtreeOf(RedBlackTree<T>& otherTree) {
    return isSubtree(root, otherTree.root);
}

// Main function for testing
int main() {
    // Example usage
    RedBlackTree<int> rbt;
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(5);
    rbt.insert(15);

    cout << "In-order traversal: ";
    rbt.inOrderTraversal();
    cout << endl;

    cout << "Pre-order traversal: ";
    rbt.preOrderTraversal();
    cout << endl;

    cout << "Post-order traversal: ";
    rbt.postOrderTraversal();
    cout << endl;

    return 0;
}
