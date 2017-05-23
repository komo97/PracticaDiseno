#pragma once
#include <vector>
#include <SDL_image.h>
#include <string>
#include "Physics2DComponent.h"
#include "RPGSAEMMOApp.h"
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
	inline bool isAlive() { return life > 0; }
	void draw();
	void Move(const fVector2& _newPos );
	virtual void Update();
	std::string name;
	void EnablePhysics2D(bool enable);
	inline Physics2DComponent* getPhysics2DComp() { return physicsEnabled; }
	std::vector<SDL_Surface*> sprites;
	float rotAngle = 0;

protected:
	virtual void OnCollisionEnter();
	virtual void OnCollisionExit();
	virtual void OnCollisionStay();
	fVector2 pos;
	fVector2 size;
	int life;
	std::string spritePath;
	bool justCollisioned = false;
	int currentSpriteIndex = 0;
	SDL_Rect* posValues = NULL;
	SDL_Rect* clipping = NULL;
	SDL_RendererFlip flip;
	SDL_Point* center = NULL;
	Physics2DComponent* physicsEnabled = NULL;
};

