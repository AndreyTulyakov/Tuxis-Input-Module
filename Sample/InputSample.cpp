/*
* ===============================================================================
* Tuxis Project
* Copyright (C) 2011-2012, Andrew Tulay
* ===============================================================================
* Input Module simple example
* ===============================================================================
*/

#include <iostream>
using namespace std;

#include "InputModule.h"
using namespace Tuxis;

int main()
{
	// Initialize input manager by window handler (or null)
	InputManager mInput(0);

	// Get keyboard interface from manager;
	IKeyboard keyboard = mInput.GetKeyboard();

	// Get mouse interface from manager;
	IMouse mouse= mInput.GetMouse();

	cout 
		<< "Input Sample.\n"
		<< "1) Press space button and move mouse.\n"
		<< "2) Press Left Control key to change cursor position.\n"
		<< "3) Press Escape key to exit\n";

	// while ESCAPE key on keyboard was not pushed, do this...
	while( !keyboard.ButtonDown(Key::ESCAPE) )
	{
		if(keyboard.ButtonHit(Key::SPACE))
			cout << "Space hit!" << endl;

		if(keyboard.ButtonUp(Key::SPACE))
			cout << "Space up!" << endl;

		if(keyboard.ButtonDown(Key::SPACE))
			if(mouse.SpeedX() || mouse.SpeedY()) 
				cout << "Mouse speed: ( " << mouse.SpeedX() << " , " << mouse.SpeedY()<< " )" << endl;

		if(keyboard.ButtonHit(Key::LCONTROL))
			mouse.SetCursorPosition(0,0);

		Sleep(50);

		// Update keyboard and mouse states
		keyboard.Update();
		mouse.Update();
	}

	return 0;
}

