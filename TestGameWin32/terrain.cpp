#include "stdafx.h"
#include "terrain.h"

void Terrain::update(long)
{
}

void Terrain::render(FBGraphics * graphics, FBCamera *camera)
{
	graphics->renderTriangleList(meshTriangles, XMLoadFloat3(&_position),
		XMVectorSet(0, 1, 0, 0),
		0.0f, XMLoadFloat3(&_scaleXYZ),
		XMVectorSet(0.6f, 0.3f, 0.2f, 0),
		*camera);
}
