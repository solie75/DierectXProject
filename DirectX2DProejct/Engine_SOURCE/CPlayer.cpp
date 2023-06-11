#include "CPlayer.h"
#include "CRenderer.h"
#include "CGameObject.h"
#include "CInput.h"
#include "CTime.h"

namespace sh
{
	CPlayer::CPlayer()
		: 
		playerSpeed(0.5f)
	{
		for (int i = 0; i < 4; i++)
		{
			OnCollision[i] = false;
		}

		transform.pos = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
		transform.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		transform.scale = Vector4(0.1f, 0.0f, 0.0f, 0.0f);
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
		if (sh::CInput::GetKeyState(sh::eKeyCode::RIGHT) == sh::eKeyState::Pressed && OnCollision[(INT)DIRECTION::RIGHT] == false)
		{
			transform.pos.x += (sh::CTime::DeltaTime() * playerSpeed);
		}
		if (sh::CInput::GetKeyState(sh::eKeyCode::LEFT) == sh::eKeyState::Pressed && OnCollision[(INT)DIRECTION::LEFT] == false)
		{
			transform.pos.x -= (sh::CTime::DeltaTime() * playerSpeed);
		}
		if (sh::CInput::GetKeyState(sh::eKeyCode::UP) == sh::eKeyState::Pressed && OnCollision[(INT)DIRECTION::UP] == false)
		{
			transform.pos.y += (sh::CTime::DeltaTime() * playerSpeed);
		}
		if (sh::CInput::GetKeyState(sh::eKeyCode::DOWN) == sh::eKeyState::Pressed && OnCollision[(INT)DIRECTION::DOWN] == false)
		{
			transform.pos.y -= (sh::CTime::DeltaTime() * playerSpeed);
		}                              
	}
	void CPlayer::LateUpdate()
	{

	}
	void CPlayer::Render()
	{
		render::constantBuffer->SetData(&(transform));
		CCell::Render();
		render::shader->Binds(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		CGameObject::Render();
	}
	void CPlayer::SetCollision(DIRECTION _direction, bool _b)
	{
		OnCollision[(int)_direction] = _b;
	}
}
