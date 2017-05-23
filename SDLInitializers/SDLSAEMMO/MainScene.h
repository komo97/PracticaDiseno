#pragma once
#include "Scene.h"
#include <vector>
#include "Character.h"
class MainScene :
	public Scene
{
public:
	void Start() final;
	void Update() final;
	void Draw() final;
	void SceneEnd() final;
private:
	Character* test1, *test2;
};

