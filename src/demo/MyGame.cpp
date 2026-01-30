#include "MyGame.h"
#include "../engine/GameMath.h"


MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(5), gameWon(false), box(5, 5, 30, 30), trailCooldown(0), victoryTimer(-1.0f), spike(390, 500, 30, 30) {
	TTF_Font * font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	gfx->useFont(font);
	gfx->setVerticalSync(true);

    for (int i = 0; i < numKeys; i++) {
        std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
        k->isAlive = true;
        k->pos = Point2(getRandom(0, 750), getRandom(0, 550));
        gameKeys.push_back(k);
    }
}

MyGame::~MyGame() {

}

void MyGame::handleKeyEvents() {
	int speed = 3;

	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed;
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed;
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed;
	}
}

void MyGame::update() {
	box.x += velocity.x;
	box.y += velocity.y;

	if (velocity.x != 0 || velocity.y != 0) {
		trailCooldown--;

		if (trailCooldown <= 0) {
			int cx = box.x + box.w / 2;
			int cy = box.y + box.h / 2;

			myEngine.spawnTrail(cx, cy, (int)velocity.x, (int)velocity.y);
			trailCooldown = 2;
		}
	}

	if (checkCollision(box, spike)) {

		myEngine.spawnDamage(box.x + 15, box.y + 15, 30, { 255, 0, 0, 255 });

		box.x = 5;
		box.y = 5;

		lives--;
		score = std::max(0, score - 100);
	}

	for (auto key : gameKeys) {
		if (key->isAlive && box.contains(key->pos)) {
			score += 200;
			key->isAlive = false;
			numKeys--;
			myEngine.burstAt(key->pos.x, key->pos.y, 80);
		}
	}

	velocity.x = 0;
    velocity.y = 0;

	if (numKeys == 0 && !gameWon) {
		gameWon = true;
		victoryTimer = 0.01f;
	}

	if (gameWon) {
		victoryTimer += 0.016f;
	}

	myEngine.update();
}

void MyGame::render() {

	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(spike);

	gfx->setDrawColor(SDL_COLOR_AQUA);
	gfx->drawRect(box);

	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : gameKeys)
        if (key->isAlive)
		    gfx->drawCircle(key->pos, 5);

	myEngine.render(gfx.get());
}

void MyGame::renderUI() {


	gfx->setDrawColor(SDL_COLOR_AQUA);

	if (gameWon)
		gfx->drawText("You Win!", 250, 50);

	if (victoryTimer > 0.0f && victoryTimer < 1.0f) {
		myEngine.spawnVictory(800, 600);
	}

}