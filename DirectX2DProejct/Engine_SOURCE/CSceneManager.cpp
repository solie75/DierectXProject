#include "CSceneManager.h"
#include "CPlayScene.h"

namespace sh
{
	CScene* CSceneManager::mActiveScene = nullptr;
	void CSceneManager::Initialize()
	{
		mActiveScene = new CPlayScene();
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
}