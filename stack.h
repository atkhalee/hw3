#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>
using namespace std;
// Use inheritance from std::vector (choose public/private) as appropriate
//we are using vectors
//stacks are LIFO --> Last in first out
template <typename T>
class Stack : private std::vector<T>
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary

};

template <typename T>
Stack<T>::Stack()
{

}
template <typename T>
Stack<T>::~Stack()
{
	while(!(std::vector<T>::empty()))
	{
		std::vector<T>::pop_back();
	}
}

template <typename T>
bool Stack<T>::empty() const
{
	//use iterator to iterate over the stack --> 
	if(!(std::vector<T>::empty())) //using c++ vector member function
	//instead: if(Item.back()!=NULL) --> however, NULL is for pointers
	{
		return false;
	}else
	{
		return true;
	}
	
}

template <typename T>
size_t Stack<T>::size() const
{
	return std::vector<T>::size();
}

template <typename T>
void Stack<T>::push(const T& item)
{
	std::vector<T>::push_back(item);
}

template <typename T>
void Stack<T>::pop()
{
	if(std::vector<T>::empty()){
		throw std::underflow_error("Stack is empty.");
	}else{
		std::vector<T>::pop_back();
	}
}

template <typename T>
const T& Stack<T>::top() const
{		
	if(std::vector<T>::empty()){
		throw std::underflow_error("Stack is empty.");
	}else{
		return std::vector<T>::back();
	}
}

#endif