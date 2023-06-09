#pragma once
#include "CEngine.h"

namespace sh
{
	class CResource
	{
	private:
		std::wstring mKey;
		std::wstring mPath;

	public:
		CResource();
		virtual ~CResource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetKey() { return mKey; }
		const std::wstring& GetPath() { return mPath; }

		void SetKey(const std::wstring& key) { mKey = key; }
		void SetPath(const std::wstring& path) { mPath = path; }
	};
}


