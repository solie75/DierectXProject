#include "CGameObject.h"
#include "CRenderer.h"
#include "CGraphicDevice_Dx11.h"

sh::CGameObject::CGameObject()
	: mState(eState::Active)
{
}

sh::CGameObject::~CGameObject()
{
}

void sh::CGameObject::Initialize()
{
}

void sh::CGameObject::Updata()
{
	// �������� ����

	// ����
}

void sh::CGameObject::LateUpdate()
{
}

void sh::CGameObject::Render()
{

	// ��� ���۷� ��ġ ���� ũ�� ����, ����, ������Ʈ �Ѵ�.

	render::mesh->BindBuffer();
	render::shader->Binds();
	graphics::GetDevice()->DrawIndexed(render::mesh->GetIndexCount(), 0, 0);
}
