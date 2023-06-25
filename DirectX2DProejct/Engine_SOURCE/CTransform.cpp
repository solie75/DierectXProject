#include "CTransform.h"
#include "CRenderer.h"
#include "CConstantBuffer.h"
#include "CCamera.h"

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
		// 크기, 회전, 이동 의 변경

	}
	void CTransform::LateUpdate()
	{
		// update 에서 변경된 내용으로 월드 변환 행렬을 생성
		mWorld = Matrix::Identity;

		Matrix scale = Matrix::CreateScale(mScale);

		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
	}
	void CTransform::Render()
	{

	}
	void CTransform::BindConstantBuffer()
	{
		render::TransformCB trCB = {};
		trCB.mWorld = mWorld;
		trCB.mView = CCamera::GetViewMatrix();
		trCB.mProjection = CCamera::GetProjectionMatrix();

		CConstantBuffer* cb = render::constantBuffer[(UINT)eCBType::Transform];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::VS);
	}
}