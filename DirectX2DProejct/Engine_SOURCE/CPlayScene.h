#pragma once
#include "CScene.h"

namespace sh
{
	class CPlayScene :
		public CScene
	{
	public:
		CPlayScene();
		virtual ~CPlayScene();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}


