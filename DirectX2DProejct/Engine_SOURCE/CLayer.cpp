#include "CLayer.h"

namespace sh
{
	CLayer::CLayer()
	{
	}

	CLayer::~CLayer()
	{
	}

	void CLayer::Initialize()
	{
	}

	void CLayer::Update()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Update();
		}
	}

	void CLayer::LateUpdate()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->LateUpdate();
		}
	}

	void CLayer::Render()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Render();
		}
	}

}

