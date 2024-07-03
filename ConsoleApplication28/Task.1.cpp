#include <iostream>
using namespace std;

class CircularQueue {
private:
    int* queue; 
    int front; 
    int rear; 
    int size; 
    int capacity; 

public:
    CircularQueue(int capacity) {
        this->capacity = capacity;
        queue = new int[capacity];
        front = -1;
        rear = -1;
        size = 0;
    }

    ~CircularQueue() {
        delete[] queue;
    }

    void enqueue(int element) {
        if (isFull()) {
            cout << "Queue is full. Can't add element: " << element << endl;
            return;
        }

        if (isEmpty()) {
            front = 0;
        }

        rear = (rear + 1) % capacity;
        queue[rear] = element;
        size++;
    }
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. No items to delete." << endl;
            return -1;
        }

        int element = queue[front];
        front = (front + 1) % capacity;
        size--;

        if (isEmpty()) {
            front = -1;
            rear = -1;
        }

        return element;
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == capacity;
    }

    int getSize() const {
        return size;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }

        cout << "Elements queues: ";
        for (int i = 0; i < size; i++) {
            cout << queue[(front + i) % capacity] << " ";
        }
        cout << endl;
    }
};

int main() {
    CircularQueue cq(5);

    cq.enqueue(10);
    cq.enqueue(20);
    cq.enqueue(30);
    cq.enqueue(40);
    cq.enqueue(50);

    cq.display();

    cout << "Deleted element: " << cq.dequeue() << endl;
    cq.display();

    cq.enqueue(60);
    cq.display();

    return 0;
}
