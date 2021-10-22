#include "Collision2D.h"
#include <list>
#include <vector>

Collision2D::Collision2D(Grid* grid ) // , Vector2 screenSize
{
	//grid->screenSize = screenSize;

	grid->gridCountX = ceil(grid->screenSize.x / grid->GridSize);
	grid->gridCountY = ceil(grid->screenSize.y / grid->GridSize);

	int collisionGridSize = grid->gridCountX * grid->gridCountY;

	std::cout << collisionGridSize - 1 << " gridXMAX: " << grid->gridCountX << " gridYMAX: " << grid->gridCountY << std::endl;

	for (int i = 0; i < collisionGridSize; i++)
	{
		grid->collisionGrid.push_back(GridCell());
		int y = floor(i / grid->gridCountX);
		int x = i - y * grid->gridCountX;

		//Upper Left
		if (x - 1 >= 0 && y - 1 >= 0) grid->collisionGrid[i].neighboorsIndex[0] = (x - 1) + (y - 1) * grid->gridCountX;
		else grid->collisionGrid[i].neighboorsIndex[0] = -1;
		//Upper middle
		if (y - 1 >= 0) grid->collisionGrid[i].neighboorsIndex[1] = (x)+(y - 1) * grid->gridCountX;
		else grid->collisionGrid[i].neighboorsIndex[1] = -1;
		//Upper Right
		if (x + 1 < grid->gridCountX && y - 1 >= 0) grid->collisionGrid[i].neighboorsIndex[2] = (x + 1) + (y - 1) * grid->gridCountX;
		else grid->collisionGrid[i].neighboorsIndex[2] = -1;
		//Right
		if (x + 1 < grid->gridCountX) grid->collisionGrid[i].neighboorsIndex[3] = (x + 1) + (y) * grid->gridCountX;
		else grid->collisionGrid[i].neighboorsIndex[3] = -1;
		//LowerRight
		if (x + 1 < grid->gridCountX && y + 1 < grid->gridCountY) grid->collisionGrid[i].neighboorsIndex[4] = (x + 1) + (y + 1) * grid->gridCountX;
		else grid->collisionGrid[i].neighboorsIndex[4] = -1;
		//Lower Middle
		if (y + 1 < grid->gridCountY) grid->collisionGrid[i].neighboorsIndex[5] = (x)+(y + 1) * grid->gridCountX;
		else grid->collisionGrid[i].neighboorsIndex[5] = -1;
		//Lower Left
		if (x - 1 >= 0 && y + 1 < grid->gridCountY) grid->collisionGrid[i].neighboorsIndex[6] = (x - 1) + (y + 1) * grid->gridCountX;
		else grid->collisionGrid[i].neighboorsIndex[6] = -1;
		//Left
		if (x - 1 >= 0) grid->collisionGrid[i].neighboorsIndex[7] = (x - 1) + (y) *grid->gridCountX;
		else grid->collisionGrid[i].neighboorsIndex[7] = -1;
	}
}

void Collision2D::Update(Grid* grid)
{
	for (int i = 0; i < grid->colliders.size(); i++)
	{
		if (grid->colliders[i]->IsActive)
		{
			continue;
		}

		GameObject* obj = grid->colliders[i];
		Vector2 pos = obj->Position;
		double objRadius = obj->radius;

		for (int j = 0; j < grid->colliders.size(); j++)
		{
			if (pos.x > 0 && pos.x < grid->screenSize.x - 1 && pos.y > 0 && pos.y <= grid->screenSize.y)
			{
				if (obj == grid->colliders[i] && !grid->colliders[i]->IsActive)
				{
					continue;
				}

				if (obj->radius * obj->radius < Vector2::DistanceNotSquard(obj->Position, grid->colliders[i]->Position))
				{
					obj->OnCollision();
					grid->colliders[i]->OnCollision();
				}
			}
		}
		/*
		if (pos.x > 0 && pos.x < grid->screenSize.x - 1 && pos.y > 0 && pos.y <= grid->screenSize.y)
		{
			
			int gridX = floor(pos.x / grid->GridSize);
			int gridY = floor(pos.y / grid->GridSize);

			if (gridX != obj->collisionCellX || gridY != obj->collisionCellY)
			{
				int index = gridX + gridY * grid->gridCountX;

				grid->collisionGrid[index].collidersInCell.push_back(obj);
				grid->collisionGrid[obj->collisionCellIndex].RemoveObj(obj);

				obj->collisionCellX = gridX;
				obj->collisionCellY = gridY;
				obj->collisionCellIndex = index;
			}

			//In cell collision
			for (int j = 0; j < grid->collisionGrid[obj->collisionCellIndex].collidersInCell.size(); j++)
			{
				GameObject* collider = grid->collisionGrid[obj->collisionCellIndex].collidersInCell[j];

				if (collider != obj)
				{
					if (!collider->IsActive) continue;

					if (!CheckCollisionMatrix(collider->layer, obj->collisionMatrix))
					{
						continue;
					}
					//if (!grid->colliders->CheckCollisionMatrix(collider->layer, obj->collisionMatrix)) continue;
					//std::cout << "true" << std::endl;
					Vector2 colliderPos = collider->Position;
					double colliderRadius = collider->radius;

					//overlap circle
					if (fabs((pos.x - colliderPos.x) * (pos.x - colliderPos.x)
						+ (pos.y - colliderPos.y) * (pos.y - colliderPos.y))
						<= (obj->radius + colliderRadius) * (obj->radius + colliderRadius))
					{
						obj->OnCollision();
						collider->OnCollision();
					}
				}
			}

			for (int j = 0; j < 8; j++)
			{
				int neighboorIndex = grid->collisionGrid[obj->collisionCellIndex].neighboorsIndex[j];

				if (neighboorIndex == -1) continue;

				for (int k = 0; k < grid->collisionGrid[neighboorIndex].collidersInCell.size(); k++)
				{

					GameObject* colliderObj = grid->collisionGrid[neighboorIndex].collidersInCell[k];
					Vector2 colliderPos = colliderObj->Position;
					double colliderRadius = colliderObj->radius;

					if (!colliderObj->IsActive) continue;
					if (!CheckCollisionMatrix(colliderObj->layer, obj->collisionMatrix)) continue;
					//std::cout << "true" << std::endl;

					//overlap circle
					if (fabs((pos.x - colliderPos.x) * (pos.x - colliderPos.x)
						+ (pos.y - colliderPos.y) * (pos.y - colliderPos.y))
						<= (obj->radius + colliderRadius) * (obj->radius + colliderRadius))
					{
						obj->OnCollision();
						colliderObj->OnCollision();
					}
				}
			}
		}*/
	}
}

void Collision2D::AddCollider(Grid* grid, GameObject* objectToAdd, int GameObjectlength)
{
	for (int i = 0; i < GameObjectlength - 1; i++)
	{
		GameObject* obj = grid->colliders[i];

		grid->colliders.push_back(obj);
		//grid->colliders.push_back(objectToAdd[i]);

		Vector2 pos = objectToAdd[i].Position;

		if (pos.x > 0 && pos.x < grid->screenSize.x && pos.y > 0 && pos.y < grid->screenSize.y)
		{
			int gridX = floor(pos.x / grid->GridSize);
			int gridY = floor(pos.y / grid->GridSize);

			grid->collisionGrid[gridX + gridY * grid->gridCountX].collidersInCell.push_back(obj);

			objectToAdd[i].collisionCellX = gridX;
			objectToAdd[i].collisionCellY = gridY;
			objectToAdd[i].collisionCellIndex = gridX + gridY * grid->gridCountX;
			//std::cout << "GridX: " << gridX << ", GridY: " << gridY << " Index: " << gridX + gridY * gridCountX << std::endl;
		}
	}
	

}

bool Collision2D::CheckCollisionMatrix(int layer, int collsionMatrix)
{
	//std::cout << collsionMatrix << " " << layer << " " << ((collsionMatrix >> layer) & 1) << std::endl;
	bool check = (collsionMatrix & layer);
	return check;
}
