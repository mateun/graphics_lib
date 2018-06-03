// graphics_lib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "graphics_lib.h"
#include <DirectXMath.h>
#include "dxsdk_legacy\d3dx9.h"




// This is an example of an exported variable
GRAPHICS_LIB_API int ngraphics_lib=0;

// This is an example of an exported function.
GRAPHICS_LIB_API int fngraphics_lib(void)
{
    return 42;
}

void DX9Graphics::clear(int r, int g, int b) {
	_d3d9dev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(r, g, b), 1.0f, 0);

}

void DX9Graphics::swapBuffers() {
	_d3d9dev->Present(NULL, NULL, NULL, NULL);
}

void DX9Graphics::renderTriangleList() {
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)


struct customvertex {
		FLOAT x, y, z;
		DWORD color;
	};

	customvertex vertices[] = {
		{ 2.5f, -3, 0,  D3DCOLOR_XRGB(0, 0, 255)},
		{ 0, 3, 0,  D3DCOLOR_XRGB(0, 255, 0) },
		{ -2.5f, -3, 0,  D3DCOLOR_XRGB(255, 0, 0) },
	};

	LPDIRECT3DVERTEXBUFFER9 vb;
	_d3d9dev->CreateVertexBuffer(3 * sizeof(customvertex), 0, CUSTOMFVF, D3DPOOL_MANAGED, &vb, NULL);
	VOID* pvoid;
	vb->Lock(0, 0, (void**)&pvoid, 0);
	memcpy(pvoid, vertices, sizeof(vertices));
	vb->Unlock();

	_d3d9dev->BeginScene();

	_d3d9dev->SetFVF(CUSTOMFVF);

	// pipeline transformed
	static float rot = 0; rot += 0.005f;
	
	DirectX::XMMATRIX world = DirectX::XMMatrixRotationY(rot);
	_d3d9dev->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&world);

	DirectX::XMVECTOR eye = DirectX::XMVectorSet(0, 0, 10.0f, 0);
	DirectX::XMVECTOR at = DirectX::XMVectorSet(0, 0, 0, 0);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0, 1, 0, 0);
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(eye, at, up);
	_d3d9dev->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&view);

	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(1.2f, 800 / 600, 1, 100);
	_d3d9dev->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&proj);

	_d3d9dev->SetRenderState(D3DRS_LIGHTING, FALSE);
	_d3d9dev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	_d3d9dev->SetStreamSource(0, vb, 0, sizeof(customvertex));
	_d3d9dev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	_d3d9dev->EndScene();
	
	vb->Release();

}

// This is the constructor of a class that has been exported.
// see graphics_lib.h for the class definition
DX9Graphics::DX9Graphics(HWND hwnd)
{
	_d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;

	HRESULT result = _d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &_d3d9dev);
}

DX9Graphics::~DX9Graphics() {
	OutputDebugString(L"in destr\n\n");
	_d3d9dev->Release();
	_d3d9dev = nullptr;
	_d3d9->Release();
	_d3d9 = nullptr;
}


