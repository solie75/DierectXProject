#include "CMaterial.h"

namespace sh::graphics
{
	CMaterial::CMaterial()
		: CResource(sh::enums::eResourceType::Material)
		, mShader(nullptr)
		, mTexture(nullptr)
		, mRenderingMode(eRenderingMode::Opaque)
	{
	}
	CMaterial::~CMaterial()
	{
	}
	HRESULT CMaterial::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	void CMaterial::Binds()
	{
		if (mTexture)
		{
			mTexture->BindShader(eShaderStage::PS, 0);
		}
		if (mShader)
		{
			mShader->Binds();
		}
		
	}
	void CMaterial::Clear()
	{
		mTexture->Clear();
	}
}