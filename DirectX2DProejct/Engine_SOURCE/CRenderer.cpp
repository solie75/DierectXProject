#include "CRenderer.h"
//#include "CInput.h"
#include "CResources.h"
#include "CTexture.h"

namespace render
{
	using namespace sh;
	using namespace sh::graphics;

	Vertex Vertexes[4] = {};

	sh::CMesh* RectangleMesh = nullptr;

	sh::CShader* shader = nullptr;

	sh::graphics::CConstantBuffer* constantBuffer = nullptr;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};

	void SetupState()
	{
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		sh::graphics::GetDevice()->CreateInputLayout(arrLayout, 3, shader->GetVSCode(), shader->GetInputLayoutAddressof());
	
		// Sampler State
		D3D11_SAMPLER_DESC desc = {};
		desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSampler(&desc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		desc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSampler(&desc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
	}

	void LoadBuffer()
	{
		RectangleMesh = new sh::CMesh();
		RectangleMesh->CreateVertexBuffer(Vertexes, 4);

		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		RectangleMesh->CreateIndexBuffer(indexes.data(), indexes.size());


		constantBuffer = new sh::graphics::CConstantBuffer(eCBType::Transform);
		constantBuffer->Create(sizeof(Transform));

		/*Vector4 pos(0.2f, 0.0f, 0.0f, 1.0f);
		constantBuffer->SetData(&pos);
		constantBuffer->Bind(eShaderStage::VS);*/
	}

	void LoadShader()
	{
		shader = new sh::CShader();
		shader->Create(eShaderStage::VS, L"VS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"PS.hlsl", "main");
	}

	void Initialize()
	{

		Vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		Vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		Vertexes[0].uv = Vector2(0.0f, 0.0f);
		
		Vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		Vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		Vertexes[1].uv = Vector2(1.0f, 0.0f);
		
		Vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		Vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		Vertexes[2].uv = Vector2(1.0f, 1.0f);
		
		Vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		Vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		Vertexes[3].uv = Vector2(0.0f, 1.0f);

		LoadBuffer();
		LoadShader();
		SetupState();

		CTexture* texture
			= CResources::Load<CTexture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		texture = CResources::Load<CTexture>(L"Link", L"..\\Resources\\Texture\\Link.png");
		texture->BindShader(eShaderStage::PS, 0);
	}

	void Update()
	{
	}
	void Release()
	{
		delete RectangleMesh;
		delete shader;
		delete constantBuffer;
	}
}

