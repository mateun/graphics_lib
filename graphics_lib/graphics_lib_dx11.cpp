#include "stdafx.h"
#include "graphics_lib.h"
#include <dxgi1_2.h>

DX11Graphics::DX11Graphics(HWND hwnd, int width, int height) {

	// Create the device and context
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0
	};

	HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE,

		nullptr, D3D11_CREATE_DEVICE_DEBUG, featureLevels, 1, D3D11_SDK_VERSION, &_device, nullptr, &_context);
	if (FAILED(hr)) {
		throw std::runtime_error("Failed to init D3D11 device!");
	}

	// Setup swap chain
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.Width = width;
	swapChainDesc.Height = height;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// no multisampling for now, cause too complicated
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	IDXGIDevice* dxgiDevice = nullptr;
	if (FAILED(hr = _device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice)))) {
		throw std::runtime_error("failed to create dxgi device!");
	}

	IDXGIAdapter* dxgiAdapter = nullptr;
	if (FAILED(hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter)))) {
		throw std::runtime_error("failed to create dxgi adapter!");
	}

	IDXGIFactory2* dxgiFactory = nullptr;
	if (FAILED(hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory)))) {
		throw std::runtime_error("failed to create dxgi factory!");
	}


	if (FAILED(hr = dxgiFactory->CreateSwapChainForHwnd(dxgiDevice, hwnd, &swapChainDesc, nullptr, nullptr, &_swapChain))) {
		if (dxgiDevice != nullptr) dxgiDevice->Release();
		if (dxgiAdapter != nullptr) dxgiAdapter->Release();
		if (dxgiFactory != nullptr) dxgiFactory->Release();
		throw std::runtime_error("failed to create swap chain!");
	}

	// Release the unneeded stuff anyway...
	if (dxgiDevice != nullptr) dxgiDevice->Release();
	if (dxgiAdapter != nullptr) dxgiAdapter->Release();
	if (dxgiFactory != nullptr) dxgiFactory->Release();

	// Creating a RTV
	ID3D11Texture2D* backBuffer;
	if (FAILED(hr = _swapChain->GetBuffer(0, _uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)))) {
		throw std::runtime_error("failed to create backbuffer!");
	}

	if (FAILED(hr = _device->CreateRenderTargetView(backBuffer, nullptr, &_rtv))) {
		throw std::runtime_error("failed to create rtv!");
	}
	if (backBuffer != nullptr) backBuffer->Release();

	// Depth stencil view stuff
	D3D11_TEXTURE2D_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.Width = width;
	dsDesc.Height = height;
	dsDesc.MipLevels = 1;
	dsDesc.ArraySize = 1;
	dsDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dsDesc.Usage = D3D11_USAGE_DEFAULT;
	dsDesc.SampleDesc.Count = 1;
	dsDesc.SampleDesc.Quality = 0;
	

	if (FAILED(hr = _device->CreateTexture2D(&dsDesc, nullptr, &_depthStencilBuffer))) {
		throw std::runtime_error("failed to create depth stencil buffer!");
	}

	if (FAILED(hr = _device->CreateDepthStencilView(_depthStencilBuffer, nullptr, &_depthStencilView))) {
		throw std::runtime_error("failed to create depth stencil view!");
	}

	_context->OMSetRenderTargets(1, &_rtv, _depthStencilView);

	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinDepth = 0;
	viewPort.MaxDepth = 1;
	_context->RSSetViewports(1, &viewPort);

}

DX11Graphics::~DX11Graphics() {

}

void DX11Graphics::clear(int, int, int) {
	XMVECTORF32 bg = { 0.2f, 0.2f, 0.9f, 1.0f };
	_context->ClearRenderTargetView(_rtv, reinterpret_cast<const float*>(&bg));
	_context->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

}

void DX11Graphics::swapBuffers() {
	HRESULT hr = _swapChain->Present(0, 0);
	if (FAILED(hr)) {
		throw std::runtime_error("failed to present swap chain!");
	}
}

void DX11Graphics::renderTriangleList(std::vector<FBTriangle>, DirectX::FXMVECTOR position, DirectX::FXMVECTOR rotationAxis, float rotRadians,
	DirectX::FXMVECTOR scale,
	DirectX::FXMVECTOR materialDiffuseColor,
	FBCamera camera) {

}