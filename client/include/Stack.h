#pragma once
#include <iostream>
template <typename T> class Stack{
public:
	Stack(int size)
	{
		internalArray = new T[size];
		this->size = size;
		length = 0;
	}
	Stack()
	{
		internalArray = new T[25];
		this->size = 25;
		length = 0;
	}
	~Stack()
	{
		delete[] internalArray;
	}
	void Push(T const item)
	{
		if (length < size)
		{
			internalArray[length] = item;
			length++;
		}
		else
		{
			std::cout << "Stack is full" << std::endl;
		}
	}
	T Pop()
	{
		length--;
		return internalArray[length];
	}
	T Top()
	{
		return internalArray[length - 1];
	}
	int GetLength()
	{
		return length;
	}
	bool IsEmpty()
	{
		return (length <= 0);
	}
private:
	int length;
	int size;
	T* internalArray;
};