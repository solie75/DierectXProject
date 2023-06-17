#pragma once
#include "CEntity.h"
#include "CLayer.h"

namespace sh
{
	class CScene : public CEntity
	{

	private:
		std::vector<CGameObject*> mLayers;
	public:
		CScene();
		virtual ~CScene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();


	};
}
