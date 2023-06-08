#include "CRenderer.h"
#include "CInput.h"

namespace render
{
	//Vertex Vertexes1[3] = {};
	Vertex vertexes[4] = {};
	//Vertex vCircle[360] = {};

	sh::CMesh* mesh = nullptr;
	sh::CShader* shader = nullptr;

	//ID3D11Buffer* triangleBuffer = nullptr;

	//ID3DBlob* errorBlob = nullptr;

	//ID3DBlob* triangleVSBlob = nullptr;

	//ID3D11VertexShader* triangleVSShader = nullptr;

	//ID3DBlob* trianglePSBlob = nullptr;

	//ID3D11PixelShader* trianglePSShader = nullptr;

	//ID3D11InputLayout* triangleLayout = nullptr;

	//ID3D11Buffer* indexBuffer = nullptr;

	sh::graphics::CConstantBuffer* constantBuffer = nullptr;

	//UINT circleIndex[1080] = {}; // 1-0-2, 1-0-3, 2-0-4, 3-0-5, ..., 358-0-360, 359-0-1

	void SetupState()
	{
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

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

		sh::graphics::GetDevice()->CreateInputLayout(arrLayout, 2, shader->GetVSCode(), shader->GetInputLayoutAddressof());
	}

	void LoadBuffer()
	{
		// vertexBuffer
		mesh = new sh::CMesh();
		mesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes = {};

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		//Constant Buffer
		constantBuffer = new sh::graphics::CConstantBuffer(eCBType::Transform);
		constantBuffer->Create(sizeof(Vector4));

		Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f);
		constantBuffer->SetData(&pos);
		constantBuffer->Bind(eShaderStage::VS);
	}

	void LoadShader()
	{
		shader = new sh::CShader();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
	}

	void Initialize()
	{
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		LoadBuffer();
		LoadShader();
		SetupState();
	}

	void Update()
	{
		/*float mSpeed = 0.01f;

		if (sh::CInput::GetKeyState(sh::eKeyCode::RIGHT) == sh::eKeyState::Pressed)
		{
			vertexes[0].pos.x += mSpeed;
			vertexes[1].pos.x += mSpeed;
			vertexes[2].pos.x += mSpeed;
			vertexes[3].pos.x += mSpeed;
		}
		if (sh::CInput::GetKeyState(sh::eKeyCode::LEFT) == sh::eKeyState::Pressed)
		{
			vertexes[0].pos.x -= mSpeed;
			vertexes[1].pos.x -= mSpeed;
			vertexes[2].pos.x -= mSpeed;
			vertexes[3].pos.x -= mSpeed;
		}
		if (sh::CInput::GetKeyState(sh::eKeyCode::UP) == sh::eKeyState::Pressed)
		{
			vertexes[0].pos.y += mSpeed;
			vertexes[1].pos.y += mSpeed;
			vertexes[2].pos.y += mSpeed;
			vertexes[3].pos.y += mSpeed;
		}
		if (sh::CInput::GetKeyState(sh::eKeyCode::DOWN) == sh::eKeyState::Pressed)
		{
			vertexes[0].pos.y -= mSpeed;
			vertexes[1].pos.y -= mSpeed;
			vertexes[2].pos.y -= mSpeed;
			vertexes[3].pos.y -= mSpeed;
		}
		LoadBuffer();*/
	}
	void Release()
	{
		delete mesh;
		delete shader;
		delete constantBuffer;
	}
}

