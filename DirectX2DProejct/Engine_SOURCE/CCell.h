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

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	};

}

