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
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;

		std::bitset<(UINT)eLayerType::End>mLayerMask;
		std::vector<CGameObject*>mOpaqueGameObjects; // �������� ��ü����
		std::vector<CGameObject*>mCutOutGameObjects; // Alpha �� �̿��� ���� ǥ��
		std::vector<CGameObject*>mTransparentGameObjects; // ������ ��ü

	public:
		CCamera();
		~CCamera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		static Matrix GetViewMatrix() { return View; }
		static Matrix GetProjectionMatrix() { return Projection; }

		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType type);

		void TurnLayerMask(eLayerType type, bool enable = true);
		void EnableLayerMasks() { mLayerMask.set(); }
		void DisableLayerMasks() { mLayerMask.reset(); }

		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();

		void RegisterCameraInRenderer();

		//void SortGameObjects();
		//bool CompareZSort(CGameObject* a, CGameObject* b);

		void AlphaSortGameObjects();
		void ZSortTransparencyGameObjects();
		void DivideAlphaBlendGameObjects(const std::vector<CGameObject*>gameObjs);

		void EnableDepthStencilState();
		void DisableDepthStencilState();
	};
}