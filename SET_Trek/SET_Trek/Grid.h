/*
* Filename:         Grid.h
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description:
* This file contains the class definition for Grid class object. The grid 
* is used in the game to access coordinates of game objects and assets. It also used 
* to randomly place Planet objects in different grid coordinates based on certain 
* game events (collision, out bounds detection).
*/


#pragma once
#include "SpriteSheet.h" 
#include "Planet.h"


class Grid
{	
public:
	
	//Data Members 
	int xRows;
	int yCols;
	int sector_grid_array[10][10];	//grid array initialized to a 10 x 10 over display

	//Constructor
	Grid();
	~Grid();

	//Methods 
	void Reset_Grid();
	void Randomize_Grid();	

};

