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

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	void SetupState()
	{
#pragma region InputLayaout
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
#pragma endregion
#pragma region SamplerState
		D3D11_SAMPLER_DESC samplerDecs = {};
		samplerDecs.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDecs.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDecs.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDecs.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(&samplerDecs, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		samplerDecs.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&samplerDecs, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region RasterizerState
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizerState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizerState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizerState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizerState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::WireFrameNone].GetAddressOf());
#pragma endregion
#pragma region DepthStencilState
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		// Less
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

		// Greater
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		// No Write
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		// None
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion
#pragma region BlendState
		D3D11_BLEND_DESC blendDesc = {};

		blendStates[(UINT)eBSType::Default] = nullptr;

		// Alpha Blend
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		// one one
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;

		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::OneOne].GetAddressOf());
#pragma endregion
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
		
		//std::shared_ptr<CTexture> texture 
		//	= CResources::Load<CTexture>(L"Link", L"..\\Resources\\Texture\\Link.png");
		{
			std::shared_ptr<CTexture> texture1
				= CResources::Load<CTexture>(L"Start_Intro_Door_Left", L"..\\Resources\\Texture\\Start_Intro_Door_Left.png");

			std::shared_ptr<CMaterial> spriteMaterial1 = std::make_shared<CMaterial>();
			spriteMaterial1->SetShader(spriteShader); // Material 에 shader 를 저장하면서 왜 위에서 spriteShader 를 따로 insert 하고 있지?
			spriteMaterial1->SetTexture(texture1);
			CResources::Insert(L"SpriteMaterial1", spriteMaterial1);

			texture1->BindShader(eShaderStage::PS, 0);
		}
		{
			std::shared_ptr<CTexture> texture2
				= CResources::Load<CTexture>(L"Start_Intro_Door_Right", L"..\\Resources\\Texture\\Start_Intro_Door_Right.png");

			std::shared_ptr<CMaterial> spriteMaterial2 = std::make_shared<CMaterial>();
			spriteMaterial2->SetShader(spriteShader); // Material 에 shader 를 저장하면서 왜 위에서 spriteShader 를 따로 insert 하고 있지?
			spriteMaterial2->SetTexture(texture2);
			CResources::Insert(L"SpriteMaterial2", spriteMaterial2);
			texture2->BindShader(eShaderStage::PS, 0);
		}
		{
			std::shared_ptr<CTexture> texture3
				= CResources::Load<CTexture>(L"Village_Backgraound", L"..\\Resources\\Texture\\Village_Background.png");

			std::shared_ptr<CMaterial> spriteMaterial3 = std::make_shared<CMaterial>();
			spriteMaterial3->SetShader(spriteShader); // Material 에 shader 를 저장하면서 왜 위에서 spriteShader 를 따로 insert 하고 있지?
			spriteMaterial3->SetTexture(texture3);
			CResources::Insert(L"SpriteMaterial3", spriteMaterial3);
			texture3->BindShader(eShaderStage::PS, 0);
		}
		{
			std::shared_ptr<CTexture> texture4
				= CResources::Load<CTexture>(L"Shop_Background", L"..\\Resources\\Texture\\Shop_Background.png");

			std::shared_ptr<CMaterial> spriteMaterial4 = std::make_shared<CMaterial>();
			spriteMaterial4->SetShader(spriteShader); // Material 에 shader 를 저장하면서 왜 위에서 spriteShader 를 따로 insert 하고 있지?
			spriteMaterial4->SetTexture(texture4);
			CResources::Insert(L"SpriteMaterial4", spriteMaterial4);
			texture4->BindShader(eShaderStage::PS, 0);
		}
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