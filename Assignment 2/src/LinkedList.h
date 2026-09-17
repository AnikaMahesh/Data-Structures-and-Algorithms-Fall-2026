#pragma once
#include <iostream>

template <typename T>
struct Node {
    Node* prev;
    Node* next;
    T data;
};

template <typename T>
class LinkedList {
public:
    Node<T>* head;
    Node<T>* last;
    int length = 0;

    LinkedList() : head(nullptr), last(nullptr) {}

    /**
    * Displays list metadata and also all the elements of the linked list.
    */
    void display() {
        cout << "head: " << head->data << "\n";
        cout << "last: " << last->data << "\n";
        cout << "length: " << length << "\n";
        Node<T>* current_node = head;
        int number = 0;
        cout << "---- Linked List Elements ----- \n";
        while (current_node != nullptr) {
            cout << "Element: " << number << "| value: " << current_node->data << "\n";
            current_node = current_node->next;
            number += 1;
        }
    }

    /**
    * Adds the element [data] to the front of the linked list.
    */
    void pushFront(T data) {
        Node<T>* new_head = new Node<T>{ nullptr, head, data };
        if (head != nullptr) {
            head->prev = new_head;
        }
        else {
            last = new_head;
        }
        head = new_head;
        length += 1;
        return;
    }

    /**
    * Adds the element [data] to the back of the linked list.
    */
    void pushBack(T data) {
        Node<T>* new_last = new Node<T>{ last, nullptr, data };
        if (last != nullptr) {
            last->next = new_last;
        }
        else {
            head = new_last;
        }
        last = new_last;
        length += 1;
        return;
    }

    /**
    * Removes an element from the front of the list. If the list is empty, it is unchanged.
    * @return the value at the front of the list or default constructed value if the list is empty
    */
    T popFront() {
        if (head == nullptr) return T{};
        Node<T>* old_head = head;
        T old_head_data = head->data;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            last = nullptr;
        }
        delete old_head;
        length -= 1;
        return old_head_data;
    }

    /**
    * Removes an element from the back of the list. If the list is empty, it is unchanged.
    * @return the value at the back of the list or nil if none exists
    */
    T popBack() {
        if (last == nullptr) return T{};
        Node<T>* old_last = last;
        T old_last_data = last->data;
        last = last->prev;
        if (last != nullptr) {
            last->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete old_last;
        length -= 1;
        return old_last_data;
    }

    /**
    * @return the value at the front of the list or nil if none exists
    */
    T peekFront() {
        if (head != nullptr) {
            T head_data = head->data;
            return head_data;
        }
        else {
            return T{};
        }
    }

    /**
    * @return the value at the back of the list or nil if none exists
    */
    T peekBack() {
        if (last != nullptr) {
            T last_data = last->data;
            return last_data;
        }
        else {
            return T{};
        }
    }

    /**
    * @return true if the list is empty and false otherwise
    */
    bool isEmpty() {
        if (head == nullptr) {
            return true;
        }
        return false;
    }
};
