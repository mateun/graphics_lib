#pragma once
#include "api.h"
#include "scene_node.h"
#include "graphics_lib.h"
#include "camera.h"

class GRAPHICS_LIB_API FBSceneGraph {
public: 
	virtual void update(long frameTime) = 0;
	virtual void render(FBGraphics*, FBCamera) = 0;
	virtual FBSceneNode* getRootNode() = 0;
	virtual void addRootNode(FBSceneNode*) = 0;
};

class GRAPHICS_LIB_API TreeSceneGraph : public FBSceneGraph {
public:
	void update(long frameTime) override;
	void render(FBGraphics*, FBCamera) override;
	FBSceneNode* getRootNode() override;
	void addRootNode(FBSceneNode*) override;

private:
	FBSceneNode * _rootNode;
};
