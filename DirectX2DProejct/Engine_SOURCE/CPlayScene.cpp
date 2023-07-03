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
			player->SetName(L"Link");
			AddGameObject(eLayerType::Player, player);
			CMeshRenderer* mr = player->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			//mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial0"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial3"));
			player->GetComponent<CTransform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			player->GetComponent<CTransform>()->SetScale(Vector3(1.0f, 1.0f, 0.0f));
		}
		{
			CGameObject* player = new CGameObject();
			player->SetName(L"dokgak");
			AddGameObject(eLayerType::UI, player);
			CMeshRenderer* mr = player->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial"));
			player->GetComponent<CTransform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			player->GetComponent<CTransform>()->SetScale(Vector3(3.0f, 1.0f, 0.0f));
		}
		// Main Camera
		CGameObject* camera = new CGameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<CTransform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		CCamera* cameraComp = camera->AddComponent<CCamera>();
		camera->AddComponent<CCameraScript>();
		// UI Camera
		CGameObject* UICamera = new CGameObject();
		AddGameObject(eLayerType::Player, UICamera);
		UICamera->GetComponent<CTransform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		CCamera* UICameraComp = UICamera->AddComponent<CCamera>();
		//UICamera->AddComponent<CCameraScript>();
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