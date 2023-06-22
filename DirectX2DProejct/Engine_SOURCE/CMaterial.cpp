#include "CMaterial.h"

namespace sh::graphics
{
	CMaterial::CMaterial()
		: CResource(sh::enums::eResourceType::Material)
		, mShader(nullptr)
		, mTexture(nullptr)
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
		mTexture->BindShader(eShaderStage::PS, 0);
		mShader->Binds();
	}
}