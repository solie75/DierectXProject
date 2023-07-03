#pragma once
#include "CGameObject.h"

namespace sh
{
	class CLayer
	{
	public:
		CLayer();
		~CLayer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void AddGameObject(CGameObject* gameObj);
		const std::vector<CGameObject*> GetGameObjects()
		{
			return mGameObjects;
		}

	private:
		std::vector<CGameObject*> mGameObjects;
	};

}

