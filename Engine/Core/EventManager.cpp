#include "pch.h"
#include "EventManager.h"

namespace nc
{

	void nc::EventManager::Subscribe(const std::string& type, function_t function, Object* owner)
	{
		Observer observer;
		observer.function = function;
		observer.owner = owner;

		M_observers[type].push_back(observer);
		//hello
	}

	void nc::EventManager::Notify(const Event& event)
	{
		auto observers = M_observers[event.type];
		for (auto& observer : observers)
		{
			// send to all, send to receiver -> owner
			if (event.recevier == nullptr || event.recevier == observer.owner)
			{
				observer.function(event);
			}
		}
	}
}
