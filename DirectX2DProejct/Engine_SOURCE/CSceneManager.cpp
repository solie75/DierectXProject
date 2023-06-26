#include "CSceneManager.h"
#include "CPlayScene.h"
#include "CStartMenuScene.h"
#include "CVillageScene.h"
#include "CShopScene.h"

namespace sh
{
	CScene* CSceneManager::mActiveScene = nullptr;
	std::map<std::wstring, CScene*> CSceneManager::mScenes;

	void CSceneManager::Initialize()
	{
		
		mScenes.insert(std::make_pair(L"PlayScene", new CPlayScene()));
		mScenes.insert(std::make_pair(L"StartMenuScene", new CStartMenuScene));
		mScenes.insert(std::make_pair(L"VillageScene", new CVillageScene));
		mScenes.insert(std::make_pair(L"ShopScene", new CShopScene));

		//mActiveScene = mScenes.find(L"StartMenuScene")->second;
		mActiveScene = mScenes.find(L"VillageScene")->second;
		//mActiveScene = mScenes.find(L"ShopScene")->second;

		mActiveScene->Initialize();
	}
	void CSceneManager::Update()
	{
		mActiveScene->Update();
	}
	void CSceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}
	void CSceneManager::Render()
	{
		mActiveScene->Render();
	}

	void CSceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	CScene* CSceneManager::LoadScene(std::wstring name)
	{
		std::map<std::wstring, CScene*>::iterator iter = mScenes.find(name);

		if (iter == mScenes.end())
		{
			return nullptr;
		}

		mActiveScene->OnExit();
		mActiveScene = iter->second;
		mActiveScene->OnEnter();

		return iter->second;
	}
}