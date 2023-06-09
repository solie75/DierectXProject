#include "CScene.h"
#include "CRenderer.h"
#include "CWall.h"
#include "CPlayer.h"

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
		AddGameObject(new CWall);
		AddGameObject(new CPlayer);

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
		/*mTime += (float)Time::DeltaTime();

		if (mTime >= 0.5f)
		{
			CellPrefab* clone = new CellPrefab();
			mGameObjects.push_back(clone);

			mTime = 0.f;
		}*/
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


