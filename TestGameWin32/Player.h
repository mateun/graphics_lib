#pragma once
#include <scene_node.h>
#include <graphics_lib.h>
#include <vector>

class Player : public FBSceneNode {
public:
	Player(std::vector<FBTriangle> meshTris);
	void render(FBGraphics*) override;

private:
	std::vector<FBTriangle> _meshTris;
};
