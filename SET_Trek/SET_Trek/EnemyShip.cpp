/*
* Filename:         EnemyShip.cpp
* Project:          PROG2215 - G.A.S. - Assignment - 01 - SET Trek
* Programmer:       Lev Cocarell
* Date:             2017-02-01
* Description:
* This file contains the class defintions for the EnemyShip object.  Vector math is used to 
* calculate the movement and rotation of the Ship object based on mouse events. The enemy ship
* The EnemyShip starts on the opposite side of the screen from the PlayerShip. The EnemyShip will
* move towards the PlayerShip anytime that the PlayerShip is under movement (See PlayerShip). 
* The EnemyShip is rotated towards the PlayerShip as it progresses along. The EnemyShip will 
* start off moving at the same speed as the PlayerShip UNTIL it gets to within 2 grid squares 
* of PlayerShip then it gets a 10% boost to its speed to try to catch the Player Ship.
*/

#include "EnemyShip.h"


//=============================================================================
// EnemyShip Constructor
//=============================================================================
/*
* Constructor: EnemyShip
* Description:
* The values and default positions of the enemyShip are set 
* in the SectorMap1 level. 
*/
EnemyShip::EnemyShip()
{
	x_ship_pos = 910; //default position (across from player)
	y_ship_pos = 100;  //default position (across from player)
	x_ship_dest = 0;
	y_ship_dest = 0;
	velocity = 9; // initially same as player ship
	engaged = false;
	collided = false;
	y_ship_distance = 0;
	x_ship_distance = 0;
	totalDistance = 0;
}


//=============================================================================
// EnemyShip Getters and Setters
//=============================================================================

SpriteSheet* EnemyShip::GetEnemyShipBmp()
{
	return EnemyShipBMP;

}

/*
* Method: SetEnemyShipBmp
* Description:
* This method
* Parameters: N/A
* Returns: N/A
*
*/
void EnemyShip::SetEnemyShipBmp(SpriteSheet* enemyShipBitmap)
{
	EnemyShipBMP = enemyShipBitmap;

}


//=============================================================================
// EnemyShip Destructor
//=============================================================================
/*
* Desctructor: EnemyShip
* Description:
*/
EnemyShip::~EnemyShip()
{
}

