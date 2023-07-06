#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name
#define CBSLOT_TRANSFORM 0
//#define CBSLOT_PARTICLE 1
#define CBSLOT_GRID 2

namespace sh::graphics
{
	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		End,
	};

	enum class eCBType
	{
		Grid,
		Transform,
		Material,
		End,
	};

	enum class eSamplerType
	{
		Point,
		Anisotropic,
		End,
	};

	enum class eRSType
	{
		SolidBack, // �ĸ��� �ﰢ���� �׸��� �ʴ´�.
		SolidFront, // ������ �ﰢ���� �׸��� �ʴ´�.
		SolidNone, // �׻� ��� �ﰢ���� �׸���.
		WireFrameNone, // ���� �׸��µ� ��� �ﰢ���� �׸�...?
		End,
	};

	enum class eDSType
	{
		Less, // turn on writes + ������ ���̰� ���� ���� ������ ���� ���� �� ī�޶�� ������ ���� �� ���� ���� �����Ѵ�.
		Greater, //  turn on writes + ������ ���� �� ���� ���� ������ ���� ���� �� ī�޶�� �ָ� ���� �� ���� ���� �����Ѵ�.
		NoWrite, // turn off writes + ���� ���� ī�޶� ����� �� ���̰� ����
		None, // turn off writes + ���� ���� ī�޶� �ֶ� ���� �� ����
		// depth-stencil buffer �� ���� write �� turn off �� ���� ���� �� ������ ���� �ǹ̰� ����?
		End,
	};

	enum class eBSType
	{
		Default, // nullptr
		AlphaBlend, // �Ϲ����� ���� ����
		OneOne, // Additive Blending; �ҽ��� ����� ��� ������ �ܼ��� ���ϴ� ������ ������ �����Ѵ�. 
				// ���, ������ ��Ⱑ �� ������� �Ǿ� ���̳� ���� ���� ȿ���� ���� �� �ִ�.
				End,
	};

	enum class eRenderingMode
	{
		Opaque, // ������ : �Ϲ����� �������� ��ü ������ ǥ��
		CutOut, // �ƾƿ� : Alpha �� �̿��� ����, �������� ǥ���� (öâ, �ʴ��ʴ��� ��, õ ���� ǥ��)
		Transparent, // ���� : ���� �ݻ�Ǵ� �������� ������ (����)
		End,
	};



	struct GpuBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		D3D11_BUFFER_DESC desc;

		GpuBuffer()
			: buffer(nullptr)
			, desc{}
		{

		}
		virtual ~GpuBuffer() = default;
	};
}
