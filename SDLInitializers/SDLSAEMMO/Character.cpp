#include "Character.h"
#include <iostream>
//http://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index2.php
//https://www.libsdl.org/projects/SDL_image/docs/SDL_image_frame.html
//https://docs.google.com/document/d/1U9dTzY36119WHmrGLuYvK0dadx5YTFP99Ml_BgNm71s/edit

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

	posValues = new SDL_Rect{ (int)round(pos.x),(int)round(pos.y),(int)round(size.x),(int)round(size.y) };
	if (pos.x + size.x >= RPGSAEMMOApp::getWidth())
		posValues->w = (int)round((pos.x + size.x)) - RPGSAEMMOApp::getWidth();
	if (pos.y + size.y >= RPGSAEMMOApp::getHeight())
		posValues->h = (int)round((pos.y + size.y)) - RPGSAEMMOApp::getHeight();
	if (pos.x < 0)
	{
		if (clipping == NULL) {
			clipping = new SDL_Rect{ (int)round(- pos.x),0, (int)round(size.x + pos.x), (int)round(size.y) };
		}
		else
		{
			clipping->x = (int)round(-pos.x);
			clipping->w = (int)round(size.x + pos.x);
		}
	}
	if (pos.y < 0)
	{
		if (clipping == NULL) {
			clipping = new SDL_Rect{ 0, (int)round(-pos.y), (int)round(size.x), (int)round(size.y + pos.y) };
		}
		else
		{
			clipping->y = (int)(-pos.y);
			clipping->h = (int)round(size.y + pos.y);
		}
	}
	if (physicsEnabled != NULL)
		physicsEnabled->angle = rotAngle;
	SDL_Texture* renderTexture = 
		SDL_CreateTextureFromSurface(RPGSAEMMOApp::getRenderer(),sprites.at(currentSpriteIndex));
	SDL_RenderCopyEx(RPGSAEMMOApp::getRenderer(), renderTexture, clipping, posValues, rotAngle, center, flip);
	SDL_DestroyTexture(renderTexture);
	delete posValues;
	++currentSpriteIndex %= sprites.size();

}

void Character::Move(const fVector2 & _newPos)
{
	physicsEnabled->UpdatePosition(_newPos);
}

void Character::Update()
{
	if (justCollisioned && !physicsEnabled->isCollisioning)
	{
		justCollisioned = false;
		OnCollisionExit();
	}
	else if (!justCollisioned && physicsEnabled->isCollisioning)
	{
		justCollisioned = true;
		OnCollisionEnter();
	}
	else if (physicsEnabled->isCollisioning)
		OnCollisionStay();
}

void Character::OnCollisionEnter()
{
	std::cout << "Entre!"<<std::endl;
}

void Character::OnCollisionExit()
{
	std::cout << "Sali!"<<std::endl;
}

void Character::OnCollisionStay()
{
}

void Character::EnablePhysics2D(bool enable)
{
	if (enable)
	{
		physicsEnabled = new Physics2DComponent(name, &pos);
		physicsEnabled->vertex.rect = { pos, size };
		physicsEnabled->collider = Colliders::Box;
		physicsEnabled->collisionType = CollisionTypes::SeparateAxis;
	}
	else
	{
		delete physicsEnabled;
		physicsEnabled = NULL;
	}
}

