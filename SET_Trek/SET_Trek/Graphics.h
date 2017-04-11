/*
* Filename:         Graphics.h
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-02-01
* Description:
* Source: The contents of this class are based on "What's a Kreel" tutorial and 
* example from class. 
* NOTE: Comments in this file are from example. 
*/

#pragma once
#include "proto.h"


class Graphics
{
	//Below, these are all COM interfaces we're using to create D2D resources.
	//We release them as part of the ~Graphics deconstructor... or bad things can happen
	ID2D1Factory* factory; //The factory allows us to create many other types of D2D resources
	ID2D1DeviceContext* rendertarget; //this is typically an area in our GPU memory.. like a back buffer 
	ID2D1SolidColorBrush* brush; //Note this COM interface! Remember to release it!
	

	//From Katty
	ID3D11Device* Direct3DDevice;
	// Direct3D device context
	ID3D11DeviceContext1 *Direct3DContext;
	// Direct2D device
	ID2D1Device *Direct2DDevice;
	// DXGI swap chain
	IDXGISwapChain1 *DXGISwapChain;
	// Direct2D target rendering bitmap
	// (linked to DXGI back buffer which is linked to Direct3D pipeline)
	ID2D1Bitmap1 *Direct2DBackBuffer;
	// Direct2D factory access
	ID2D1Factory1 *Direct2D;

	// Windows Imaging Component factory access
	IWICImagingFactory2 *ImageFactory;



public:
	Graphics();
	~Graphics();
	bool Init(HWND windowHandle);

	// Represents an object that can receive drawing commands. Interfaces that inherit from ID2D1RenderTarget
	// render the drawing commands they receive in different ways. 
	ID2D1DeviceContext* GetRenderTarget()
	{
		return rendertarget;
	}
	IDXGISwapChain1* GetSwapChain()
	{
		return DXGISwapChain;
	}

	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float c, float y, float radius, float r, float g, float b, float a);

};
