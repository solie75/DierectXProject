#include "CShader.h"
namespace sh
{
	CShader::CShader()
		: mInputLayout(nullptr)
		, mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	{
	}
	CShader::~CShader()
	{
		mInputLayout->Release();
	}
	HRESULT CShader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	bool CShader::Create(const eShaderStage _stage, const std::wstring& fileName, const std::string& funcName)
	{
		// VS shader °æ·Îs

		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader_SOURCE\\";

		std::filesystem::path fullPath(shaderPath.c_str());
		fullPath += fileName;

		ID3DBlob* errorBlob = nullptr;

		if (_stage == eShaderStage::VS)
		{
			GetDevice()->CompileFromFile(fullPath, funcName, "vs_5_0", mVSBlob.GetAddressOf());
			GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer(), mVSBlob->GetBufferSize(), mVS.GetAddressOf());
		}
		else if (_stage == eShaderStage::PS)
		{
			GetDevice()->CompileFromFile(fullPath, funcName, "ps_5_0", mPSBlob.GetAddressOf());
			GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer(), mPSBlob->GetBufferSize(), mPS.GetAddressOf());
		}

		return true;
	}
	void CShader::Binds()
	{
		GetDevice()->BindPrimitiveTopology(mTopology);
		GetDevice()->BindInputLayout(mInputLayout);
		GetDevice()->BindVertexShader(mVS.Get());
		GetDevice()->BindPixelShader(mPS.Get());
	}
}
