#include "stdafx.h"
#include "camera.h"

FBCamera::FBCamera()
{
	FBCamera(XMVectorSet(0, 0, -10, 0), XMVectorSet(0, 0, 0, 0), XMVectorSet(0, 1, 0, 0), 1.5f, (float) 800.0f/600.0f, 1, 100);
}

FBCamera::FBCamera(FXMVECTOR position, FXMVECTOR camTarget, FXMVECTOR camUp, float vfov, float ar, float nearClip, float farClip)
{
	XMStoreFloat3(&_position, position);
	XMStoreFloat3(&_camTarget, camTarget);
	XMStoreFloat3(&_camUp, camUp);
	_vfov = vfov;
	_ar = ar;
	_nearClip = nearClip;
	_farClip = farClip;
}

XMMATRIX FBCamera::GetProjectionMatrix() const
{
	return DirectX::XMMatrixPerspectiveFovLH(_vfov, _ar, _nearClip, _farClip);
}

XMMATRIX FBCamera::GetViewMatrix() const
{	
	return  DirectX::XMMatrixLookAtLH(XMLoadFloat3(&_position), XMLoadFloat3(&_camTarget), XMLoadFloat3(&_camUp));
}
