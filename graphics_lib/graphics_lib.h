// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GRAPHICS_LIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GRAPHICS_LIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once
#include "api.h"

#include <Windows.h>
#include <d3d9.h>
#include <vector>
#include <DirectXMath.h>
#include "triangle.h"
#include "camera.h"
#include <d3d11.h>
#include <dxgi1_2.h>



// This class is exported from the graphics_lib.dll
class GRAPHICS_LIB_API FBGraphics {
public:
	virtual ~FBGraphics() {
		OutputDebugString(L"<<<<<<<<<<<<<<< in base destr.");
	}
	virtual void clear(int red, int green, int blue) = 0;
	virtual void swapBuffers() = 0;
	virtual void renderTriangleList(std::vector<FBTriangle>, DirectX::FXMVECTOR position, DirectX::FXMVECTOR rotationAxis, float rotRadians, 
										DirectX::FXMVECTOR scale,
										DirectX::FXMVECTOR materialDiffuseColor,
										FBCamera camera) = 0;
};

class GRAPHICS_LIB_API DX9Graphics : public FBGraphics {
public:
	DX9Graphics(HWND);
	~DX9Graphics() override;
	void clear(int, int, int) override;
	void swapBuffers() override;
	void renderTriangleList(std::vector<FBTriangle>, DirectX::FXMVECTOR position, DirectX::FXMVECTOR rotationAxis, float rotRadians, 
						DirectX::FXMVECTOR scale,
						DirectX::FXMVECTOR materialDiffuseColor,
						FBCamera camera) override;

private:
	LPDIRECT3D9 _d3d9;
	LPDIRECT3DDEVICE9 _d3d9dev;
};

class GRAPHICS_LIB_API DX11Graphics : public FBGraphics {
public:
	DX11Graphics(HWND, int w, int h); 
	~DX11Graphics() override;
	void clear(int, int, int) override;
	void swapBuffers() override;
	void renderTriangleList(std::vector<FBTriangle>, DirectX::FXMVECTOR position, DirectX::FXMVECTOR rotationAxis, float rotRadians,
		DirectX::FXMVECTOR scale,
		DirectX::FXMVECTOR materialDiffuseColor,
		FBCamera camera) override;
private:
	ID3D11Device * _device;
	ID3D11DeviceContext* _context;
	IDXGISwapChain1* _swapChain;
	ID3D11RenderTargetView* _rtv;
	ID3D11Texture2D* _depthStencilBuffer;
	ID3D11DepthStencilView* _depthStencilView;
};

extern GRAPHICS_LIB_API int ngraphics_lib;

GRAPHICS_LIB_API int fngraphics_lib(void);
