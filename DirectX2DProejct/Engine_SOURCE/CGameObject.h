#pragma once
#include "CEntity.h"

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
		virtual void Updata();
		virtual void LateUpdate();
		virtual void Render();

	};
}


