/*
* Filename:         main.cpp
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-13-03
*
* This source file contains the winMain for C++ Win32 game "SET TREK II".
* This game uses Direct2D
* This main has been modified for Assignment 2 to add the functionality of mouse 
* coordinates for control of player ship.
* The default cursor has been changed to a "hand" symbol.
* If the player collides with the enemy ship, the sector map is reset.
* NOTE:
* The original version of the game was based on the "Whats a Creel" Direct2D tutorial 
* and the example supplied in GAS class. It has been modified and appended with extra methods to fit the requirements
* in assingment 2. As well, this class borrows from Kitty's Code Blog on how to implement
* Direct2D graphic objects. 
* 
*/

#include "proto.h"
#include "constants.h"
#include "Graphics.h"
#include "SectorMap1.h"
#include "GameController.h"
#include "resource.h"


//global variables
Graphics* graphics; //pointer to graphics object
int xPosCord; //xPos for mouse coordinates 
int yPosCord; //yPos for mouse coordinates 


//========================================================================
// Window event callback function
//========================================================================
LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam )
{

	//If user clicks on red x of window - return 0 
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }
	else if (uMsg == WM_LBUTTONUP)
	{
		//ADDED FOR ASSIGNMENT 2:
		//Mouse coordinates for control 
		xPosCord = GET_X_LPARAM(lParam);
		yPosCord = GET_Y_LPARAM(lParam);
	}
	
//NOTE From Tutorial:
//BIG CHANGE! We are not Drawing/rendering here! 
// We've moved this down to the message handling loop below - RUSS

	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}


//========================================================================
// Starting point for a Windows application
// Parameters are:
//   hInstance. Handle to the current instance of the application
//   hPrevInstance. Always NULL, obsolete parameter
//   lpCmdLine. Pointer to null-terminated string of command line arguments
//   nCmdShow. Specifies how the window is to be shown
//========================================================================
int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmd,
	int nCmdShow
)
{

	//NOTE From Tutorial WHATS A CREEL tutuorial:
	//
	WNDCLASSEX windowclass;  //zero window class 
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hCursor = LoadCursor(NULL, IDC_HAND); //changed default cursor 
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;  //background color of window
	windowclass.hInstance = hInstance;  //instance of application 
	windowclass.lpfnWndProc = WindowProc; // the procedure from above - - what event handling is 
	windowclass.lpszClassName = "MainWindow";  // CLASS NAME --> name of the class
	windowclass.style = CS_HREDRAW | CS_VREDRAW; // Style are different options -- CS_HREDRAW --> when window is resized will redraw horizontally -- CS_VRE -- redraw vert  

	RegisterClassEx(&windowclass); // call with pointer to window class function -- WNDCLASSEX windowclass


	RECT rect = { 0, 0, 1024, 768 };//Do these numbers look significant to you? What are they?
	AdjustWindowRectEx(&rect, WS_OVERLAPPED, false, WS_EX_OVERLAPPEDWINDOW);



	//Below is another important process to understand... what are we doing?
	//Why is this connected to rect we just defined above? - russ

	//https://msdn.microsoft.com/en-us/library/windows/desktop/ms632680(v=vs.85).aspx  -- whats a kreel 
	// MainWindow is class, Title bar - Direct X shell, WS_OVERLAPPEDWINDOW (title bar and close bar), x, y (pos)
	HWND windowhandle = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW, 
		"MainWindow", 
		"SET_Trek_2017", 
		WS_OVERLAPPEDWINDOW, 
		100, 
		100, 
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		0 
	);


	//ADDED FOR ASSIGNMENT 2:
	//Mouse coordinates are set to -1 initially.
	xPosCord = -1;
	yPosCord = -1;


	if (!windowhandle) return -1;


	graphics = new Graphics();
	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return -1;
	}


	GameLevel::Init(graphics);
	ShowWindow(windowhandle, nCmdShow);
	GameController::LoadInitialLevel(new SectorMap1());


#pragma region GameLoop
	//Below, we have essentially an infinite loop that will keep the window running and will dispatch/show messages
	//As many people will tell you, most Windows you see are just infinite loops waiting for some kind of work-flow or 
	//system-based interuption.

	//Note - Our message handling has changed from the first demo code.
	//Here, we use a PeekMessage to avoid locking the graphics/windoProc
	//when a message has to be dispatched.
	MSG message;
	message.message = WM_NULL; //Do not have this set to WM_QUIT, which has a specific context
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{

			xPosCord = -1;
			yPosCord = -1;
			//This allows us to send a message to the WindowProc IF there is one
			DispatchMessage(&message);
		}
		else
		{
			//Update Routine... we've moved the code for handling updates to GameController
			GameController::Update(xPosCord, yPosCord);
		    
			//Render Routine... This is very modular. GameController now handles the rendering
			graphics->BeginDraw();
			GameController::Render();
			graphics->EndDraw();
			// Present (new for Direct2D 1.1)
			DXGI_PRESENT_PARAMETERS parameters = { 0 };
			parameters.DirtyRectsCount = 0;
			parameters.pDirtyRects = nullptr;
			parameters.pScrollRect = nullptr;
			parameters.pScrollOffset = nullptr;

			HRESULT res = graphics->GetSwapChain()->Present1(1, 0, &parameters);
		
		}
	}

#pragma endregion
	delete graphics;
	return 0;
}

