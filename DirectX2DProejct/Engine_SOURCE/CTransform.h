#pragma once
#include "CComponent.h"

namespace sh
{
	using namespace math;

	class CTransform :
		public Component
	{
	private:
		// 월드 변환 행렬
		Matrix mWorld;

		// 월드 변환의 요소
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;

		// 각 물체가 가지는 자신의 방향 벡터
		Vector3 mUp;
		Vector3 mRight;
		Vector3 mForward;
		
	public:
		CTransform();
		~CTransform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindConstantBuffer();

		void SetPosition(Vector3 pos) { mPosition = pos; }
		void SetRotation(Vector3 rot) { mRotation = rot; }
		void SetScale(Vector3 scale) { mScale = scale; }

		void SetPosition(float x, float y, float z) { mPosition = Vector3(x, y, z); }
		void SetRotation(float x, float y, float z) { mRotation = Vector3(x, y, z); }
		void SetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }

		Vector3 GetPosition() { return mPosition; }
		Vector3 GetRotation() { return mRotation; }
		Vector3 GetScale() { return mScale; }

		Vector3 Forward() { return mForward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }
	};


}
