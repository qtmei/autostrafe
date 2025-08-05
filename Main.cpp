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
	bool lastDir = false, runonce = true; //lastDir false=left, true=right

	cout << "© 2021 Meiware.net\nsimulates key press (no memory modification)\nhold mouse5 to autostrafe" << endl;

	while(true)
	{
		GetWindowRect(GetForegroundWindow(), &screen);
		GetCursorPos(&cursor);

		if(GetAsyncKeyState(VK_XBUTTON2)) //XBUTTON2 is the virtual key code for mouse5
		{
			if(cursor.x < screen.right / 2 || cursor.x <= screen.right / 2 && !lastDir) //we want to ensure A or D is still being pressed when the mouse is not being moved
			{
				SimulateKey(input, K_D, VK_D, false);
				SimulateKey(input, K_A, VK_A, true);

				lastDir = false;
			}
			else if(cursor.x > screen.right / 2 || cursor.x >= screen.right / 2 && lastDir)
			{
				SimulateKey(input, K_A, VK_A, false);
				SimulateKey(input, K_D, VK_D, true);

				lastDir = true;
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

		Sleep(2); //1000ms / 500 updates/s = 2ms
	}

	return 0;
}

