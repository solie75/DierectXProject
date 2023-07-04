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
		// background
		{
			CGameObject* VillageBackground = new CGameObject();
			AddGameObject(eLayerType::Background, VillageBackground, L"Village_Background");
			CMeshRenderer* mr = VillageBackground->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"spriteMaterial_Village_Background"));
			VillageBackground->GetComponent<CTransform>()->SetPosition(Vector3(0.f, 0.0f, 0.0f));
			VillageBackground->GetComponent<CTransform>()->SetScale(Vector3(15.56f, 12.80f, 0.0f));
			// 아직 비율이 완전한지 모르겠음 SetScale 의 비율은 원 이미지의 비율을 따름 (원이미지 크기 2048, 1680 픽셀)
			//VillageBackground->GetComponent<CTransform>()->SetScale(Vector3(10.28f, 8.40f, 0.0f));
		}
		{
			CGameObject* VillageWillsHome = new CGameObject();
			AddGameObject(eLayerType::Background, VillageWillsHome, L"VillageWillsHome");
			CMeshRenderer* mr = VillageWillsHome->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_WillsHome"));
			VillageWillsHome->GetComponent<CTransform>()->SetPosition(Vector3(1.9f, 4.6f, -0.01f));
			VillageWillsHome->GetComponent<CTransform>()->SetScale(Vector3(3.0f, 3.0f, 0.0f));
		}
		{
			CGameObject* Village_House_01 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_House_01, L"Village_House_01");
			CMeshRenderer* mr = Village_House_01->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_House_01"));
			Village_House_01->GetComponent<CTransform>()->SetPosition(Vector3(5.9f, -2.3f, -0.01f));
			Village_House_01->GetComponent<CTransform>()->SetScale(Vector3(2.8f, 2.8f, 0.0f));
		}
		{
			CGameObject* Village_House_02 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_House_02, L"Village_House_02");
			CMeshRenderer* mr = Village_House_02->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_House_02"));
			Village_House_02->GetComponent<CTransform>()->SetPosition(Vector3(-1.15f, 4.15f, -0.01f));
			Village_House_02->GetComponent<CTransform>()->SetScale(Vector3(2.0f, 2.2f, 0.0f));
		}
		{
			CGameObject* Village_House_06 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_House_06, L"Village_House_06");
			CMeshRenderer* mr = Village_House_06->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_House_06"));
			Village_House_06->GetComponent<CTransform>()->SetPosition(Vector3(2.1f, -2.7f, -0.03f));
			Village_House_06->GetComponent<CTransform>()->SetScale(Vector3(2.0f, 2.0f, 0.0f));
		}
		{
			CGameObject* Village_House_05 = new CGameObject();
			AddGameObject(eLayerType::Background, Village_House_05, L"Village_House_05");
			CMeshRenderer* mr = Village_House_05->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_House_05"));
			Village_House_05->GetComponent<CTransform>()->SetPosition(Vector3(-2.45f, -3.15f, -0.03f));
			Village_House_05->GetComponent<CTransform>()->SetScale(Vector3(2.55f, 2.0f, 0.0f));
		}
		{
			CGameObject* Village_Awning = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Awning, L"Village_Awning");
			CMeshRenderer* mr = Village_Awning->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Awning"));
			Village_Awning->GetComponent<CTransform>()->SetPosition(Vector3(-2.42f, 3.9f, -0.03f));
			Village_Awning->GetComponent<CTransform>()->SetScale(Vector3(0.635f, 1.3f, 0.0f));
		}


		{
			CGameObject* Village_Board = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Board, L"Village_Board");
			CMeshRenderer* mr = Village_Board->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Board"));
			Village_Board->GetComponent<CTransform>()->SetPosition(Vector3(0.97f, 0.435f, -0.03f));
			Village_Board->GetComponent<CTransform>()->SetScale(Vector3(1.15, 0.7f, 0.0f));
		} 
		/*{
			CGameObject* Village_Fence_Column = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Fence_Column, L"Village_Fence_Column");
			CMeshRenderer* mr = Village_Fence_Column->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Fence_Column"));
			Village_Fence_Column->GetComponent<CTransform>()->SetPosition(Vector3(3.9f, 4.6f, -0.01f));
			Village_Fence_Column->GetComponent<CTransform>()->SetScale(Vector3(0.1, 1.7f, 0.0f));
		}
		{
			CGameObject* Village_Fence_Row = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Fence_Row, L"Village_Fence_Row");
			CMeshRenderer* mr = Village_Fence_Row->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Fence_Row"));
			Village_Fence_Row->GetComponent<CTransform>()->SetPosition(Vector3(3.9f, 4.6f, -0.02f));
			Village_Fence_Row->GetComponent<CTransform>()->SetScale(Vector3(2.0, 0.8f, 0.0f));
		}*/


		// black Smith
		{
			CGameObject* Village_Blacksmith_House_old = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Blacksmith_House_old, L"Village_Blacksmith_House_old");
			CMeshRenderer* mr = Village_Blacksmith_House_old->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Blacksmith_House_old"));
			Village_Blacksmith_House_old->GetComponent<CTransform>()->SetPosition(Vector3(6.68f, 0.245f, -0.01f));
			Village_Blacksmith_House_old->GetComponent<CTransform>()->SetScale(Vector3(1.85f, 1.0f, 0.0f));
		}
		{
			CGameObject* Village_Blacksmith_Roof_old = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Blacksmith_Roof_old, L"Village_Blacksmith_Roof_old");
			CMeshRenderer* mr = Village_Blacksmith_Roof_old->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Blacksmith_Roof_old"));
			Village_Blacksmith_Roof_old->GetComponent<CTransform>()->SetPosition(Vector3(6.53f, 1.223f, -0.02f));
			Village_Blacksmith_Roof_old->GetComponent<CTransform>()->SetScale(Vector3(1.61f, 1.95f, 0.0f));
		}
		{
			CGameObject* Village_Blacksmith_Stand1_old = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Blacksmith_Stand1_old, L"Village_Blacksmith_Stand1_old");
			CMeshRenderer* mr = Village_Blacksmith_Stand1_old->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Blacksmith_Stand1_old"));
			Village_Blacksmith_Stand1_old->GetComponent<CTransform>()->SetPosition(Vector3(5.09f, 0.53f, -0.03f));
			Village_Blacksmith_Stand1_old->GetComponent<CTransform>()->SetScale(Vector3(1.42f, 0.5f, 0.0f));
		}
		{
			CGameObject* Village_Blacksmith_Stand2_old = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Blacksmith_Stand2_old, L"Village_Blacksmith_Stand2_old");
			CMeshRenderer* mr = Village_Blacksmith_Stand2_old->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Blacksmith_Stand2_old"));
			//Village_Blacksmith_Stand2_old->GetComponent<CTransform>()->SetPosition(Vector3(4.55f, 1.12f, -0.04f));
			Village_Blacksmith_Stand2_old->GetComponent<CTransform>()->SetPosition(Vector3(4.55f, 1.0735f, -0.04f));
			Village_Blacksmith_Stand2_old->GetComponent<CTransform>()->SetScale(Vector3(0.35f, 0.7f, 0.0f));
		}
		{
			CGameObject* Village_Blacksmith_Fence = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Blacksmith_Fence, L"Village_Blacksmith_Fence");
			CMeshRenderer* mr = Village_Blacksmith_Fence->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Blacksmith_Fence"));
			Village_Blacksmith_Fence->GetComponent<CTransform>()->SetPosition(Vector3(5.045f, 1.515f, -0.03f));
			Village_Blacksmith_Fence->GetComponent<CTransform>()->SetScale(Vector3(1.5f, 0.75f, 0.0f));
		}
		//witch
		{
			CGameObject* Village_Witch_House_old = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Witch_House_old, L"Village_Witch_House_old");
			CMeshRenderer* mr = Village_Witch_House_old->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Witch_House_old"));
			Village_Witch_House_old->GetComponent<CTransform>()->SetPosition(Vector3(-5.53f, -2.6f, -0.01f));
			Village_Witch_House_old->GetComponent<CTransform>()->SetScale(Vector3(1.25f, 1.77f, 0.0f));
		}
		{
			CGameObject* Village_Witch_Roof_old = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Witch_Roof_old, L"Village_Witch_Roof_old");
			CMeshRenderer* mr = Village_Witch_Roof_old->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Witch_Roof_old"));
			Village_Witch_Roof_old->GetComponent<CTransform>()->SetPosition(Vector3(-5.53f, -1.7f, -0.03f));
			Village_Witch_Roof_old->GetComponent<CTransform>()->SetScale(Vector3(1.6f, 3.0f, 0.0f));
		}
		{
			CGameObject* Village_Witch_Table_old = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Witch_Table_old, L"Village_Witch_Table_old");
			CMeshRenderer* mr = Village_Witch_Table_old->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Witch_Table_old"));
			Village_Witch_Table_old->GetComponent<CTransform>()->SetPosition(Vector3(-5.5f, -3.7f, -0.02f));
			Village_Witch_Table_old->GetComponent<CTransform>()->SetScale(Vector3(1.8f, 1.23f, 0.0f));
		}
		{
			CGameObject* Village_Witch_Storage_old = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Witch_Storage_old, L"Village_Witch_Storage_old");
			CMeshRenderer* mr = Village_Witch_Storage_old->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Witch_Storage_old"));
			Village_Witch_Storage_old->GetComponent<CTransform>()->SetPosition(Vector3(-6.85f, -3.8f, -0.03f));
			Village_Witch_Storage_old->GetComponent<CTransform>()->SetScale(Vector3(1.0f, 1.15f, 0.0f));
		}



		// Rival
		{
			CGameObject* Village_Rival_House_old = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Rival_House_old, L"Village_Rival_House_old");
			CMeshRenderer* mr = Village_Rival_House_old->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Rival_House_old"));
			Village_Rival_House_old->GetComponent<CTransform>()->SetPosition(Vector3(-6.05f, 3.75f, -0.01f));
			Village_Rival_House_old->GetComponent<CTransform>()->SetScale(Vector3(3.3f, 2.0f, 0.0f));
		}
		{
			CGameObject* Village_Rival_Roof_old = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Rival_Roof_old, L"Village_Rival_Roof_old");
			CMeshRenderer* mr = Village_Rival_Roof_old->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Rival_Roof_old"));
			Village_Rival_Roof_old->GetComponent<CTransform>()->SetPosition(Vector3(-5.215f, 4.167f, -0.02f));
			Village_Rival_Roof_old->GetComponent<CTransform>()->SetScale(Vector3(2.05f, 1.7f, 0.0f));
		}
		{
			CGameObject* Village_Rival_Fountain_old = new CGameObject();
			AddGameObject(eLayerType::Background, Village_Rival_Fountain_old, L"Village_Rival_Fountain_old");
			CMeshRenderer* mr = Village_Rival_Fountain_old->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Village_Rival_Fountain_old"));
			Village_Rival_Fountain_old->GetComponent<CTransform>()->SetPosition(Vector3(-5.32f, 1.62f, -0.02f));
			Village_Rival_Fountain_old->GetComponent<CTransform>()->SetScale(Vector3(0.5f, 0.58f, 0.0f));
		}
		




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


		// UI
		{
			CGameObject* Cash_UI_Base_Circle = new CGameObject();
			AddGameObject(eLayerType::UI, Cash_UI_Base_Circle, L"Cash_UI_Base_Circle");
			CMeshRenderer* mr = Cash_UI_Base_Circle->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Cash_UI_Base_Circle"));
			Cash_UI_Base_Circle->GetComponent<CTransform>()->SetPosition(Vector3(-3.67f, 1.82f, -0.11f));
			Cash_UI_Base_Circle->GetComponent<CTransform>()->SetScale(Vector3(0.5f, 0.5f, 0.0f));
		}
		{
			CGameObject* Gold4 = new CGameObject();
			AddGameObject(eLayerType::UI, Gold4, L"Gold4");
			CMeshRenderer* mr = Gold4->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Gold4"));
			Gold4->GetComponent<CTransform>()->SetPosition(Vector3(-3.67f, 1.82f, -0.111f));
			Gold4->GetComponent<CTransform>()->SetScale(Vector3(0.3f, 0.3f, 0.0f));
		}
		{
			CGameObject* HealthBar_Circle = new CGameObject();
			AddGameObject(eLayerType::UI, HealthBar_Circle, L"Health_UI_Circle");
			CMeshRenderer* mr = HealthBar_Circle->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Health_UI_Circle"));
			HealthBar_Circle->GetComponent<CTransform>()->SetPosition(Vector3(-3.175f, 1.9f, -0.12f));
			HealthBar_Circle->GetComponent<CTransform>()->SetScale(Vector3(0.3f, 0.3f, 0.0f));
		}
		{
			CGameObject* Health_Icon = new CGameObject();
			AddGameObject(eLayerType::UI, Health_Icon, L"Health_Icon");
			CMeshRenderer* mr = Health_Icon->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Health_Icon"));
			Health_Icon->GetComponent<CTransform>()->SetPosition(Vector3(-3.18f, 1.9f, -0.121f));
			Health_Icon->GetComponent<CTransform>()->SetScale(Vector3(0.21f, 0.21f, 0.0f));
		}
		{
			CGameObject* HealthBar_Base = new CGameObject();
			AddGameObject(eLayerType::UI, HealthBar_Base, L"HealthBar_UI_Base");
			CMeshRenderer* mr = HealthBar_Base->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_HealthBar_UI_Base"));
			HealthBar_Base->GetComponent<CTransform>()->SetPosition(Vector3(-2.58f, 1.9f, -0.13f));
			HealthBar_Base->GetComponent<CTransform>()->SetScale(Vector3(1.0f, 0.28f, 0.0f));
		}
		// set off
		{
			CGameObject* Weapon_UI_Base_Circle = new CGameObject();
			AddGameObject(eLayerType::UI, Weapon_UI_Base_Circle, L"Weapon_UI_Base_Circle");
			CMeshRenderer* mr = Weapon_UI_Base_Circle->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Weapon_UI_Base_Circle"));
			Weapon_UI_Base_Circle->GetComponent<CTransform>()->SetPosition(Vector3(3.5f, 1.56f, -0.14f));
			Weapon_UI_Base_Circle->GetComponent<CTransform>()->SetScale(Vector3(0.485f, 0.485f, 0.0f));
		}
		{
			CGameObject* HUD_Set2 = new CGameObject();
			AddGameObject(eLayerType::UI, HUD_Set2, L"HUD_Set2");
			CMeshRenderer* mr = HUD_Set2->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_HUD_Set2"));
			HUD_Set2->GetComponent<CTransform>()->SetPosition(Vector3(3.13f, 1.6f, -0.143f));
			HUD_Set2->GetComponent<CTransform>()->SetScale(Vector3(0.18f, 0.18f, 0.0f));
		}
		// set On
		{
			CGameObject* Weapon_UI_Base_Circle = new CGameObject();
			AddGameObject(eLayerType::UI, Weapon_UI_Base_Circle, L"Weapon_UI_Base_Circle");
			CMeshRenderer* mr = Weapon_UI_Base_Circle->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Weapon_UI_Base_Circle"));
			Weapon_UI_Base_Circle->GetComponent<CTransform>()->SetPosition(Vector3(3.6f, 1.56f, -0.142f));
			Weapon_UI_Base_Circle->GetComponent<CTransform>()->SetScale(Vector3(0.485f, 0.485f, 0.0f));
		}
		{
			CGameObject* HUD_Set1 = new CGameObject();
			AddGameObject(eLayerType::UI, HUD_Set1, L"HUD_Set1");
			CMeshRenderer* mr = HUD_Set1->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_HUD_Set1"));
			HUD_Set1->GetComponent<CTransform>()->SetPosition(Vector3(3.23f, 1.6f, -0.145f));
			HUD_Set1->GetComponent<CTransform>()->SetScale(Vector3(0.18f, 0.18f, 0.0f));
		}
		// on or off
		{
			CGameObject* Weapon_UI_YesNo_Circle = new CGameObject();
			AddGameObject(eLayerType::UI, Weapon_UI_YesNo_Circle, L"Weapon_UI_YesNo_Circle");
			CMeshRenderer* mr = Weapon_UI_YesNo_Circle->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_YesNo_Circle"));
			Weapon_UI_YesNo_Circle->GetComponent<CTransform>()->SetPosition(Vector3(3.6f, 1.56f, -0.141f));
			Weapon_UI_YesNo_Circle->GetComponent<CTransform>()->SetScale(Vector3(0.18f, 0.18f, 0.0f));
		}
		{
			CGameObject* HUD_Set_YesNo_Circle = new CGameObject();
			AddGameObject(eLayerType::UI, HUD_Set_YesNo_Circle, L"HUD_Set_YesNo_Circle");
			CMeshRenderer* mr = HUD_Set_YesNo_Circle->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_YesNo_Circle"));
			HUD_Set_YesNo_Circle->GetComponent<CTransform>()->SetPosition(Vector3(3.23f, 1.6f, -0.144f));
			HUD_Set_YesNo_Circle->GetComponent<CTransform>()->SetScale(Vector3(0.18f, 0.18f, 0.0f));
		}
		
		{
			CGameObject* Inventory_UI_Base_Circle = new CGameObject();
			AddGameObject(eLayerType::UI, Inventory_UI_Base_Circle, L"Inventory_UI_Base_Circle");
			CMeshRenderer* mr = Inventory_UI_Base_Circle->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Inventory_UI_Base_Circle"));
			Inventory_UI_Base_Circle->GetComponent<CTransform>()->SetPosition(Vector3(3.6f, 0.96f, -0.15f));
			Inventory_UI_Base_Circle->GetComponent<CTransform>()->SetScale(Vector3(0.485f, 0.485f, 0.0f));
		}
		{
			CGameObject* Bag_UI = new CGameObject();
			AddGameObject(eLayerType::UI, Bag_UI, L"Bag_UI");
			CMeshRenderer* mr = Bag_UI->AddComponent<CMeshRenderer>();
			mr->SetMesh(CResources::Find<CMesh>(L"RectMesh"));
			mr->SetMaterial(CResources::Find<CMaterial>(L"SpriteMaterial_Bag_UI"));
			Bag_UI->GetComponent<CTransform>()->SetPosition(Vector3(3.61f, 0.96f, -0.151f));
			Bag_UI->GetComponent<CTransform>()->SetScale(Vector3(0.4f, 0.4f, 0.0f));
		}







		

		// Main Camera
		{
			CGameObject* mainCamera = new CGameObject();
			AddGameObject(eLayerType::Player, mainCamera, L"mainCamera");
			mainCamera->GetComponent<CTransform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			CCamera* cameraComp = mainCamera->AddComponent<CCamera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			mainCamera->AddComponent<CCameraScript>();
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