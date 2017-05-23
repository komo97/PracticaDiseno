#pragma once
#include <chrono>
#include <vector>
#include <cstdarg>
#include "fVector2.h"
#include "PhysicsRect2D.h"
#include "RPGSAEMMOApp.h"
namespace CollisionDirections
{
	enum CollisionDirection {
		NoCollision = 0,
		Left,
		Right,
		Up,
		Down,
	};
}
namespace CollisionTypes
{
	enum CollisionType {
		NoCollision = 0,
		SeparateAxis,
	};
}
namespace Colliders
{
	enum Collider {
		Circle = 0,
		Box,
		Complex,
	};
}
class Physics2D
{
public:
	~Physics2D();
	void AddEnabledEntity(class Physics2DComponent* const& entity);
	void RemoveEnabledEntity(class Physics2DComponent* const& entity);
	static Physics2D* getInstance();
	void UpdatePhysics();
private:
	std::vector<class Physics2DComponent*> enabledEntities;
	std::vector<class Physics2DComponent*> collisionableEntities;
	void SeekCollisionableEntities();
	void CollisionDetection();
	void Collisions();
	void CollisionResolution();
	void UpdatePositions();

	void SetRotations();
	fVector2 findMinVertexRect(const PhysicsRect2D& vertex);
	fVector2 findMaxVertexRect(const PhysicsRect2D& vertex);
	static Physics2D* instance;
	Physics2D();
};

