/*
* Filename:         SpriteSheet.h
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description:
* This source file contains the SpriteSheet class header file that was originally sourced
* from the "Whats a Creel" Direct2D tutorial and the example supplied in GAS
* class. It has been modified and appended with extra methods to fit the requirements 
* in assingment 2. As well, this class borrows from Kitty's Code Blog on how to implement 
* Direct2D graphic objects. It has several methods added to it by programmer for Assignement 1
* and 2. 
*/


#pragma once

 //This is the WIC codec header - we need this to decode image files
#include "Graphics.h" //This includes both Windows and D2D libraries
//Remember to add "windowscodecs.lib" to your Linker/Input/AdditionalDependencies


class SpriteSheet
{
	Graphics* gfx; //Reference to the Graphics class
	ID2D1Bitmap* bmp; //This will hold our loaded and converted Bitmap file
	ID2D1Effect* chromakeyEffect;
	ID2D1Effect* affineTransformEffect;
	int  sprite_width;      // width of sprite in pixels
	int  sprite_height;     // height of sprite in pixels
	int  sprites_across;   // how many sprites across in our image there are for each row 

public:
	//Constructor
	SpriteSheet(wchar_t* filename, Graphics* gfx);
	SpriteSheet(wchar_t* filename, Graphics* gfx, int sprite_width, int sprite_height);
	//Destructor
	~SpriteSheet();
	//Draw methods for bitmaps to the render target
	void Draw(float x, float y, float c, float d, float angle);
	void DrawBackground();

	//Add chromakey effects (on game load)
	void Add_Chromakey(float r, float g, float b, float input, float tolerance);
	

};