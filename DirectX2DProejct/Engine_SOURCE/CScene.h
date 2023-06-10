#pragma once
#include "CEntity.h"
#include "CGameObject.h"
#include "CWall.h"

namespace sh
{
	class CScene : public CEntity
	{
	public:
		CScene();
		virtual ~CScene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		std::vector<CGameObject*> mGameObjects;
		CWall* wall;

	public:
		void AddGameObject(CGameObject* _pGameObject);
	};
}
