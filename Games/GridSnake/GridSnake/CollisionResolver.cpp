#include "CollisionResolver.h"


CollisionResolver::CollisionResolver(void)
{
}


CollisionResolver::~CollisionResolver(void)
{
}

void CollisionResolver::registerCollision(GridCell * collisionCell, const GridCellOccupant * collider)
{
	assert( collisionCell != NULL && collider != NULL && collisionCell->getOccupant() != collider );

	if( collisionCell != NULL && collider != NULL && collisionCell->getOccupant() != collider )
	{
		keys.push_back(collisionCell);
		collisions.insert( std::pair<GridCell *, const GridCellOccupant *>( collisionCell, collider ) );
	}
}

bool CollisionResolver::resolveCollisions()
{
	bool allResolved = false;

	// TODO: Add code to resolve collisions

	return allResolved;
}

void CollisionResolver::clearCollisions()
{
	for(std::vector<GridCell *>::const_iterator it = keys.begin(); it != keys.end(); ++it)
	{
		collisions.erase( *it );
	}
}

static const bool checkCollision(GridCell * collisionCell)
{
	bool collision = false;

	assert( collisionCell != NULL );

	if( collisionCell != NULL )
	{
		if( collisionCell->getState() != EMPTY )
		{
			collision = true;
		}
	}

	return collision;
}