#include "CScene.h"
#include "CRenderer.h"

namespace sh
{
	CScene::CScene()
	{
		mLayers.resize((int)sh::enums::eLayerType::End);
	}
	CScene::~CScene()
	{
	}

	void CScene::Initialize()
	{

	}

	void CScene::Update()
	{
		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i].Update();
		}
	}

	void CScene::LateUpdate()
	{
		for (CLayer& layer : mLayers)
		{
			layer.LateUpdate();
		}
	}
	void CScene::Render()
	{
		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i].Render();
		}
	}
	void CScene::AddGameObject(sh::enums::eLayerType type, CGameObject* gameObj)
	{
		mLayers[(int)type].AddGameObject(gameObj);
	}
}