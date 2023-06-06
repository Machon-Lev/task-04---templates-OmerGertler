#pragma once

#include <iostream>
#include <list>
#include <exception>

template<typename T>
class PriorityQueue {
   
public:
	
	void push(const T& t); 
	T poll();

private:

	std::list<T> myList;

	/// <summary>
	/// Struct for compare between two generic objects.
	/// </summary>
	struct MyComparator
	{
		/// <summary>
		/// Compare between two items and return true if the first is bigger.
		/// Assume the item-type has an implementation for ">" and "-" operators.
		/// </summary>
		/// <param name="lhs">First item</param>
		/// <param name="rhs">Second item</param>
		/// <returns>True if lhs is bigger than rhs, else return false.</returns>
		bool operator()(T lhs, T rhs) const
		{
			T delta = lhs - rhs;
			return delta > 0;
		};
	};
};


/// <summary>
/// Push a new item to the priority queue.
/// The priority is increasing order.
/// </summary>
/// <typeparam name="T">A generic type.</typeparam>
/// <param name="t">New item to insert to the pririty queue.</param>
template<typename T>
inline void PriorityQueue<T>::push(const T& t)
{
	MyComparator myComparator;
	typename std::list<T>::iterator it = myList.begin(); 
	while (it != myList.end() && myComparator(t, *it))
		++it;
	myList.insert(it, t);
}

/// <summary>
/// Poll the biggest item in the priority queue.
/// Throw an exception if the queue is empty.
/// </summary>
/// <typeparam name="T">A generic type.</typeparam>
/// <returns>Return the biggest ite in the queue.</returns>
template<typename T>
inline T PriorityQueue<T>::poll()
{
	if(myList.empty())
		throw std::runtime_error("Priority queue is empty");
	T tmp = myList.front();
	myList.pop_front();
	return tmp;
}


