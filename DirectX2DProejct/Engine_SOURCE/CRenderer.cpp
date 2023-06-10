#include "CRenderer.h"
#include "CInput.h"

namespace render
{
	Vertex cellVertexes[362] = {};
	Vertex wallVertexes[4] = {};

	sh::CMesh* cellMesh = nullptr;
	sh::CMesh* wallMesh = nullptr;

	sh::CShader* shader = nullptr;

	sh::graphics::CConstantBuffer* constantBuffer = nullptr;
	sh::graphics::CConstantBuffer* FixedPosConstantBuffer = nullptr;

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
		wallMesh = new sh::CMesh();

		constantBuffer = new sh::graphics::CConstantBuffer(eCBType::Transform);
		constantBuffer->Create(sizeof(Transform));
		constantBuffer->Bind(eShaderStage::VS);

		/*FixedPosConstantBuffer = new sh::graphics::CConstantBuffer(eCBType::Transform);
		FixedPosConstantBuffer->Create(sizeof(Transform));
		FixedPosConstantBuffer->Bind(eShaderStage::VS);*/
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

