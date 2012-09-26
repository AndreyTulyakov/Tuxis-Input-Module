
#include "Input.h"
#include "EngineInput.h"

namespace Tuxis
{
	Input::Input(HWND pHWND)
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

	Input::~Input()
	{
		if(EngineInput::GetInstance()!=nullptr)
		{
			delete EngineInput::GetInstance();
		}
	}


	void Input::SetMousePosition( int x, int y)
	{
		EngineInput::GetInstance()->SetMousePosition(x,y);
	}

	void Input::GetMousePosition(int& x, int& y)
	{
		EngineInput::GetInstance()->GetMousePosition(x,y);
	}

	void Input::Update()
	{
		EngineInput::GetInstance()->Update();
	}

	int Input::MouseSpeedX()
	{
		return EngineInput::GetInstance()->MouseSpeedX();
	}

	int Input::MouseSpeedY()
	{
		return EngineInput::GetInstance()->MouseSpeedY();
	}

	int Input::MouseSpeedZ()
	{
		return EngineInput::GetInstance()->MouseSpeedZ();
	}

	bool Input::KeyDown( BYTE in_kb )
	{
		return EngineInput::GetInstance()->KeyDown(in_kb);
	}

	bool Input::KeyHit( BYTE in_kb )
	{
		return EngineInput::GetInstance()->KeyHit(in_kb);
	}

	bool Input::KeyUp( BYTE in_kb )
	{
		return EngineInput::GetInstance()->KeyUp(in_kb);
	}

	bool Input::MouseDown( BYTE in_mb )
	{
		return EngineInput::GetInstance()->MouseDown(in_mb);
	}

	bool Input::MouseHit( BYTE in_mb )
	{
		return EngineInput::GetInstance()->MouseHit(in_mb);
	}

	bool Input::MouseUp( BYTE in_mb )
	{
		return EngineInput::GetInstance()->MouseUp(in_mb);
	}

}