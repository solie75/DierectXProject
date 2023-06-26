#include "CVillageScene.h"
#include "CMeshRenderer.h"
#include "CResources.h"
#include "CTransform.h"
#include "CCamera.h"
#include "CCameraScript.h"

namespace sh
{
	CVillageScene::CVillageScene()
	{
	}
	CVillageScene::~CVillageScene()
	{
	}
	void CVillageScene::Initialize()
	{
		{
			CGameObject* VillageBackground = new CGameObject();
			AddGameObject(eLayerType::Background, VillageBackground);
			CMeshRenderer* mr = VillageBackground->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial3"));
			VillageBackground->GetComponent<CTransform>()->SetPosition(Vector3(0.f, 0.0f, 0.0f));
			// ���� ������ �������� �𸣰��� SetScale �� ������ �� �̹����� ������ ���� (���̹��� ũ�� 2048, 1680 �ȼ�)
			//VillageBackground->GetComponent<CTransform>()->SetScale(Vector3(10.28f, 8.40f, 0.0f));
			VillageBackground->GetComponent<CTransform>()->SetScale(Vector3(15.56f, 12.80f, 0.0f));
		}
		// Main Camera
		CGameObject* camera = new CGameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<CTransform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		CCamera* cameraComp = camera->AddComponent<CCamera>();
		camera->AddComponent<CCameraScript>();
	}
	void CVillageScene::Update()
	{
		CScene::Update();
	}
	void CVillageScene::LateUpdate()
	{
		CScene::LateUpdate();
	}
	void CVillageScene::Render()
	{
		CScene::Render();
	}
}