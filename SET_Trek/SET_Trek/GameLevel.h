/*
* Filename:         GameLevel.h
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-02-01
* Description:
* Source: The contents of this class are based on "What's a Kreel" tutorial and 
* example from class. 
* NOTE:Comments in this file are from example. 
*/

#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"

class GameLevel
{
protected:
	static Graphics* gfx;

public:
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(int xPosCord, int yPosCord) = 0; //modified to take in player mouse positions
	virtual void Render() = 0;
};