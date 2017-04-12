/*
* Filename:         Grid.h
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description:
* This file contains the class definition for Grid class object. The grid
* is used in the game to access coordinates of game objects and assets. It also used
* to randomly place Planet objects in different grid coordinates based on certain
* game events (collision, out bounds detection). No immediate values are set for the Grid class at start of game. 
* Grid values need to be randomaly generated in Load() method of SectorMethod1 class.
* The grid is represented by a multidimensional 10 x 10 array. 
*/

#include "Grid.h"


//=============================================================================
// Grid Default Constructor
//=============================================================================
/*
* Default Constructor: Grid
* Description: No immediate value are set in constructor.
*/
Grid::Grid()
{}




//=============================================================================
// Grid Methods
//=============================================================================
/*
* Method Name: Randomize_Grid()
* Description: Generic grid adder 
* Param: N/A
* Returns: N/A
*/
void Grid::Randomize_Grid()
{
	
	srand(time(NULL)); // pseudo-random number generator is initialized 
	int random_element_id = 0;
	int dice = 0;
	dice = rand() % 100;
	//Loop through Y-Axis of grid 
	for (int i = 0; i < 10; i++)
	{
		//Loop through X-Axis of grid 
		for (int j = 0; j < 10; j++)
		{
			int dice = 0; //dice are initialized 
			dice = rand() % 100; //generate a rand between 0 and 99
			if (dice < 5) //if the number is less than five 
			{
				//Assign random element to array  
				random_element_id = rand() % 3 + 1; //generate a number between 1-3 and assign value to grid array number 
				sector_grid_array[i][j] = random_element_id;  //what planet where 
			}
		}
	}	
}


/*
* Method: Reset_Grid
* Description:
* This method iterates through the grid and set all elements to zero. 
* This allows planets to be reset in grid positions on start of new screen. 
* Parameters: N/A
* Returns: N/A
*
*/
void Grid::Reset_Grid()
{
	//Iterate through multidimensional 10 x 10 array (represented by grid) 
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			//Set all elements of the grid to zero
			sector_grid_array[x][y] = 0;
		}
	}
}



//=============================================================================
// Grid Destructor
//=============================================================================
/*
* Desctructor: EnemyShip
*/
Grid::~Grid()
{


}

