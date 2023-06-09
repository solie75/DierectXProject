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


/*for (GameObject* gameObj : mGameObjects)
{
    gameObj->Render();
}

wall->Render();

if (mGameObjects.size() <= 1)
return;

auto playerIter = mGameObjects.begin();
for (auto iter = playerIter + 1; iter != mGameObjects.end();)
{
    if (Vector2::Distance(Vector2((*playerIter)->trans.pos.x, (*playerIter)->trans.pos.y)
        , Vector2((*iter)->trans.pos.x, (*iter)->trans.pos.y))
        - fabs((*playerIter)->trans.scale.x + (*iter)->trans.scale.x) < 0)
    {

        (*playerIter)->trans.scale.x += (*iter)->trans.scale.x * 0.3f;

        iter = mGameObjects.erase(iter);
    }
    else
    {
        iter++;
    }
}

if (((*playerIter)->trans.pos.x - (*playerIter)->trans.scale.x)
    - (wall->trans.pos.x - wall->trans.scale.x) <= 0)
    GameObject::OnCollision[0] = true;
else
GameObject::OnCollision[0] = false;

if (((*playerIter)->trans.pos.x + (*playerIter)->trans.scale.x)
    - (wall->trans.pos.x + wall->trans.scale.x) >= 0)
    GameObject::OnCollision[1] = true;
else
GameObject::OnCollision[1] = false;

if (((*playerIter)->trans.pos.y + (*playerIter)->trans.scale.x)
    - (wall->trans.pos.y + wall->trans.scale.x) >= 0)
    GameObject::OnCollision[2] = true;
else
GameObject::OnCollision[2] = false;

if (((*playerIter)->trans.pos.y - (*playerIter)->trans.scale.x)
    - (wall->trans.pos.y - wall->trans.scale.x) <= 0)
    GameObject::OnCollision[3] = true;
else
GameObject::OnCollision[3] = false;
    }*/