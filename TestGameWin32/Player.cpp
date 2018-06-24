#include "stdafx.h"
#include "Player.h"

Player::Player(std::vector<FBTriangle> meshTris)
{
	_meshTris = meshTris;
}

void Player::render(FBGraphics* graphics, FBCamera cam) {
	static float rot = 0; rot += 0.05f;
	graphics->renderTriangleList(_meshTris, XMLoadFloat3(&position), DirectX::XMVectorSet(0, 1, 0, 0), rot, DirectX::XMVectorSet(1, 1, 1, 0), XMVectorSet(100, 100, 100, 0), cam);
}