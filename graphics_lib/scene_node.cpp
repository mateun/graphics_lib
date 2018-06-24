#include "stdafx.h"
#include "scene_node.h"
#include "graphics_lib.h"

void FBSceneNode::update(long frameTime) {
	for each (const auto& c in _children) {
		c->update(frameTime);
	}
}

void FBSceneNode::render(FBGraphics* graphics, FBCamera cam) {
	for each (const auto& c in _children) {
		c->render(graphics, cam);
	}
}

void FBSceneNode::addChild(FBSceneNode* child) {
	_children.push_back(child);
}