#include "CPlayScene.h"
#include "CGameObject.h"
#include "CMeshRenderer.h"
#include "CTransform.h"

namespace sh
{
	CPlayScene::CPlayScene()
	{
	}
	CPlayScene::~CPlayScene()
	{
	}
	void CPlayScene::Initialize()
	{
		CGameObject* player = new CGameObject();
		AddGameObject(eLayerType::Player, player);
		player->AddComponent<CMeshRenderer>();
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