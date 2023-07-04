#include "CShopScene.h"
#include "CMeshRenderer.h"
#include "CResources.h"
#include "CTransform.h"
#include "CCamera.h"
//#include "CCameraScript.h"

namespace sh
{
	CShopScene::CShopScene()
	{
	}

	CShopScene::~CShopScene()
	{
	}

	void CShopScene::Initialize()
	{
		{
			CGameObject* ShopBackground = new CGameObject();
			AddGameObject(eLayerType::Background, ShopBackground, L"ShopBackground");
			CMeshRenderer* mr = ShopBackground->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial4"));
			ShopBackground->GetComponent<CTransform>()->SetPosition(Vector3(0.f, 0.0f, 0.0f));
			ShopBackground->GetComponent<CTransform>()->SetScale(Vector3(4.32f, 5.32f, 0.0f));
		}
		// Main Camera
		CGameObject* camera = new CGameObject();
		AddGameObject(eLayerType::Player, camera, L"MainCamera");
		camera->GetComponent<CTransform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		CCamera* cameraComp = camera->AddComponent<CCamera>();
		//camera->AddComponent<CCameraScript>();
	}

	void CShopScene::Update()
	{
		CScene::Update();
	}

	void CShopScene::LateUpdate()
	{
		CScene::LateUpdate();
	}

	void CShopScene::Render()
	{
		CScene::Render();
	}

}

