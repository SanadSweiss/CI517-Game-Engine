#include "ParticleEngine.h"
#include "GraphicsEngine.h"
#include <algorithm>
#include <cmath>

float randomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void ParticleEngine::emitBurst(const Vector2f& origin, int count) {

	if ((int)particles.size() >= maxParticles) return;

	for (int i = 0; i < count; i++) {
		float angle = randomFloat(0, 360) * 3.14159f / 180.0f;
		float speed = randomFloat(50, 200);

		Vector2f vel;
		vel.x = cosf(angle) * speed;
		vel.y = sinf(angle) * speed;

		float life = randomFloat(30, 80) / 100.0f;
		float radius = randomFloat(2, 5);

		SDL_Color color = {
			randomFloat(200, 255),
			randomFloat(50, 200),
			0,
			255
		};

		particles.emplace_back(origin, vel, life, radius, color);

		if ((int)particles.size() >= maxParticles) break;
	}
}

void ParticleEngine::emitTrail(const Vector2f& origin, const Vector2f& velocity) {

	if ((int)particles.size() >= maxParticles) return;

	Vector2f spawnPos = origin;
	float offset = 15.0f;

	if (velocity.x > 0) spawnPos.x -= offset;
	else if (velocity.x < 0) spawnPos.x += offset;

	if (velocity.y > 0) spawnPos.y -= offset;
	else if (velocity.y < 0) spawnPos.y += offset;

	int count = 1;

	for (int i = 0; i < count; i++) {

		Vector2f spawnPos = origin;
		spawnPos.x -= velocity.x * 0.1f;
		spawnPos.y -= velocity.y * 0.1f;
		spawnPos.x += getRandom(-3, 3);
		spawnPos.y += getRandom(-3, 3);

		Vector2f vel = { randomFloat(-5, 5), randomFloat(-5, 5) };

		float life = randomFloat(0.3f, 0.6f);
		float radius = randomFloat(2, 4);

		SDL_Color color = { 128, 128, 128, 255 };

		particles.emplace_back(spawnPos, vel, life, radius, color);
	}
}

void ParticleEngine::emitVictory(const Vector2f& screenCenter) {

	if ((int)particles.size() >= maxParticles) return;

	for (int i = 0; i < 5; i++) {


		Vector2f vel = { randomFloat(-200, 200), randomFloat(-500, -300) };

		float life = randomFloat(1.0f, 2.0f);
		float radius = randomFloat(2, 4);

		SDL_Color color = {
			getRandom(150, 255),
			getRandom(150, 255),
			getRandom(150, 255),
			255
		};

		particles.emplace_back(screenCenter, vel, life, radius, color);
	}
}

void ParticleEngine::emitDamage(float x, float y, int count, SDL_Color color) {
	
	for (int i = 0; i < count; i++) {
		float vx = randomFloat(-400, 400);
		float vy = randomFloat(-400, 400);
		float life = randomFloat(0.1f, 0.3f);
		float radius = randomFloat(1, 3);

		SDL_Color color = {
			255,
			0,
			0,
			255
		};

		particles.emplace_back(Vector2f(x, y), Vector2f(vx, vy), life, radius, color);
	}
}

void ParticleEngine::update(float dt) {
	for (auto& p : particles) {

		p.vel.y += 200.0f * dt;

		p.update(dt);
	}

	particles.erase(
		std::remove_if(particles.begin(), particles.end(),
			[](const Particle& p) { return !p.isAlive(); }),
		particles.end()
	);
}

void ParticleEngine::draw(GraphicsEngine& gfx) {
	for (auto& p : particles) {
		gfx.setDrawColor(p.color);

		Point2 center;
		center.x = (int)p.pos.x;
		center.y = (int)p.pos.y;

		gfx.drawCircle(center, p.radius);
	}
}