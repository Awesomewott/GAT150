#include "pch.h"
#include "ContactListener.h"
#include "Objects/GameObject.h"

void nc::ContactListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (fixtureA->GetUserData() && fixtureB->GetUserData())
	{
		GameObject* gameobjectA = static_cast<GameObject*>(fixtureA->GetUserData());
		GameObject* gameobjectB = static_cast<GameObject*>(fixtureB->GetUserData());

		gameobjectA->BeginContact(gameobjectB);
		gameobjectB->BeginContact(gameobjectA);
	}
}

void nc::ContactListener::EndContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (fixtureA->GetUserData() && fixtureB->GetUserData())
	{
		GameObject* gameobjectA = static_cast<GameObject*>(fixtureA->GetUserData());
		GameObject* gameobjectB = static_cast<GameObject*>(fixtureB->GetUserData());

		gameobjectA->EndContact(gameobjectB);
		gameobjectB->EndContact(gameobjectA);
	}
}
