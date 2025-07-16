#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	cout << "© 2021 Meiware.net" << endl << "simulates key press (no memory modification)" << endl << "hold mouse5 to autostrafe" << endl;

	bool runonce = true;
	RECT rect;
	POINT point;
	INPUT input;
	input.type = INPUT_KEYBOARD;

	while(true)
	{
		GetWindowRect(GetForegroundWindow(), &rect);

		if(GetAsyncKeyState(VK_XBUTTON2))
		{
			GetCursorPos(&point);

			if(point.x < (rect.right / 2))
			{
				input.ki.dwFlags = KEYEVENTF_KEYUP;
				input.ki.wVk = 'D';
				SendInput(1, &input, sizeof(INPUT));

				input.ki.dwFlags = 0;
				input.ki.wVk = 'A';
				SendInput(1, &input, sizeof(INPUT));
			}
			else if(point.x > (rect.right / 2))
			{
				input.ki.dwFlags = KEYEVENTF_KEYUP;
				input.ki.wVk = 'A';
				SendInput(1, &input, sizeof(INPUT));

				input.ki.dwFlags = 0;
				input.ki.wVk = 'D';
				SendInput(1, &input, sizeof(INPUT));
			}

			runonce = true;
		}
		else
			if(runonce)
			{
				input.ki.dwFlags = KEYEVENTF_KEYUP;

				input.ki.wVk = 'A';
				SendInput(1, &input, sizeof(INPUT));

				input.ki.wVk = 'D';
				SendInput(1, &input, sizeof(INPUT));

				runonce = false;
			}

		Sleep(5);
	}

	return 0;
}
