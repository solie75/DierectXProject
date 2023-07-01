#pragma once
#include "CScene.h"

namespace sh
{
	class CSceneManager
	{
	private:
		static CScene* mActiveScene;
		static std::map<std::wstring, CScene*> mScenes;
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		static CScene* GetActiveScene() { return mActiveScene; }
		static CScene* LoadScene(std::wstring name);

		template <typename T>
		static bool CreateScene(std::wstring name)
		{
			T* scene = new T();

			std::map<std::wstring, CScene*>::iterator iter = mScenes.find(name);

			if (iter != mScenes.end())
			{
				return false;
			}

			mScenes.insert(std::make_pair(name, scene));
			mActiveScene = scene;
			scene->Initialize();
			return true;
		}
	};
}


