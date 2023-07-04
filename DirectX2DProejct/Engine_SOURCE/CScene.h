#pragma once
#include "CEntity.h"
#include "CLayer.h"

namespace sh
{
	class CScene : public CEntity
	{

	private:
		std::vector<CLayer> mLayers;
	public:
		CScene();
		virtual ~CScene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(sh::enums::eLayerType type, CGameObject* gameObj, const std::wstring& name);

		/*template <typename T>
		std::vector<T*> FindObjectsOfType()
		{
			std::vector<T*> findObjs = {};
			for (Layer* layer : mLayers)
			{
				auto gameObjs = layer->GetGameObjects();
				for (CGameObject* obj : gameObjs)
				{
					T* buff = dynamic_cast<T*>(obj);
					if (buff != nullptr)
					{
						findObjs.push_back(buff);
					}
				}
			}
			return findObjs;
		}*/
		CLayer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }
	};
}
