/*
* Filename:         Graphics.cpp
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description:
* Source: The contents of this class are based on "What's a Kreel" tutorial and
* example from class.
* NOTE: Comments in this file are from example.
*/


#include "Graphics.h"

/***********************************************************************************
The intent of the Graphics class is to handle our DirectX calls, and to be largely responsible 
for managing the rendertarget.
******************************************************************************************/

//Constructor for Graphics class
Graphics::Graphics()
{
	factory = NULL;
	rendertarget = NULL;
	brush = NULL;
}


//Destructor for Graphics class
//Note that all COM objects we instantiate should be 'released' here 
//Look for comments on COM usage in the corresponding header file.
Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();
	if (brush) brush->Release();

	//Katty
	if (Direct3DDevice) Direct3DDevice->Release();
	if (Direct2DDevice) Direct2DDevice->Release();
	if (Direct2DBackBuffer) Direct2DBackBuffer->Release();
	if (DXGISwapChain) DXGISwapChain->Release();
}



//Provide some comments for each of the methods below.
//Be sure you get a sense of what is happening, and resolve any issues you have understanding these
// methods, their parameters, returns and so on.
bool Graphics::Init(HWND windowHandle)
{
	D2D1_FACTORY_OPTIONS options;
	ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), &options, reinterpret_cast<void **>(&Direct2D));


	if (res != S_OK) return false;



	RECT rect;
	GetClientRect(windowHandle, &rect); //set the rect's right and bottom properties = the client window's size



	// Set feature levels supported by our application
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};


	// This flag adds support for surfaces with a different color channel ordering
	// than the API default. It is required for compatibility with Direct2D.
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	// Create Direct3D device and context
	ID3D11Device *device;
	ID3D11DeviceContext *context;
	D3D_FEATURE_LEVEL returnedFeatureLevel;

	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creationFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION,
		&device, &returnedFeatureLevel, &context);


	device->QueryInterface(__uuidof(ID3D11Device1), (void **)&Direct3DDevice);
	context->QueryInterface(__uuidof(ID3D11DeviceContext1), (void **)&Direct3DContext);

	//Get the underlying DXGI device of the Direct3D device (we’ll need this temporarily to set up interoperability with Direct2D, see above)
	IDXGIDevice *dxgiDevice;
	Direct3DDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&dxgiDevice);

	//Create the Direct2D device from the DXGI device:
	Direct2D->CreateDevice(dxgiDevice, &Direct2DDevice);


	//Create the Direct2D device context(to be used as the rendering interface later) from the Direct2D device :
	Direct2DDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &rendertarget);

	// Get the GPU we are using
	IDXGIAdapter *dxgiAdapter;
	dxgiDevice->GetAdapter(&dxgiAdapter);

	// Get the DXGI factory instance
	IDXGIFactory2 *dxgiFactory;
	dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));


	//Then we describe the swap chain:
	// Describe Windows 7-compatible Windowed swap chain
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };

	swapChainDesc.Width = 0;
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;


	// Create DXGI swap chain targeting a window handle (the only Windows 7-compatible option)
	dxgiFactory->CreateSwapChainForHwnd(Direct3DDevice, windowHandle, &swapChainDesc, nullptr, nullptr, &DXGISwapChain);

	// Get the back buffer as an IDXGISurface (Direct2D doesn't accept an ID3D11Texture2D directly as a render target)
	IDXGISurface *dxgiBackBuffer;
	DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));


	// Get screen DPI
	FLOAT dpiX, dpiY;
	Direct2D->GetDesktopDpi(&dpiX, &dpiY);

	// Create a Direct2D surface (bitmap) linked to the Direct3D texture back buffer via the DXGI back buffer
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), dpiX, dpiY);

	rendertarget->CreateBitmapFromDxgiSurface(dxgiBackBuffer, &bitmapProperties, &Direct2DBackBuffer);


	// Set surface as render target in Direct2D device context
	rendertarget->SetTarget(Direct2DBackBuffer);

	if (dxgiBackBuffer) dxgiBackBuffer->Release();
	if (dxgiFactory) dxgiFactory->Release();
	if (dxgiAdapter) dxgiAdapter->Release();
	if (dxgiDevice)  dxgiDevice->Release();
	if (context)  context->Release();
	if (device)   device->Release();


	//Constant checking results 
	if (res != S_OK) return false;
	
	res = rendertarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (res != S_OK) return false;
	return true;

}



void Graphics::ClearScreen(float r, float g, float b) 
{
	rendertarget->Clear(D2D1::ColorF(r, g, b));
}






void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	rendertarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);	

}


