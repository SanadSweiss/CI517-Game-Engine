#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"
#include "../engine/custom/MyEngineSystem.h"



struct GameKey {
	Point2 pos;
	bool isAlive;
};

class MyGame : public AbstractGame {
	private:

		MyEngineSystem myEngine;

		Rect box;
		Rect spike;

		Vector2i velocity;

		std::vector<std::shared_ptr<GameKey>> gameKeys;

		/* GAMEPLAY */
		int score, numKeys, lives;
		int trailCooldown;
		bool gameWon;
		float victoryTimer = 0.0f;

		bool checkCollision(Rect a, Rect b) {
			return (a.x < b.x + b.w &&
				    a.x + a.w > b.x &&
				    a.y < b.y + b.h &&
				    a.y + a.h > b.y);
		}
	

		void handleKeyEvents();
		void update();
		void render();
		void renderUI();

	public:
        MyGame();
		~MyGame();
};

#endif