#include "Particle.h"

void Particle::Update(float dt)
{

	position = position + (velocity * dt);
	if (lifespan != 0) lifespan = lifespan - dt;
}

void Particle::Draw(Renderer& renderer)
{
	if (lifespan > 0) {
		renderer.SetColor(rand() % 255,rand() % 255, rand() % 255, rand() % 255);
		renderer.DrawPoint(position.x, position.y);
	}
	
}
