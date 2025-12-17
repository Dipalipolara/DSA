#include <iostream>
using namespace std;

// BST Node
struct Node
{
    Node* left;
    int data;
    Node* right;
};

// Queue node for Level Order Traversal
struct Queue
{
    Node* data;
    Queue* next;
};

Queue* front = NULL;
Queue* rear = NULL;

// Check if queue is empty
bool isEmpty()
{
    return (front == NULL);
}

// Remove element from queue
void Pop()
{
    if (isEmpty())
        return;

    Queue* temp = front;
    front = front->next;
    delete temp;
}

// Peek front element
Node* Pfront()
{
    return front->data;
}

// Insert into queue
void Enqueue(Node* data)
{
    Queue* temp = new Queue();
    temp->data = data;
    temp->next = NULL;

    if (front == NULL && rear == NULL)
    {
        front = rear = temp;
        return;
    }

    rear->next = temp;
    rear = temp;
}

// Create new BST node
Node* NewNode(int data)
{
    Node* temp = new Node();
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

// Traversals
void PreOrder(Node* root)
{
    if (root == NULL) return;
    cout << root->data << " ";
    PreOrder(root->left);
    PreOrder(root->right);
}

void InOrder(Node* root)
{
    if (root == NULL) return;
    InOrder(root->left);
    cout << root->data << " ";
    InOrder(root->right);
}

void PostOrder(Node* root)
{
    if (root == NULL) return;
    PostOrder(root->left);
    PostOrder(root->right);
    cout << root->data << " ";
}

// Find minimum value node
Node* FindMin(Node* root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Level Order Traversal
void LevelOrder(Node* root)
{
    if (root == NULL) return;

    Enqueue(root);

    while (!isEmpty())
    {
        Node* current = Pfront();
        cout << current->data << " ";

        if (current->left != NULL)
            Enqueue(current->left);
        if (current->right != NULL)
            Enqueue(current->right);

        Pop();
    }
}

// Insert into BST
Node* insert(Node* root, int data)
{
    if (root == NULL)
        return NewNode(data);

    if (data <= root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);

    return root;
}

// Delete from BST
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
        // No child
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
        }
        // One child
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
        // Two children
        else
        {
            Node* temp = FindMin(root->right);
            root->data = temp->data;
            root->right = Delete(root->right, temp->data);
        }
    }
    return root;
}