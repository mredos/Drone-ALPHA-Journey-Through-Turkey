#include "Queue.h"
#include <iostream>

// Constructor to initialize an empty queue
Queue::Queue() {
    // TODO: Your code here
    front = -1;
    rear = -1;
}

// Adds a province to the end of the queue
void Queue::enqueue(int province) {
    // TODO: Your code here
    // Implement circular structure
    // Add the province
    if((rear+1) % MAX_QUEUE_SIZE == front) {
        return;
    }

    rear = (rear+1) % MAX_QUEUE_SIZE;
    if(front == -1) {
        front += 1;
    }
    data[rear] = province;
}

// Removes and returns the front province from the queue
int Queue::dequeue() {
    // TODO: Your code here

    if (front == -1) {
        return -1;
    }else if(front == rear) {
        int deletedProvince = data[front];
        front = -1;
        rear = -1;
        return deletedProvince;
    }else {
        int deletedProvince = data[front];
        front += 1;
        return deletedProvince;
    }


}

// Returns the front province without removing it
int Queue::peek() const {
    // TODO: Your code here
    if(front == -1) {
        return -1;
    }

    return data[front];
}

// Checks if the queue is empty
bool Queue::isEmpty() const {
    // TODO: Your code here

    if(front == -1) {
        return true;
    }

    return false;
}

// Add a priority neighboring province in a way that will be dequeued and explored before other non-priority neighbors
void Queue::enqueuePriority(int province) {
    // TODO: Your code here

    if((rear+1) % MAX_QUEUE_SIZE == front) {
        return;
    }

    if(front == -1) {
        rear += 1;
        front += 1;
        data[front] = province;
        return;
    }

    // TODO BURADA EKSIK VAR SORUN SU KI YA FRONT 0 OLURSA
    if(front == 0) {
        front = MAX_QUEUE_SIZE-1;
    }else {
        front -= 1;
    }

    data[front] = province;


}

