#include "CPlayScene.h"
#include "CGameObject.h"
#include "CMeshRenderer.h"
#include "CTransform.h"

namespace sh
{
	CPlayScene::CPlayScene()
	{
		CGameObject* player = new CGameObject();
		AddGameObject(eLayerType::Player, player);
		player->AddComponent<CMeshRenderer>();
	}
	CPlayScene::~CPlayScene()
	{
	}
	void CPlayScene::Initialize()
	{
		
	}
	void CPlayScene::Update()
	{
		CScene::Update();
	}
	void CPlayScene::LateUpdate()
	{
		CScene::LateUpdate();
	}
	void CPlayScene::Render()
	{
		CScene::Render();
	}
}