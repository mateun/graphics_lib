#pragma once
#include <game_object.h>
#include <graphics_lib.h>
#include <camera.h>
#include <DirectXMath.h>
#include <vector>
#include <triangle.h>

using namespace DirectX;

class PlayerChar : public FBGameObject {


public:
	
	void update(long ft) override;
	void render(FBGraphics* gr, FBCamera* camera) override;
	
};

