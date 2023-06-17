#include "CSceneManager.h"

namespace sh
{
	CScene* CSceneManager::mActiveScene = nullptr;
	void CSceneManager::Initialize()
	{
		mActiveScene = new CPlayScene();
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