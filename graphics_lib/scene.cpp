#include "stdafx.h"
#include "scene.h"

void FBScene::addCamera(const FBCamera * camera)
{
	_cameras.push_back(camera);

}

void FBScene::addGameObject(FBGameObject * gameObject)
{
	_gameObjects.push_back(gameObject);
}

void FBScene::setMainCamera(FBCamera * cam)
{
	_mainCamera = cam;
}
	

void FBScene::update(long frametime)
{
	for (const auto& go : _gameObjects)
	{
		go->update(frametime);
	}
}

void FBScene::render(FBGraphics & graphics)
{
	if (_mainCamera == nullptr) {
		throw std::runtime_error("No _mainCamera has been set!");
	}

	for (const auto& go : _gameObjects) {
		go->render(&graphics, _mainCamera);
	}
}
