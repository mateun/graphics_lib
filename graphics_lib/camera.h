#pragma once
#include "api.h"
#include <DirectXMath.h>

using namespace DirectX;

class GRAPHICS_LIB_API FBCamera {

public:
	FBCamera();
	FBCamera(FXMVECTOR position, FXMVECTOR camTarget, FXMVECTOR camUp);

	XMMATRIX GetViewMatrix() const;
	XMMATRIX GetProjectionMatrix() const;

	void SetPosition(FXMVECTOR position) { XMStoreFloat3(&_position, position); }
	void SetCameraTarget(FXMVECTOR target) { XMStoreFloat3(&_camTarget, target); };
	void SetCameraUpVector(FXMVECTOR up) { XMStoreFloat3(&_camUp, up); }

	XMVECTOR GetPosition() { return XMLoadFloat3(&_position); }
	XMVECTOR GetTarget() { return XMLoadFloat3(&_camTarget); }
	XMVECTOR GetCamUp() { return XMLoadFloat3(&_camUp); }

private:
	XMFLOAT3 _position;
	XMFLOAT3 _camTarget;
	XMFLOAT3 _camUp;
		 
};
