#pragma once
#include "CComponent.h"

namespace sh
{
	class CScript
		: public Component
	{
	private:

	public:
		CScript();
		~CScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}


