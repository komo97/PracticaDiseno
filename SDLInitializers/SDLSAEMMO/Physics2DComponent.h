#pragma once
#include <chrono>
#include <deque>
#include "Physics2D.h"
#include "PhysicsRect2D.h"

typedef struct CircleCollider2D {
	float radius;
	fVector2 pos;
	~CircleCollider2D() {}
	CircleCollider2D() {}
}CircleCollider2D;

typedef struct ComplexCollider2D {
	std::vector<fVector2> vertex;
	fVector2 pos;
}ComplexCollider2D;

typedef union Verts{
	PhysicsRect2D rect;
	ComplexCollider2D complexVertex;
	CircleCollider2D circleCollider;
	~Verts() {}
	Verts(PhysicsRect2D _rect) { rect = _rect; }
	Verts(std::vector<fVector2> _vertex, fVector2 _pos) { 
		complexVertex.vertex = _vertex;
		complexVertex.pos = _pos;
	}
	Verts(CircleCollider2D _collider) {
		circleCollider = _collider;
	}
	Verts() {}
}Verts;

class Physics2DComponent
{
public:
	std::string name;
	bool isCollisioning = false;
	short collisionDirection : 3;
	short collisionType : 2;
	short collider : 2;
	float penetrationAllowance = .1f;
	float angle;
	float mass;
	Verts vertex;
	std::chrono::milliseconds physicsTimerStart;
	std::chrono::milliseconds physicsTimer;
	Physics2DComponent(std::string _name, fVector2* _position);
	~Physics2DComponent();
	void SetVelocity(const fVector2& _newVel);
	void SetVelocity(float _x, float _y);
	inline fVector2 getVelocity() { return velocity; }
	inline float getSpeed() { return speed; }
	inline fVector2 getAcceleration(){ return acceleration; }
	void PhysicsUpdate();
	std::vector<Physics2DComponent*> collisionedEntities;
	fVector2 getCenter();
	fVector2* position = NULL;
	void UpdatePosition(fVector2 newPos);
private:
	fVector2 center;
	bool centerMoved = true;
	fVector2 velocity = fVector2::zero;
	fVector2 acceleration = fVector2::zero;
	std::deque<fVector2> last3Positions;
	float speed;
};

