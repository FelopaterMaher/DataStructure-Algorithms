#include <iostream>
#include <queue> // For level-order traversal

using namespace std;

// Definition of a node in a BST
struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : key(val), left(nullptr), right(nullptr) {} // Constructor to initialize a node with a key value
};

// Function to insert a key into a BST
TreeNode* insert(TreeNode* root, int key) {
    // If the tree is empty, create a new node as the root
    if (root == nullptr) {
        return new TreeNode(key);
    }

    // Otherwise, recursively insert the key in the appropriate subtree
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

// Function to search for a key in a BST
bool search(TreeNode* root, int key) {
    // If the tree is empty or the key is found at the root, return true
    if (root == nullptr || root->key == key) {
        return (root != nullptr);
    }

    // Recursively search in the appropriate subtree based on the key
    if (key < root->key) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

// Function to perform inorder traversal of a BST (prints the keys in sorted order)
void inorderTraversal(TreeNode* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->key << " ";
        inorderTraversal(root->right);
    }
}

// Function to perform preorder traversal of a BST
void preorderTraversal(TreeNode* root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Function to perform postorder traversal of a BST
void postorderTraversal(TreeNode* root) {
    if (root != nullptr) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        cout << root->key << " ";
    }
}

// Function to perform level-order traversal of a BST
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

// Function to find the successor of a given node in a BST
TreeNode* findSuccessor(TreeNode* root) {
    if (root == nullptr) {
        return nullptr; // Tree is empty
    }
    while (root->left != nullptr) {
        root = root->left; // Keep traversing left until the leftmost node is reached
    }
    return root;
}

// Function to find the predecessor of a given node in a BST
TreeNode* findPredecessor(TreeNode* root) {
    if (root == nullptr) {
        return nullptr; // Tree is empty
    }
    while (root->right != nullptr) {
        root = root->right; // Keep traversing right until the rightmost node is reached
    }
    return root;
}

// Function to delete a key from a BST
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) {
        return nullptr; // Key not found or tree is empty
    }
    if (key < root->key) {
        root->left = deleteNode(root->left, key); // Recursively delete from the left subtree
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key); // Recursively delete from the right subtree
    } else {
        // Case 1: No child or 1 child
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        // Case 2: Two children
        TreeNode* temp = findSuccessor(root->right); // Find the successor node
        root->key = temp->key; // Copy the value of the successor node to the current node
        root->right = deleteNode(root->right, temp->key); // Delete the successor node from the right subtree
    }
    return root;
}

// Function to check if one binary tree is a subtree of another
bool isIdentical(TreeNode* t1, TreeNode* t2) {
    // If both trees are empty, they are identical
    if (t1 == nullptr && t2 == nullptr) {
        return true;
    }
    // If one tree is empty and the other is not, they are not identical
    if (t1 == nullptr || t2 == nullptr) {
        return false;
    }
    // If the keys at the current nodes are not equal, they are not identical
    if (t1->key != t2->key) {
        return false;
    }
    // Recursively check if the left and right subtrees are identical
    return isIdentical(t1->left, t2->left) && isIdentical(t1->right, t2->right);
}

// Function to check if t2 is a subtree of t1
bool isSubtree(TreeNode* t1, TreeNode* t2) {
    // If t2 is empty, it is always a subtree of t1
    if (t2 == nullptr) {
        return true;
    }
    // If t1 is empty but t2 is not, t2 cannot be a subtree of t1
    if (t1 == nullptr) {
        return false;
    }
    // If t1 and t2 are identical, t2 is a subtree of t1
    if (isIdentical(t1, t2)) {
        return true;
    }
    // Recursively check if t2 is a subtree of the left or right subtree of t1
    return isSubtree(t1->left, t2) || isSubtree(t1->right, t2);
}

int main() {
    // Create the first binary tree
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(4);
    root1->right = new TreeNode(5);
    root1->left->left = new TreeNode(1);
    root1->left->right = new TreeNode(2);

    // Create the second binary tree
    TreeNode* root2 = new TreeNode(4);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(2);

    // Check if root2 is a subtree of root1
    if (isSubtree(root1, root2)) {
        cout << "Tree 2 is a subtree of Tree 1" << endl;
    } else {
        cout << "Tree 2 is not a subtree of Tree 1" << endl;
    }

    // Perform various traversals on root1
    cout << "Inorder Traversal: ";
    inorderTraversal(root1);
    cout << endl;

    cout << "Preorder Traversal: ";
    preorderTraversal(root1);
    cout << endl;

    cout << "Postorder Traversal: ";
    postorderTraversal(root1);
    cout << endl;

    cout << "Level-order Traversal: ";
    levelOrderTraversal(root1);
    cout << endl;

    return 0;
}
