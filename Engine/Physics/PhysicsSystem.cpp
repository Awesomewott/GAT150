#include "pch.h"
#include "PhysicsSystem.h"
#include "ContactListener.h"

bool nc::PhysicsSystem::Startup()
{
	b2Vec2 gravity{ 0, 10 };
	m_world = new b2World{ gravity };
	m_contactListener = new ContactListener;
	m_world->SetContactListener(m_contactListener);

	return true;
}

void nc::PhysicsSystem::Shutdown()
{
	delete m_world;
	m_world = nullptr;
	delete m_contactListener;
	m_contactListener = nullptr;
}


void nc::PhysicsSystem::Update()
{
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;
	
	m_world->Step(timeStep, velocityIterations, positionIterations);
}


b2Body* nc::PhysicsSystem::CreateBody(const Vector2& position, float angle, const RigidBodyData& data, GameObject* gameobject)
{
	b2BodyDef bodyDef;

	Vector2 worldPosition = ScreenToWorld(position);

	bodyDef.type = (data.isDynamic) ? b2_dynamicBody : b2_staticBody;
	bodyDef.position.Set(worldPosition.x, worldPosition.y);
	bodyDef.angle = nc::DegreesToRadians(angle);
	bodyDef.fixedRotation = data.lockAngle;
	b2Body* body = m_world->CreateBody(&bodyDef);

	Vector2 worldSize = ScreenToWorld(data.size);
	b2PolygonShape shape;
	shape.SetAsBox(worldSize.x, worldSize.y);

	b2FixtureDef fixtureDef;
	fixtureDef.density = data.density;
	fixtureDef.friction = data.friction;
	fixtureDef.restitution = data.restitution;
	fixtureDef.isSensor = data.isSensor;
	fixtureDef.userData = gameobject;
	fixtureDef.shape = &shape;

	body->CreateFixture(&fixtureDef);

	return body;
}

void nc::PhysicsSystem::DestroyBody(b2Body* body)
{
	m_world->DestroyBody(body);
}


