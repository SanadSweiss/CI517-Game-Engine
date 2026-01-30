#pragma once
#include <SDL.h>
#include "GameMath.h"

struct Particle {
	Vector2f pos;
	Vector2f vel;
	float life;
	float startLife;
	float radius;
	float startRadius;
	SDL_Color color;

	Particle(const Vector2f& p, const Vector2f& v, float lifetime, float r, SDL_Color c)
		: pos(p), vel(v), life(lifetime), startLife(lifetime), radius(r), startRadius(r), color(c) {}

	void update(float dt) {
		pos.x += vel.x * dt;
		pos.y += vel.y * dt;
		life -= dt;

		float lifeParams = life / startLife;

		if (lifeParams < 0.0f) lifeParams = 0.0f;

		radius = startRadius * lifeParams;
	}

	bool isAlive() const { return life > 0.0f; }

};


