#include "CShopScene.h"
#include "CMeshRenderer.h"
#include "CResources.h"
#include "CTransform.h"
#include "CCamera.h"
#include "CCameraScript.h"

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
		// player(will)
		{
			CGameObject* Will = new CGameObject();
			AddGameObject(eLayerType::UI, Will, L"Will");
			CMeshRenderer* mr = Will->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Will"));
			Will->GetComponent<CTransform>()->SetPosition(Vector3(0.0f, 0.0f, -0.1f));
			Will->GetComponent<CTransform>()->SetScale(Vector3(0.3f, 0.35f, 0.0f));
		}
		//background
		{
			CGameObject* ShopBackground = new CGameObject();
			AddGameObject(eLayerType::Background, ShopBackground, L"Shop_Background");
			CMeshRenderer* mr = ShopBackground->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"spriteMaterial_Shop_Background"));
			ShopBackground->GetComponent<CTransform>()->SetPosition(Vector3(0.f, 0.0f, -0.01f));
			ShopBackground->GetComponent<CTransform>()->SetScale(Vector3(4.32f, 5.32f, 0.0f));
		}
		// Main Camera
		{
			CGameObject* camera = new CGameObject();
			AddGameObject(eLayerType::Player, camera, L"MainCamera");
			camera->GetComponent<CTransform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			CCamera* cameraComp = camera->AddComponent<CCamera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CCameraScript>();
		}
		// UI Camera
		{
			CGameObject* UICamera = new CGameObject();
			AddGameObject(eLayerType::Player, UICamera, L"UICamera");
			UICamera->GetComponent<CTransform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			CCamera* UICameraComp = UICamera->AddComponent<CCamera>();
			UICameraComp->TurnLayerMask(eLayerType::Player, false);
			UICameraComp->TurnLayerMask(eLayerType::Background, false);
		}
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

