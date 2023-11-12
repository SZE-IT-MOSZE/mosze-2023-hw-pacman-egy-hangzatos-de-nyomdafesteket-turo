#ifndef KEYREADER_H
#define KEYREADER_H

#include <Windows.h>
#include <winuser.h>

#define KEY_NUMBER 6

#define VK_LEFT 0x25
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28

#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

#define VK_NUMPAD0 0x60
#define VK_NUMPAD1 0x61
#define VK_NUMPAD2 0x62
#define VK_NUMPAD3 0x63
#define VK_NUMPAD4 0x64
#define VK_NUMPAD5 0x65
#define VK_NUMPAD6 0x66
#define VK_NUMPAD7 0x67
#define VK_NUMPAD8 0x68
#define VK_NUMPAD9 0x69

#define VK_F1 0x70
#define VK_F2 0x71
#define VK_F3 0x72
#define VK_F4 0x73
#define VK_F5 0x74
#define VK_F6 0x75
#define VK_F7 0x76
#define VK_F8 0x77
#define VK_F9 0x78
#define VK_F10 0x79
#define VK_F11 0x7A
#define VK_F12 0x7B

#define VK_BACKSPACE 0x08
#define VK_ENTER 0x0D
#define VK_ESCAPE 0x1B
#define VK_SPACEBAR 0x20



class KeyInput
{
public:
	static enum KeyName {
		Undef = 0,
		Backspace = VK_BACKSPACE,
		Enter = VK_ENTER,
		Esc = VK_ESCAPE,
		Spacebar = VK_SPACEBAR,
		LeftArrow = VK_LEFT,
		UpArrow = VK_UP,
		RightArrow = VK_RIGHT,
		DownArrow = VK_DOWN,
		Number0 = VK_0,
		Number1 = VK_1,
		Number2 = VK_2,
		Number3 = VK_3,
		Number4 = VK_4,
		Number5 = VK_5,
		Number6 = VK_6,
		Number7 = VK_7,
		Number8 = VK_8,
		Number9 = VK_9,
		LetterA = VK_A,
		LetterB = VK_B,
		LetterC = VK_C,
		LetterD = VK_D,
		LetterE = VK_E,
		LetterF = VK_F,
		LetterG = VK_G,
		LetterH = VK_H,
		LetterI = VK_I,
		LetterJ = VK_J,
		LetterK = VK_K,
		LetterL = VK_L,
		LetterM = VK_M,
		LetterN = VK_N,
		LetterO = VK_O,
		LetterP = VK_P,
		LetterQ = VK_Q,
		LetterR = VK_R,
		LetterS = VK_S,
		LetterT = VK_T,
		LetterU = VK_U,
		LetterV = VK_V,
		LetterW = VK_W,
		LetterX = VK_X,
		LetterY = VK_Y,
		LetterZ = VK_Z,
		NumpadNumber0 = VK_NUMPAD0,
		NumpadNumber1 = VK_NUMPAD1,
		NumpadNumber2 = VK_NUMPAD2,
		NumpadNumber3 = VK_NUMPAD3,
		NumpadNumber4 = VK_NUMPAD4,
		NumpadNumber5 = VK_NUMPAD5,
		NumpadNumber6 = VK_NUMPAD6,
		NumpadNumber7 = VK_NUMPAD7,
		NumpadNumber8 = VK_NUMPAD8,
		NumpadNumber9 = VK_NUMPAD9,
		F1 = VK_F1,
		F2 = VK_F2,
		F3 = VK_F3,
		F4 = VK_F4,
		F5 = VK_F5,
		F6 = VK_F6,
		F7 = VK_F7,
		F8 = VK_F8,
		F9 = VK_F9,
		F10 = VK_F10,
		F11 = VK_F11,
		F12 = VK_F12

	};
	void operator=(const KeyInput& other) = delete;
	KeyInput(const KeyInput& other) = delete;

	// static void Delete(); // wat

	/// <summary>
	/// Get the active keys in the frame. 0: Arrows. 1: Numbers. 2: Letters. 3: NumpadNumbers. 4: Function buttons. 5: Utilities
	/// </summary>
	/// <returns>The pointer to the active keys</returns>
	static KeyName* GetActiveKeys();

	/// <summary>
	/// Reads the keys that are currently held down
	/// </summary>
	/// <returns></returns>
	static int Update();


	/// <summary>
	/// Access the pointer to this singleton object
	/// </summary>
	/// <returns>The pointer to this</returns>
	static KeyInput* GetInstance();

	~KeyInput();
private:
	static KeyName* activeKeys; // activeKeys[] won't work, can't make constexpr for class member array
	static KeyInput* keyreaderPtr;
	KeyInput();

};

KeyInput* KeyInput::keyreaderPtr = nullptr;
KeyInput::KeyName* KeyInput::activeKeys = nullptr;

#endif