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

		if (CInput::GetKey(eKeyCode::E))
		{
			pos.z += (float)(5.0 * CTime::DeltaTime());
			tr->SetPosition(pos);
		}
		else if (CInput::GetKey(eKeyCode::Q))
		{
			pos.z -= (float)(5.0 * CTime::DeltaTime());
			tr->SetPosition(pos);
		}
		else if (CInput::GetKey(eKeyCode::A))
		{
			pos.x -= (float)(5.0 * CTime::DeltaTime());
			tr->SetPosition(pos);
		}
		else if (CInput::GetKey(eKeyCode::D))
		{
			pos.x += (float)(5.0 * CTime::DeltaTime());
			tr->SetPosition(pos);
		}
		else if (CInput::GetKey(eKeyCode::S))
		{
			pos.y -= (float)(5.0 * CTime::DeltaTime());
			tr->SetPosition(pos);
		}
		else if (CInput::GetKey(eKeyCode::W))
		{
			pos.y += (float)(5.0 * CTime::DeltaTime());
			tr->SetPosition(pos);
		}


		/*pos.x += 1.0f * CTime::DeltaTime();
		tr->SetPosition(pos);*/
	}
}