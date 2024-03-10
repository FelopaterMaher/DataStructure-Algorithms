#include <iostream>
#include <queue>
using namespace std;

// Definition of a node in an AVL tree
struct TreeNode {
    int key;
    int height;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : key(val), height(1), left(nullptr), right(nullptr) {}
};

// Function to get the height of a node
int getHeight(TreeNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// Function to update the height of a node
void updateHeight(TreeNode* node) {
    if (node == nullptr) return;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Function to perform right rotation
TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

// Function to perform left rotation
TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

// Function to balance a subtree
TreeNode* balance(TreeNode* root) {
    if (root == nullptr) return root;

    // Check the balance factor
    int balanceFactor = getHeight(root->left) - getHeight(root->right);

    // Left heavy case
    if (balanceFactor > 1) {
        if (getHeight(root->left->left) >= getHeight(root->left->right)) {
            // Left-left case
            return rightRotate(root);
        } else {
            // Left-right case
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    // Right heavy case
    if (balanceFactor < -1) {
        if (getHeight(root->right->right) >= getHeight(root->right->left)) {
            // Right-right case
            return leftRotate(root);
        } else {
            // Right-left case
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root; // Tree is balanced
}

// Function to insert a key into an AVL tree
TreeNode* insertAVL(TreeNode* root, int key) {
    // Perform standard BST insertion
    if (root == nullptr) return new TreeNode(key);

    if (key < root->key) {
        root->left = insertAVL(root->left, key);
    } else if (key > root->key) {
        root->right = insertAVL(root->right, key);
    } else {
        return root; // Duplicate keys are not allowed
    }

    // Update height of the current node
    updateHeight(root);

    // Balance the tree
    return balance(root);
}

// Function to perform inorder traversal of an AVL tree (prints the keys in sorted order)
void inorderTraversal(TreeNode* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->key << " ";
        inorderTraversal(root->right);
    }
}

// Function to perform level-order traversal of an AVL tree
void levelOrderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        cout << current->key << " ";

        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}

// Function to find the successor of a given node in an AVL tree
TreeNode* findSuccessor(TreeNode* root) {
    if (root == nullptr) return nullptr;

    if (root->right != nullptr) {
        root = root->right;
        while (root->left != nullptr) {
            root = root->left;
        }
        return root;
    }

    return nullptr;
}

// Function to find the predecessor of a given node in an AVL tree
TreeNode* findPredecessor(TreeNode* root) {
    if (root == nullptr) return nullptr;

    if (root->left != nullptr) {
        root = root->left;
        while (root->right != nullptr) {
            root = root->right;
        }
        return root;
    }

    return nullptr;
}

// Function to delete a key from an AVL tree
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) return nullptr;

    // Perform standard BST delete
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node to be deleted found
        if (root->left == nullptr || root->right == nullptr) {
            TreeNode* temp = (root->left != nullptr) ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            TreeNode* successor = findSuccessor(root);
            root->key = successor->key;
            root->right = deleteNode(root->right, successor->key);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr) return root;

    // Update height of the current node
    updateHeight(root);

    // Balance the tree
    return balance(root);
}

int main() {
    TreeNode* root = nullptr;

    // Insert elements into the AVL tree
    root = insertAVL(root, 10);
    root = insertAVL(root, 20);
    root = insertAVL(root, 30);
    root = insertAVL(root, 40);
    root = insertAVL(root, 50);
    root = insertAVL(root, 25);

    // Perform inorder traversal of the AVL tree
    cout << "Inorder traversal of the AVL tree: ";
    inorderTraversal(root);
    cout << endl;

    // Perform level-order traversal of the AVL tree
    cout << "Level-order traversal of the AVL tree: ";
    levelOrderTraversal(root);
    cout << endl;

    // Find predecessor and successor
    TreeNode* predecessor = findPredecessor(root->left->right);
    TreeNode* successor = findSuccessor(root->left->right);
    if (predecessor != nullptr) cout << "Predecessor of " << root->left->right->key << " is " << predecessor->key << endl;
    if (successor != nullptr) cout << "Successor of " << root->left->right->key << " is " << successor->key << endl;

    // Delete a node from the AVL tree
    root = deleteNode(root, 30);
    cout << "After deleting node with key 30, inorder traversal of the AVL tree: ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
