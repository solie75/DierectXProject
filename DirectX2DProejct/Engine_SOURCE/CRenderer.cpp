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

	std::vector<sh::CCamera*> cameras = {};

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
		mesh->CreateIndexBuffer(indexes.data(), (UINT)indexes.size());


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
		/*{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Link", L"..\\Resources\\Texture\\Link.png");

			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader); 
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_Link", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"dokgak", L"..\\Resources\\Texture\\dokgak.png");

			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader); 
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_dokgak", spriteMaterial);
		}{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"spriteMaterial_Smile", spriteMaterial);
		}*/


		// will
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Will", L"..\\Resources\\Texture\\Will.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_Will", spriteMaterial);
		}
		// UI
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"UI_Base_Circle", L"..\\Resources\\Texture\\UI_Base_Circle.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_Cash_UI_Base_Circle", spriteMaterial);
			CResources::Insert(L"SpriteMaterial_Weapon_UI_Base_Circle", spriteMaterial);
			CResources::Insert(L"SpriteMaterial_Inventory_UI_Base_Circle", spriteMaterial);
		}


		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Bag", L"..\\Resources\\Texture\\Bag.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_Bag_UI", spriteMaterial);
		}



		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Health_UI_Circle", L"..\\Resources\\Texture\\HealthBar_Circle.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_Health_UI_Circle", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"HealthBar_UI_Base", L"..\\Resources\\Texture\\HealthBar_Base.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_HealthBar_UI_Base", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Gold4", L"..\\Resources\\Texture\\Gold4.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_Gold4", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Health_Icon", L"..\\Resources\\Texture\\Health_Icon.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_Health_Icon", spriteMaterial);
		}

		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"HUD_Set1", L"..\\Resources\\Texture\\HUD_Set1.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_HUD_Set1", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"HUD_Set2", L"..\\Resources\\Texture\\HUD_Set2.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_HUD_Set2", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"YesNo_Circle", L"..\\Resources\\Texture\\YesNo_Circle.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_YesNo_Circle", spriteMaterial);
		}

		
		// main menu
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Start_Intro_Door_Left", L"..\\Resources\\Texture\\Start_Intro_Door_Left.png");

			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader); 
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"spriteMaterial_Start_Intro_Door_Left", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Start_Intro_Door_Right", L"..\\Resources\\Texture\\Start_Intro_Door_Right.png");

			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"spriteMaterial_Start_Intro_Door_Right", spriteMaterial);
		}
		// shop
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Shop_Background", L"..\\Resources\\Texture\\Shop_Background.png");

			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"spriteMaterial_Shop_Background", spriteMaterial);
		}
		// village
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Backgraound", L"..\\Resources\\Texture\\Village_Background.png");

			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"spriteMaterial_Village_Background", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"WillsHome", L"..\\Resources\\Texture\\WillsHome.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader); 
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_WillsHome", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_House_01", L"..\\Resources\\Texture\\Village_House_01.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_House_01", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Blacksmith_House_old", L"..\\Resources\\Texture\\Village_Blacksmith_House_old.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_Blacksmith_House_old", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Blacksmith_Roof_old", L"..\\Resources\\Texture\\Village_Blacksmith_Roof_old.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_Blacksmith_Roof_old", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Blacksmith_Stand1_old", L"..\\Resources\\Texture\\Village_Blacksmith_Stand1_old.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_Blacksmith_Stand1_old", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Blacksmith_Stand2_old", L"..\\Resources\\Texture\\Village_Blacksmith_Stand2_old.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_Village_Blacksmith_Stand2_old", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Blacksmith_Fence", L"..\\Resources\\Texture\\Village_Blacksmith_Fence.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_Blacksmith_Fence", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_House_06", L"..\\Resources\\Texture\\Village_House_06.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_House_06", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_House_05", L"..\\Resources\\Texture\\Village_House_05.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_House_05", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_House_02", L"..\\Resources\\Texture\\Village_House_02.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_House_02", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Awning", L"..\\Resources\\Texture\\Village_Awning.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_Awning", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Board", L"..\\Resources\\Texture\\Village_Board.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_Board", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Fence_Column", L"..\\Resources\\Texture\\Village_Fence_Column.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_Village_Fence_Column", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Fence_Row", L"..\\Resources\\Texture\\Village_Fence_Row.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_Village_Fence_Row", spriteMaterial);
		}
		// witch
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Witch_House_old", L"..\\Resources\\Texture\\Village_Witch_House_old.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_Witch_House_old", spriteMaterial);
		} 
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Witch_Roof_old", L"..\\Resources\\Texture\\Village_Witch_Roof_old.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			CResources::Insert(L"SpriteMaterial_Village_Witch_Roof_old", spriteMaterial);
		} 
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Witch_Table_old", L"..\\Resources\\Texture\\Village_Witch_Table_old.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_Witch_Table_old", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Witch_Storage_old", L"..\\Resources\\Texture\\Village_Witch_Storage_old.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_Witch_Storage_old", spriteMaterial);
		}
		//rival
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Rival_House_old", L"..\\Resources\\Texture\\Village_Rival_House_old.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_Rival_House_old", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Rival_Roof_old", L"..\\Resources\\Texture\\Village_Rival_Roof_old.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_Rival_Roof_old", spriteMaterial);
		}
		{
			std::shared_ptr<CTexture> texture
				= CResources::Load<CTexture>(L"Village_Rival_Fountain_old", L"..\\Resources\\Texture\\Village_Rival_Fountain_old.png");
			std::shared_ptr<CMaterial> spriteMaterial = std::make_shared<CMaterial>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRenderingMode(eRenderingMode::Opaque);
			CResources::Insert(L"SpriteMaterial_Village_Rival_Fountain_old", spriteMaterial);
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

	void Render()
	{
		for (CCamera* cam : cameras)
		{
			if (cam == nullptr)
			{
				continue;
			}

			cam->Render();
		}

		cameras.clear(); // 왜 clear 해주는 거지?
	}

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