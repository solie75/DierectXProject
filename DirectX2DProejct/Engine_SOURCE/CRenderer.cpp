#include "CRenderer.h"
#include "CInput.h"

namespace render
{
	Vertex cellVertexes[360] = {};
	Vertex wallVertexes[4] = {};

	sh::CMesh* cellMesh = nullptr;
	sh::CMesh* wallMesh = nullptr;

	sh::CShader* shader = nullptr;

	sh::graphics::CConstantBuffer* constantBuffer = nullptr;

	Transform transform = {};

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
		cellMesh = new sh::CMesh();
		
		//wallMesh = new sh::CMesh();

		//wallMesh->CreateVertexBuffer(wallVertexes, 4);
		//std::vector<UINT> wallMeshIndexes = {};
		//wallMesh->CreateIndexBuffer(wallMeshIndexes.data(), wallMeshIndexes.size());

		constantBuffer = new sh::graphics::CConstantBuffer(eCBType::Transform);
		constantBuffer->Create(sizeof(Transform));
		Transform trans = Transform{ Vector4(0.0f, 0.0f, 0.0f, 1.f) , Vector4(1.0f, 0.f, 0.f, 0.f), Vector4(0.0f, 0.0f, 0.0f, 1.f) };
		constantBuffer->SetData(&trans);
		constantBuffer->Bind(eShaderStage::VS);
	}

	void LoadShader()
	{
		shader = new sh::CShader();
		shader->Create(eShaderStage::VS, L"VS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"PS.hlsl", "main");
	}

	void Initialize()
	{
		LoadShader();
		LoadBuffer();
		SetupState();
	}

	void Update()
	{
	}
	void Release()
	{
		delete cellMesh;
		delete wallMesh;
		delete shader;
		delete constantBuffer;
	}
}

