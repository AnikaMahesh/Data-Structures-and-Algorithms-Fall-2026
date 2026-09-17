#pragma once
#include "LinkedList.h"

template <typename T>
class Queue {
    LinkedList<T> list;
public:
    /**
    * Add [data] to the end of the queue.
    */
    void enqueue(T data) {
        list.pushBack(data);
    }

    /**
    * Remove the element at the front of the queue.  If the queue is empty, it remains unchanged.
    * @return the value at the front of the queue or nil if none exists
    */
    T dequeue() {
        return list.popFront();
    }

    /**
    * @return the value at the front of the queue or nil if none exists
    */
    T peek() {
        return list.peekFront();
    }

    /**
    * @return true if the queue is empty and false otherwise
    */
    bool isEmpty() {
        return list.isEmpty();
    }
};
