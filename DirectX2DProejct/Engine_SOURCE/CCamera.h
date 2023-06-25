#pragma once
#include "CComponent.h"
#include "CGraphics.h"

namespace sh
{
	class CCamera :
		public Component
	{
	public:
		enum class eProjectionType
		{
			Perspective,
			OrthoGraphic,
			None
		};

	private:
		static Matrix mView;
		static Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;

	public:
		CCamera();
		~CCamera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		static Matrix GetViewMatrix() { return mView; }
		static Matrix GetProjectionMatrix() { return mProjection; }

		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType type);
	};
}