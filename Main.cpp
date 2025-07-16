#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	cout << "© 2021 Meiware.net" << endl << "simulates key press (no memory modification)" << endl << "hold mouse5 to autostrafe" << endl;

	const WORD VK_A = MapVirtualKey((WORD)'A', MAPVK_VK_TO_VSC); //maps hardware key to virtual key so we emulate low level and are multi-device compatible
	const WORD VK_D = MapVirtualKey((WORD)'D', MAPVK_VK_TO_VSC); //using a constant variable because devices aren't changed frequently and won't happen during runtime

	bool runonce = true;
	RECT rect;
	POINT point;
	INPUT input;
	input.type = INPUT_KEYBOARD;

	while(true)
	{
		GetWindowRect(GetForegroundWindow(), &rect);
		GetCursorPos(&point);

		if(GetAsyncKeyState(VK_XBUTTON2)) //XBUTTON2 is the virtual key code for mouse5
		{
			if(point.x < (rect.right / 2))
			{
				input.ki.dwFlags = KEYEVENTF_KEYUP;
				input.ki.wScan = VK_D;
				SendInput(1, &input, sizeof(INPUT));

				input.ki.dwFlags = 0; //0 defines a keydown event
				input.ki.wScan = VK_A;
				SendInput(1, &input, sizeof(INPUT));
			}
			else if(point.x > (rect.right / 2))
			{
				input.ki.dwFlags = KEYEVENTF_KEYUP;
				input.ki.wScan = VK_A;
				SendInput(1, &input, sizeof(INPUT));

				input.ki.dwFlags = 0;
				input.ki.wScan = VK_D;
				SendInput(1, &input, sizeof(INPUT));
			}

			runonce = true;
		}
		else
			if(runonce) //we release the keys when mouse5 is not held, but only once
			{
				input.ki.dwFlags = KEYEVENTF_KEYUP;

				input.ki.wScan = VK_A;
				SendInput(1, &input, sizeof(INPUT));

				input.ki.wScan = VK_D;
				SendInput(1, &input, sizeof(INPUT));

				runonce = false;
			}

		Sleep(1);
	}

	return 0;
}
