#include "CScene.h"
#include "CRenderer.h"

namespace sh
{
	CScene::CScene()
	{
	}
	CScene::~CScene()
	{

	}

	void CScene::Initialize()
	{
		//AddGameObject(new CPlayer);

		for (int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Initialize();
		}
	}

	void CScene::Update()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Update();
		}
	}

	void CScene::LateUpdate()
	{
	}
	void CScene::Render()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Render();
		}
	}
	void CScene::AddGameObject(CGameObject* _pGameObject)
	{
		mGameObjects.push_back(_pGameObject);
	}
}