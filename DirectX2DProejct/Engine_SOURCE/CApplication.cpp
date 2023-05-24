#include "CApplication.h"

namespace sh
{
	CApplication::CApplication()
		: graphicDevice(nullptr)
		, mHwnd(NULL)
		, mWidth(-1)
		, mHeight(-1)
	{
	}

	CApplication::~CApplication()
	{
	}

	void CApplication::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void CApplication::Initialize()
	{
	}

	void CApplication::Update()
	{
	}

	void CApplication::LateUpdate()
	{
	}

	void CApplication::Render()
	{
		graphicDevice->Draw();
	}

	void CApplication::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;

			graphicDevice = std::make_unique<sh::graphics::CGraphicDevice_Dx11>();
		}

		RECT rt = { 0, 0, (LONG)width, (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

}

