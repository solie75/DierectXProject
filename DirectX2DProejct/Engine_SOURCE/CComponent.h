#pragma once
#include "CEntity.h"

namespace sh
{
	using namespace sh::enums;

	class Component : public CEntity
	{
	public:
		Component();
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		const eComponentType mType;
	};
}