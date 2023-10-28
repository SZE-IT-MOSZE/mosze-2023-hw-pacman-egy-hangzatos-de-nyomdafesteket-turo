#ifndef DLINKED_LIST
#define DLINKED_LIST

#include <stdexcept>
#include "DLinkedList.hpp"

// #include "DLinkedListNode.hpp"


template<class T>
DLinkedList<T>::DLinkedList()
{
	firstElement = nullptr;
	currentElement = nullptr;
	lastElement = nullptr;
	currentIndex = 0;
	count = 0;
}

template<class T>
DLinkedList<T>::~DLinkedList()
{
	Empty();
}


template<class T>
int DLinkedList<T>::Count()
{
	return count;
}

template<class T>
int DLinkedList<T>::CurrentIndex()
{
	return currentIndex;
}


template<class T>
void DLinkedList<T>::SeekToIndex(unsigned int newIndex)
{
	if (newIndex >= count)
	{
		return;
	}
	if (currentIndex == newIndex)
	{
		return;
	}
	else
	{
		if (currentIndex > newIndex)
		{
			if (currentIndex - newIndex > newIndex)
			{
				currentElement = firstElement;
				currentIndex = 0;
				for (unsigned int i = 0; i < newIndex; i++)
				{
					StepForward();
				}
			}
			else
			{
				unsigned int steps = currentIndex - newIndex;
				for (unsigned int i = 0; i < steps; i++)
				{
					StepBackward();
				}
			}
		}
		else
		{
			if (newIndex - currentIndex > count - newIndex)
			{
				currentElement = lastElement;
				currentIndex = count - 1;
				for (unsigned int i = 0; i < count - 1 - newIndex; i++)
				{
					StepBackward();
				}
			}
			else
			{
				unsigned int steps = newIndex - currentIndex;
				for (unsigned int i = 0; i < steps; i++)
				{
					StepForward();
				}
			}
		}
	}
	if (currentIndex != newIndex)
	{
		// big trouble now...
		throw std::runtime_error("Current index does not match new index in DLinkedList.");
	}
}


template<class T>
bool DLinkedList<T>::StepForward()
{
	if (currentIndex == count - 1)
	{
		return false;
	}
	else
	{
		currentIndex++;
		currentElement = currentElement->nextElement;
	}
	return true;
}


template<class T>
bool DLinkedList<T>::StepBackward()
{
	if (currentIndex == 0)
	{
		return false;
	}
	else
	{
		currentIndex--;
		currentElement = currentElement->previousElement;
	}
	return true;
}


template<class T>
bool DLinkedList<T>::PushBefore(T data)
{
	if (count == 0)
	{
		return FirstPush(data);
	}
	else
	{
		if (CurrentIndex() == 0)
		{
			return PushFirst(data);
		}
		else
		{
			DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
			if (d != nullptr)
			{
				currentElement->previousElement->nextElement = d;
				d->previousElement = currentElement->previousElement;

				d->nextElement = currentElement;
				currentElement->previousElement = d;
				currentIndex++;
				count++;
				return true;
			}
			else return false;
		}


	}
}


template<class T>
bool DLinkedList<T>::PushAfter(T data)
{
	if (count == 0)
	{
		return FirstPush(data);
	}
	else
	{
		if (currentIndex == count - 1)
		{
			return PushLast(data);
		}
		else
		{
			DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
			if (d != nullptr)
			{
				currentElement->nextElement->previousElement = d;
				d->nextElement = currentElement->nextElement;

				d->previousElement = currentElement;
				currentElement->nextElement = d;

				count++;
				return true;
			}
			else return false;
		}
	}
}


template<class T>
bool DLinkedList<T>::PushFirst(T data)
{
	if (count == 0)
	{
		return FirstPush(data);
	}
	else
	{
		DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
		if (d != nullptr)
		{
			firstElement->previousElement = d;
			d->nextElement = firstElement;

			firstElement = d;
			count++;
			currentIndex++;
			return true;
		}
		else return false;
	}
}


template<class T>
bool DLinkedList<T>::PushLast(T data)
{
	if (count == 0)
	{
		return FirstPush(data);
	}
	else
	{
		DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
		if (d != nullptr)
		{
			lastElement->nextElement = d;
			d->previousElement = lastElement;
			lastElement = d;
			count++;
			return true;
		}
		else return false;
	}
}


template<class T>
void DLinkedList<T>::RemoveAt(int index)
{
	int revert = currentIndex;
	if (index < revert)
	{
		revert--;
	}
	SeekToIndex(index);
	if (index == 0) // first element
	{
		currentElement = currentElement->nextElement;
		delete (firstElement);
		firstElement = currentElement;
		currentElement->previousElement = nullptr;
	}
	else if (index == count - 1) // last element
	{
		currentElement = currentElement->previousElement;
		delete lastElement;
		lastElement = currentElement;
		currentElement->nextElement = nullptr;
		currentIndex--;
	}
	else // Any in between
	{
		currentElement = currentElement->previousElement;
		currentElement->nextElement = currentElement->nextElement->nextElement;
		delete (currentElement->nextElement->previousElement);
		currentElement->nextElement->previousElement = currentElement;
	}
	count--;
	SeekToIndex(revert);
}


template<class T>
void DLinkedList<T>::RemoveCurrent()
{
	if (count == 1)
	{
		delete(currentElement);
		firstElement = nullptr;
		lastElement = nullptr;
		currentElement = nullptr;
		currentIndex = 0;
		count = 0;
	}
	else if (currentIndex == 0)
	{
		currentElement = currentElement->nextElement;
		delete firstElement;
		firstElement = currentElement;
		currentElement->previousElement = nullptr;
		count--;
	}
	else if (currentIndex == count - 1)
	{
		currentElement = currentElement->previousElement;
		delete lastElement;
		lastElement = currentElement;
		currentElement->nextElement = nullptr;
		count--;
		currentIndex--;
	}
	else
	{
		DLinkedListNode<T>* tmp = currentElement;
		currentElement->previousElement->nextElement = currentElement->nextElement;
		currentElement->nextElement->previousElement = currentElement->previousElement;
		currentElement = currentElement->nextElement;
		delete tmp;
		count--;
	}
}

template<class T>
void DLinkedList<T>::Swap(int leftIndex, int rightIndex)
{
	int revert = currentIndex;
	SeekToIndex(leftIndex);
	T left = currentElement->data;
	SeekToIndex(rightIndex);
	T right = currentElement->data;
	currentElement->data = left;
	SeekToIndex(leftIndex);
	currentElement->data = right;
	SeekToIndex(revert);
}



template<class T>
void DLinkedList<T>::Empty(bool deleteItem)
{
	DLinkedListNode<T>* tmp;
	while (firstElement != nullptr)
	{
		tmp = firstElement->nextElement;
		if (deleteItem)
		{
			firstElement->Delete();
		}
		delete(firstElement);
		firstElement = tmp;
	}
	lastElement = nullptr;
	currentElement = nullptr;
	currentIndex = 0;
	count = 0;
}



template<class T>
bool DLinkedList<T>::FirstPush(T data)
{
	DLinkedListNode<T>* d = new DLinkedListNode<T>(data);
	if (d != nullptr)
	{
		firstElement = d;
		lastElement = d;
		currentElement = d;
		currentIndex = 0;
		count = 1;

		return true;
	}
	else return false;
}


#endif