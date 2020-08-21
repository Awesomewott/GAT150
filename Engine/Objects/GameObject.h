#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Engine.h"
#include "Core/Json.h"

namespace nc
{
	class Component;

	class GameObject : public Object
	{
	public:
		// Inherited via Object
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() const override { return new GameObject{*this}; }

		void Read(const rapidjson::Value& value) override;

		void Update();
		void Draw();

		template<typename T>
		T* GetComponent();
	
		void AddComponent(Component* component);
		void ReadComponents(const rapidjson::Value& value);
		void RemoveComponent(Component* component);
		void RemoveAllObjects();

	public:
		Transform m_transform;
		Engine* m_engine{nullptr};
		std::string m_name;

	protected:
		std::vector<Component*> m_components;
	};

	template<typename T>
	T* GameObject::GetComponent()
	{
		T* result{ nullptr };

		for (auto component : m_components)
		{
			result = dynamic_cast<T*>(component);
			if (result) break;
		}
		return result;
	}
}
