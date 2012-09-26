// InputSample.cpp: определяет точку входа для консольного приложения.
//
#include <windows.h>
#include <iostream>
#include "InputInclude/Input.h"
using namespace std;
using namespace Tuxis;

// Find Console HWND
BOOL CALLBACK EnumWndProc(HWND hwnd, LPARAM lParam)
{
   if(GetWindowThreadProcessId(hwnd, NULL) == GetCurrentThreadId())
   {
      *(HWND*)lParam = hwnd;
      return FALSE;
   }

   return TRUE;
}

int main(int argc, wchar_t* argv[])
{
	HWND hWnd;
	EnumWindows(EnumWndProc, (LPARAM)&hWnd);

	Input *mInput = new Input(hWnd);

	

	cout 
		<< "Input Sample.\n"
		<< "1) Press space button and move mouse.\n"
		<< "2) Press Left Control key to change cursor position.\n"
		<< "3) Press Escape key to exit\n";

	while( !mInput->KeyDown(Key::ESCAPE) )
	{
		if(mInput->KeyHit(Key::SPACE))
			cout << "Space hit!" << endl;

		if(mInput->KeyUp(Key::SPACE))
			cout << "Space up!" << endl;

		if(mInput->KeyDown(Key::SPACE))
			if(mInput->MouseSpeedX() || mInput->MouseSpeedY()) 
				cout << "Mouse speed: ( " << mInput->MouseSpeedX() << " , " << mInput->MouseSpeedY()<< " )" << endl;

		if(mInput->KeyHit(Key::LCONTROL))
			mInput->SetMousePosition(0,0);

		Sleep(50);
		mInput->Update();
	}

	delete mInput;

	return 0;
}

