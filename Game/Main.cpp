#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Objects/Scene.h"
#include "Core/Json.h"
#include "Core/Factory.h"
#include "Core/EventManager.h"
#include "Objects/ObjectFactory.h"
#include "Components/PlayerComponent.h"
#include "Components/EnemyComponent.h"
#include "Components/Component.h"
#include "Source Files/TileMap.h"

nc::Engine engine;
nc::Scene scene;
nc::TileMap tileMap;
using namespace nc;

void OnPlayerDead(const Event& event)
{
	int* pdata = static_cast<int*>(event.data);
	int score = *pdata;

	std::cout << "Player Dead\n" << score << std::endl;
}


	int main(int, char**)
	{
		
		engine.Startup();

		nc::ObjectFactory::Instance().Initialize();
		nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);
		nc::ObjectFactory::Instance().Register("EnemyComponent", new nc::Creator<nc::EnemyComponent, nc::Object>);

		nc::EventManager::Instance().Subscribe("PlayerDead", &OnPlayerDead);

		scene.Create(&engine);

		rapidjson::Document document;
		nc::json::Load("Scene.txt", document);
		scene.Read(document);

		nc::json::Load("TileMap.txt", document);
		tileMap.Read(document);
		tileMap.Create(&scene);
		//for (size_t i = 0; i < 10; i++)
		//{
		//	nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoCoin");
		//	gameObject->m_transform.position = { nc::random(0, 800), nc::random(300, 450) };
			//gameObject->m_transform.angle = nc::random(0, 360);

		//	scene.AddGameObject(gameObject);
		//}

		SDL_Event event;
		bool quit = false;
		while (!quit)
		{

			SDL_PollEvent(&event);
			switch (event.type)
			{
			case SDL_QUIT:
			quit = true;
			break;
			}
		
			//Update
			engine.Update();
			scene.Update();

			if (engine.GetSystem<InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
			{
				quit = true;
			}

			// draw
			engine.GetSystem<nc::Renderer>()->BeginFrame();

			scene.Draw();

			engine.GetSystem<nc::Renderer>()->EndFrame();
			
		}
		scene.Destroy();
		engine.ShutDown();
		
		return 0;

	}




