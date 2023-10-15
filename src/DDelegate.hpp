#ifndef DDELEGATE_H
#define DDELEGATE_H

#include "DDelegateAction.hpp"
#include "DLinkedList.hpp"

/// <summary>
/// Delegate event handler
/// </summary>
/// <typeparam name="Return">Type of the function (void, int, char...)</typeparam>
/// <typeparam name="...Params">Flexible number of function parameter types</typeparam>
template <class Return, class... Params>
class DDelegate
{
public:
	DDelegate();
	~DDelegate();

	// DDelegate<Return, Params...>(DDelegate<Return, Params...>& original); // TODO
	// DDelegate operator=(DDelegate<Return, Params...>& original); // TODO
	/// <summary>
	/// Fires all subscribed function. Does not handle the returned value, may cause memory leak. If that happens, use Fire() instead
	/// </summary>
	/// <param name="...p">Arguments for every function to use</param>
	void FireAllWithoutReturn(Params... p);

	/// <summary>
	/// Fires all functions with specified ID. Does not handle the returned value, may cause memory leak. If that happens, use Fire() instead
	/// </summary>
	/// <param name="...p">Arguments for every function to use</param>
	/// <param name="ID">ID filter</param>
	void FireAllWithoutReturn(Params... p, int ID);

	/// <summary>
	/// Fires all function and returns their values in an array
	/// </summary>
	/// <param name="...p">Parameters for every function to use</param>
	/// <returns>The reurned value of each function</returns>
	Return* FireAll(Params... p);

	/// <summary>
	/// Fires all function with specified ID and returns their values in an array
	/// </summary>
	/// <param name="...p">Parameters for every function to use</param>
	/// <param name="ID">ID filter</param>
	/// <returns>The reurned value of each function</returns>
	Return* FireAll(Params... p, int ID);

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(Return(*function)(Params...));

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <param name="id">ID of function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(Return(*function)(Params...), int id);

	/// <summary>
	/// Unsubrscribes all occurences of the specified function
	/// </summary>
	/// <param name="functionPointer">Function to remove from the delegate</param>
	void Unsubscribe(Return(*functionPointer)(Params...));

	/// <summary>
	/// Unsubscribes all functions with the specified ID
	/// </summary>
	/// <param name="ID">ID filter</param>
	void Unsubscribe(int ID);

	/// <summary>
	/// Unsibscribes every function
	/// </summary>
	void UnsubscribeAll();


	DLinkedList<DDelegateAction<Return, Params...>*>* actionList;
};

template <class ...Params>
class DDelegate<void, Params...>
{
public:
	DDelegate();
	~DDelegate();

	// DDelegate(DDelegate<void, Params...>& original); // TODO
	// DDelegate operator=(DDelegate<void, Params...>& original); // TODO

	/// <summary>
	/// Fires all subscribed function
	/// </summary>
	/// <param name="...p">Arguments for every function to use</param>
	void FireAllWithoutReturn(Params... p);

	/// <summary>
	/// Fires all functions with specified ID
	/// </summary>
	/// <param name="...p">Arguments for every function to use</param>
	/// <param name="ID">ID filter</param>
	void FireAllWithoutReturn(Params... p, int ID);

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(void(*function)(Params...));

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <param name="id">ID of function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(void(*function)(Params...), int id);

	/// <summary>
	/// Unsubrscribes all occurences of the specified function
	/// </summary>
	/// <param name="functionPointer">Function to remove from the delegate</param>
	void Unsubscribe(void(*functionPointer)(Params...));

	/// <summary>
	/// Unsubscribes all functions with the specified ID
	/// </summary>
	/// <param name="ID">ID filter</param>
	void Unsubscribe(int ID);

	/// <summary>
	/// Unsibscribes every function
	/// </summary>
	void UnsubscribeAll();


	DLinkedList<DDelegateAction<void, Params...>*>* actionList;
};

#endif