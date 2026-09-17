#pragma once
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"

template <typename T>
Stack<T> reverseStack(Stack<T> stack) {
	Stack<T> stack_temp;
	Queue<T> queue_temp;
	while (!stack.isEmpty()) {
		queue_temp.enqueue(stack.pop());
	}
	while (!queue_temp.isEmpty()) {
		stack.push(queue_temp.dequeue());
	}
	return stack;
}