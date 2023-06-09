#include "CPlayer.h"
#include "CRenderer.h"
#include "CGameObject.h"
#include "CInput.h"
#include "CTime.h"

namespace sh
{
	CPlayer::CPlayer()
		: playerRadius(0.5f)
		, playerSpeed(0.01f)
		, playerPos(0.f, 0.f, 0.f)
		, playerColor(1.0f, 0.f, 0.f, 1.f)
	{
		transform.pos = Vector4(0.f, 0.f, 0.f, 1.0f);
		transform.scale = Vector4(playerRadius, 0.0f, 0.0f, 0.0f);
		transform.color = (playerColor);
	}
	CPlayer::~CPlayer()
	{
	}
	void CPlayer::Initialize()
	{
		CCell::Initialize();
	}
	void CPlayer::Update()
	{
		if (sh::CInput::GetKeyState(sh::eKeyCode::RIGHT) == sh::eKeyState::Pressed)
		{	
			playerPos.x += sh::CTime::DeltaTime()* playerSpeed;
		}
		if (sh::CInput::GetKeyState(sh::eKeyCode::LEFT) == sh::eKeyState::Pressed)
		{	
			playerPos.x -= sh::CTime::DeltaTime() * playerSpeed;
		}
		if (sh::CInput::GetKeyState(sh::eKeyCode::UP) == sh::eKeyState::Pressed)
		{	
			playerPos.y += sh::CTime::DeltaTime() * playerSpeed;
		}
		if (sh::CInput::GetKeyState(sh::eKeyCode::DOWN) == sh::eKeyState::Pressed)
		{	
			playerPos.y -= sh::CTime::DeltaTime() * playerSpeed;
		}
	}
	void CPlayer::LateUpdate()
	{
	}
	void CPlayer::Render()
	{
		render::constantBuffer->SetData(&transform);
		CCell::Render();
		CGameObject::Render();
	}
}