#include "stdafx.h"
#include "player_char_go.h"

void PlayerChar::update(long ft)
{
	// todo: just do some business logic here...
}

void PlayerChar::render(FBGraphics * gr, FBCamera* camera)
{
	static float rot = 0; rot += 0.0f;
	gr->renderTriangleList(meshTriangles, XMLoadFloat3(&_position), XMVectorSet(0, 1, 0, 0), -rot, XMVectorSet(_scale, _scale, _scale, 0), XMVectorSet(1, 0, 0.2f, 0), *camera);
	
}
