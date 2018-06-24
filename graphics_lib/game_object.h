#pragma once
#include <vector>
#include "triangle.h"
#include "camera.h"
#include "graphics_lib.h"

class FBGameObject {

public:
	bool renders = true;
	
	void setPosition(XMFLOAT3 pos) { _position = pos;  }
	void setPosition(FXMVECTOR pos) { XMStoreFloat3(&_position, pos); }
	void setPosition(float x, float y, float z) { _position.x = x; _position.y = y; _position.z = z; }

	void setScale(float uni) { _scaleXYZ.x = uni; _scaleXYZ.y = uni; _scaleXYZ.z = uni; }
	void setScale(float x, float y, float z) {
		_scaleXYZ.x = x; 
		_scaleXYZ.y = y;
		_scaleXYZ.z = z;
	}

	std::vector<FBTriangle> meshTriangles;
	virtual void update(long frameTime) = 0;
	virtual void render(FBGraphics* graphics, FBCamera* camera) = 0;

protected: 
	XMFLOAT3 _position;
	XMFLOAT3 _scaleXYZ;

};
