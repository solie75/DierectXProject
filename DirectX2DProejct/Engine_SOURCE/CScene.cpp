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
		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i]->Initialize();
		}
	}

	void CScene::Update()
	{
		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i]->Update();
		}
	}

	void CScene::LateUpdate()
	{
	}
	void CScene::Render()
	{
		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i]->Render();
		}
	}
}