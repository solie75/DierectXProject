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
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
			{
				continue;
			}
			delete comp;
			comp = nullptr;
		}
		for (CScript* script : mScripts)
		{
			if (script == nullptr)
			{
				continue;
			}
			delete script;
			script = nullptr;
		}
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
		for (CScript* script : mScripts)
		{
			script->Update();
		}
	}

	void CGameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			comp->LateUpdate();
		}
		for (CScript* script : mScripts)
		{
			script->LateUpdate();
		}
	}

	void CGameObject::Render()
	{
		// ��� ���۷� ��ġ ���� ũ�� ����, ����, ������Ʈ �Ѵ�.
		
		for (Component* comp : mComponents)
		{
			comp->Render();
		}
		for (CScript* script : mScripts)
		{
			script->Render();
		}

	}
}

