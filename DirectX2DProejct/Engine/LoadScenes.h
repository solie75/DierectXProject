#pragma once
#include "CSceneManager.h"
#include "CVillageScene.h"
#include "CPlayScene.h"

//#ifdef _DEBUG
//#pragma comment(lib, "..\\x64\\Debug\\Engine_d.lib")
//#else
//#pragma comment(lib, "..\\x64\\Release\\Engine.lib")
//#endif

namespace sh
{
	void InitializeScenes()
	{
		CSceneManager::CreateScene<CPlayScene>(L"PlayScene");
		//CSceneManager::CreateScene<CPlayScene>(L"StartMenuScene");
		//CSceneManager::CreateScene<CVillageScene>(L"VillageScene");
		//CSceneManager::CreateScene<CPlayScene>(L"ShopScene");
	}
}