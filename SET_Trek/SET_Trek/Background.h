/*
* Filename:         Background.h
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description:
* This source file contains the class for the Background object. It is used to 
* display the static space background to the game at all times. Unlike the other
* graphic objects, this bitmap does not change position during gameplay. It is updated 
* in the render event during each cycle of gameplay.
*/

#pragma once
#include "Grid.h"



class Background
{
public:
	//Data Members 
	SpriteSheet* backgroundBmp; // type of sprite sheet used to instantiate the sector background.
	
	//Constructor 
	Background();

	//Destructor 
	~Background();

	//Getters and Setters 
	SpriteSheet* GetBackgroundBmp();
	void SetBackgroundBmp(SpriteSheet* backgroundBmp);

};

