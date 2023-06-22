#pragma once
#include "CResource.h"

namespace sh
{
	class CResources
	{
	private:
		static std::map<std::wstring, std::shared_ptr<CResource>> mResources;

	public:
		template <typename T>
		static std::shared_ptr<T> Find(const std::wstring& key)
		{
			std::map<std::wstring, std::shared_ptr<CResource>>::iterator iter = mResources.find(key);

			if (iter != mResources.end())
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}
			return nullptr;
		}

		template <typename T>
		static std::shared_ptr<T> Load(const std::wstring& key, const std::wstring& path)
		{
			std::shared_ptr<T> resource = CResources::Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			resource = std::make_shared<T>();
			if (FAILED(resource->Load(path)))
			{
				assert(false);
				return nullptr;
			}

			resource->SetKey(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return std::dynamic_pointer_cast<T>(resource);
		}

		template <typename T>
		static void Insert(const std::wstring& key, std::shared_ptr<T> resource)
		{
			mResources.insert(std::make_pair(key, resource));
		}

		/*static void Release() // shared ptr �� �����Ǿ��� ������ Release �� ���� ������ �ʿ䰡 ����.
		{
			for (auto pair : mResources)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}*/
	};
}


