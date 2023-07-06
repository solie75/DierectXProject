#include "CGridScript.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CApplication.h"

extern sh::CApplication application;

namespace sh
{
	CGridScript::CGridScript()
		: mCamera(nullptr)
	{
	}
	CGridScript::~CGridScript()
	{
	}


	void CGridScript::Initialize()
	{
	}
	void CGridScript::Update()
	{
		if (mCamera == nullptr)
		{
			return;
		}

		CGameObject* gameObj = mCamera->GetOwner();
		CTransform* tr = gameObj->GetComponent<CTransform>();
		Vector3 pos = tr->GetPosition();

		float scale = mCamera->GetSize();

		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 resolution(width, height);

		// CB buffer
		graphics::CConstantBuffer* cb = render::constantBuffer[(int)eCBType::Grid];

		render::GridCB data;
		data.CameraPosition = Vector4(pos.x, pos.y, pos.z, 1.0f);
		data.Resolution = resolution;
		data.CameraScale = Vector2(scale, scale);

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);

	}
	void CGridScript::LateUpdate()
	{
	}
	void CGridScript::Render()
	{
	}
}