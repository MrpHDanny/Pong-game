#include "RectangleCollider.h"

RectangleCollider::RectangleCollider(unsigned int w, unsigned int h, Vector2 pos, Rigidbody* rb)
{
	setPosition(pos);
	width = w;
	height = h;
	parentBody = rb;
}
