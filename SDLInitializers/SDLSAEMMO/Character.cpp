#include "Character.h"


Character::Character(std::string _name) : name(_name)
{
}

Character::Character(fVector2 _pos, fVector2 _size, std::string _name) : Character(_name)
{
	pos = _pos;
	size = _size;
}

Character::Character(fVector2 _pos, fVector2 _size, int _life,
	std::string _name) : Character(_pos,_size,_name)
{
	life = _life;
}

Character::Character(fVector2 _pos, fVector2 _size, int _life,
	std::string _spritePath, std::string _name) :
	Character(_pos,_size,_life)
{
	spritePath = _spritePath;
	name = _name;
}

Character::~Character()
{
}

void Character::draw()
{
	//TODO: LLENAR ESTO.
	//http://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index2.php
	//https://www.libsdl.org/projects/SDL_image/docs/SDL_image_frame.html
	//https://docs.google.com/document/d/1U9dTzY36119WHmrGLuYvK0dadx5YTFP99Ml_BgNm71s/edit
}
