## Exercise 3: How would you reverse the elements in a stack (i.e., put the elements at the top of the stack on the bottom and vice versa)? You can use as many additional stacks and queues as temporary storage in your approach.
take stack as input

queue_temp = empty queue
While stack is not empty
    element = stack.pop()
    queue_temp.requeue(element)
while queue is not empty
    element = queue_temp.dequeue()
    stack.push(element)

solution in excersise.h and tests in test.cpp
## Exercise 4: Come up with a strategy to solve the valid parentheses problem.

Create a empty stack
for all elements in the input string
    if the character is \{ and the last element in the stack is 1 or the stack is empty, add 1 to the stack. else return False
    if it is \[ and the last element in the stack is 1 or 2 or the stack is empty, add 2 to the stack. else return false
    if it is \(, add 3 to the stack. 
    if the chracter is \} and the last element in the stack is 1 remove the element from the stack. else return False
    if the character is \] and the last element in the stack is 2 remove the element from the stack, else return False
    if the character is \) and the last element in the stack is 3 remove the element from the stack, else return False. 
return true
## Given a stack return a copy of the original stack (i.e., a new stack with the same values as the original, stored in the same order as the original). Your method should create the new stack and fill it up with the same values that are stored in the original stack.
take stack as input

stack_copy = empty stack
tempqueue = empty queue
// reverse the stack once
While stack is not empty
    element = stack.pop()
    stack_copy.push(element)
// transfer stack copy to the queue
While stack_copy is not empty
    element = stack_copy.pop()
    tempqueue.requeue(element)
// reverse again and transfer elements to the queue
while queue is not empty
    element = tempqueue.dequeue()
    stack.push(element)
    stack_copy.push(element)





