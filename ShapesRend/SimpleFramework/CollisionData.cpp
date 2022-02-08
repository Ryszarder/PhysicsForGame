#include "CollisionData.h"

void CollisionData::Draw(LineRenderer& lines)
{
	/*if (depth > 0)
	{
		lines.DrawLineSegment(worldPos, worldPos + normal * depth);
	}*/
	
	lines.DrawLineSegment(worldPos2 - normal * depth, worldPos + normal * depth);
}