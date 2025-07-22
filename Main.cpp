#include <Windows.h>
#include <iostream>

using namespace std;

void SimulateKey(INPUT &input, WORD VK_KEY, bool pressed)
{
	input.ki.dwFlags = pressed ? 0 : KEYEVENTF_KEYUP;
	input.ki.wScan = VK_KEY;
	SendInput(1, &input, sizeof(INPUT));
}

int main()
{
	const WORD VK_A = MapVirtualKey((WORD)'A', MAPVK_VK_TO_VSC); //maps hardware key to virtual key so we emulate low level and are multi-device compatible
	const WORD VK_D = MapVirtualKey((WORD)'D', MAPVK_VK_TO_VSC); //using a constant variable because devices aren't changed frequently and won't happen during runtime
	bool runonce = true;
	RECT screen;
	POINT cursor;
	INPUT input;
	input.type = INPUT_KEYBOARD;

	cout << "© 2021 Meiware.net\nsimulates key press (no memory modification)\nhold mouse5 to autostrafe" << endl;

	while(true)
	{
		GetWindowRect(GetForegroundWindow(), &screen);
		GetCursorPos(&cursor);

		if(GetAsyncKeyState(VK_XBUTTON2)) //XBUTTON2 is the virtual key code for mouse5
		{
			if(cursor.x < (screen.right / 2))
			{
				SimulateKey(input, VK_D, false);
				SimulateKey(input, VK_A, true);
			}
			else if(cursor.x > (screen.right / 2))
			{
				SimulateKey(input, VK_A, false);
				SimulateKey(input, VK_D, true);
			}

			runonce = true;
		}
		else
			if(runonce) //we release the keys when mouse5 is not held, but only once
			{
				SimulateKey(input, VK_A, false);
				SimulateKey(input, VK_D, false);

				runonce = false;
			}

		Sleep(1);
	}

	return 0;
}
