#pragma once
#include "CScene.h"

namespace sh
{
	class CVillageScene :
		public CScene
	{
	public:
		CVillageScene();
		virtual ~CVillageScene();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}


