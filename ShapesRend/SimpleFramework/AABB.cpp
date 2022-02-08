#include "AABB.h"

void AABB::Draw(LineRenderer& lines)
{
	lines.AddPointToLine(glm::vec2(xMin, yMin));
	lines.AddPointToLine(glm::vec2(xMin, yMax));
	lines.AddPointToLine(glm::vec2(xMax, yMax));
	lines.AddPointToLine(glm::vec2(xMax, yMin));
	lines.FinishLineLoop();
}
