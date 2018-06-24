#include "stdafx.h"
#include "ship.h"

void Ship::update(long ft)
{
	// literally do nothing for now...
}

void Ship::render(FBGraphics * graphics, FBCamera * camera)
{
	static float rot = 0; rot += 0.003f;
	graphics->renderTriangleList(meshTriangles, XMLoadFloat3(&_position), 
		XMVectorSet(0, 1, 0, 0), 
		-rot, XMLoadFloat3(&_scaleXYZ), 
		XMVectorSet(1, 1, 1, 0), 
		*camera);
}
