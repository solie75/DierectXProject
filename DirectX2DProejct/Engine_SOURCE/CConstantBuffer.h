#pragma once
#include "CGraphics.h"

namespace sh::graphics
{
	class CConstantBuffer : public GpuBuffer
	{
	private:
		const eCBType mType;
	public:
		CConstantBuffer(const eCBType type);
		~CConstantBuffer();

		bool Create(size_t size);
		void SetData(void* data);
		void Bind(eShaderStage stage);

	};
}


