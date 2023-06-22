#include "CTransform.h"
#include "CRenderer.h"
#include "CConstantBuffer.h"

namespace sh
{
	CTransform::CTransform()
		: Component(eComponentType::Transform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
	{
	}
	CTransform::~CTransform()
	{
	}
	void CTransform::Initialize()
	{
	}
	void CTransform::Update()
	{
	}
	void CTransform::LateUpdate()
	{
	}
	void CTransform::Render()
	{

	}
	void CTransform::BindConstantBuffer()
	{
		//CConstantBuffer* cb = render::constantBuffer;
		CConstantBuffer* cb = render::constantBuffer[(UINT)eCBType::Transform];
		Vector4 pos(mPosition.x, mPosition.y, mPosition.z, 1.0f);
		cb->SetData(&pos);
		cb->Bind(eShaderStage::VS);
	}
}