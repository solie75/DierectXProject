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

		std::bitset<(UINT)eLayerType::End>mLayerMask;
		std::vector<CGameObject*>mOpaqueGameObjects; // 불투명한 고체물질
		std::vector<CGameObject*>mCutOutGameObjects; // Alpha 를 이용한 투명도 표현
		std::vector<CGameObject*>mTransparentGameObjects; // 투명한 물체

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

		void TurnLayerMask(eLayerType type, bool enable = true);
		void EnableLayerMasks() { mLayerMask.set(); }
		void DisableLayerMasks() { mLayerMask.reset(); }

		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();

		void RegisterCameraInRenderer();

		void SortGameObjects();
	};
}