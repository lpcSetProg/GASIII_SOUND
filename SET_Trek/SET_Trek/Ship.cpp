/*
* Filename:         Ship.cpp
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


#include "Ship.h"

//=============================================================================
// Ship Constructor
//=============================================================================
/*
* Default Constructor: Background
* Description: No immediate value are set in constructor.
*/
Ship::Ship()
{

	x_ship_pos = 0; //0 to 10 on x axis 
	y_ship_pos = 100; 
	x_ship_dest = 0;
	y_ship_dest = 100;
	x_ship_distance = 0;
	y_ship_distance = 0;	
	totalDistance = 0;
	energyLevel = 900; //default energy level
	velocity = 9; // initially same as player ship
	angle = 0; // initially zero degree angle
	collided = false;
	engaged = false;
	marsVisited = false;
	earthVisited = false;
	saturnVisited = false;

	width = 100;
	height = 75;

	currentPlanetX = 0;
	currentPlanetY = 0;

}



//=============================================================================
// Ship Getters and Setters
//=============================================================================
SpriteSheet* Ship::GetEnterpriseBmp()
{
	return enterpriseShipBMP;
}
void Ship::SetEnterpriseBmp(SpriteSheet* enterprisebitmap)
{
	enterpriseShipBMP = enterprisebitmap;

}


//=============================================================================
// Ship Destructor
//=============================================================================
Ship::~Ship()
{


}