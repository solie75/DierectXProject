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
	// 공움직임 구현

	// 랜더
}

void sh::CGameObject::LateUpdate()
{
}

void sh::CGameObject::Render()
{

	// 상수 버퍼로 위치 정보 크기 정보, 색깔, 업데이트 한다.

	render::mesh->BindBuffer();
	render::shader->Binds();
	graphics::GetDevice()->DrawIndexed(render::mesh->GetIndexCount(), 0, 0);
}
