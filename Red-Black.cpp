#include <iostream>
#include <queue>
using namespace std;

// CLRS Based Red Black Tree
enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int d) {
        data = d;
        color = RED;
        left = right = parent = NULL;
    }
};

Node* root = NULL;

// -------------------- Level Order --------------------
void levelOrder(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();

        cout << cur->data << " ";

        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

// -------------------- Rotations --------------------
void leftRotate(Node*& root, Node*& x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left)
        y->left->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(Node*& root, Node*& x) {
    Node* y = x->left;
    x->left = y->right;

    if (y->right)
        y->right->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}

// -------------------- Fix Insertion --------------------
void fixInsert(Node*& root, Node*& z) {
    while (z != root && z->parent->color == RED) {
        Node* parent = z->parent;
        Node* grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if (uncle && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                z = grandparent;
            } else {
                if (z == parent->right) {
                    leftRotate(root, parent);
                    z = parent;
                }
                rightRotate(root, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                z = parent;
            }
        } else {
            Node* uncle = grandparent->left;

            if (uncle && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                z = grandparent;
            } else {
                if (z == parent->left) {
                    rightRotate(root, parent);
                    z = parent;
                }
                leftRotate(root, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                z = parent;
            }
        }
    }
    root->color = BLACK;
}

// -------------------- Insert --------------------
void insert(int data) {
    Node* z = new Node(data);
    Node* y = NULL;
    Node* x = root;

    while (x) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (!y)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    fixInsert(root, z);
}

// -------------------- Preorder --------------------
void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// -------------------- Search --------------------
Node* search(Node* root, int key) {
    if (!root || root->data == key)
        return root;
    if (key < root->data)
        return search(root->left, key);
    return search(root->right, key);
}

// -------------------- Minimum --------------------
Node* minimum(Node* node) {
    while (node->left)
        node = node->left;
    return node;
}

// -------------------- Transplant --------------------
void transplant(Node*& root, Node*& u, Node*& v) {
    if (!u->parent)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v)
        v->parent = u->parent;
}

// -------------------- Fix Delete --------------------
void fixDelete(Node*& root, Node*& x) {
    while (x != root && (!x || x->color == BLACK)) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }

            if ((!w->left || w->left->color == BLACK) &&
                (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (!w->right || w->right->color == BLACK) {
                    if (w->left) w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right) w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }

            if ((!w->left || w->left->color == BLACK) &&
                (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (!w->left || w->left->color == BLACK) {
                    if (w->right) w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left) w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = root;
            }
        }
    }
    if (x) x->color = BLACK;
}

// -------------------- Delete --------------------
void deleteNode(Node* z) {
    Node* y = z;
    Color yOriginal = y->color;
    Node* x;

    if (!z->left) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (!z->right) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = minimum(z->right);
        yOriginal = y->color;
        x = y->right;

        if (y->parent == z) {
            if (x) x->parent = y;
        } else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginal == BLACK)
        fixDelete(root, x);
}

// -------------------- MAIN --------------------
int main() {
    insert(2);
    insert(1);
    insert(4);
    insert(5);
    insert(9);
    insert(3);
    insert(6);
    insert(7);

    cout << "Preorder: ";
    preorder(root);

    cout << "\nLevel Order: ";
    levelOrder(root);

    Node* x = search(root, 5);
    deleteNode(x);

    cout << "\nAfter Deleting 5\nPreorder: ";
    preorder(root);

    cout << "\nLevel Order: ";
    levelOrder(root);

    return 0;
}
