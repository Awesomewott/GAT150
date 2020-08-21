#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Objects/Scene.h"
#include "Core/Json.h"
#include "Core/Factory.h"
#include "Objects/ObjectFactory.h"
#include "Components/PlayerComponent.h"
#include "Components/Component.h"




nc::Engine engine;
nc::Scene scene;


using namespace nc;

	//using clock = std::chrono::high_resolution_clock;
	//using clock_duration = std::chrono::duration < clock::rep, std::nano> ;
	int main(int, char**)
	{
		//nc::Timer timer;
		//nc::clock::time_point start = nc::clock::now();
		//for (size_t i = 0; i < 100; i++) { std::sqrt(rand() % 100); }
		//nc::clock_duration duration = nc::clock::now() - start;
		//std::cout << timer.ElapsedTicks() << std::endl;
		//std::cout << timer.ElapsedSeconds() << std::endl;
		// 0 <-> 1.0 (0 <-> 1000000000

		engine.Startup();

		nc::ObjectFactory::Instance().Initialize();
		
		nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);

		//nc::GameObject* player = nc::ObjectFactory::Instance().Create<nc::GameObject>("GameObject");
		//player->Create(&engine);
	    //player.m_transform.position = { 400, 300 };
		//player.m_transform.angle = 45;

		/*
		rapidjson::Document document;
		nc::json::Load("player.txt", document);
		player->Read(document);
		*/

		scene.Create(&engine);

		rapidjson::Document document;
		nc::json::Load("Scene.txt", document);
		scene.Read(document);

		for (size_t i = 0; i < 10; i++)
		{
			nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create < nc::GameObject>("ProtoExplosion");
			gameObject->m_transform.position = { nc::random(0, 800), nc::random(0,600)};
			gameObject->m_transform.angle = nc::random(400, 300);
		}


		/*nc::Component* component;
		component = nc::ObjectFactory::Instance().Create<nc::Component>("PhysicsComponent");
		component->Create(player);
		player->AddComponent(component);

		component = nc::ObjectFactory::Instance().Create<nc::Component>("PlayerComponent");
		component->Create(player);
		player->AddComponent(component);

		component = nc::ObjectFactory::Instance().Create<nc::Component>("SpriteComponent");
		player->AddComponent(component);
		nc::json::Load("sprite.txt", document);
		component->Create(player);
		component->Read(document);*/


		/*std::string str;
		nc::json::Get(document, "string", str);
		std::cout << str << std::endl;

		bool b;
		nc::json::Get(document, "bool", b);
		std::cout << b << std::endl;

		int i1;
		nc::json::Get(document, "integer1", i1);
		std::cout << i1 << std::endl;

		int i2;
		nc::json::Get(document, "integer2", i2);
		std::cout << i2 << std::endl;

		float f;
		nc::json::Get(document, "float", f);
		std::cout << f << std::endl;

		nc::Vector2 v2;
		nc::json::Get(document, "vector2", v2);
		std::cout << v2 << std::endl;

		nc::Color color;
		nc::json::Get(document, "color", color);
		std::cout << color << std::endl;*/

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
//}



