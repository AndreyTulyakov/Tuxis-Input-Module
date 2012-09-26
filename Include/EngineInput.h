/*
* ===============================================================================
* Tuxis Project
* Copyright (C) 2011-2012, Andrew Tulay
* ===============================================================================
* EngineInput Module
* Required: dinput.h , dinput8.lib, dxguid.lib
* ===============================================================================
*/

#pragma once
#include "_DllExport.h"

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

namespace Tuxis
{

	class DLL_EXPORT EngineInput
	{
	public:
		static EngineInput* GetInstance();

		EngineInput(HWND);
		~EngineInput();

		void Update();

		bool KeyDown( BYTE in_kb );		
		bool KeyHit( BYTE in_kb );	
		bool KeyUp( BYTE in_kb );	

		bool MouseDown( BYTE in_mb ); 
		bool MouseHit( BYTE in_mb );	
		bool MouseUp( BYTE in_mb );

		void	SetMousePosition(int x, int y);
		void	GetMousePosition(int& x, int& y);

		int MouseSpeedX();
		int MouseSpeedY();
		int MouseSpeedZ();

	private:

		void Initialize(HWND theHWND);
		void Release();

		HWND hWindow;
		LPDIRECTINPUT8 lpDI;					
		LPDIRECTINPUTDEVICE8 KeyboardDevice,MouseDevice;		
		DIMOUSESTATE2 MouseState;

		BYTE Buttons[256];

		bool KeyHits[256];
		bool KeyUps[256];

		bool MouseHits[8];
		bool MouseUps[8];



		static EngineInput* mInstance;
	};

}