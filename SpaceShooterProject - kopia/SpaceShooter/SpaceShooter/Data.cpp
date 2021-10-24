#include "Data.h"

void GameObject::SetCollisionMatrix(std::vector<CollisionLayers> layers)
{
	for (int i = 0; i < layers.size(); i++)
	{
		//collisionMatrix |= layers[i];
	}
}

void GameObject::OnCollision()
{		
	IsActive = false;
	//print = true;	
}
