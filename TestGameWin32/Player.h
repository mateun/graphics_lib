#pragma once
#include <scene_node.h>
#include <graphics_lib.h>
#include <vector>
#include <camera.h>

class Player : public FBSceneNode {
public:
	Player(std::vector<FBTriangle> meshTris);
	void render(FBGraphics*, FBCamera cam) override;

private:
	std::vector<FBTriangle> _meshTris;
};
