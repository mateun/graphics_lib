#pragma once
#include <game_object.h>
#include <DirectXMath.h>

class Ship : public FBGameObject {

public:
	void update(long ft) override;
	void render(FBGraphics* graphics, FBCamera* camera) override;
};
