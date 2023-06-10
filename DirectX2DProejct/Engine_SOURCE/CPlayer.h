#pragma once
#include "CCell.h"

namespace sh
{
	class CPlayer :
		public CCell
	{
	private:
		//math::Vector3 playerPos;
		//float playerRadius;
		float playerSpeed;
		//math::Vector4 playerColor;

	public:
		CPlayer();
		virtual ~CPlayer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	};
}



