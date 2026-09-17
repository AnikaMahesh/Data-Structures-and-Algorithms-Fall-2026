#include "pch.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "Excersise.h"
// Testing Linked List
// -----------------------------------------------------------------------------------------------------------------------------

// Testing isEmpty() is true and length is 0 when a fresh linked list is created
TEST(LinkedListTest, NewListIsEmpty) {
	LinkedList<int> list;
	EXPECT_TRUE(list.isEmpty());
	EXPECT_EQ(list.length, 0);
}
// Testing isEmpty() is true and length is 0 when elements are added and then deleted
TEST(LinkedListTest, EmptiedListIsEmpty) {
	LinkedList<int> list;
	list.pushFront(1);
	list.pushFront(2);
	list.popBack();
	list.popBack();
	EXPECT_TRUE(list.isEmpty());
	EXPECT_EQ(list.length, 0);
}
// Testing head and last both point to the same node in a one element list created using pushFront
TEST(LinkedListTest, TestHeadAndLastInOneItemListCreatedByPushFront) {
	LinkedList<int> list;
	list.pushFront(1);
	EXPECT_EQ(list.head->data, 1);
	EXPECT_EQ(list.last->data, 1);
	EXPECT_EQ(list.length, 1);
}

// Testing that a list created by pushFront would accurately show the relationships between
// nodes and the next node
TEST(LinkedListTest, TestForwardLinkagesInThreeItemListCreatedbyPushFront) {
	LinkedList<int> list;
	list.pushFront(2);
	list.pushFront(1);
	list.pushFront(3);
	EXPECT_EQ(list.head->data, 3);
	EXPECT_EQ(list.head->next->data, 1);
	EXPECT_EQ(list.head->next->next->data, 2);
	EXPECT_EQ(list.length, 3);
}

// Testing that a list created by pushFront would accurately show the relationships between
// nodes and the previous
TEST(LinkedListTest, TestBackwardLinkagesInThreeItemListCreatedbyPushFront) {
	LinkedList<int> list;
	list.pushFront(2);
	list.pushFront(1);
	list.pushFront(3);
	EXPECT_EQ(list.last->data, 2);
	EXPECT_EQ(list.last->prev->data, 1);
	EXPECT_EQ(list.last->prev->prev->data, 3);
	EXPECT_EQ(list.length, 3);
}

// Testing head and last both point to the same node in a one element list created using pushback
TEST(LinkedListTest, TestHeadAndLastInOneItemListCreatedByPushBack) {
	LinkedList<int> list;
	list.pushBack(1);
	EXPECT_EQ(list.head->data, 1);
	EXPECT_EQ(list.last->data, 1);
	EXPECT_EQ(list.length, 1);
}

// Testing that a list created by pushBack would accurately show the relationships between
// nodes and the next node
TEST(LinkedListTest, TestForwardLinkagesInThreeItemListCreatedByPushBack) {
	LinkedList<int> list;
	list.pushBack(2);
	list.pushBack(1);
	list.pushBack(3);
	EXPECT_EQ(list.head->data, 2);
	EXPECT_EQ(list.head->next->data, 1);
	EXPECT_EQ(list.head->next->next->data, 3);
	EXPECT_EQ(list.length, 3);
}

// Testing that a list created by pushBack would accurately show the relationships between
// nodes and their previous nodes
TEST(LinkedListTest, TestBackwardLinkagesInThreeItemListCreatedByPushBack) {
	LinkedList<int> list;
	list.pushBack(2);
	list.pushBack(1);
	list.pushBack(3);
	EXPECT_EQ(list.last->data, 3);
	EXPECT_EQ(list.last->prev->data, 1);
	EXPECT_EQ(list.last->prev->prev->data, 2);
	EXPECT_EQ(list.length, 3);
}

// Testing that a list created by pushBack and pushFront would accurately show the relationships between
// nodes and their previous nodes
TEST(LinkedListTest, TestBackwardLinkagesInThreeItemListCreatedByPushBackandPushFront) {
	LinkedList<int> list;
	list.pushBack(2);
	list.pushFront(1);
	list.pushBack(3);
	EXPECT_EQ(list.last->data, 3);
	EXPECT_EQ(list.last->prev->data, 2);
	EXPECT_EQ(list.last->prev->prev->data, 1);
	EXPECT_EQ(list.length, 3);
}

// Testing that a list created by pushBack and pushFront would accurately show the relationships between
// nodes and the next Node
TEST(LinkedListTest, TestForwardLinkagesInThreeItemListCreatedByPushBackandPushFront) {
	LinkedList<int> list;
	list.pushBack(2);
	list.pushFront(1);
	list.pushBack(3);
	EXPECT_EQ(list.head->data, 1);
	EXPECT_EQ(list.head->next->data, 2);
	EXPECT_EQ(list.head->next->next->data, 3);
	EXPECT_EQ(list.length, 3);
}

// Testing that popfront removes an element and changes the length
TEST(LinkedListTest, PopFrontReturnsAndRemovesElement) {
	LinkedList<int> list;
	list.pushBack(1);
	list.pushBack(2);
	int val = list.popFront();
	EXPECT_EQ(val, 1);
	EXPECT_EQ(list.length, 1);
	EXPECT_EQ(list.peekFront(), 2);
}
// Testing that popBack removes an element and empties the list
TEST(LinkedListTest, PopBackOnSingleElementEmptiesList) {
	LinkedList<int> list;
	list.pushBack(42);
	int val = list.popBack();
	EXPECT_EQ(val, 42);
	EXPECT_TRUE(list.isEmpty());
	EXPECT_EQ(list.length, 0);
}

// Testing that popFront returns 0 if the list is empty
TEST(LinkedListTest, PopFrontOnEmptyListReturnsDefault) {
	LinkedList<int> list;
	int val = list.popFront();
	EXPECT_EQ(val, 0); // T{} for int is 0
	EXPECT_TRUE(list.isEmpty());
}
// Testing that peekFront returns 0 if the list is empty
TEST(LinkedListTest, PeekFrontOnEmptyListReturnsDefault) {
	LinkedList<int> list;
	EXPECT_EQ(list.peekFront(), 0); // T{} for int is 0
}

// Testing that peekBack returns 0 if the list is empty
TEST(LinkedListTest, PeekBackOnEmptyListReturnsDefault) {
	LinkedList<int> list;
	EXPECT_EQ(list.peekBack(), 0);
}

// Testing that peekFront returns the correct value in a 3 element list.
TEST(LinkedListTest, PeekFrontReturnsFrontWithoutRemoving) {
	LinkedList<int> list;
	list.pushBack(10);
	list.pushBack(20);
	list.pushBack(30);
	EXPECT_EQ(list.peekFront(), 10);
	EXPECT_EQ(list.length, 3);
}

// Testing that peekBack returns the correct value in a 3 element list.
TEST(LinkedListTest, PeekBackReturnsBackWithoutRemoving) {
	LinkedList<int> list;
	list.pushBack(10);
	list.pushBack(20);
	list.pushBack(30);
	EXPECT_EQ(list.peekBack(), 30);
	EXPECT_EQ(list.length, 3);
}

// Testing that peekBack and peekFront return the same value in a one element list
TEST(LinkedListTest, PeekFrontAndBackOnSingleElementListMatch) {
	LinkedList<int> list;
	list.pushFront(99);
	EXPECT_EQ(list.peekFront(), 99);
	EXPECT_EQ(list.peekBack(), 99); // one element = both ends point to it
}

// Testing that peekFront can be called repeatedly without any side effects 
// like removing or adding elements
TEST(LinkedListTest, PeekFrontCanBeCalledRepeatedlyWithoutSideEffects) {
	LinkedList<int> list;
	list.pushBack(7);
	list.peekFront();
	list.peekFront();
	int val = list.peekFront();
	EXPECT_EQ(val, 7);
	EXPECT_EQ(list.length, 1);
}

// Testing Stack
// -----------------------------------------------------------------------------------------------------------------------------

// Testing that push adds element to the top in a empty list
TEST(StackTest, PushAddsElementToTop) {
	Stack<int> stack;
	stack.push(5);
	EXPECT_EQ(stack.peek(), 5);
}

// Testing that push adds element to the top in a 2 element list
TEST(StackTest, PushMultipleKeepsLastPushedOnTop) {
	Stack<int> stack;
	stack.push(1);
	stack.push(2);
	stack.push(3);
	EXPECT_EQ(stack.peek(), 3); // most recently pushed = top
}

// Testing that Pop returns the last pushed element
TEST(StackTest, PopReturnsTopElement) {
	Stack<int> stack;
	stack.push(11);
	stack.push(21);
	int val = stack.pop();
	EXPECT_EQ(val, 21);
}
// Testing that 2 consecutive pops work as expected
TEST(StackTest, PopRemovesElementSoNextPopReturnsPrevious) {
	Stack<int> stack;
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.pop(); 
	int val = stack.pop(); 
	EXPECT_EQ(val, 2);
}

// Testing that peek returns the correct value
TEST(StackTest, PeekReturnsTopWithoutRemoving) {
	Stack<int> stack;
	stack.push(7);
	int val = stack.peek();
	EXPECT_EQ(val, 7);
}

// Testing that peek can be called multiple times and the stack does not change
TEST(StackTest, PeekCanBeCalledMultipleTimesWithoutChangingStack) {
	Stack<int> stack;
	stack.push(1);
	stack.push(2);
	stack.peek();
	stack.peek();
	int val = stack.peek();
	EXPECT_EQ(val, 2); 
}

// Testing that isEmpty returns true on empty list
TEST(StackTest, NewStackIsEmpty) {
	Stack<int> stack;
	EXPECT_TRUE(stack.isEmpty());
}

// Testing that isEmpty returns false on 1 element list
TEST(StackTest, StackIsNotEmptyAfterPush) {
	Stack<int> stack;
	stack.push(1);
	EXPECT_FALSE(stack.isEmpty());
}

// Testing Queue
// -----------------------------------------------------------------------------------------------------------------------------

// Testing that Enqueue adds element and peek returns the added element
TEST(QueueTest, EnqueueAddsElement) {
	Queue<int> queue;
	queue.enqueue(5);
	EXPECT_EQ(queue.peek(), 5);
}

// Testing that the first queued is the one returned when peek is used
TEST(QueueTest, EnqueueKeepsFirstEnqueuedAtFront) {
	Queue<int> queue;
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);
	EXPECT_EQ(queue.peek(), 1);
}

// Testing that the first queued is the one dequeued
TEST(QueueTest, DequeueReturnsFrontElement) {
	Queue<int> queue;
	queue.enqueue(10);
	queue.enqueue(20);
	int val = queue.dequeue();
	EXPECT_EQ(val, 10);
}

// Testing dequeue in a 3 element list
TEST(QueueTest, DequeueRemovesElementSoNextDequeueReturnsNext) {
	Queue<int> queue;
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);
	queue.dequeue();
	int val = queue.dequeue();
	EXPECT_EQ(val, 2);
}

// Testing that peek returns the right value
TEST(QueueTest, PeekReturnsFrontWithoutRemoving) {
	Queue<int> queue;
	queue.enqueue(7);
	int val = queue.peek();
	EXPECT_EQ(val, 7);
}

// Testing that peek can be called multiple times without affecting the queue
TEST(QueueTest, PeekCanBeCalledMultipleTimesWithoutChangingQueue) {
	Queue<int> queue;
	queue.enqueue(1);
	queue.enqueue(2);
	queue.peek();
	queue.peek();
	int val = queue.peek();
	EXPECT_EQ(val, 1); // still 1 — nothing was ever dequeued
}

// Testing that isEmpty returns true in a new queue
TEST(QueueTest, NewQueueIsEmpty) {
	Queue<int> queue;
	EXPECT_TRUE(queue.isEmpty());
}

// Testing that isEmpty returns false in a 1 element queue
TEST(QueueTest, QueueIsNotEmptyAfterEnqueue) {
	Queue<int> queue;
	queue.enqueue(1);
	EXPECT_FALSE(queue.isEmpty());
}

// Testing reverse list
// -----------------------------------------------------------------------------------------------------------------------------
//
//
// Tests a stack is properly reversed
TEST(ReverseStackTest, ReversesOrderOfElements) {
	Stack<int> stack;
	stack.push(1);
	stack.push(2);
	stack.push(3); 
	Stack<int> reversed = reverseStack(stack);
	EXPECT_EQ(reversed.pop(), 1);
	EXPECT_EQ(reversed.pop(), 2);
	EXPECT_EQ(reversed.pop(), 3);
}

// Tests on empty stack
TEST(ReverseStackTest, EmptyStackReversesToEmptyStack) {
	Stack<int> stack;
	Stack<int> reversed = reverseStack(stack);
	EXPECT_TRUE(reversed.isEmpty());
}

// Tests a reversed single element stack is identical to the original
TEST(ReverseStackTest, SingleElementStackReversesToSameSingleElement) {
	Stack<int> stack;
	stack.push(42);
	Stack<int> reversed = reverseStack(stack);
	EXPECT_EQ(reversed.pop(), 42);
	EXPECT_TRUE(reversed.isEmpty());
}