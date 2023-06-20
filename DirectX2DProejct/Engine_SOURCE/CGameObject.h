#pragma once
#include "CEntity.h"
#include "CComponent.h"

namespace sh
{
	enum eState
	{
		Active,
		Paused,
		Dead,
	};

	class CGameObject : public CEntity
	{
	private:
		eState mState;
		std::vector<Component*> mComponents;

	public:
		CGameObject();
		virtual ~CGameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		//render::Transform transform;

		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
				{
					return component;
				}
			}
			return nullptr;
		}

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			Component* buff = dynamic_cast<Component*>(comp);
			if (buff == nullptr)
			{
				return nullptr;
			}
			mComponents.push_back(buff);
			comp->SetOwner(this);

			return comp;
		}
	};
}


