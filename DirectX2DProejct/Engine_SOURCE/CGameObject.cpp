#include "CGameObject.h"
#include "CRenderer.h"
#include "CGraphicDevice_Dx11.h"

namespace sh
{
	CGameObject::CGameObject()
		: mState(eState::Active)
	{
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
	}

	void CGameObject::LateUpdate()
	{
	}

	void CGameObject::Render()
	{
		// ��� ���۷� ��ġ ���� ũ�� ����, ����, ������Ʈ �Ѵ�.
		
		//render::wallMesh->BindBuffer();
		
		//render::shader->Binds();
		graphics::GetDevice()->DrawIndexed(render::cellMesh->GetIndexCount(), 0, 0);
		//graphics::GetDevice()->DrawIndexed(render::wallMesh->GetIndexCount(), 0, 0);

	}
}

