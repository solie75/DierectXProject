#pragma once
#include "CEntity.h"


namespace sh
{
	using namespace sh::enums;
	using namespace sh::math;
	class CGameObject;
	class Component : public CEntity
	{
	public:
		Component(eComponentType type);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		CGameObject* GetOwner(){ return mOwner; }
		void SetOwner(CGameObject* owner){ mOwner = owner; }

	private:
		const eComponentType mType;
		CGameObject* mOwner;
	};
}