#include "CStartMenuScene.h"
#include "CMeshRenderer.h"
#include "CResources.h"
#include "CTransform.h"
#include "CCamera.h"
//#include "CCameraScript.h"

namespace sh
{
	CStartMenuScene::CStartMenuScene()
	{
	}
	CStartMenuScene::~CStartMenuScene()
	{
	}
	void CStartMenuScene::Initialize()
	{
		{
			CGameObject* leftDoor = new CGameObject();
			AddGameObject(eLayerType::Background, leftDoor, L"LeftDoor");
			CMeshRenderer* mr = leftDoor->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial1"));
			// SetPosition 에서 위치를 좀더 왼쪽으로 하여 두 문사이의 가운데가 초록으로 보여야 함
			leftDoor->GetComponent<CTransform>()->SetPosition(Vector3(-2.f, 0.0f, 0.0f));
			leftDoor->GetComponent<CTransform>()->SetScale(Vector3(4.0f, 5.0f, 0.0f));
		}
		{
			CGameObject* rightDoor = new CGameObject();
			AddGameObject(eLayerType::Background, rightDoor, L"RightDoor");
			CMeshRenderer* mr = rightDoor->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial2"));
			rightDoor->GetComponent<CTransform>()->SetPosition(Vector3(2.f, 0.0f, 0.0f));
			rightDoor->GetComponent<CTransform>()->SetScale(Vector3(4.0f, 5.0f, 0.0f));
		}

		// Main Camera
		CGameObject* camera = new CGameObject();
		AddGameObject(eLayerType::Player, camera, L"MainCamera");
		camera->GetComponent<CTransform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		CCamera* cameraComp = camera->AddComponent<CCamera>();
		//camera->AddComponent<CCameraScript>();
	}
	void CStartMenuScene::Update()
	{
		CScene::Update();
	}
	void CStartMenuScene::LateUpdate()
	{
		CScene::LateUpdate();
	}
	void CStartMenuScene::Render()
	{
		CScene::Render();
	}
}