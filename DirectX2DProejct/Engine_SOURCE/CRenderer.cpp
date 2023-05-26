#include "CRenderer.h"

namespace sh::render
{
	//Vertex Vertexes1[3] = {};
	//Vertex Vertexes2[4] = {};
	Vertex vCircle[360] = {};

	ID3D11Buffer* triangleBuffer = nullptr;

	ID3DBlob* errorBlob = nullptr;

	ID3DBlob* triangleVSBlob = nullptr;

	ID3D11VertexShader* triangleVSShader = nullptr;

	ID3DBlob* trianglePSBlob = nullptr;

	ID3D11PixelShader* trianglePSShader = nullptr;

	ID3D11InputLayout* triangleLayout = nullptr;

	ID3D11Buffer* indexBuffer = nullptr;

	//UINT indices[6] = {};
	UINT circleIndex[1080] = {}; // 1-0-2, 1-0-3, 2-0-4, 3-0-5, ..., 358-0-360, 359-0-1

	void SetupState()
	{

	}

	void LoadBuffer()
	{
		//D3D11_BUFFER_DESC triangleDesc = {};
		//triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		//triangleDesc.ByteWidth = sizeof(Vertex) * 3;
		//triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		//triangleDesc.CPUAccessFlags = D3D10_CPU_ACCESS_FLAG::D3D10_CPU_ACCESS_WRITE;

		//D3D11_BUFFER_DESC SquareDesc = {};
		//SquareDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		//SquareDesc.ByteWidth = sizeof(Vertex) * 4;
		//SquareDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		//SquareDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_BUFFER_DESC circleDesc = {};
		circleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		circleDesc.ByteWidth = sizeof(Vertex) * 360;
		circleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		circleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		//D3D11_SUBRESOURCE_DATA SqaureData = {};
		//SqaureData.pSysMem = Vertexes2;
		//sh::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &SquareDesc, &SqaureData);

		D3D11_SUBRESOURCE_DATA circleData = {};
		circleData.pSysMem = vCircle;
		sh::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &circleDesc, &circleData);

		circleIndex[0] = 1;
		circleIndex[1] = 0;
		circleIndex[2] = 2;

		for (int i = 1; i < 359; i++)
		{
			circleIndex[i * 3] = i;
			circleIndex[(i * 3) + 1] = 0;
			circleIndex[(i * 3) + 2] = i + 2;
		}

		circleIndex[1077] = 359;
		circleIndex[1078] = 0;
		circleIndex[1079] = 1;

		// index buffer
		D3D11_BUFFER_DESC indexDesc = {};
		indexDesc.Usage = D3D11_USAGE_DEFAULT;
		indexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		//indexDesc.ByteWidth = sizeof(unsigned int) * 6;
		indexDesc.ByteWidth = sizeof(UINT) * 1080;

		D3D11_SUBRESOURCE_DATA indexData = {};
		//indexData.pSysMem = indices;
		indexData.pSysMem = circleIndex;
		(sh::graphics::GetDevice()->CreateBuffer(&indexBuffer , &indexDesc, &indexData));
	}

	void LoadShader()
	{
		sh::graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		double pi = 3.1215926;
		double ra = 0.5f;
		double degree = pi / 180;
		//Vertexes2[0].pos = Vector3(-0.5f, 0.5f, 0.5f);
		//Vertexes2[0].color = Vector4(1.f, 0.f, 0.f, 1.f);

		//Vertexes2[1].pos = Vector3(0.5f, 0.5f, 0.5f);
		//Vertexes2[1].color = Vector4(0.f, 1.f, 0.f, 1.f);

		//Vertexes2[2].pos = Vector3(0.5f, -0.5f, 0.5f);
		//Vertexes2[2].color = Vector4(0.f, 0.f, 1.f, 1.f);

		//Vertexes2[3].pos = Vector3(-0.5f, -0.5f, 0.5f);
		//Vertexes2[3].color = Vector4(0.f, 0.f, 0.f, 1.f);

		// 1사분면
		vCircle[0].pos = Vector3(0.f, 0.f, 0.0f);
		vCircle[0].color = Vector4(0.1f, 0.f, 0.f, 1.f);

		for (int i = 1; i < 90; i++)
		{
			vCircle[i].pos = Vector3((float)cos(i * degree) * ra, (float)sin(i * degree)* ra, 0.0f);
			vCircle[i].color = Vector4(0.1f*i, 0.f, 0.f, 1.f);
		}
		// 2사분면
		for (int i = 0; i < 90; i++)
		{
			vCircle[i+90].pos = Vector3(-(float)cos((90 - i) * degree) * ra, (float)sin((90-i) * degree) * ra, 0.0f);
			vCircle[i+90].color = Vector4(0.f, 0.1f * i, 0.f, 1.f);
		}
		// 3사분면
		for (int i = 0; i < 90; i++)
		{
			vCircle[i+180].pos = Vector3(-(float)cos(i * degree) * ra, -((float)sin(i * degree) * ra), 0.0f);
			vCircle[i+180].color = Vector4(0.f, 0.f, 0.1f * i, 1.f);
		}
		// 4사분면
		for (int i = 0; i < 90; i++)
		{
			vCircle[i+270].pos = Vector3((float)cos((90 - i) * degree) * ra, -((float)sin((90-i) * degree) * ra), 0.0f);
			vCircle[i+270].color = Vector4(0.1f * i, 0.f, 0.f, 1.f);
		}

		//// 1사분면
		//for (int i = 0; i < 90; i++)
		//{
		//	vCircle[i].pos = Vector3((ra * ((double)(90 - i) / (double)90)), (ra * ((double)(i) / (double)90)), 0.0f);
		//	vCircle[i].color = Vector4(0.1f * i, 0.f, 0.f, 1.f);
		//}
		//// 2사분면
		//for (int i = 0; i < 90; i++)
		//{
		//	vCircle[i + 90].pos = Vector3(-(ra * ((double)(i) / (double)90)), (ra * ((double)(90 - i) / (double)90)), 0.0f);
		//	vCircle[i + 90].color = Vector4(0.1f * i, 0.f, 0.f, 1.f);
		//}
		//// 3사분면
		//for (int i = 0; i < 90; i++)
		//{
		//	vCircle[i + 180].pos = Vector3(-(ra * ((double)(90 - i) / (double)90)), -(ra * ((double)(i) / (double)90)), 0.0f);
		//	vCircle[i + 180].color = Vector4(0.1f * i, 0.f, 0.f, 1.f);
		//}
		//// 4사분면
		//for (int i = 0; i < 90; i++)
		//{
		//	vCircle[i + 270].pos = Vector3((ra * ((double)(i) / (double)90)), -(ra * ((double)(90 - i) / (double)90)), 0.0f);
		//	vCircle[i + 270].color = Vector4(0.1f * i, 0.f, 0.f, 1.f);
		//} // 마름모가 된다... 같은 비율료 x 와 y 가 달라지면 직선이 되지...

		SetupState();
		LoadBuffer();
		LoadShader();
	}
}

