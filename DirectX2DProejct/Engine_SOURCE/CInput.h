#pragma once
#include "CEngine.h"

namespace sh
{
	using namespace sh::math;

	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		UP, DOWN, LEFT, RIGHT, SPACE,
		LBUTTON, RBUTTON,
		END,
	};

	enum class eKeyState
	{
		Down,
		Pressed,
		Up,
		None,
	};

	class CInput
	{
	public:
		struct Key
		{
			eKeyCode key;
			eKeyState state;
			bool bPressed;
		};

	private:
		static std::vector<Key> mKeys;
		static Vector2 mMousePos;
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		
		inline static eKeyState GetKeyState(eKeyCode keyCode)
		{
			return mKeys[(UINT)keyCode].state;
		}
		static __forceinline bool GetKey(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Pressed;
		}

		static __forceinline bool GetKeyDown(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Down;
		}

		static __forceinline bool GetKeyUp(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Up;
		}
	};

}


