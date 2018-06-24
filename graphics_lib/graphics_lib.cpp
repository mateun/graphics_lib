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
	_d3d9dev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(r, g, b), 1.0f, 0);

}

void DX9Graphics::swapBuffers() {
	_d3d9dev->Present(NULL, NULL, NULL, NULL);
}

void DX9Graphics::renderTriangleList(std::vector<FBTriangle> triangles, DirectX::FXMVECTOR position, DirectX::FXMVECTOR rotationAxis, float rotRadians, DirectX::FXMVECTOR scale, DirectX::FXMVECTOR materialDiffuseColor, FBCamera camera)
{
	#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)

	struct customvertex {
		FLOAT x, y, z;
		FLOAT nx, ny, nz;
	};

	std::vector<customvertex> vertices;
	for each (const auto& t in triangles) {
		customvertex v1 = { t.p1.x, t.p1.y, t.p1.z, t.n1.x, t.n1.y, t.n1.z };
		customvertex v2 = { t.p2.x, t.p2.y, t.p2.z, t.n2.x, t.n2.y, t.n2.z };
		customvertex v3 = { t.p3.x, t.p3.y, t.p3.z, t.n3.x, t.n3.y, t.n3.z };
		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
	}
	

	LPDIRECT3DVERTEXBUFFER9 vb;
	_d3d9dev->CreateVertexBuffer(3 * triangles.size() * sizeof(customvertex), 0, CUSTOMFVF, D3DPOOL_MANAGED, &vb, NULL);
	VOID* pvoid;
	vb->Lock(0, 0, (void**)&pvoid, 0);
	memcpy(pvoid, vertices.data(), sizeof(customvertex) * triangles.size() * 3);
	vb->Unlock();

	// create directional light
	D3DLIGHT9 dlight;
	D3DMATERIAL9 material;
	ZeroMemory(&dlight, sizeof(dlight));
	dlight.Type = D3DLIGHT_DIRECTIONAL;
	dlight.Diffuse = D3DXCOLOR(1.8f, 1.8f, 1.8f, 1.0f);
	dlight.Direction = *(D3DXVECTOR3*)(&XMVectorSet(0.7f, -0.3f, -0.0f, 0));
	
	_d3d9dev->SetLight(0, &dlight);
	_d3d9dev->LightEnable(0, TRUE);

	ZeroMemory(&material, sizeof(material));
	material.Diffuse = *(D3DXCOLOR*)(&materialDiffuseColor);
	material.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	
	_d3d9dev->SetMaterial(&material);
	_d3d9dev->BeginScene();
	_d3d9dev->SetFVF(CUSTOMFVF);

	// pipeline transformed
	static float rot = 0; rot += 0.005f;
	
	DirectX::XMMATRIX mrot = DirectX::XMMatrixRotationAxis(rotationAxis, rotRadians);
	DirectX::XMMATRIX mtransl = DirectX::XMMatrixTranslationFromVector(position);
	DirectX::XMMATRIX mscale = DirectX::XMMatrixScaling(XMVectorGetX(scale), XMVectorGetY(scale), XMVectorGetZ(scale));
	DirectX::XMMATRIX mworld = DirectX::XMMatrixMultiply(mrot, mscale);
	mworld = DirectX::XMMatrixMultiply(mworld, mtransl);
	_d3d9dev->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&mworld);

	// camera stuff
	_d3d9dev->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&camera.GetViewMatrix());

	_d3d9dev->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&camera.GetProjectionMatrix());

	// Set some renderflags... TODO move into settable parameter of some form. 
	_d3d9dev->SetRenderState(D3DRS_LIGHTING, TRUE);
	_d3d9dev->SetRenderState(D3DRS_ZENABLE, TRUE);
	_d3d9dev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(200, 200, 200));
	_d3d9dev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	_d3d9dev->SetStreamSource(0, vb, 0, sizeof(customvertex));
	_d3d9dev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, triangles.size());

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
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	HRESULT result = _d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &_d3d9dev);
}

DX9Graphics::~DX9Graphics() {
	OutputDebugString(L"in destr\n\n");
	_d3d9dev->Release();
	_d3d9dev = nullptr;
	_d3d9->Release();
	_d3d9 = nullptr;
}


