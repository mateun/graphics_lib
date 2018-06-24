#pragma once
#include "api.h"
#include "camera.h"
#include "game_object.h"
#include "graphics_lib.h"
#include <vector>

/*
	An FBScene describes all the objects which 
	together form a scene of the game. 
	It consists of a bunch of cameras, where one is the currently active one. 
	And it has a list of game objects (game objects can have children). 

	A scene has public update and render methods. 

*/


class GRAPHICS_LIB_API FBScene {
public:
	void addCamera(const FBCamera* camera);
	void addGameObject(FBGameObject* gameObject);
	void setMainCamera(FBCamera* cam);

	// todo add lights

	void update(long frametime);
	void render(FBGraphics& graphics);

private:
	FBCamera * _mainCamera;
	std::vector<const FBCamera*> _cameras;
	std::vector<FBGameObject*> _gameObjects;


	


};
