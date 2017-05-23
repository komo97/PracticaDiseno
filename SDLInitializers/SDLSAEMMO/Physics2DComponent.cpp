#include "Physics2DComponent.h"
#include "RPGSAEMMOApp.h"



Physics2DComponent::Physics2DComponent(std::string _name, fVector2* _position)
{
	name = _name;
	position = _position;
	Physics2D::getInstance()->AddEnabledEntity(this);
}

Physics2DComponent::~Physics2DComponent()
{
	Physics2D::getInstance()->RemoveEnabledEntity(this);
}

void Physics2DComponent::SetVelocity(const fVector2 & _newVel)
{
	velocity = _newVel;
}

void Physics2DComponent::SetVelocity(float _x, float _y)
{
	velocity.x = _x;
	velocity.y = _y;
}

void Physics2DComponent::PhysicsUpdate()
{
	last3Positions.push_back(*position);
	if (last3Positions.size() > 3)
	{
		last3Positions.pop_front();
		physicsTimer = std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::system_clock::now().time_since_epoch()) - physicsTimerStart;
		velocity = (last3Positions.at(2) - last3Positions.at(1))/ ((float)RPGSAEMMOApp::getDeltaTime() / 10);
		acceleration = ((last3Positions.at(2) - last3Positions.at(1)) -
			(last3Positions.at(1) - last3Positions.at(0))) / (float)physicsTimer.count();
	}
}

fVector2 Physics2DComponent::getCenter()
{
	if (centerMoved)
	{
		std::vector<fVector2> vertexy;
		if (collider == Colliders::Box ||
			collider == Colliders::Complex)
		{
			if (collider == Colliders::Box)
			{
				vertexy.push_back(vertex.rect.pos);
				vertexy.push_back(vertex.rect.size + vertex.rect.pos);
			}
			else vertexy = vertex.complexVertex.vertex;
			center = fVector2::zero;
			for (auto i : vertexy)
			{
				center += i;
			}
			center /= (float)vertexy.size();
			centerMoved = false;
			return center;
		}
	}
	else return center;
	return center;
}

void Physics2DComponent::UpdatePosition(fVector2 newPos)
{
	if (newPos != fVector2::zero)
	{
		centerMoved = true;
		if (physicsTimerStart.count() == 0 || velocity == fVector2::zero)
			physicsTimerStart = 
			std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::system_clock::now().time_since_epoch());
	}
	*position += newPos;
	if (collider == Colliders::Box)
		vertex.rect.pos = *position;
	else if (collider == Colliders::Complex)
		vertex.complexVertex.pos = *position;
	else if (collider == Colliders::Circle)
		vertex.circleCollider.pos = *position;
}
