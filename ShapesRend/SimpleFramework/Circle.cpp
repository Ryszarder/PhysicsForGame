#include "Circle.h"

void Circle::Draw(LineRenderer& lines)
{
	lines.DrawCircle(centre, radius);
}