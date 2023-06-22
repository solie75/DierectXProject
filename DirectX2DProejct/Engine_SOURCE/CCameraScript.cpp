#include "CCameraScript.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "CTime.h"

namespace sh
{
	void CCameraScript::Update()
	{
		CTransform* tr = GetOwner()->GetComponent<CTransform>();
		Vector3 pos = tr->GetPosition();
		pos.x += 1.0f * CTime::DeltaTime();
		tr->SetPosition(pos);
	}
}