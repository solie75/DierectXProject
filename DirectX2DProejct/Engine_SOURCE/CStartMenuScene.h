#pragma once
#include "CScene.h"

namespace sh
{
	class CStartMenuScene :
		public CScene
	{
	public:
		CStartMenuScene();
		virtual ~CStartMenuScene();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}

