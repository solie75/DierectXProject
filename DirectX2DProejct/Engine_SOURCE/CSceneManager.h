#pragma once
#include "CScene.h"

namespace sh
{
	class CSceneManager
	{
	private:
		static CScene* mActiveScene;
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
	};
}


