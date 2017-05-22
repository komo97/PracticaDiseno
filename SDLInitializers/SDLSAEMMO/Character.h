#pragma once
#include <vector>
#include <SDL_image.h>
#include "RPGSAEMMOApp.h"
#include <string>
#include "fVector2.h"
class Character
{
public:
	Character(std::string _name = "");
	Character(fVector2 _pos, fVector2 _size,
		std::string _name = "");
	Character(fVector2 _pos, fVector2 _size, int _life,
		std::string _name = "");
	Character(fVector2 _pos, fVector2 _size, int _life,
		std::string _spritePath, std::string _name = "");
	~Character();
	inline bool isAlive() { return life > 0; };
	void draw();
protected:
	std::string name;
	fVector2 pos;
	fVector2 size;
	int life;
	std::string spritePath;

};

