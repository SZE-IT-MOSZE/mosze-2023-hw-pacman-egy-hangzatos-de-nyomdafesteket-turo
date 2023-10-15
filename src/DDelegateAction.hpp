#ifndef DDELEGATE_ACTION_H
#define DDELEGATE_ACTION_H

/// <summary>
/// Delegate action, containing the pointer to a function and other information
/// </summary>
/// <typeparam name="Return">Type of the function (void, int, char...)</typeparam>
/// <typeparam name="...Params">Flexible number of function parameter types</typeparam>
template<class Return, class... Params>
class DDelegateAction
{
public:
	DDelegateAction();
	DDelegateAction(int ID);
	DDelegateAction(Return(*function)(Params...), int ID);
	DDelegateAction(Return(*function)(Params...));
	~DDelegateAction();

	/// <summary>
	/// Calls the function
	/// </summary>
	/// <param name="...p">Parameters for the functions to use</param>
	/// <returns>The returned value of the function</returns>
	Return Fire(Params... p);

	Return (*functionPointer)(Params...);
	int ID;
	int timesCalled;

private:
};


/// <summary>
/// Delegate action, containing the pointer to a function and other information
/// </summary>
/// <typeparam name="...Params"></typeparam>
template<class... Params>
class DDelegateAction<void, Params...>
{
public:
	DDelegateAction();
	DDelegateAction(int ID);
	DDelegateAction(void(*function)(Params...), int ID);
	DDelegateAction(void(*function)(Params...));
	~DDelegateAction();

	/// <summary>
	/// Calls the function
	/// </summary>
	/// <param name="...p">Parameters for the functions to use</param>
	void Fire(Params... p);

	void (*functionPointer)(Params...);
	int ID;
	int timesCalled;

private:
};


#endif