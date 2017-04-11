/*
* Filename:         Planet.h
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description:
* This source file contains the class defintion  for the Planet object used to
* render the Planet bitmaps to the screen. There are three seperate planets (Earth,
* Mars, Saturn) and each planet has different attributes and methods related to the game.
*/


#pragma once
#include "Grid.h"
#include "Asset.h"
#include <tchar.h>


class Planet
{
public:
	//Data Members 
	float	x_pos;
	float	y_pos;
	int		planet_id;
	int     width_planet;      // width of sprite in pixels
	int     height_planet;     // height of sprite in pixels
	int		min;
	int		max;
	int		collisionRadius;
	SpriteSheet* earthBMP;
	SpriteSheet* marsBMP;
	SpriteSheet* saturnBMP;


	//Constructor 
	Planet();
	//Destructor 
	~Planet();

	//Getters and Setters 
	SpriteSheet* GetEarthBmp();
	SpriteSheet* GetMarsBmp();
	SpriteSheet* GetSaturnBmp();
	void SetEarthBmp(SpriteSheet* earthbitmap);
	void SetMarsBmp(SpriteSheet* marsbitmap);
	void SetSaturnBmp(SpriteSheet* saturnbitmap);

	//Methods
	int GenerateEnergyPoints();
	int GenerateSciencePoints();
	void EarthMessage();
	void MarsMessage();
	void SaturnMessage();
};

