#include <iostream>
using namespace std;

// Stack node
struct Node
{
    int data;
    Node* next;
};

Node* top = NULL;

// Push operation
void push(int x)
{
    Node* temp = new Node();
    temp->data = x;
    temp->next = top;
    top = temp;
}

// Pop operation
void pop()
{
    if (top == NULL)
    {
        cout << "Error: Stack is empty\n";
        return;
    }

    Node* temp = top;
    top = top->next;
    delete temp;
}

// Print stack
void printstack()
{
    Node* temp = top;

    cout << "Stack: ";
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main()
{
    push(6);
    printstack();

    push(3);
    printstack();

    push(4);
    printstack();

    pop();
    printstack();

    return 0;
}
