#include <iostream>
using namespace std;

class CircularQueue {
private:
    char* queue;
    int front;
    int rear;
    int size;
    int capacity;

public:
    CircularQueue(int capacity) {
        this->capacity = capacity;
        queue = new char[capacity];
        front = -1;
        rear = -1;
        size = 0;
    }

    ~CircularQueue() {
        delete[] queue;
    }

    void enqueue(char element) {
        if (isFull()) {
            return;
        }

        if (isEmpty()) {
            front = 0;
        }

        rear = (rear + 1) % capacity;
        queue[rear] = element;
        size++;
    }

    char dequeue() {
        if (isEmpty()) {
            return '\0';
        }

        char element = queue[front];
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

    char getFront() const {
        if (isEmpty()) {
            return '\0';
        }
        return queue[front];
    }

    void display() const {
        if (isEmpty()) {
            return;
        }

        for (int i = 0; i < size; i++) {
            cout << queue[(front + i) % capacity] << " ";
        }
    }
};

int rand() {
    static unsigned int seed = 5323;
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    return seed % 32768;
}

void spinReel(CircularQueue& reel) {
    int spins = rand() % 10 + 1;
    for (int i = 0; i < spins; i++) {
        reel.enqueue(reel.dequeue());
    }
}

bool checkWin(CircularQueue& reel1, CircularQueue& reel2, CircularQueue& reel3) {
    return (reel1.getFront() == reel2.getFront() && reel2.getFront() == reel3.getFront());
}

int main() {
    CircularQueue reel1(6);
    CircularQueue reel2(6);
    CircularQueue reel3(6);

    char symbols[] = { 'A', 'B', 'C', 'D', 'E', 'F' };

    for (int i = 0; i < 6; i++) {
        reel1.enqueue(symbols[i]);
        reel2.enqueue(symbols[i]);
        reel3.enqueue(symbols[i]);
    }

    char playAgain;
    do {
        cout << "Press to 'Enter' for spin the reels...";
        cin.ignore();

        spinReel(reel1);
        spinReel(reel2);
        spinReel(reel3);

        cout << "Reel 1: ";
        reel1.display();
        cout << endl;

        cout << "Reel 2: ";
        reel2.display();
        cout << endl;

        cout << "Reel 3: ";
        reel3.display();
        cout << endl;

        if (checkWin(reel1, reel2, reel3)) {
            cout << "You win!" << endl;
        }
        else {
            cout << "try again!" << endl;
        }

        cout << "Would you like to play again?? (y/n): ";
        cin >> playAgain;
        cin.ignore();
    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}
