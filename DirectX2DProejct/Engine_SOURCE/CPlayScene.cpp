#include "CPlayScene.h"
#include "CGameObject.h"
#include "CMeshRenderer.h"
#include "CTransform.h"
#include "CResources.h"
#include "CCameraScript.h"

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
		CMeshRenderer* mr = player->AddComponent<CMeshRenderer>();
		mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
		mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial"));

		player->AddComponent<CCameraScript>();
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