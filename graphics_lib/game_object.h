#pragma once
#include <vector>
#include "triangle.h"

class FBGameObject {

public:
	bool renders = true;
	std::vector<FBTriangle> meshTriangles;
	virtual void update(long frameTime) = 0;

};
