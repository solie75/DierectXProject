#pragma once
#include "CResource.h"
#include "CGraphicDevice_Dx11.h"

namespace sh
{
	using namespace graphics;

	class CMesh : public CResource
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;

		D3D11_BUFFER_DESC mVBDesc;
		D3D11_BUFFER_DESC mIBDesc;

		UINT mIndexCount;

	public:
		CMesh();
		~CMesh();

		virtual HRESULT Load(const std::wstring& path) override;

		bool CreateVertexBuffer(void* _data, UINT _count);
		bool CreateIndexBuffer(void* _data, UINT _count);

		void BindBuffer();

		UINT GetIndexCount() { return mIndexCount; }
	};
}


