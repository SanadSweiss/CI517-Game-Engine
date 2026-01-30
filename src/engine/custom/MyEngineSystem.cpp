#include "MyEngineSystem.h"
#include <memory>
#include <type_traits>

#include "../ParticleEngine.h"
#include "../GameMath.h"
#include "../GraphicsEngine.h"


MyEngineSystem::MyEngineSystem()
	: particleEngine(std::make_unique<ParticleEngine>()) {}

MyEngineSystem::~MyEngineSystem() = default;

void MyEngineSystem::update() {
	const float dt = 1.0f / 60.0f;
	particleEngine->update(dt);
}

void MyEngineSystem::render(GraphicsEngine* gfx) {
	if (!gfx) return;
	particleEngine->draw(*gfx);
}

void MyEngineSystem::burstAt(int x, int y, int count) {
	particleEngine->emitBurst(Vector2f((float)x, (float)y), count);
}

void MyEngineSystem::spawnDamage(float x, float y, int count, SDL_Color color) {
	
	particleEngine->emitDamage(x, y, count, color);
}

void MyEngineSystem::spawnTrail(int x, int y, int velX, int velY) {

	Vector2f position((float)x, (float)y);
	Vector2f velocity((float)velX, (float)velY);

	particleEngine->emitTrail(position, velocity);
}

void MyEngineSystem::spawnVictory(int screenWidth, int screenHeight) {
	Vector2f center((float)screenWidth / 2.0f, (float)screenHeight / 2.0f);
	particleEngine->emitVictory(center);
}