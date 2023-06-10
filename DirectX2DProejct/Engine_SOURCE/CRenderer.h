#pragma once
#include "CEngine.h"
#include "CGraphicDevice_Dx11.h"
#include "CMesh.h"
#include "CShader.h"
#include "CConstantBuffer.h"

using namespace sh::math;
namespace render
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	struct Transform
	{
		Vector4 pos;
		Vector4 scale;
		Vector4 color;
	};

	//extern Transform transform;
	extern sh::CMesh* cellMesh;
	extern sh::CMesh* wallMesh;
	extern sh::CShader* shader;

	extern Vertex cellVertexes[];
	extern Vertex wallVertexes[];

	extern sh::graphics::CConstantBuffer* constantBuffer;
	extern sh::graphics::CConstantBuffer* FixedPosConstantBuffer;

	void Initialize();
	void Update();
	void Release();
}

