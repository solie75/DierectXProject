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
		graphics::GetDevice()->DrawIndexed(render::cellMesh->GetIndexCount(), 0, 0);
	}
}

