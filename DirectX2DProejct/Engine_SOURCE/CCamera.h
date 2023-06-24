#pragma once
#include "CComponent.h"
#include "CGraphics.h"

namespace sh
{
	class CCamera :
		public Component
	{
	private:
		static Matrix mView;
		static Matrix mProjection;
	public:
		CCamera();
		~CCamera();
	};
}