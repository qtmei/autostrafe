#include <Windows.h>
#include <iostream>

using namespace std;

void SimulateKey(INPUT &input, WORD key, WORD vKey, bool pressed)
{
	input.ki.dwFlags = pressed ? 0 : KEYEVENTF_KEYUP;
	input.ki.wScan = vKey; //low level key simulation
	input.ki.wVk = key; //high level key simulation, for some programs this is necessary
	SendInput(1, &input, sizeof(INPUT));
}

int main()
{
	const WORD K_A = (WORD)'A', K_D = (WORD)'D';
	const WORD VK_A = MapVirtualKey(K_A, MAPVK_VK_TO_VSC), VK_D = MapVirtualKey(K_D, MAPVK_VK_TO_VSC); //maps hardware key to virtual key so we emulate low level and are multi-device compatible

	RECT screen;
	POINT cursor;
	INPUT input;
	input.type = INPUT_KEYBOARD;
	bool runonce = true;

	cout << "© 2021 Meiware.net\nsimulates key press (no memory modification)\nhold mouse5 to autostrafe" << endl;

	while(true)
	{
		GetWindowRect(GetForegroundWindow(), &screen);
		GetCursorPos(&cursor);

		if(GetAsyncKeyState(VK_XBUTTON2)) //XBUTTON2 is the virtual key code for mouse5
		{
			if(cursor.x < screen.right / 2)
			{
				SimulateKey(input, K_D, VK_D, false);
				SimulateKey(input, K_A, VK_A, true);
			}
			else if(cursor.x > screen.right / 2)
			{
				SimulateKey(input, K_A, VK_A, false);
				SimulateKey(input, K_D, VK_D, true);
			}

			runonce = true;
		}
		else
			if(runonce) //we release the keys when mouse5 is not held, but only once
			{
				SimulateKey(input, K_A, VK_A, false);
				SimulateKey(input, K_D, VK_D, false);

				runonce = false;
			}

		Sleep(1000 / 128); //128 updates/second
	}

	return 0;
}
