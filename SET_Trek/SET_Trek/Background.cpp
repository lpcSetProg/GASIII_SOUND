/*
* Filename:         Background.cpp
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description:
* This source file contains the definition for the Background class object.
* It used to render the space background bitmap to the screen.
*/

#include "Background.h"

//=============================================================================
// Background Default Constructor
//=============================================================================
/*
* Default Constructor: Background
* Description: No immediate value are set in constructor.
*/
Background::Background()
{
}


//=============================================================================
// Background Getters and Setters
//=============================================================================
SpriteSheet* Background::GetBackgroundBmp()
{

	return backgroundBmp;

}

void Background::SetBackgroundBmp(SpriteSheet* backgroundBitmap)
{
	backgroundBmp = backgroundBitmap;
}


//=============================================================================
// Grid Destructor
//=============================================================================
Background::~Background()
{
}
