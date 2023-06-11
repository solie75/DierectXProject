#pragma once
#include "CEntity.h"
#include "CRenderer.h"

namespace sh
{
	enum eState
	{
		Active,
		Paused,
		Dead,
	};

	class CGameObject : public CEntity
	{
	private:
		eState mState;

	public:
		CGameObject();
		virtual ~CGameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	

		render::Transform transform;

	};
}


