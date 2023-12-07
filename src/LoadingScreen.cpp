#ifndef LOADING_SCREEN
#define LOADING_SCREEN

#define SLEEPLENGTH 80
#define LINE_SLEEPLENGTH 250
#define SAY std::cout <<
#define ENDL std::endl

void StartLoadingScreen(int seed);
void Spinner(int rotCount);

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <chrono>
#include <ctime>


static COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &csbi))
	{
		return csbi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

static void StartLoadingScreen(int robotCount = 0)
{
	system("cls");
	SAY "ROS 3.14.7533" << ENDL;
	SAY "Interface ID: 301748656" << ENDL;
	Sleep(LINE_SLEEPLENGTH * 3);
	SAY "Welcome Operator. Today's task is:" << ENDL;
	Spinner(20);
	Sleep(LINE_SLEEPLENGTH * 3);
	SAY "An earthquake shook the mine at site: ID" << rand() << ". Management needs you to investigate and recover the robots." << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "Starting systems";
	for (int j = 0; j < 3; j++)
	{
		Spinner(5);
		SAY '.';
	}
	SAY ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "NO. of robots: " << robotCount << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "Connecting to main communications cluster. Pinging";
	Sleep(LINE_SLEEPLENGTH);
	for (int j = 0; j < 5; j++)
	{
		Spinner(10);
		SAY '.';
	}
	SAY ENDL;
	SAY "\tConnection failed. Status: UNREACHABLE" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "Connecting to individual robots" << ENDL;
	for (int i = 0; i < 2; i++)
	{
		SAY "Connecting to Robot NO. " << i + 1 << ENDL;
		Sleep(LINE_SLEEPLENGTH / 2);
		SAY "Establishing connection. Pinging";
		Sleep(LINE_SLEEPLENGTH * 2);
		for (int j = 0; j < 3; j++)
		{
			Spinner(5);
			SAY '.';
		}
		SAY ENDL;
		Sleep(LINE_SLEEPLENGTH);
		SAY "\tConnection failed. Status: UNREACHABLE" << ENDL;
		Sleep(LINE_SLEEPLENGTH * 2);

	}
	SAY "Connecting to Robot NO. 3" << ENDL;
	Sleep(LINE_SLEEPLENGTH / 2);
	SAY "Establishing connection. Pinging";
	Sleep(LINE_SLEEPLENGTH * 2);
	for (int j = 0; j < 2; j++)
	{
		Spinner(5);
		SAY '.';
	}
	SAY ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "\tConnection sucessful. Status: OK" << ENDL;
	Sleep(LINE_SLEEPLENGTH * 4);
	SAY "Requesting status of robot";
	for (int i = 0; i < 3; i++)
	{
		Spinner(rand() % 15);
		SAY '.';
	}
	for (int i = 0; i < 5; i++)
	{
		Spinner(rand() % 5);
		SAY '.';
	}
	SAY ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "Robot status:" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "Camera: ERROR" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "EMF detector: OK" << ENDL;
	Sleep(LINE_SLEEPLENGTH * 2);
	SAY "LIDAR: OK" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "Mobility: OK" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "Power supply: 0.77" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "Cooling system: ERROR" << ENDL;
	Sleep(LINE_SLEEPLENGTH / 3);
	SAY "Cooling at fault, systems are operating at a reduced rate" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "Near Field Communication: OK" << ENDL;
	Sleep(LINE_SLEEPLENGTH * 2);
	SAY "\tNear Field Communication reports several nearby robots" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "Tool 1: MISSING" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "Tool 2: OK" << ENDL;
	Sleep(LINE_SLEEPLENGTH / 2);
	SAY "\tTool 2: Extendable gripper arm" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "System check:" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "\tLocation chart: ERROR" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "\tCPU: OVERHEAT" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "\tMEM: 278 455 bytes remaining" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "\tAutomation: NOT POSSIBLE" << ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "Systems operational. Communication stable. Ping average: 120 ms. Jitter MAX: 30 ms.";
	SAY ENDL;
	Sleep(LINE_SLEEPLENGTH);
	SAY "Reports claim there are openings to the surface. Objective: use the arrow keys to find an exit! Operation begins shortly; Switching to manual drive";
	Sleep(LINE_SLEEPLENGTH);
	for (int j = 0; j < 7; j++)
	{
		Spinner(12);
		SAY '.';
	}
}

static void Spinner(int rotCount)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = GetConsoleCursorPosition(output);
	std::cout.flush();
	for (int i = 0; i < rotCount; i++)
	{
		SAY '|';
		SetConsoleCursorPosition(output, pos);
		Sleep(SLEEPLENGTH);
		SAY '/';
		SetConsoleCursorPosition(output, pos);
		Sleep(SLEEPLENGTH);
		SAY '-';
		SetConsoleCursorPosition(output, pos);
		Sleep(SLEEPLENGTH);
		SAY '\\';
		SetConsoleCursorPosition(output, pos);
		Sleep(SLEEPLENGTH);
	}
	SetConsoleCursorPosition(output, pos);
}

#endif