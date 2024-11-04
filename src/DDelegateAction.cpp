#ifndef DDELEGATE_ACTION
#define DDELEGATE_ACTION

#include "DDelegateAction.hpp"

template<class Return, class... Params>
DDelegateAction<Return, Params...>::DDelegateAction()
{
	this->functionPointer = nullptr;
	ID = 0;
	timesCalled = 0;
}

template<class Return, class... Params>
DDelegateAction<Return, Params...>::DDelegateAction(int ID)
{
	this->functionPointer = nullptr;
	this->ID = ID;
	timesCalled = 0;
}

template<class Return, class... Params>
DDelegateAction<Return, Params...>::DDelegateAction(Return(*function)(Params...), int ID)
{
	this->functionPointer = function;
	this->ID = ID;
	timesCalled = 0;
}

template<class Return, class... Params>
DDelegateAction<Return, Params...>::DDelegateAction(Return(*function)(Params...))
{
	this->functionPointer = function;
	this->ID = 0;
	timesCalled = 0;
}

template<class Return, class... Params>
DDelegateAction<Return, Params...>::~DDelegateAction()
{

}

template<class Return, class... Params>
Return DDelegateAction<Return, Params...>::Fire(Params... p)
{
	timesCalled++;
	return functionPointer(p...);
}


// #####################################################


template<class... Params>
DDelegateAction<void, Params...>::DDelegateAction()
{
	this->functionPointer = nullptr;
	ID = 0;
	timesCalled = 0;
}

template<class... Params>
DDelegateAction<void, Params...>::DDelegateAction(int ID)
{
	this->functionPointer = nullptr;
	this->ID = ID;
	timesCalled = 0;
}

template<class... Params>
DDelegateAction<void, Params...>::DDelegateAction(void(*function)(Params...), int ID)
{
	this->functionPointer = function;
	this->ID = ID;
	timesCalled = 0;
}

template<class... Params>
DDelegateAction<void, Params...>::DDelegateAction(void(*function)(Params...))
{
	this->functionPointer = function;
	this->ID = 0;
	timesCalled = 0;
}

template<class... Params>
DDelegateAction<void, Params...>::~DDelegateAction()
{

}


template<class... Params>
void DDelegateAction<void, Params...>::Fire(Params... p)
{
	timesCalled++;
	functionPointer(p...);
}

#endif