#ifndef KEYREADER
#define KEYREADER

#include "KeyInput.hpp"


KeyInput::KeyName* KeyInput::GetActiveKeys()
{
	return activeKeys;
}


int KeyInput::Update()
{
	for (int i = KeyName::LeftArrow; i <= KeyName::DownArrow; ++i)
	{
		if (GetAsyncKeyState(i) < 0)
		{
			activeKeys[0] = (KeyName)i;
			break;
		}
		else
		{
			activeKeys[0] = Undef;
		}
	}
	for (int i = KeyName::Number0; i <= KeyName::Number9; ++i)
	{
		if (GetAsyncKeyState(i) < 0)
		{
			activeKeys[1] = (KeyName)i;
			break;
		}
		else
		{
			activeKeys[1] = Undef;
		}
	}
	for (int i = KeyName::LetterA; i <= KeyName::LetterZ; ++i)
	{
		if (GetAsyncKeyState(i) < 0)
		{
			activeKeys[2] = (KeyName)i;
			break;
		}
		else
		{
			activeKeys[2] = Undef;
		}
	}
	for (int i = KeyName::NumpadNumber0; i <= KeyName::NumpadNumber9; ++i)
	{
		if (GetAsyncKeyState(i) < 0)
		{
			activeKeys[3] = (KeyName)i;
			break;
		}
		else
		{
			activeKeys[3] = Undef;
		}
	}
	for (int i = KeyName::F1; i <= KeyName::F12; ++i)
	{
		if (GetAsyncKeyState(i) < 0)
		{
			activeKeys[4] = (KeyName)i;
			break;
		}
		else
		{
			activeKeys[4] = Undef;
		}
	}
	for (int i = KeyName::Backspace; i <= KeyName::Spacebar; ++i)
	{
		if (GetAsyncKeyState(i) < 0)
		{
			activeKeys[5] = (KeyName)i;
			break;
		}
		else
		{
			activeKeys[5] = Undef;
		}
	}
	return 0;
}

KeyInput* KeyInput::GetInstance()
{
	if (keyreaderPtr == nullptr)
	{
		keyreaderPtr = new KeyInput();
	}
	return keyreaderPtr;
}

KeyInput::~KeyInput()
{
	delete[] activeKeys;
}

KeyInput::KeyInput()
{
	activeKeys = new KeyName[KEY_COUNT];
}

//void KeyInput::Delete()
//{
//	delete[] activeKeys;
//}
// wat

#endif