#pragma once
#include "CGameObject.h"

namespace sh
{
	class CWall :
		public CGameObject
	{
	public:
		CWall();
		virtual ~CWall();

		virtual void Initialize();
		virtual void Render();
		virtual void Update();
		//virtual void LateUpdate();

	};
}


