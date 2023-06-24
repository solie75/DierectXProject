#pragma once
#include "CEngine.h"
#include "CGraphicDevice_Dx11.h"
#include "CMesh.h"
#include "CShader.h"
#include "CConstantBuffer.h"

using namespace sh::math;
using namespace sh::graphics;
namespace render
{


	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	//struct Transform
	//{
	//	Vector4 pos;
	//	Vector4 scale;
	//	Vector4 color;
	//};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	//extern Transform transform;
	/*extern sh::CMesh* RectangleMesh;
	extern sh::CShader* shader;*/

	extern Vertex Vertexes[];

	//extern sh::graphics::CConstantBuffer* constantBuffer;
	extern sh::graphics::CConstantBuffer* constantBuffer[(UINT)eCBType::End];

	void Initialize();
	//void Update();
	void Release();
}

