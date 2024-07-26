#include "Bullet.h"
#include "Engine.h"

void Bullet::Update(float dt)
{
	

	m_velocity = Vector2{ 30.0f, 0.0f }.Rotate(m_transform.rotation) * m_speed ;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	Actor::Update(dt);
}

void Bullet::OnCollision(Actor* actor)
{
}
