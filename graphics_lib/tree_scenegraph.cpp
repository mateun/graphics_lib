#include "stdafx.h"
#include "scenegraph.h"

void TreeSceneGraph::update(long frameTime) {
	_rootNode->update(frameTime);
}

void TreeSceneGraph::render(FBGraphics* graphics) {
	_rootNode->render(graphics);
}

FBSceneNode* TreeSceneGraph::getRootNode() {
	return _rootNode;
}

void TreeSceneGraph::addRootNode(FBSceneNode * rootNode)
{
	_rootNode = rootNode;
}
