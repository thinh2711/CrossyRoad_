 #include "GameInitialization.h"
#include "Genio.h"
#include "GameLogic.h"
#include "Rendering.h"
#include "Cleanup.h"

void pause() 
{
	G_Rect pauseRect = { (windowPos.w - 402) / 2,(windowPos.h - 512) / 2,402,512 };
	G_Draw(PauseButton.texture, &pauseRect);
	if (gameEvent == G_MOUSEBUTTONDOWN && G_Mouse == G_BUTTON_LEFT)
		state = PLAY;
}

void checkPlayerStatus()
{
	if (state != PLAY) return;

	if (Player.position.y + 5 >= windowPos.h) {
		state = OUT;
		Eagle.position.x = Player.position.x - (Eagle.position.w / 2);
		Eagle.position.y = -Eagle.position.h;
		eagleIntersection = false;
		return;
	}

	if (Player.position.x <= -TILE_LENGTH || Player.position.x >= windowPos.w)
		state = GAME_OVER;

	bool onStick = false;
	G_Rect temp = { Player.position.x + realPlayerClip.x + 5 , Player.position.y + realPlayerClip.y + 5 , realPlayerClip.w - 5,realPlayerClip.h - 5 };
	for (int i = 0; i < objects.size(); i++) {
		if (SDL_HasIntersection(&temp, &objects[i].position) == SDL_TRUE) {
			if (objects[i].type == CAR || objects[i].type == TRAIN) {
				state = GAME_OVER;
				G_PlaySound(Player.sound, 0);
			}
			else if (objects[i].type == STICK) {
				onStick = true;
				if (!Player.isMoving) {
					if (objects[i].isMoving) Player.position.x += objects[i].moveSpeed;
					if (Player.position.x >= map1[Player.tile.x][0].position.x + TILE_LENGTH) Player.tile.x++;
					else if (Player.position.x <= map1[Player.tile.x][0].position.x - TILE_LENGTH) Player.tile.x--;
					if (Player.tile.x >= columns || Player.tile.x < 0) state = GAME_OVER;
				}
			}
			else if (objects[i].type == COIN) {
				coins++;
				G_PlaySound(Coin.sound, 0);
				updateScore();
				objects.erase(objects.begin() + i);
				i--;
				continue;
			}
		}
	}
	if (!Player.isMoving && !onStick && map1[Player.tile.x][Player.tile.y].type == WATER)
		state = GAME_OVER;
}

bool clickOnButton(G_Rect* r) {
	SDL_Point mouse_point = { G_motion.x , G_motion.y };
	if (gameEvent == G_MOUSEBUTTONDOWN && G_Mouse == G_BUTTON_LEFT && SDL_PointInRect(&mouse_point, r)) {
		G_PlaySound(clickSound, 0);
		return true;
	}
	return false;
}

void addCar(int)
{
	Direction dir = (Direction)((rand() % 2) + 2);
	Car.dir = dir;
	Car.position.y = map1[0][row].position.y;
	Car.tile.y = row;
	Car.moveSpeed = (rand() % 5 + 2) * (dir == RIGHT ? 1 : -1);
	int num = (rand() % 3) + 1;
	int space = (windowPos.w - ((num - 1) * Car.position.w)) / num;
	int randPos = rand() % windowPos.w;
	for (int i = 0; i < num; i++)
	{
		objects.push_back(Car);
		if (dir == LEFT)
			objects.back().position.x = windowPos.w + (i*(space + Car.position.w)) - randPos;
		else
			objects.back().position.x = -Car.position.w - (i*(space + Car.position.w)) + randPos;
		short int tex = rand() % 3;
		switch (tex)
		{
		case 1:
			objects.back().texture = car2Texture;
			break;
		case 2:
			objects.back().texture = car3Texture;
			break;
		}
	}
}

void addStick(int)
{
	Direction dir = (Direction)((rand() % 2) + 2);
	Stick.dir = dir;
	Stick.position.y = map1[0][row].position.y;
	Stick.tile.y = row;
	Stick.moveSpeed = (rand() % 5 + 2) * (dir == RIGHT ? 1 : -1);
	int num = (rand() % (maxSticksInARow - minSticksInARow + 1)) + minSticksInARow;
	int space = (windowPos.w - ((num - 1) * Stick.position.w)) / num;
	int randPos = rand() % windowPos.w;
	for (int i = 0; i < num; i++)
	{
		objects.push_back(Stick);
		if (dir == LEFT)
			objects.back().position.x = windowPos.w + (i*(space + Stick.position.w)) - randPos;
		else
			objects.back().position.x = -Stick.position.w - (i*(space + Stick.position.w)) + randPos;
	}

}

void addTrain(int)
{
	Direction dir = (Direction)((rand() % 2) + 2);
	Train.dir = dir;
	Train.position.y = map1[0][row].position.y;
	Train.tile.y = row;
	Train.timer = ((rand() % 5) + 2) * FPS;

	objects.push_back(Train);
	if (dir == LEFT)
		objects.back().position.x = windowPos.w + Train.position.w;
	else
		objects.back().position.x = -Train.position.w;

	Lamp.tile.y = row;
	Lamp.position.y = map1[0][row].position.y + TILE_LENGTH - Lamp.position.h;
	Lamp.position.x = map1[0][row].position.x + 20;
	objects.push_back(Lamp);
}

void addCoins(int)
{
	int num = 0;
	Coin.position.y = map1[0][row].position.y;
	Coin.position.w = Coin.position.h = 100;
	Coin.tile.y = row;
	for (int i = 0; i < columns; i++)
	{
		if (map1[i][row].type != TREE) {
			int chance = rand() % 101;
			if (chance >= 90 && num < maxCoinsInARow) {
				num++;
				Coin.position.x = map1[i][row].position.x;
				objects.push_back(Coin);
			}
		}
	}
}

