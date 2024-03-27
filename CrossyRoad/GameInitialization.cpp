#include "GameInitialization.h"
#include "Genio.h"
#include "Rendering.h"
#include "GameLogic.h"

void load() {
	grassTile.texture = G_LoadImage("assets/image/grass.png");
	grassTile.position = { 0,0,100,100 };
	grassTile.type = GRASS;

	treeTile.texture = G_LoadImage("assets/image/tree.png");
	treeTile.position = { 0,0,100,100 };
	treeTile.type = TREE;

	waterTile.texture = G_LoadImage("assets/image/sea.png");
	waterTile.position = { 0,0,100,100 };
	waterTile.type = WATER;

	roadTile.texture = G_LoadImage("assets/image/street.png");
	roadTile.position = { 0,0,100,100 };
	roadTile.type = ROAD;

	railTile.texture = G_LoadImage("assets/image/rail.png");
	railTile.position = { 0,0,100,100 };
	railTile.type = RAIL;

	Car.texture = G_LoadImage("assets/image/car.png"); 
	Car.position = { 0,0,169,100 }; 
	Car.isMoving = true;
	Car.type = CAR;
	Car.sound = G_LoadSound("assets/sound/car-horn.wav");
	car2Texture = G_LoadImage("assets/image/car2.png");
	car3Texture = G_LoadImage("assets/image/car3.png");

	Stick.texture = G_LoadImage("assets/image/stick1.png");
	Stick.position = { 0,0,100,100 };
	Stick.type = STICK;
	Stick.sound = G_LoadSound("assets/sound/water.wav");

	Train.texture = G_LoadImage("assets/image/train.png");
	Train.position = { 0,0,544,100 };
	Train.type = TRAIN;
	Train.sound = G_LoadSound("assets/sound/train_pass_no_horn.wav");

	Lamp.texture = G_LoadImage("assets/image/green-lamp.png");
	Lamp.position = { 0,0,39,93 };
	Lamp.type = LAMP;
	Lamp.sound = G_LoadSound("assets/sound/train_alarm.wav");
	redLampTexture = G_LoadImage("assets/image/red-lamp.png");

	Eagle.texture = G_LoadImage("assets/image/eagle.png");
	Eagle.position = { 0,0,426,184 };
	Eagle.type = EAGLE;
	Eagle.moveSpeed = 20;
	Eagle.sound = G_LoadSound("assets/sound/eagle_hit.wav");

	Coin.texture = G_LoadImage("assets/image/coin.png");
	Coin.position = { windowPos.w - 100,20,100,100 };
	Coin.dir = LEFT;
	Coin.type = COIN;
	Coin.sound = G_LoadSound("assets/sound/coin_tap.wav");

	initTiles();

	sheepTexture = G_LoadImage("assets/image/player.png");
	cowTexture = G_LoadImage("assets/image/player2.png");
	pigTexture = G_LoadImage("assets/image/player3.png");
	Player.texture = sheepTexture;
	Player.tile = { columns / 2 , rows - 2 };
	Player.position = map1[Player.tile.x][Player.tile.y].position;
	Player.type = PLAYER;
	Player.sound = G_LoadSound("assets/sound/car_squish.wav");

	font = G_OpenFont("assets/font/editundo.ttf", 72);
	ScoreText.texture = G_LoadFont(font, "0", 255, 255, 255);
	ScoreText.position = { 10,10,31,42 };

	TopScoreText.texture = G_LoadFont(font, "TOP 0", 255, 255, 255);
	TopScoreText.position = { 10,60,81,52 };

	CoinText.texture = G_LoadFont(font, "0", 253, 230, 75);
	CoinText.position = { windowPos.w - 70 ,8,20,35 };

	GameOverText.texture = G_LoadFont(font, "GAME OVER!", 0, 0, 0);
	GameOverText.position = { (windowPos.w - 345) / 2,(windowPos.h - 43) / 2,345,43 };

	Logo.texture = G_LoadImage("assets/image/logo.png");
	Logo.position = { (windowPos.w - 764) / 2,(windowPos.h - 144) / 3,764,144 };

	ClickButton.texture = G_LoadImage("assets/image/click.png");
	ClickButton.position = { (windowPos.w - 100) / 2,Logo.position.y + 190 ,100,172 };

	TryAgainButton.texture = G_LoadImage("assets/image/again.png");
	TryAgainButton.position = { (windowPos.w - 177) / 2,(windowPos.h / 2) + 150,177,89 };

	PauseButton.texture = G_LoadImage("assets/image/pause.png");
	PauseButton.position = { windowPos.w - 70,70,50,50 };

	PlayerChooseButton.texture = G_LoadImage("assets/image/settings.png");
	PlayerChooseButton.position = { 20,windowPos.h - 120 ,125,100 };

	clickSound = G_LoadSound("assets/sound/click.wav");
}

void initTiles()
{
	columns = ceil(windowPos.w / TILE_LENGTH);
	rows = ceil(windowPos.h / TILE_LENGTH) + 1;
	map1 = new Tile*[columns];
	for (int i = 0; i < columns; i++)
		map1[i] = new Tile[rows];

	for (int y = rows - 1; y >= 0; y--)
	{
		if (y >= rows - 2) {
			for (auto x = 0; x < columns; x++) {
				map1[x][y] = (x == 0 || x == columns - 1) ? treeTile : grassTile;
				map1[x][y].position.x = x * 100;
				map1[x][y].position.y = (y - 1) * 100;
			}
		}
		else
		{
			generateTiles(y);
			addObjects(y);
		}
	}
}

void start()
{
	G_Draw(Logo.texture, &Logo.position);
	G_Draw(ClickButton.texture, &ClickButton.position);
	G_Draw(PlayerChooseButton.texture, &PlayerChooseButton.position);
	if (clickOnButton(&PlayerChooseButton.position))
		state = CHOOSE_PLAYER;
	else if (gameEvent == G_MOUSEBUTTONDOWN && G_Mouse == G_BUTTON_LEFT)
		state = PLAY;
}

void choose_player()
{
	int num = 3;
	PlayerButton.position = { (windowPos.w - (num * 150 - 50)) / 2,(windowPos.h - 100) / 2,100,100 };
	for (int i = 0; i < num; i++) {
		switch (i) {
		case 0: PlayerButton.texture = sheepTexture; break;
		case 1: PlayerButton.texture = cowTexture; break;
		case 2: PlayerButton.texture = pigTexture; break;
		}
		if (clickOnButton(&PlayerButton.position)) {
			Player.texture = PlayerButton.texture;
			state = START;
			break;
		}
		SDL_SetRenderDrawColor(renderer, 0, 196, 255, 255);
		SDL_RenderFillRect(renderer, &PlayerButton.position);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &PlayerButton.position);
		G_Draw(PlayerButton.texture, &PlayerButton.position);
		PlayerButton.position.x += 150;
	}
}