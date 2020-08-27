#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "ObjectFactory.h"

namespace nc
{
	void nc::Scene::Create(void* data)
	{
		m_engine = static_cast<Engine*>(data);
	}

	void nc::Scene::Destroy()
	{
		// call the member function to remove all game objects
		RemoveAllGameObjects();
	}

	void nc::Scene::Read(const rapidjson::Value& value)
	{
		if (value.HasMember("Prototypes"))
		{
			const rapidjson::Value& objectsValue = value["Prototypes"];
			if (objectsValue.IsArray())
			{
				ReadPrototypes(objectsValue);
			}
		}

		if (value.HasMember("GameObjects"))
		{
			const rapidjson::Value& objectsValue = value["GameObjects"];
			if (objectsValue.IsArray())
			{
				ReadGameObjects(objectsValue);
			}
		}
	}

	void Scene::ReadGameObjects(const rapidjson::Value& value)
	{
		for (rapidjson::SizeType i = 0; i < value.Size(); i++)
		{

			const rapidjson::Value& objectValue = value[i];
			if (objectValue.IsObject())
			{
				std::string typeName;
				// read component “type” name from json (get)
				json::Get(objectValue, "type", typeName);
				nc::GameObject* gameobject = ObjectFactory::Instance().Create<GameObject>(typeName);// create from object factory, use typename as the key

				if (gameobject)
				{
					gameobject->Create(m_engine);
					// call game object read (pass in objectvalue)
					gameobject->Read(objectValue);
					// call addgameobject passing in the game object
					AddGameObject(gameobject);
				}
			}
		}
	}

	void Scene::ReadPrototypes(const rapidjson::Value& value)
	{
		for (rapidjson::SizeType i = 0; i < value.Size(); i++)
		{

			const rapidjson::Value& objectValue = value[i];
			if (objectValue.IsObject())
			{
				std::string typeName;
				// read component “type” name from json (get)
				json::Get(objectValue, "type", typeName);
				nc::GameObject* gameobject = ObjectFactory::Instance().Create<GameObject>(typeName);// create from object factory, use typename as the key

				if (gameobject)
				{
					gameobject->Create(m_engine);
					// call game object read (pass in objectvalue)
					gameobject->Read(objectValue);
					// call addgameobject passing in the game object
					AddGameObject(gameobject);

					ObjectFactory::Instance().Register(gameobject->m_name, new Prototype<Object>(gameobject));
				}
			}
		}
	}

	void nc::Scene::Update()
	{
		// iterate through the actors and call Update on each actor
		//upadate game objects
		for (auto gameObject : m_gameObjects)
		{
			gameObject->Update();
		}
		auto iter = m_gameObjects.begin();
		//remove destroy gameobject
		while (iter != m_gameObjects.end())
		{
			// iter( GameObject* )
			if ((*iter)->m_flags[GameObject::eFlags::DESTROY])
			{
				(*iter)->Destroy();
				delete (*iter);
				iter = m_gameObjects.erase(iter);
			}

			else
			{
				iter++;
			}
		}
	}

	void nc::Scene::Draw()
	{
		// iterate through the actors and call Draw on each actor
		for (auto gameObject : m_gameObjects)
		{
			// draw
			gameObject->Draw();
		}
	}

	GameObject* nc::Scene::Find(const std::string& name)
	{
		for (auto gameObject : m_gameObjects)
		{
			// compare game object name to name parameter (==)
			if(gameObject->m_name == name)
			{
				return gameObject;
			}
		}
		return nullptr;
	}

	std::vector<GameObject*> Scene::FindGameObjectWithTag(const std::string& tag)
	{
		std::vector<GameObject*> gameobjects;

		for (auto gameObject : m_gameObjects)
		{
			// compare game object name to name parameter (==)
			if (gameObject->m_tag == tag)
			{
				gameobjects.push_back(gameObject);
			}
		}

		return gameobjects;
	}

	void nc::Scene::AddGameObject(GameObject* gameObject)
	{
		// push back gameObject
		m_gameObjects.push_back(gameObject);
	}

	void nc::Scene::RemoveGameObject(GameObject* gameObject)
	{
		auto iter = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
		if (iter != m_gameObjects.end())
		{
			// destroy (*iter)->
			// delete 
			// erase iter from m_gameObjects
			(*iter)->Destroy();
			delete (*iter);
			m_gameObjects.erase(iter);
			//???
		}

	}

	void nc::Scene::RemoveAllGameObjects()
	{
		for (GameObject* gameObject : m_gameObjects)
		{
			// destroy
			// delete
			gameObject->Destroy();
			delete gameObject;
		}

		m_gameObjects.clear();
		// clear game objects

	}
}
