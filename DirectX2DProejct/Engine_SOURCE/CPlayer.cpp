#include "CPlayer.h"
#include "CRenderer.h"
#include "CGameObject.h"
#include "CInput.h"
#include "CTime.h"

namespace sh
{
	CPlayer::CPlayer()
		: playerRadius(0.5f)
		, playerSpeed(0.5f)
		, playerPos(0.f, 0.f, 0.f)
		, playerColor(1.0f, 0.f, 0.f, 1.f)
	{
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
			playerPos.x += (sh::CTime::DeltaTime()* playerSpeed);
		}
		if (sh::CInput::GetKeyState(sh::eKeyCode::LEFT) == sh::eKeyState::Pressed)
		{	
			playerPos.x -= (sh::CTime::DeltaTime()* playerSpeed);
		}
		if (sh::CInput::GetKeyState(sh::eKeyCode::UP) == sh::eKeyState::Pressed)
		{	
			playerPos.y += (sh::CTime::DeltaTime()* playerSpeed);
		}
		if (sh::CInput::GetKeyState(sh::eKeyCode::DOWN) == sh::eKeyState::Pressed)
		{	
			playerPos.y -= (sh::CTime::DeltaTime()* playerSpeed);
		}
		//SetCellPosition(playerPos);
		render::transform.pos = Vector4(playerPos.x, playerPos.y, 0.f, 1.0f);
		render::transform.scale = Vector4(playerRadius, 0.0f, 0.0f, 0.0f);
		render::transform.color = (playerColor);
	}
	void CPlayer::LateUpdate()
	{
	}
	void CPlayer::Render()
	{
		render::constantBuffer->SetData(&(render::transform));
		CCell::Render();
		CGameObject::Render();
	}
}

/*for (GameObject* gameObj : mGameObjects)
{
	gameObj->Render();
}

wall->Render();

if (mGameObjects.size() <= 1)
return;

auto playerIter = mGameObjects.begin();
for (auto iter = playerIter + 1; iter != mGameObjects.end();)
{
	if (Vector2::Distance(Vector2((*playerIter)->trans.pos.x, (*playerIter)->trans.pos.y)
		, Vector2((*iter)->trans.pos.x, (*iter)->trans.pos.y))
		- fabs((*playerIter)->trans.scale.x + (*iter)->trans.scale.x) < 0)
	{

		(*playerIter)->trans.scale.x += (*iter)->trans.scale.x * 0.3f;

		iter = mGameObjects.erase(iter);
	}
	else
	{
		iter++;
	}
}

if (((*playerIter)->trans.pos.x - (*playerIter)->trans.scale.x)
	- (wall->trans.pos.x - wall->trans.scale.x) <= 0)
	GameObject::OnCollision[0] = true;
else
GameObject::OnCollision[0] = false;

if (((*playerIter)->trans.pos.x + (*playerIter)->trans.scale.x)
	- (wall->trans.pos.x + wall->trans.scale.x) >= 0)
	GameObject::OnCollision[1] = true;
else
GameObject::OnCollision[1] = false;

if (((*playerIter)->trans.pos.y + (*playerIter)->trans.scale.x)
	- (wall->trans.pos.y + wall->trans.scale.x) >= 0)
	GameObject::OnCollision[2] = true;
else
GameObject::OnCollision[2] = false;

if (((*playerIter)->trans.pos.y - (*playerIter)->trans.scale.x)
	- (wall->trans.pos.y - wall->trans.scale.x) <= 0)
	GameObject::OnCollision[3] = true;
else
GameObject::OnCollision[3] = false;
	}*/