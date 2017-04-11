/*
* Filename:         Ship.h
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description:
* This source file contains the definition for the Ship object that is controlled
* by the player to move the Enterprise bitmap around the SectorMap during the game.
* The ship has energy and science points that are derived from harvesting planet object
* resources. Vector math is used to calculate the movement and rotation of the Ship object
* based on mouse events. During the game, the Ship object is composed of two bitmaps, in order 
* to give it more detail.
*/

#pragma once
#include "GameLevel.h"
#include "SpriteSheet.h"

class Ship
{
public:
	//Data Members 
	int     x_ship_start_pos;
	int     y_ship_start_pos;
	int     width;      // width of sprite in pixels
	int     height;     // height of sprite in pixels
	int     x_ship_dest;
	int     y_ship_dest;
	int     velocity;
	int     destination;
	int     shipLocationXinGrid;
	int		shipLocationYinGrid;
	int     currentPlanetX;
	int     currentPlanetY;
	int		sciencePoints;
	int		energyLevel; 	//points
	float   x_ship_pos; // screen location (top left corner of sprite)
	float   y_ship_pos;	
	float   x_ship_distance;
	float   y_ship_distance;
	float	angle; //used for rotation transform effect
	float   totalDistance;
	bool    engaged;
	bool    collided;
	bool	marsVisited;
	bool	earthVisited;
	bool	saturnVisited;
	SpriteSheet* enterpriseShipBMP; //used to display bitmap


	//Constructor 
	Ship();
	//Destructor
	~Ship();

	//Getters and Setters 
	SpriteSheet* GetEnterpriseBmp();
	void SetEnterpriseBmp(SpriteSheet* enterprisebitmap);

	
};
