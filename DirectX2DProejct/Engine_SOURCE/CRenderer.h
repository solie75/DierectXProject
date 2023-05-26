#pragma once
#include "CEngine.h"
#include "CGraphicDevice_Dx11.h"

using namespace sh::math;
namespace sh::render
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern Vertex Vertexes2[];
	extern ID3D11Buffer* triangleBuffer;
	extern ID3D11Buffer* indexBuffer;
	extern ID3DBlob* errorBlob;
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVSShader;
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePSShader;
	extern ID3D11InputLayout* triangleLayout;
	//extern UINT indices[];
	extern UINT circleIndex[];

	void Initialize();
}

