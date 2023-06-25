#include "CCameraScript.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "CTime.h"
#include "CInput.h"

namespace sh
{
	void CCameraScript::Update()
	{
		CTransform* tr = GetOwner()->GetComponent<CTransform>();
		Vector3 pos = tr->GetPosition();

		if (CInput::GetKey(eKeyCode::W))
		{
			pos.z += 5.0f * CTime::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (CInput::GetKey(eKeyCode::S))
		{
			pos.z -= 5.0f * CTime::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (CInput::GetKey(eKeyCode::A))
		{
			pos.x -= 5.0f * CTime::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (CInput::GetKey(eKeyCode::D))
		{
			pos.x += 5.0f * CTime::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (CInput::GetKey(eKeyCode::Q))
		{
			pos.y -= 5.0f * CTime::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (CInput::GetKey(eKeyCode::E))
		{
			pos.y += 5.0f * CTime::DeltaTime();
			tr->SetPosition(pos);
		}


		/*pos.x += 1.0f * CTime::DeltaTime();
		tr->SetPosition(pos);*/
	}
}