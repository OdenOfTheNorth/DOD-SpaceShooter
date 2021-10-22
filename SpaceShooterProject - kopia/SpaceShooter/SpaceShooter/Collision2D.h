#pragma once
#include <iostream>
#include <vector>

#include "Vector2.h"
#include "Player.h"
#include "Enemy.h"
#include "Data.h"

#pragma once
#include <map>
#include <math.h>
#include <iostream>
#include <vector>

struct GridCell
{

	Vector2 worldPosition;
	int gridIndex;
	int neighboorsIndex[8];

	std::vector<GameObject*> collidersInCell;

public:
	void RemoveObj(GameObject* objToRemove)
	{
		for (int i = 0; i < collidersInCell.size(); i++)
		{
			if (collidersInCell[i] == objToRemove)
			{
				collidersInCell.erase(collidersInCell.begin() + i);				
			}
		}
	}
};

struct Grid {
	std::vector<GameObject*> colliders;
	std::vector<GridCell> collisionGrid;
	double GridSize = 60;

	int gridCountX, gridCountY;

	Vector2 screenSize;
};

class Collision2D
{
public:
	Collision2D(Grid* grid);
	static void Update(Grid* grid);
	static void AddCollider(Grid* grid, GameObject* objectToAdd, int GameObjectlength);
	static bool CheckCollisionMatrix(int layer, int collsionMatrix);
};

