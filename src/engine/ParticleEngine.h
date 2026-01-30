#pragma once
#include <vector>
#include "Particle.h"
#include "GameMath.h"
#include "GraphicsEngine.h"

class GraphicsEngine;
struct Vector2f;

class ParticleEngine {

private:
	std::vector<Particle> particles;
	int maxParticles = 1000;

public:
	void emitBurst(const Vector2f& origin, int count);
	void emitDamage(float x, float y, int count, SDL_Color color);
	void emitTrail(const Vector2f& origin, const Vector2f& velocity);
	void emitVictory(const Vector2f& screenCenter);
	void update(float dt);
	void draw(GraphicsEngine& gfx);

	int getParticleCount() const { return (int)particles.size(); }
};

