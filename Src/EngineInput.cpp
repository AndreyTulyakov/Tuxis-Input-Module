
#include "EngineInput.h"

namespace Tuxis
{
	void Error(const char* msg) { MessageBoxA(0,msg,"Error",0); }

	EngineInput* EngineInput::mInstance = nullptr;

	EngineInput::EngineInput(HWND pHWND)
	{
		mInstance=this;
		Initialize(pHWND);
	}

	EngineInput::~EngineInput()
	{
		Release();
		mInstance = nullptr;
	}

	void EngineInput::Initialize(HWND theHWND)
	{
		hWindow=theHWND;

		MSG msg = {0};

		if( FAILED( DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION, IID_IDirectInput8, ( void ** )&lpDI, NULL ) ) )
			Error("Input: DirectInput8Create");

		// Keyboard
		ZeroMemory( &Buttons, sizeof( BYTE ) * 256 );
		for( unsigned short i = 0; i < 256; i++ )
		{
			KeyHits[i] = true;
			KeyUps[i] = false;
		}

		if( FAILED( lpDI->CreateDevice( GUID_SysKeyboard, &KeyboardDevice, NULL ) ) )
			Error("Input: Can't create Keyboard device");

		if( FAILED( KeyboardDevice->SetDataFormat( &c_dfDIKeyboard ) ) )
			Error("Input: Can't Set Data Format for Keyboard device");

		//if( FAILED( KeyboardDevice->SetCooperativeLevel( hWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
		//Error("Input: Can't Set Cooperative Level for Keyboard");


		// Mouse

		ZeroMemory( &MouseState, sizeof( DIMOUSESTATE2 ) );
		for( int i = 0; i < 8; i++ )
		{
			MouseHits[i] = true;
			MouseUps[i] = false;
		}

		if( FAILED(lpDI->CreateDevice(GUID_SysMouse, &MouseDevice, NULL)) )
			Error("Input: Can't create Mouse device");

		if( FAILED( MouseDevice->SetDataFormat( &c_dfDIMouse2 ) ) )
			Error("Input: Can't Set Data Format for Mouse device");

		if( FAILED( MouseDevice->SetCooperativeLevel( hWindow, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND ) ) )
			Error("Input: Can't Set Cooperative Level for mouse");
	}
	


	EngineInput* EngineInput::GetInstance()
	{
		return mInstance;
	}


	void EngineInput::UpdateAllStates()
	{
		MSG msg;
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		UpdateKeyboardState();
		UpdateMouseState();
	}


	// MOUSE BLOCK

	void EngineInput::SetMousePosition( int X, int Y)
	{
		POINT CurPos;
		CurPos.x = X;
		CurPos.y = Y;
		ClientToScreen( hWindow, &CurPos );
		SetCursorPos( CurPos.x, CurPos.y );
	}

	void EngineInput::GetMousePosition(int& x, int& y)
	{
		POINT CurPos;
		GetCursorPos( &CurPos );
		ScreenToClient( hWindow, &CurPos );
		x=CurPos.x;
		y=CurPos.y;
	}

	int EngineInput::MouseSpeedX()
	{
		return MouseState.lX;
	}

	int EngineInput::MouseSpeedY()
	{
		return MouseState.lY;
	}

	int EngineInput::MouseSpeedZ()
	{
		return MouseState.lZ;
	}

	bool EngineInput::MouseDown( BYTE in_mb )
	{
		if(int(in_mb)>7 && int(in_mb)<0) return false;

		if( MouseState.rgbButtons[in_mb])
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	bool EngineInput::MouseHit( BYTE in_mb )
	{
		if(int(in_mb)>7 && int(in_mb)<0) return false;

		if( MouseState.rgbButtons[in_mb] & 0x80 )
		{
			if( MouseHits[in_mb] )
			{
				MouseHits[in_mb] = false;
				return true;
			}
		}
		else
		{
			MouseHits[in_mb] = true;
		}

		return false;
	}


	bool EngineInput::MouseUp( BYTE in_mb )
	{
		if(int(in_mb)>7 && int(in_mb)<0) return false;

		if( MouseState.rgbButtons[in_mb] & 0x80 )
		{
			MouseUps[in_mb] = true;
		}
		else
		{
			if( MouseUps[in_mb] )
			{
				MouseUps[in_mb] = false;
				return true;
			}
		}

		return false;
	}




	// KEYBOARD BLOCK

	bool EngineInput::KeyDown( BYTE in_kb )
	{
		if(int(in_kb)>255 && int(in_kb)<0) return false;

		if( Buttons[in_kb] & 0x80 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	bool EngineInput::KeyHit( BYTE in_kb )
	{
		if(int(in_kb)>255 && int(in_kb)<0) return false;

		if( Buttons[in_kb] & 0x80 )
		{
			if( KeyHits[in_kb] )
			{
				KeyHits[in_kb] = false;
				return true;
			}
		}
		else
		{
			KeyHits[in_kb] = true;
		}
		return false;
	}


	bool EngineInput::KeyUp( BYTE in_kb )
	{
		if(int(in_kb)>255 && int(in_kb)<0) return false;

		if( Buttons[in_kb] & 0x80 )
		{
			KeyUps[in_kb] = true;
		}
		else
		{
			if( KeyUps[in_kb] )
			{
				KeyUps[in_kb] = false;
				return true;
			}
		}
		return false;
	}


	void EngineInput::Release( void )
	{
		if( KeyboardDevice )
			KeyboardDevice->Unacquire();

		if( MouseDevice )
			MouseDevice->Unacquire();

		if( KeyboardDevice )
		{
			KeyboardDevice->Release();
			KeyboardDevice = nullptr;
		}

		if( MouseDevice )
		{
			MouseDevice->Release();
			MouseDevice = nullptr;
		}

		if( lpDI )
			lpDI->Release();
	}

	void EngineInput::UpdateKeyboardState()
	{
		HRESULT hr = KeyboardDevice->GetDeviceState( sizeof( BYTE ) * 256, &Buttons );
		if( FAILED( hr ) )
		{
			do
			{
				hr = KeyboardDevice->Acquire();
			}
			while( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED );
		}
	}

	void EngineInput::UpdateMouseState()
	{
		HRESULT hr = MouseDevice->GetDeviceState( sizeof( DIMOUSESTATE2 ), &MouseState );
		if( FAILED( hr ) )
		{
			do
			{
				hr = MouseDevice->Acquire();
			}
			while( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED );
		}
	}

}


