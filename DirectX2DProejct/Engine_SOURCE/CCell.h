#pragma once
#include "CGameObject.h"

namespace sh
{
	class CCell :
		public CGameObject
	{
	private:
		float degree;
		double radius;
		sh::math::Vector3 position;

	public:
		CCell();
		virtual ~CCell();

		//void SetCellPosition(sh::math::Vector3 _v3);

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	};

}

