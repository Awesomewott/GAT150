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


	int main(int, char**)
	{
		
		engine.Startup();

		nc::ObjectFactory::Instance().Initialize();
		
		nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);

		scene.Create(&engine);

		rapidjson::Document document;
		nc::json::Load("Scene.txt", document);
		scene.Create(&engine);
		scene.Read(document);

		for (size_t i = 0; i < 10; i++)
		{
			nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoBox");
			gameObject->m_transform.position = { nc::random(0, 800), nc::random(0, 300) };
			gameObject->m_transform.angle = nc::random(0, 360);

			scene.AddGameObject(gameObject);
		}

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




