#include "CSceneManager.h"
#include "CPlayScene.h"

namespace sh
{
	CScene* CSceneManager::mActiveScene = nullptr;
	std::map<std::wstring, CScene*> CSceneManager::mScenes;

	void CSceneManager::Initialize()
	{
		mActiveScene = new CPlayScene();
		
		mScenes.insert(std::make_pair(L"PlayScene", mActiveScene));

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