#pragma once
#include "CEngine.h"
#include "CGraphicDevice_Dx11.h"

namespace sh
{
	class CApplication
	{
	private:
		bool mbInitialize = false;
		std::unique_ptr<sh::graphics::CGraphicDevice_Dx11> graphicDevice;

		//HDC mHDC; -> GPU API
		HWND mHwnd;
		UINT mWidth;
		UINT mHeight;

	public:
		CApplication();
		~CApplication();

		void Run();
		void Initialize();
		void Update();
		void LateUpdate();
		void Render();
		void SetWindow(HWND hwnd, UINT widh, UINT height);

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HWND GetHwnd() { return mHwnd; }
	};
}



