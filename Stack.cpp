#include "Stack.h"
#include <iostream>

// Constructor to initialize an empty stack
Stack::Stack() {
    // TODO: Your code here

    top = -1;
}

// Adds a province to the top of the stack
void Stack::push(int province) {
    // TODO: Your code here

    if(top >= MAX_SIZE - 1) {
        return; // if is Full
    }

    top += 1;
    data[top] = province;

}

// Removes and returns the top province from the stack
int Stack::pop() {
    // TODO: Your code here

    if(top == -1) {
        return -1; //empty
    }

    top -= 1;
    return data[top + 1];
}

// Returns the top province without removing it
int Stack::peek() const {
    // TODO: Your code here

    if(top == -1) {
        return -1; //empty
    }

    return data[top];
}

// Checks if the stack is empty
bool Stack::isEmpty() const {
    // TODO: Your code here

    if(top == -1) {
        return true; //empty
    }

    return false;
}

// Function to get the current size of the stack
int Stack::getSize() const {
    // TODO: Your code here


    return (top + 1);
}
