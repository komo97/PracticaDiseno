#include "MainScene.h"
#include "RPGSAEMMOApp.h"
#include <iostream>
#include "fVector2.h"
#include <SDL_ttf.h>

void MainScene::Start()
{
	std::cout << "init";
	test1 = new Character(fVector2(0, 0), fVector2(50, 50), "Test 1");
	test2 = new Character(fVector2(90, 0), fVector2(50, 50), "Test 2");
	test1->sprites.push_back(SDL_CreateRGBSurface(NULL, 50, 50, 32, 0, 0, 0, 0));
	test2->sprites.push_back(SDL_CreateRGBSurface(NULL, 50, 50, 32, 0, 0, 0, 0));
	SDL_FillRect(test1->sprites.at(0), NULL, SDL_MapRGB(test1->sprites.at(0)->format, 250, 0, 0));
	SDL_FillRect(test2->sprites.at(0), NULL, SDL_MapRGB(test2->sprites.at(0)->format, 0, 250, 0));
	test1->EnablePhysics2D(true);
	test2->EnablePhysics2D(true);
}

void MainScene::Update()
{
	const Uint8* key = SDL_GetKeyboardState(NULL);
	test1->Update();
	test2->Update();
	if (key[SDL_SCANCODE_A])
		test1->Move(fVector2(-1, 0));
	if (key[SDL_SCANCODE_D])
		test1->Move(fVector2(1, 0));
	if (key[SDL_SCANCODE_W])
		test1->Move(fVector2(0, -1));
	if (key[SDL_SCANCODE_S])
		test1->Move(fVector2(0, 1));
}

void MainScene::Draw()
{
	test1->draw();
	test2->draw();
}

void MainScene::SceneEnd()
{
}
