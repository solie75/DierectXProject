#pragma once
#include "CScript.h"
#include "CCamera.h"

namespace sh
{
	class CGridScript :
		public CScript
	{
	private:
		CCamera* mCamera;

	public:
		CGridScript();
		~CGridScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetCamera(CCamera* camera) { mCamera = camera; }
	};
}


