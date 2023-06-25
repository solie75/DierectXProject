#pragma once
#include "CResource.h"
#include "CShader.h"
#include "CTexture.h"

namespace sh::graphics
{
	class CMaterial :
		public CResource
	{
	private:
		std::shared_ptr<CShader> mShader;
		std::shared_ptr<CTexture> mTexture;

	public:
		CMaterial();
		~CMaterial();

		virtual HRESULT Load(const std::wstring& path) override;

		void Binds();
		void Clear();

		void SetShader(std::shared_ptr<CShader> shader) { mShader = shader; }
		void SetTexture(std::shared_ptr<CTexture> texture) { mTexture = texture; }
	};
}