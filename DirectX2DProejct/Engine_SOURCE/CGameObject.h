#pragma once
#include "CEntity.h"
#include "CComponent.h"
#include "CScript.h"

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
		std::vector<CScript*> mScripts;

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
			for (CScript* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
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
			CScript* script = dynamic_cast<CScript*>(buff); // �̷��� �Ǹ� ��� ������Ʈ ���� CScript �� �Ǿ� script ������ ����Ǵ°� �ƴѰ�?

			if (buff == nullptr)
			{
				return nullptr;
			}
			if (script == nullptr)
			{
				mComponents.push_back(buff);
			}
			else
			{
				mScripts.push_back(script);
			}
			mComponents.push_back(buff);
			comp->SetOwner(this);

			return comp;
		}
	};
}


