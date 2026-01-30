#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include <memory>
#include "../EngineCommon.h"
#include "../GraphicsEngine.h"


class ParticleEngine;

class MyEngineSystem {
	friend class XCube2Engine;

	private:
		std::unique_ptr<ParticleEngine> particleEngine;

	public:
		MyEngineSystem();
		~MyEngineSystem();

		void update();
		void render(GraphicsEngine* gfx);
		void burstAt(int x, int y, int count);
		void spawnDamage(float x, float y, int count, SDL_Color color);
		void spawnTrail(int x, int y, int VelX, int VelY);
		void spawnVictory(int screenWidth, int screenHeight);
};

#endif