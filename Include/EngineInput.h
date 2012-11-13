/**
===============================================================================
Tuxis Project
Copyright (C) 2011-2012, Andrew Tulay
===============================================================================
EngineInput Module
Required: dinput.h , dinput8.lib, dxguid.lib
===============================================================================
*/

#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include "InputModule.h"

namespace Tuxis
{

	class DLL_EXPORT EngineInput
	{
	public:
		static EngineInput* GetInstance();

		EngineInput(HWND);
		~EngineInput();

		void UpdateAllStates();

		// Keyboard
		bool KeyDown( BYTE key );
		bool KeyHit( BYTE key );
		bool KeyUp( BYTE key );
		void UpdateKeyboardState();

		// Mouse
		bool MouseDown( BYTE mouse_key ); 
		bool MouseHit( BYTE mouse_key );	
		bool MouseUp( BYTE mouse_key );

		void SetMousePosition(int x, int y);
		void GetMousePosition(int& x, int& y);

		int MouseSpeedX();
		int MouseSpeedY();
		int MouseSpeedZ();

		void UpdateMouseState();

	private:

		// Keyboard
		LPDIRECTINPUTDEVICE8 KeyboardDevice;
		BYTE Buttons[256];
		bool KeyHits[256];
		bool KeyUps[256];

		// Mouse
		LPDIRECTINPUTDEVICE8 MouseDevice;
		DIMOUSESTATE2 MouseState;
		bool MouseHits[8];
		bool MouseUps[8];

		void Initialize(HWND theHWND);
		void Release();

		HWND hWindow;
		LPDIRECTINPUT8 lpDI;					

		static EngineInput* mInstance;
	};

}