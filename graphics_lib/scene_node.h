#pragma once
#include "api.h"
#include <vector>
#include <DirectXMath.h>
#include "graphics_lib.h"

using namespace DirectX;

class GRAPHICS_LIB_API FBSceneNode {
public:
	void addChild(FBSceneNode* child);
	virtual void update(long frameTime);
	virtual void render(FBGraphics* );
	XMVECTOR position;
	
private:
	std::vector<FBSceneNode*> _children;
};
