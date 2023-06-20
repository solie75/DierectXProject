#include "CGameObject.h"
#include "CRenderer.h"
#include "CGraphicDevice_Dx11.h"
#include "CTransform.h"

namespace sh
{
	CGameObject::CGameObject()
		: mState(eState::Active)
	{
		AddComponent<CTransform>();
	}

	CGameObject::~CGameObject()
	{
	}

	void CGameObject::Initialize()
	{
	
	}

	void CGameObject::Update()
	{
		// �������� ����

		// ����
		for (Component* comp : mComponents)
		{
			comp->Update();
		}
	}

	void CGameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			comp->LateUpdate();
		}
	}

	void CGameObject::Render()
	{
		// ��� ���۷� ��ġ ���� ũ�� ����, ����, ������Ʈ �Ѵ�.
		
		for (Component* comp : mComponents)
		{
			comp->Render();
		}

	}
}

