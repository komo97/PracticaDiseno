#include "Physics2D.h"
#include "Physics2DComponent.h"
#include <iostream>
#include <string>

Physics2D* Physics2D::instance = NULL;

Physics2D::Physics2D()
{
}


Physics2D::~Physics2D()
{
}

void Physics2D::AddEnabledEntity(Physics2DComponent * const & entity)
{
	enabledEntities.push_back(entity);
}

void Physics2D::RemoveEnabledEntity(Physics2DComponent * const & entity)
{
	for (int i = enabledEntities.size(); i--;)
	{
		if (enabledEntities.at(i) == entity) {
			enabledEntities.erase(enabledEntities.begin() + i);
		}
	}
	delete entity;
}

Physics2D * Physics2D::getInstance()
{
	return instance == NULL ? instance = new Physics2D() : instance;
}

void Physics2D::UpdatePhysics()
{
	while (1)
	{
		Collisions();
		SDL_Delay(RPGSAEMMOApp::GetFrameLock());
	}
}

void Physics2D::SeekCollisionableEntities()
{
	std::vector<Physics2DComponent*> collisionables;
	for (auto entity : enabledEntities)
	{
		if (entity->collisionType == CollisionTypes::SeparateAxis)
			collisionables.push_back(entity);
	}
	for (auto entity : collisionables)
	{
		for (auto currEntity : collisionables)
		{
			if (entity != currEntity)
			{
				if (entity->collider == Colliders::Box)
				{
					if (currEntity->collider == Colliders::Box)
					{
						if (entity->vertex.rect.pos.Distance(currEntity->vertex.rect.pos)
							< entity->vertex.rect.size.Lenght())
						{
							collisionableEntities.push_back(entity);
							break;
						}
					}
				}
			}
		}
	}
	collisionables.clear();
}


void Physics2D::CollisionDetection()
{
	bool colX, colY;
	fVector2 minVect1, minVect2;
	fVector2 maxVect1, maxVect2;
	for (auto entity : collisionableEntities)
	{
		entity->isCollisioning = false;
		for (auto collisioner : collisionableEntities)
		{
			if (entity != collisioner)
			{
				colX = false;
				colY = false;
				if (entity->collider == Colliders::Box)
				{
					if (collisioner->collider == Colliders::Box)
					{
						minVect1 = findMinVertexRect(entity->vertex.rect);
						minVect2 = findMinVertexRect(collisioner->vertex.rect);
						maxVect1 = findMaxVertexRect(entity->vertex.rect);
						maxVect2 = findMaxVertexRect(collisioner->vertex.rect);
						if((minVect2.x >= minVect1.x &&
							minVect2.x <= maxVect1.x) ||
							(maxVect2.x <= maxVect1.x &&
								maxVect2.x >= minVect1.x)) 
						{
							colX = true;
						}
						if ((minVect2.y >= minVect1.y &&
							minVect2.y <= maxVect1.y) ||
							(maxVect2.y <= maxVect1.y &&
								maxVect2.y >= minVect1.y))
						{
							colY = true;
						}
						if (colX && colY)
						{
							entity->isCollisioning = true;
							entity->collisionedEntities.push_back(collisioner);
						}
					}
				}

			}
		}
	}
}

void Physics2D::Collisions()
{
	SetRotations();
	SeekCollisionableEntities();
	CollisionDetection();
	CollisionResolution();
	collisionableEntities.clear();
	UpdatePositions();
	for (auto i : enabledEntities)
	{
		std::cout << i->getVelocity().x << " " << i->getVelocity().y << " Velocity." << std::endl;
		std::cout << i->getAcceleration().x << " " << i->getAcceleration().y << " Acceleration." << std::endl;
	}
}

void Physics2D::CollisionResolution()
{

}

void Physics2D::UpdatePositions()
{
	for (auto i : enabledEntities)
		i->PhysicsUpdate();
}

void Physics2D::SetRotations()
{
	for (auto i : enabledEntities) {
		fVector2 center = i->getCenter();
		std::cout << center.x << " " << center.y <<" Center"<< std::endl;
		if (i->collider == Colliders::Box)
		{
			i->vertex.rect.pos.Rotate(i->angle, center);
			fVector2 size = i->vertex.rect.pos + i->vertex.rect.size;
			size.Rotate(i->angle, center);
			i->vertex.rect.size = size - i->vertex.rect.pos;
		}
	}
}

fVector2 Physics2D::findMinVertexRect(const PhysicsRect2D & vertex)
{
	fVector2 minVertex(vertex.pos.x,vertex.pos.y);
	if (minVertex.x > vertex.size.x + vertex.pos.x)
		minVertex.x = vertex.size.x + vertex.pos.x;
	if (minVertex.y > vertex.size.y + vertex.pos.y)
		minVertex.y = vertex.size.y + vertex.pos.y;
	return minVertex;
}

fVector2 Physics2D::findMaxVertexRect(const PhysicsRect2D & vertex)
{
	fVector2 minVertex(vertex.pos.x, vertex.pos.y);
	if (minVertex.x < vertex.size.x + vertex.pos.x)
		minVertex.x = vertex.size.x + vertex.pos.x;
	if (minVertex.y < vertex.size.y + vertex.pos.y)
		minVertex.y = vertex.size.y + vertex.pos.y;
	return minVertex;
}
