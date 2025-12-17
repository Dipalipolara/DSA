#include <iostream>
using namespace std;

// AVL Tree Node
struct Node
{
    int data;
    int height;
    Node* left;
    Node* right;
};

// Create new node
Node* NewNode(int data)
{
    Node* temp = new Node();
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}

// Utility functions
int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(Node* node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int Balance(Node* node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Right Rotation
Node* RightRotate(Node* z)
{
    Node* y = z->left;
    Node* t3 = y->right;

    y->right = z;
    z->left = t3;

    z->height = max(height(z->left), height(z->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Left Rotation
Node* LeftRotate(Node* z)
{
    Node* y = z->right;
    Node* t2 = y->left;

    y->left = z;
    z->right = t2;

    z->height = max(height(z->left), height(z->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Preorder traversal
void preorder(Node* root)
{
    if (root == NULL)
        return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Find minimum value node
Node* FindMin(Node* node)
{
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Insert into AVL Tree
Node* Insert(Node* root, int data)
{
    if (root == NULL)
        return NewNode(data);

    if (data < root->data)
        root->left = Insert(root->left, data);
    else if (data > root->data)
        root->right = Insert(root->right, data);
    else
        return root;

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = Balance(root);

    // LL Case
    if (balance > 1 && data < root->left->data)
        return RightRotate(root);

    // RR Case
    if (balance < -1 && data > root->right->data)
        return LeftRotate(root);

    // LR Case
    if (balance > 1 && data > root->left->data)
    {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    // RL Case
    if (balance < -1 && data < root->right->data)
    {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root;
}

// Delete node from AVL Tree
Node* Delete(Node* root, int data)
{
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = Delete(root->left, data);
    else if (data > root->data)
        root->right = Delete(root->right, data);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
        }
        else if (root->left != NULL && root->right == NULL)
        {
            Node* temp = root;
            root = root->left;
            delete temp;
        }
        else if (root->right != NULL && root->left == NULL)
        {
            Node* temp = root;
            root = root->right;
            delete temp;
        }
        else
        {
            Node* temp = FindMin(root->right);
            root->data = temp->data;
            root->right = Delete(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = Balance(root);

    // LL Case
    if (balance > 1 && Balance(root->left) >= 0)
        return RightRotate(root);

    // RR Case
    if (balance < -1 && Balance(root->right) <= 0)
        return LeftRotate(root);

    // LR Case
    if (balance > 1 && Balance(root->left) < 0)
    {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    // RL Case
    if (balance < -1 && Balance(root->right) > 0)
    {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root;
}

// Main function
int main()
{
    Node* root = NULL;

    root = Insert(root, 5);
    root = Insert(root, 10);
    root = Insert(root, 15);
    root = Insert(root, 25);
    root = Insert(root, 30);
    root = Insert(root, 14);
    root = Insert(root, 23);
    root = Insert(root, 6);
    root = Insert(root, 24);
    root = Insert(root, 30);
    root = Insert(root, 3);

    cout << "\nPreorder traversal of AVL Tree: ";
    preorder(root);

    root = Delete(root, 10);

    cout << "\nPreorder traversal after deleting 10: ";
    preorder(root);

    return 0;
}

