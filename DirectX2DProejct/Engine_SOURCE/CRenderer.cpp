#include "CRenderer.h"
//#include "CInput.h"
#include "CResources.h"
#include "CTexture.h"
#include "CMaterial.h"

namespace render
{
	using namespace sh;
	using namespace sh::graphics;

	Vertex Vertexes[4] = {};

	//sh::CMesh* RectangleMesh = nullptr;

	//sh::CShader* shader = nullptr;

	//sh::graphics::CConstantBuffer* constantBuffer = nullptr;

	sh::graphics::CConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};

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

		//sh::graphics::GetDevice()->CreateInputLayout(arrLayout, 3, shader->GetVSCode(), shader->GetInputLayoutAddressof());
	
		/*CShader* shader = sh::CResources::Find<CShader>(L"TriangleShader");
		sh::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());*/

		std::shared_ptr<CShader> shader = sh::CResources::Find<CShader>(L"SpriteShader");
		sh::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

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
		//RectangleMesh = new sh::CMesh();
		//RectangleMesh->CreateVertexBuffer(Vertexes, 4);

		std::shared_ptr<CMesh> mesh = std::make_shared<CMesh>();
		CResources::Insert(L"RectMesh", mesh);
		mesh->CreateVertexBuffer(Vertexes, 4);

		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());


		constantBuffer[(UINT)eCBType::Transform] = new CConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

	}

	void LoadShader()
	{
		//shader = new sh::CShader();
		/*CShader* shader = new sh::CShader();
		shader->Create(eShaderStage::VS, L"VS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"PS.hlsl", "main");
		CResources::Insert(L"TriangleShader", shader);*/



		std::shared_ptr<CShader> spriteShader = std::make_shared<CShader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		CResources::Insert(L"SpriteShader", spriteShader);
		
		std::shared_ptr<CTexture> texture 
			= CResources::Load<CTexture>(L"Link", L"..\\Resources\\Texture\\Link.png");

		std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
		spriteMaterial->SetShader(spriteShader); // Material 에 shader 를 저장하면서 왜 위에서 spriteShader 를 따로 insert 하고 있지?
		spriteMaterial->SetTexture(texture);
		CResources::Insert(L"SpriteMaterial", spriteMaterial);

		texture->BindShader(eShaderStage::PS, 0);
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

		//std::shared_ptr<CTexture> texture = CResources::Load<CTexture>(L"Link", L"..\\Resources\\Texture\\Link.png");
		
	}

	//void Update()
	//{
	//}
	void Release()
	{
		/*delete mesh;
		delete shader;
		delete constantBuffer;*/

		for (CConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;
			
			delete buff;
			buff = nullptr;
		}
	}
}