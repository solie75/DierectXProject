#include "CScene.h"
#include "CRenderer.h"
#include "CPlayer.h"
#include "CTime.h"
#include "CCellFeed.h"
#include "CGameObject.h"
#include "CApplication.h"

namespace sh
{
	CScene::CScene()
		: wall(nullptr)
	{
	}
	CScene::~CScene()
	{

	}

	void CScene::Initialize()
	{
		AddGameObject(new CWall);
		AddGameObject(new CPlayer);

		SetScore(mGameObjects[1]->transform.scale.x);

		CCellFeed* cellfeed = new CCellFeed;

		for (int i = 0; i < 20; i++)
		{
			AddGameObject(new CCellFeed);
		}

		for (int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Initialize();
		}
		
	}

	void CScene::Update()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i] != nullptr)
			{
				mGameObjects[i]->Update();
			}
			
		}
	}

	void CScene::LateUpdate()
	{
		for (int i = 2; i < mGameObjects.size() - 2; i++)
		{
			if (mGameObjects[i] != nullptr)
			{
				if (Vector2::Distance(Vector2(mGameObjects[1]->transform.pos.x, mGameObjects[1]->transform.pos.y), Vector2(mGameObjects[i]->transform.pos.x, mGameObjects[i]->transform.pos.y)) 
					< mGameObjects[1]->transform.scale.x + mGameObjects[i]->transform.scale.x)
				{
					if (mGameObjects[1]->transform.scale.x > mGameObjects[i]->transform.scale.x)
					{
						mGameObjects[1]->transform.scale.x += mGameObjects[i]->transform.scale.x;
						SetScore(mGameObjects[1]->transform.scale.x);
						delete mGameObjects[i];
						mGameObjects[i] = nullptr;
					}
					else
					{
						SetScore(-1.0f);
					}
				}
			}
		}

		if (abs((mGameObjects[1]->transform.pos.x) - ((mGameObjects[0]->transform.pos.x) + (mGameObjects[0]->transform.scale.x))) < mGameObjects[1]->transform.scale.x)
		{
			
			dynamic_cast<CPlayer*>(mGameObjects[1])->SetCollision(DIRECTION::RIGHT, true);
		}
		else
		{
			dynamic_cast<CPlayer*>(mGameObjects[1])->SetCollision(DIRECTION::RIGHT, false);
		}
		
		if (abs((mGameObjects[1]->transform.pos.x) - ((mGameObjects[0]->transform.pos.x) - (mGameObjects[0]->transform.scale.x))) < mGameObjects[1]->transform.scale.x)
		{
			dynamic_cast<CPlayer*>(mGameObjects[1])->SetCollision(DIRECTION::LEFT, true);
		}
		else
		{
			dynamic_cast<CPlayer*>(mGameObjects[1])->SetCollision(DIRECTION::LEFT, false);
		}
		if (abs((mGameObjects[1]->transform.pos.y) - ((mGameObjects[0]->transform.pos.y) + (mGameObjects[0]->transform.scale.x))) < mGameObjects[1]->transform.scale.x)
		{

			dynamic_cast<CPlayer*>(mGameObjects[1])->SetCollision(DIRECTION::UP, true);
		}
		else
		{
			dynamic_cast<CPlayer*>(mGameObjects[1])->SetCollision(DIRECTION::UP, false);
		}
		if (abs((mGameObjects[1]->transform.pos.y) - ((mGameObjects[0]->transform.pos.y) - (mGameObjects[0]->transform.scale.x))) < mGameObjects[1]->transform.scale.x)
		{

			dynamic_cast<CPlayer*>(mGameObjects[1])->SetCollision(DIRECTION::DOWN, true);
		}
		else
		{
			dynamic_cast<CPlayer*>(mGameObjects[1])->SetCollision(DIRECTION::DOWN, false);
		}
	}
	void CScene::Render()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i] != nullptr)
			{
				mGameObjects[i]->Render();
			}
		}
	}
	void CScene::AddGameObject(CGameObject* _pGameObject)
	{
		mGameObjects.push_back(_pGameObject);
	}
}


