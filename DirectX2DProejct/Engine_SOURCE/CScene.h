#pragma once
#include "CEntity.h"
#include "CGameObject.h"

namespace sh
{
	class Scene : public CEntity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		std::vector<CGameObject*> mGameObjects;
	};
}
