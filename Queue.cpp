#include <iostream>
using namespace std;

int A[10];
int front = -1;
int rear  = -1;

// Check if queue is empty
bool isEmpty()
{
    return (front == -1 && rear == -1);
}

// Enqueue operation
void enqueue(int x)
{
    // Queue is full
    if ((rear + 1) % 10 == front)
        return;

    // First insertion
    if (isEmpty())
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear = (rear + 1) % 10;
    }

    A[rear] = x;
}

// Dequeue operation
void dequeue()
{
    if (isEmpty())
        return;

    // Only one element
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front = (front + 1) % 10;
    }
}

// Display queue elements
void display()
{
    if (isEmpty())
    {
        cout << "Queue is empty\n";
        return;
    }

    cout << "Queue elements: ";
    int i = front;
    while (true)
    {
        cout << A[i] << " ";
        if (i == rear)
            break;
        i = (i + 1) % 10;
    }
    cout << endl;
}

int main()
{
    enqueue(2);
    enqueue(3);
    enqueue(6);

    display();

    dequeue();
    display();

    return 0;
}
