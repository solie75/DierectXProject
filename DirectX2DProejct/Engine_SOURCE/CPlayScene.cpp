#include "CPlayScene.h"
#include "CGameObject.h"
#include "CMeshRenderer.h"
#include "CTransform.h"
#include "CResources.h"
#include "CCameraScript.h"
#include "CCamera.h"

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
		{
			CGameObject* player = new CGameObject();
			AddGameObject(eLayerType::Player, player, L"Link");
			CMeshRenderer* mr = player->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial0"));
			player->GetComponent<CTransform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0001f));

			CGameObject* player2 = new CGameObject();
			AddGameObject(eLayerType::Player, player2, L"LinkChild");
			CMeshRenderer* mr2 = player2->AddComponent<CMeshRenderer>();
			mr2->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr2->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial0"));
			player2->GetComponent<CTransform>()->SetPosition(Vector3(1.0f, 0.0f, 1.0001f));
			player2->GetComponent<CTransform>()->SetParent(player->GetComponent<CTransform>());

			const float pi = 3.141592f;
			float degree = pi / 2.0f;

			player->GetComponent<CTransform>()->SetPosition(Vector3(-3.0f, 0.0f, 1.0001f));
			player->GetComponent<CTransform>()->SetRotation(Vector3(0.0f, 0.0f, degree));
		}
		{
			CGameObject* player = new CGameObject();
			AddGameObject(eLayerType::Player, player, L"Smile");
			CMeshRenderer* mr = player->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial5"));
			player->GetComponent<CTransform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			//player->GetComponent<CTransform>()->SetScale(Vector3(1.0f, 1.0f, 0.0f));
		}
		{
			CGameObject* player = new CGameObject();
			AddGameObject(eLayerType::UI, player, L"Smile1");
			CMeshRenderer* mr = player->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial5"));
			player->GetComponent<CTransform>()->SetPosition(Vector3(0.2f, 0.0f, 0.0f));
			//player->GetComponent<CTransform>()->SetScale(Vector3(1.0f, 1.0f, 0.0f));
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
		}
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