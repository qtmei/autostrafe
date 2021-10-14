#include <Windows.h>
#include <iostream>
#include <thread>

using namespace std;

bool toggle = false;

void Autostrafe()
{
	bool runonce = true;

	RECT rect;
	POINT point;
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;

	while(true)
	{
		if(toggle && GetAsyncKeyState(VK_XBUTTON2))
		{
			runonce = true;

			GetWindowRect(GetDesktopWindow(), &rect);
			GetCursorPos(&point);

			if(point.x < (rect.right / 2))
			{
				input.ki.wScan = MapVirtualKey((WORD)0x44, MAPVK_VK_TO_VSC);
				input.ki.wVk = (WORD)0x44;
				input.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &input, sizeof(INPUT));

				input.ki.wScan = MapVirtualKey((WORD)0x41, MAPVK_VK_TO_VSC);
				input.ki.wVk = (WORD)0x41;
				input.ki.dwFlags = 0;
				SendInput(1, &input, sizeof(INPUT));
			}
			else if(point.x > (rect.right / 2))
			{
				input.ki.wScan = MapVirtualKey((WORD)0x41, MAPVK_VK_TO_VSC);
				input.ki.wVk = (WORD)0x41;
				input.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &input, sizeof(INPUT));

				input.ki.wScan = MapVirtualKey((WORD)0x44, MAPVK_VK_TO_VSC);
				input.ki.wVk = (WORD)0x44;
				input.ki.dwFlags = 0;
				SendInput(1, &input, sizeof(INPUT));
			}
		}
		else
		{
			if(runonce)
			{
				input.ki.dwFlags = KEYEVENTF_KEYUP;

				input.ki.wScan = MapVirtualKey((WORD)0x41, MAPVK_VK_TO_VSC);
				input.ki.wVk = (WORD)0x41;
				SendInput(1, &input, sizeof(INPUT));

				input.ki.wScan = MapVirtualKey((WORD)0x44, MAPVK_VK_TO_VSC);
				input.ki.wVk = (WORD)0x44;
				SendInput(1, &input, sizeof(INPUT));

				runonce = false;
			}
		}

		Sleep(5);
	}
}

int main()
{
	thread autostrafe(Autostrafe);

	cout << "F1 to enable/disable" << endl;
	cout << "hold mouse5 to autostrafe" << endl;

	while(true)
	{
		if(GetAsyncKeyState(VK_F1) & 1)
		{
			toggle = !toggle;

			if(toggle)
			{
				cout << "enabled" << endl;
			}
			else
			{
				cout << "disabled" << endl;
			}
		}

		Sleep(5);
	}
}
