/*
* ===============================================================================
* Tuxis Project
* Copyright (C) 2011-2012, Andrew Tulay
* ===============================================================================
* Input Module simple example
* ===============================================================================
*/

#include <windows.h>
#include <iostream>
#include "InputInclude/Input.h"
using namespace std;
using namespace Tuxis;

int main()
{
	Input mInput(0);

	cout 
		<< "Input Sample.\n"
		<< "1) Press space button and move mouse.\n"
		<< "2) Press Left Control key to change cursor position.\n"
		<< "3) Press Escape key to exit\n";


	while( !mInput.KeyDown(Key::ESCAPE) )
	{
		if(mInput.KeyHit(Key::SPACE))
			cout << "Space hit!" << endl;

		if(mInput.KeyUp(Key::SPACE))
			cout << "Space up!" << endl;

		if(mInput.KeyDown(Key::SPACE))
			if(mInput.MouseSpeedX() || mInput.MouseSpeedY()) 
				cout << "Mouse speed: ( " << mInput.MouseSpeedX() << " , " << mInput.MouseSpeedY()<< " )" << endl;

		if(mInput.KeyHit(Key::LCONTROL))
			mInput.SetMousePosition(0,0);

		Sleep(50);
		mInput.Update();
	}

	return 0;
}

