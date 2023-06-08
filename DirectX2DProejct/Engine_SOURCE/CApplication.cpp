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
		CTime::Initiailize();
		CInput::Initialize();

		render::Initialize(); // 왜 renderer 는 class 가 아니지?
		
	}

	void CApplication::Update()
	{
		CTime::Update();
		CInput::Update();
	}

	void CApplication::LateUpdate()
	{
		render::Update();
	}

	void CApplication::Render()
	{
		CTime::Render();

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
			sh::graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width, (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

}

