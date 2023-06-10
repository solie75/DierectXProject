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
		// 공움직임 구현

		// 랜더
	}

	void CGameObject::LateUpdate()
	{
	}

	void CGameObject::Render()
	{
		// 상수 버퍼로 위치 정보 크기 정보, 색깔, 업데이트 한다.
		
		//render::wallMesh->BindBuffer();
		
		//render::shader->Binds();
		graphics::GetDevice()->DrawIndexed(render::cellMesh->GetIndexCount(), 0, 0);
		//graphics::GetDevice()->DrawIndexed(render::wallMesh->GetIndexCount(), 0, 0);

	}
}

