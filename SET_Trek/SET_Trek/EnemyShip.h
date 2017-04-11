/*
* Filename:         EnemyShip.h
* Project:          PROG2215 - G.A.S. - Assignment - 01 - SET Trek
* Programmer:       Lev Cocarell
* Date:             2017-02-01
* Description:
* Source: Russ' example
*/

#pragma once
#include "GameLevel.h"
#include "SpriteSheet.h"
#include "Planet.h"

class EnemyShip
{
public:
	float   x_ship_pos; // screen location (top left corner of sprite)
	float   y_ship_pos;
	int     velocity;
	float   angle;
	int     x_ship_dest;
	int     y_ship_dest;
	bool    engaged;
	bool    collided;
	int     width;      // width of sprite in pixels
	int     height;     // height of sprite in pixels					
	int     x_ship_start_pos;
	int     y_ship_start_pos;
	int		totalDistance;
	int     EnemyShipLocationXinGrid;
	int		EnemyShipLocationYinGrid;
	bool    boostersActivated; 
	int y_ship_distance;
	int x_ship_distance;
	SpriteSheet* EnemyShipBMP;
	EnemyShip();
	~EnemyShip();
	SpriteSheet* GetEnemyShipBmp();
	void SetEnemyShipBmp(SpriteSheet* enemyShipBitmap);	
	

};
