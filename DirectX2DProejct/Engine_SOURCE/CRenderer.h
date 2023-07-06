#pragma once
#include "CEngine.h"
#include "CGraphicDevice_Dx11.h"
#include "CMesh.h"
#include "CShader.h"
#include "CConstantBuffer.h"
#include "CCamera.h"

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

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};

	//extern Transform transform;
	/*extern sh::CMesh* RectangleMesh;
	extern sh::CShader* shader;*/

	extern Vertex Vertexes[];

	//extern sh::graphics::CConstantBuffer* constantBuffer;
	extern sh::graphics::CConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<sh::CCamera*> cameras;


	void Initialize();
	//void Update();
	void Render();
	void Release();
}

