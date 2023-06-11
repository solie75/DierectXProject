#pragma once
#include "CCell.h"

namespace sh
{
	enum class DIRECTION
	{
		RIGHT,
		LEFT,
		UP,
		DOWN
	};
	class CPlayer :
		public CCell
	{
	private:
		float playerSpeed;
	public:
		bool OnCollision[4] = {};

	public:
		CPlayer();
		virtual ~CPlayer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		void SetCollision(DIRECTION _direction, bool _b);
	};
}



