#pragma once
#include "CResource.h"
#include "CGraphicDevice_Dx11.h"

namespace sh
{
	using namespace graphics;

	class CShader : public CResource
	{
	private:
		ID3D11InputLayout* mInputLayout;

		Microsoft::WRL::ComPtr<ID3DBlob> mVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mHSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mDSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mGSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mPSBlob;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVS;
		Microsoft::WRL::ComPtr<ID3D11HullShader> mHS;
		Microsoft::WRL::ComPtr<ID3D11DomainShader> mDS;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPS;
	public:
		CShader();
		~CShader();

		virtual HRESULT Load(const std::wstring& path) override;
		bool Create(const eShaderStage _stage, const std::wstring& fileName, const std::string& funcName);
		void Binds(D3D11_PRIMITIVE_TOPOLOGY mTopology);

		ID3DBlob* GetVSCode()
		{
			return mVSBlob.Get();
		}
		ID3D11InputLayout* GetInputLayout()
		{
			return mInputLayout;
		}
		ID3D11InputLayout** GetInputLayoutAddressof()
		{
			return &mInputLayout;
		}
	};
}


