#include "CApplication.h"

sh::CApplication::CApplication()
	: graphicDevice(nullptr)
	, mHwnd(NULL)
	, mWidth(-1)
	, mHeight(-1)
{
}

sh::CApplication::~CApplication()
{
}

void sh::CApplication::Run()
{
}

void sh::CApplication::Initialize()
{
}

void sh::CApplication::Update()
{
}

void sh::CApplication::LateUpdate()
{
}

void sh::CApplication::Render()
{
}

void sh::CApplication::SetWindow(HWND hwnd, UINT width, UINT height)
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
