#pragma once
#include "LinkedList.h"

template <typename T>
class Stack {
    LinkedList<T> list;
public:
    /**
    * Add [data] to the top of the stack
    */
    void push(T data) {
        list.pushFront(data);
    }
    /**
    * Remove the element at the top of the stack.  If the stack is empty, it remains unchanged.
    * @return the value at the top of the stack or nil if none exists
    */
    T pop() {
        return list.popFront();
    }
    /**
    * @return the value on the top of the stack or  if none exists
    */
    T peek() {
        return list.peekFront();
    }
    /**
    * @return true if the stack is empty and false otherwise
    */
    bool isEmpty() {
        return list.isEmpty();
    }
};
