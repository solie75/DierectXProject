#include "CTime.h"
#include "CApplication.h"

extern sh::CApplication application;

namespace sh
{
	double CTime::mDeltaTime = 0.01;
	double CTime::mSecond = 0.0f;
	LARGE_INTEGER CTime::mCpuFrequency = {};
	LARGE_INTEGER CTime::mPrevFrequency = {};
	LARGE_INTEGER CTime::mCurFrequency = {};

	void CTime::Initiailize()
	{
		QueryPerformanceFrequency(&mCpuFrequency);

		QueryPerformanceCounter(&mPrevFrequency);
	}

	void CTime::Update()
	{
		QueryPerformanceCounter(&mCurFrequency);

		double differnceFrequency = mCurFrequency.QuadPart - mPrevFrequency.QuadPart;

		mDeltaTime = differnceFrequency / mCpuFrequency.QuadPart;

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void CTime::Render()
	{
		mSecond += mDeltaTime;

		if (mSecond > 1.0f)
		{
			HWND hWnd = application.GetHwnd();

			wchar_t szFloat[50] = {};
			float FPS = 1.0f / (float)mDeltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d", (UINT)FPS);
			SetWindowText(hWnd, szFloat);
			mSecond = 0.0f;
		}
	}
}


