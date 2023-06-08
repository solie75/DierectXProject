#include "CMesh.h"
#include "CREnderer.h"

namespace sh
{
	CMesh::CMesh()
		: mVertexBuffer(nullptr)
		, mIndexBuffer(nullptr)
		, mVBDesc{}
		, mIBDesc{}
		, mIndexCount(0)
	{

	}

	CMesh::~CMesh()
	{
	}

	HRESULT CMesh::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	bool CMesh::CreateVertexBuffer(void* _data, UINT _count)
	{
		mIndexCount = _count;
		mVBDesc.ByteWidth = sizeof(render::Vertex) * _count;
		mVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		mVBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mVBDesc.CPUAccessFlags = 0; // NONE

		D3D11_SUBRESOURCE_DATA sub = {};
		sub.pSysMem = _data;

		if (!GetDevice()->CreateBuffer(mVertexBuffer.GetAddressOf(), &mVBDesc, &sub))
		{
			return false;
		}

		return true;
	}

	bool CMesh::CreateIndexBuffer(void* _data, UINT _count)
	{
		mIndexCount = _count;
		mIBDesc.ByteWidth = sizeof(UINT) * _count;
		mIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		mIBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mIBDesc.CPUAccessFlags = 0; // NONE

		D3D11_SUBRESOURCE_DATA sub = {};
		sub.pSysMem = _data;

		if (!GetDevice()->CreateBuffer(mIndexBuffer.GetAddressOf(), &mIBDesc, &sub))
		{
			return false;
		}

		return true;
	}

	void CMesh::BindBuffer()
	{
		UINT stride = sizeof(render::Vertex);
		UINT offset = 0;

		GetDevice()->BindVertexBuffer(0, mVertexBuffer.GetAddressOf(), &stride, &offset);
		GetDevice()->BindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

}

