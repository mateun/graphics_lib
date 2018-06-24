#pragma once
#include <vector>
#include "triangle.h"
#include "camera.h"
#include "graphics_lib.h"

class FBGameObject {

public:
	bool renders = true;
	std::vector<FBTriangle> meshTriangles;
	virtual void update(long frameTime) = 0;
	virtual void render(FBGraphics* graphics, FBCamera* camera) = 0;

};
