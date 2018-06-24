#pragma once
#include <game_object.h>
#include <DirectXMath.h>

class Terrain : public FBGameObject {

public:
	void update(long) override;
	void render(FBGraphics*, FBCamera*) override;
};
