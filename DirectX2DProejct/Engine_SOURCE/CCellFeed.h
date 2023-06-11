#pragma once
#include "CCell.h"
#include "CRenderer.h"
namespace sh
{
	class CCellFeed :
		public CCell
	{
	public:
		CCellFeed();
		virtual ~CCellFeed();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	};

}

