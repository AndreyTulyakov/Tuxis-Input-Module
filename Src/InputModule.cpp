
#include "InputModule.h"
#include "EngineInput.h"

namespace Tuxis
{
	InputManager::InputManager(HWND pHWND)
	{
		if(EngineInput::GetInstance()==nullptr)
		{
			new EngineInput(pHWND);
		}
		else
		{
			throw "Copy in Input class already exist";
		}
	}

	InputManager::~InputManager()
	{
		if(EngineInput::GetInstance()!=nullptr)
		{
			delete EngineInput::GetInstance();
		}
	}

	void InputManager::UpdateAllStates()
	{
		EngineInput::GetInstance()->UpdateAllStates();
	}



	bool IKeyboard::ButtonDown( BYTE in_kb )
	{
		return EngineInput::GetInstance()->KeyDown(in_kb);
	}

	bool IKeyboard::ButtonHit( BYTE in_kb )
	{
		return EngineInput::GetInstance()->KeyHit(in_kb);
	}

	bool IKeyboard::ButtonUp( BYTE in_kb )
	{
		return EngineInput::GetInstance()->KeyUp(in_kb);
	}

	void IKeyboard::Update()
	{
		EngineInput::GetInstance()->UpdateKeyboardState();
	}


	// IMouse Methods

	bool IMouse::ButtonDown( BYTE in_mb )
	{
		return EngineInput::GetInstance()->MouseDown(in_mb);
	}

	bool IMouse::ButtonHit( BYTE in_mb )
	{
		return EngineInput::GetInstance()->MouseHit(in_mb);
	}

	bool IMouse::ButtonUp( BYTE in_mb )
	{
		return EngineInput::GetInstance()->MouseUp(in_mb);
	}

	void IMouse::SetCursorPosition( int x, int y)
	{
		EngineInput::GetInstance()->SetMousePosition(x,y);
	}

	void IMouse::GetCursorPosition(int& x, int& y)
	{
		EngineInput::GetInstance()->GetMousePosition(x,y);
	}

	void IMouse::Update()
	{
		EngineInput::GetInstance()->UpdateMouseState();
	}

	int IMouse::SpeedX()
	{
		return EngineInput::GetInstance()->MouseSpeedX();
	}

	int IMouse::SpeedY()
	{
		return EngineInput::GetInstance()->MouseSpeedY();
	}

	int IMouse::SpeedZ()
	{
		return EngineInput::GetInstance()->MouseSpeedZ();
	}
}