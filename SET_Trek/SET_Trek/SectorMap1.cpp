/*
* Filename:         SectorMap1.cpp
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description:
* This source file contains the defintion for the SectorMap1 Class. This is where 
* the primary action of the SET TREK game events take place (though called in WinMain). 
* All graphic objects and character movements are handled and updated in the methods in
* this class. It is derived from the GameLevel class.
* NOTE:This class is based on the class "What's a Creel" referes to as the 
* "GameLevel" class in the tutorial. 
* NOTE: Energy point comparison methods  is not fully functional and has been defered. 
*/



#include "GameController.h"
#include "Graphics.h"
#include "SectorMap1.h"
#include "Ship.h"
#include "Planet.h"
#include "Grid.h"
#include "constants.h"



//=============================================================================
//  Load all game items
//=============================================================================
/*
* Method: Load
* Description:
* This method loads all render objects values and applies effects on each 
* update of project. Utilized in winMain game loop. 
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::Load()
{
	spaceTheme.createAudio();
	load_Background_Bitmap();
	load_Ship_Bitmap();
	load_EnemyShip_Bitmap();
	load_Planets_Bitmap();
	gameBoard = Grid();
	gameBoard.Randomize_Grid();
	ApplyChromaKeyEffects();
	
		
}


//=============================================================================
// Unload all game items
//=============================================================================
/*
* Method: Unload
* Description:
* This method removes all bitMaps used in the game.
* Called in winMain on closing of game loop.
* Parameters: N/A
* Returns: N/A
*/
void SectorMap1::Unload()
{
	//Delete all bitMaps used in the game
	delete Earth.earthBMP;
	delete Mars.earthBMP;
	delete Saturn.earthBMP;
	delete Enterprise.enterpriseShipBMP;
	delete SpaceSectorMapBackground.backgroundBmp;
	delete Klingon.EnemyShipBMP;
}


//=============================================================================
// Update all game items
//=============================================================================
/*
* Method: Update
* Description:
* This method continously updates key game functions in the WinMain.
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::Update(int xPosCord, int yPosCord)
{
	//Move the  Enterprise (player) ship according to the coordinates the user's mouse input
	move_ship_position(xPosCord, yPosCord, Enterprise.velocity);
	
	//Find Enterprise (player) ship
	Determine_Enterprise_Distance();

	//Find enemy distance 
	Determine_Enemy_Distance();
	//Move the enemy in relation to the Enterprise (player) ship
	move_enemy_ship_position(Klingon.x_ship_pos, Klingon.y_ship_pos, Klingon.velocity);
	
	
	Enterprise.engaged = false;


	//Ship locating methods 
	shipLocationInGrid();
	EnemyShipLocationInGrid();

	//Detection methods (continously looking for game actions) based
	collisionDetection();
	boundsDetection();
	energyDetection();
	boosterDetection();
	planetCollisionDetection();

}


//=============================================================================
// Render game items
//=============================================================================
/*
* Method: Render
* Description:
* This method renders (aka draws) all the bitmaps and graphic elements to the screen.
* Used in the winMain of the game. Continously updated throughout gameplay.
*
* Parameters: N/A
* Returns: N/A
*/
void SectorMap1::Render()
{
	//Clears the screen (to default green-screen value), hidden to player by background image
	gfx->ClearScreen(0.0f, 255.0f, 0.0f);

	//Draw the space sector background 
	SpaceSectorMapBackground.backgroundBmp->DrawBackground();

	//Places planets in grid randomly 
	Render_Planets();

	//Draw Enterprise (player) ship based on mouse x and y position of users coordinates, will rotate according to angle
	Enterprise.enterpriseShipBMP->Draw(Enterprise.x_ship_pos, Enterprise.y_ship_pos, 60, 0, Enterprise.angle);

	EDetail.enterpriseShipBMP->Draw(Enterprise.x_ship_pos, Enterprise.y_ship_pos, 60, 0, Enterprise.angle);
	//Draw Klingon (enemy-AI) ship based on mouse x and y position of users coordinates, will rotate according to angle
	Klingon.EnemyShipBMP->Draw(Klingon.x_ship_pos, Klingon.y_ship_pos, 44, 0, Klingon.angle);

}




//=============================================================================
// Move the Enterprise Player Ship
//=============================================================================

/*
* Method: move_ship_position
* Description:
* This method utilizes mouse coordinates from user (sourced from winMain and passed to parameters) 
* to move the Player Ship position across the SectorMap1 screen. As with the original version of the project
* each time ship reaches last grid width on the right, the grid is reset and randomized again.
* This method provides positions for the enemyShip to derive the PlayerShip location. 
* Parameters: int xPosCord, int yPosCord, int velocity
* Returns: N/A
*
*/
void SectorMap1::move_ship_position(int xPosCord, int yPosCord, int velocity)
{
	//If mouse "buttonUp" is not -1 (if the user has clicked the left button)
	if (xPosCord >= 0)
	{
		Enterprise.engaged = true;
		double result; // used for result of atan2 application

		Enterprise.velocity = velocity; //assign the default velocity to the player Ship
		Enterprise.x_ship_dest = xPosCord; //assign the x-mouse coordinate to the player Ship
		Enterprise.y_ship_dest = yPosCord; //assign the y-mouse coordinate to the player Ship


		Enterprise.y_ship_distance = Enterprise.y_ship_dest - Enterprise.y_ship_pos;

		Enterprise.x_ship_distance = Enterprise.x_ship_dest - Enterprise.x_ship_pos;

		//NOTE: The below method is sourced from a tutorial on implemtning the atan2 function in c++.
		//Explanation from: http://www.cplusplus.com/reference/cmath/atan2/
		//  "Returns the principal value of the arc tangent of y / x, expressed in radians.
		//	To compute the value, the function takes into account the sign of both arguments in order to determine the quadrant.
		//	In C++, this function is overloaded in <valarray>(see valarray atan2)."
		Enterprise.angle = atan2(Enterprise.y_ship_distance, Enterprise.x_ship_distance) * 180 / PI; //constant 3.1415926
		Enterprise.totalDistance = sqrt(pow(Enterprise.y_ship_distance, 2) + pow(Enterprise.x_ship_distance, 2));

	}
}



/*
* Method: boundsDetection
* Description:
* This method is modified version of a method that was utilized in Assignment 01.
* It is continously updated to determine if the PlayerShip (Enterprise) has left 
* the active screen. 
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::boundsDetection()
{
	//Get the width and height of the right-end quadrant of the graphics object. 
	//This represents the end of the game section. 
	float sectorWidth = gfx->GetRenderTarget()->GetSize().width / 10;
	float sectorHeight = gfx->GetRenderTarget()->GetSize().height / 10;

	//Check if outside of bounds Screen 
	if (Enterprise.x_ship_pos + sectorWidth >= gfx->GetRenderTarget()->GetSize().width)
	{
		// Reset the sector map, places planets in random sections of grid map
		Reset_Sector_Map();
	}
}



//=============================================================================
// Move Enemy (Klingon) Ship
//=============================================================================
/*
* Method: move_enemy_ship_position
* Description:
* This method uses vector math to move the EnemyShip position across the screen.
* (x,y) of the EnemyShip while it is moving (not static). This was sourced from: 
  http://www.cplusplus.com/reference/cmath/atan2/
* Parameters: int xStartCord, int yStartCord, int velocity
* Returns: N/A
*
*/
void SectorMap1::move_enemy_ship_position(int xStartCord, int yStartCord, int velocity) //add VELOCITY in param 
{
	if (Enterprise.engaged)
	{
		//Assign the Enterprise X,Y positions (mouse coordinates) to Klingon's destination
		Klingon.x_ship_dest = Enterprise.x_ship_pos;
		Klingon.y_ship_dest = Enterprise.y_ship_pos;

		double result;

		//Same vector math utilized for player movement (see above)
		Klingon.y_ship_distance = Klingon.y_ship_dest - Klingon.y_ship_pos;
		Klingon.x_ship_distance = Klingon.x_ship_dest - Klingon.x_ship_pos;
		Klingon.angle = atan2(Klingon.y_ship_distance, Klingon.x_ship_distance) * 180 / PI;
		Klingon.totalDistance = sqrt(pow(Klingon.y_ship_distance, 2) + pow(Klingon.x_ship_distance, 2));
	}
}



/*
* Method: Determine_Enterprise_Distance
* Description:
* This method uses vector math (distance formula) to find the distance between the coordinitates
* (x,y) of the PlayerShip while it is moving (not static). 
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::Determine_Enterprise_Distance()
{
	//Determine the current distance of the PlayerShip ship
	float currentDistance = sqrt(pow(Enterprise.y_ship_pos - Enterprise.y_ship_dest, 2) + pow(Enterprise.x_ship_pos - Enterprise.x_ship_dest, 2));

	if (currentDistance >= Enterprise.velocity)
	{
		Enterprise.y_ship_pos += (Enterprise.y_ship_distance / Enterprise.totalDistance) * Enterprise.velocity;  //
		Enterprise.x_ship_pos += (Enterprise.x_ship_distance / Enterprise.totalDistance) * Enterprise.velocity;
		Enterprise.engaged = true;
	}
}


/*
* Method: Determine_Enemy_Distance
* Description:
* This method uses vector math  (distance formula) to find the distance between the coordinitates 
* (x,y) of the EnemyShip while it is moving (not static).
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::Determine_Enemy_Distance()
{
	//Determine the current distance of the Klingon ship
	float currentDistance = sqrt(pow(Klingon.y_ship_pos - Klingon.y_ship_dest, 2) + pow(Klingon.x_ship_pos - Klingon.x_ship_dest, 2));

	//If the current distance is greater than or equal to the speed 
	if (currentDistance >= Klingon.velocity)
	{
		//If the Enemy ship's speed is not equal to zero
		if (Klingon.totalDistance != 0)
		{
			//Determine the positions of the Klingon ship
			Klingon.y_ship_pos += (Klingon.y_ship_distance / Klingon.totalDistance) * Klingon.velocity;
			Klingon.x_ship_pos += (Klingon.x_ship_distance / Klingon.totalDistance) * Klingon.velocity;
		}
		//Bool flag used for determining whether the Klingon is moving 
		Klingon.engaged = true;
	}
}


/*
* Method: shipLocationInGrid
* Description:
* This method determines the location of the PlayerShip in the grid the multidimensional array by locating it 
* in the Graphics object and its current x and y positions (derived from mouse coordinates). This captured in order to provide 
* location for collision detection with EnemyShip and Planet objects in the grid.
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::shipLocationInGrid()
{
	int shipLocationXinGrid; //instance variable 
	Enterprise.shipLocationXinGrid = (Enterprise.x_ship_pos / gfx->GetRenderTarget()->GetSize().width) * 10; //1024 
	int shipLocationYinGrid; //instance variable 
	Enterprise.shipLocationYinGrid = (Enterprise.y_ship_pos / gfx->GetRenderTarget()->GetSize().height) * 10; //768

}


/*
* Method: EnemyShipLocationInGrid
* Description:
* This method determines the location of the EnemyShip in the game grid (the multidimensional array) by locating it
* in the Graphics object and its current x and y positions on SectorMap1 screen. This captured in order to provide 
* location for collision detection with PlayerShip in the grid.
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::EnemyShipLocationInGrid()
{
	//Find position of enemyShip X coordinate by x-position
	Klingon.EnemyShipLocationXinGrid = (Klingon.x_ship_pos / 
		gfx->GetRenderTarget()->GetSize().width) * 10; //Portion of 1024 screen size
	//Find position of enemyShip Y coordinate by x-position																										
	Klingon.EnemyShipLocationYinGrid = (Klingon.y_ship_pos / 
		gfx->GetRenderTarget()->GetSize().height) * 10; //Portion of 768 screen size

																										
}


/*
* Method: collisionDetection
* Description:
* This method uses the current location of both Player and Enemy ships in the grid to determine 
* whether they have collided. If the player collides with the enemy ship, the sector map is reset and
* 300 Energy points are drained from the player's collection. If the player loses all energy points 
* the game is over. 
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::collisionDetection()
{
	//If the player and the enemy are in the same grid position
	if (Enterprise.shipLocationXinGrid == Klingon.EnemyShipLocationXinGrid  && Enterprise.shipLocationYinGrid == Klingon.EnemyShipLocationYinGrid)
	{
		//Collision message is displayed to user
		MessageBox(NULL, "Collision Detected!\n-300 Energy Points\n\n Avoid Damadge!","WARNING!!!", NULL);
		DWORD poo = spaceTheme.VolumeValue(9000);
		waveOutSetVolume(NULL, poo);
		//Player energy points are subtracted 
		Enterprise.energyLevel - 300;

		//Map is reset
		Reset_Sector_Map();
	}
}



/*
* Method: boosterDetection
* Description:
* This method ensures that the EnemyShip will start off moving at the same speed as the 
* PlayerShip. When the enemy ship (Klingon) it gets to within 2 grid squares of PlayerShip
* then it gets a 10% boost to its speed to try to catch the Player Ship.
* NOTE: This method is not totally functional and there is a logic flaw that might be preventing it
* from activing. Needs furthur work in next iteration of project.
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::boosterDetection()
{
	if (Enterprise.shipLocationXinGrid == Klingon.EnemyShipLocationXinGrid && Enterprise.shipLocationYinGrid == Klingon.EnemyShipLocationYinGrid)
	{
		Klingon.velocity = 9.9; // 10% increase
		Klingon.boostersActivated = true;
	}

}



/*
* Method: ApplyChromaKeyEffects()
* Description:
* As with Assignment 1, the Direct2D Chromakey effect is accomplished by converting a 
* given color plus or minus a tolerance to alpha. In this version of the project, 
* I utilized a modified version of the method that was more modular and able to apply 
* modified versions of the effect to all render targets and bitmaps used in the game. 
* In order to render the “blue-screen” background for the EnemyShip to transparent,
* I changed the R,G,B and tolerance  values to RGB = 0, 0, 1 (Blue). Tolerance is same value 
* as other bitmaps. *
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::ApplyChromaKeyEffects()
{
	Mars.GetMarsBmp()->Add_Chromakey(0.0, 1.0, 0.0, 0, 0.7);
	Saturn.GetSaturnBmp()->Add_Chromakey(0.0, 1.0, 0.0, 0, 0.7);
	Earth.GetEarthBmp()->Add_Chromakey(0.0, 1.0, 0.0, 0, 0.7);
	Enterprise.GetEnterpriseBmp()->Add_Chromakey(0.0, 1.0, 0.0, 0, 0.7);
	SpaceSectorMapBackground.GetBackgroundBmp()->Add_Chromakey(0.0, 1.0, 0.0, 0, 0.7);
	Klingon.GetEnemyShipBmp()->Add_Chromakey(0.0, 0.0, 1.0, 0, 0.7); //Klingon has special chromakey requirements (BLUE) 
	EDetail.GetEnterpriseBmp()->Add_Chromakey(0.0, 1.0, 0.0, 0, 0.7);

}




//=============================================================================
// SectorMap1 - Planet Related Methods
//=============================================================================

/*
* Method: Render_Planets
* Description:
* This method renders the planets to the grid class with randomized sector array. 
* If value of index of grid array is a planet, a selected planet (one of three bitmaps)
* will be rendered to the display. 
* Parameters: N/A
* Returns: N/A
*
*/

void SectorMap1::Render_Planets()
{
	//Grab the window client size of the entire window
	float sectorWidth = gfx->GetRenderTarget()->GetSize().width / 10;
	float sectorHeight = gfx->GetRenderTarget()->GetSize().height / 10;

	//Loop through Y-Axis of grid
	for (int i = 0; i < 10; i++)

		//Loop through X-Axis of grid
		for (int j = 0; j < 10; j++)
		{
			//Check if value at index is a planet
			if (gameBoard.sector_grid_array[i][j] >= 1 && gameBoard.sector_grid_array[i][j] <= 3)
			{
				//Value of planet
				switch (gameBoard.sector_grid_array[i][j])  // 
				{
					//Render Earth to client window with provided coordinates
				case EARTH: //earth
					Earth.earthBMP->Draw(j*sectorWidth, i*sectorHeight,
						((j*sectorWidth) + sectorWidth), ((i*sectorHeight) + sectorHeight), 0);
					break;
					//Render Mars to client window with provided coordinates
				case MARS:
					Mars.marsBMP->Draw(j*sectorWidth, i*sectorHeight, ((j*sectorWidth)
						+ sectorWidth), ((i*sectorHeight) + sectorHeight), 0);
					break;
					//Render Saturn to client window with provided coordinates
				case SATURN:
					Saturn.saturnBMP->Draw(j*sectorWidth, i*sectorHeight, ((j*sectorWidth)
						+ sectorWidth), ((i*sectorHeight) + sectorHeight), 0);

					break;
					//End case so process can be repeated
				default:
					break;
				}
			}
		}
}


/*
* Method: planetCollisionDetection
* Description:
* This method loops through the multidimensional grid object (gameBoard.sector_grid_array)
* and determines wether the player ship (Enterprise) has made contact with a Planet object.
* It has boolean flags that determine if a player ship has accessed the resources from a planet 
* so it cannot visit a planet twice before a grid has been reset. 
* NOTE: This method is not functioning 100%, and has several bugs (i.e is generating incorrect message for Earth/Mars).
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::planetCollisionDetection()
{
	//Loop through Y-Axis of grid
	for (int i = 0; i < 10; i++)
		//Loop through X-Axis of grid
		for (int j = 0; j < 10; j++)
		{
			//Ensure gameboard grid sector is not an empty grid
			if (gameBoard.sector_grid_array[i][j] != EMPTY_GRID_SECTION)
			{
				// Planets and ship collions are determined by:
				// comparing array elements to the ship x and y positions
				// (derived from the mouse coordinates) with 1-3 array elements 
				// (constants represented by planets).
				if (gameBoard.sector_grid_array[i][j] == EARTH) //Equals Earth in index
				{
					if (Enterprise.shipLocationXinGrid == j && Enterprise.shipLocationYinGrid == i)
					{
						if (Enterprise.earthVisited == false)
						{
							if (Enterprise.currentPlanetX != j && Enterprise.currentPlanetY != i)
							{
								ExploreEarth();
								Enterprise.earthVisited = true;
							}
						}

					}
				}
				else if (gameBoard.sector_grid_array[i][j] == MARS)
				{
					if (Enterprise.shipLocationXinGrid == j && Enterprise.shipLocationYinGrid == i)
					{
						if (Enterprise.marsVisited = false)
						{
							if (Enterprise.currentPlanetX != j && Enterprise.currentPlanetY != i)
							{
								ExploreMars();
								Enterprise.earthVisited = true;
							}
						}

					}
				}
				else if (gameBoard.sector_grid_array[i][j] == SATURN)
				{
					if (Enterprise.shipLocationXinGrid == j && Enterprise.shipLocationYinGrid == i)
					{
						if (Enterprise.saturnVisited == false)
						{
							if (Enterprise.currentPlanetX != j && Enterprise.currentPlanetY != i)
							{
								ExploreSaturn();
								Enterprise.saturnVisited = true;
							}
						}
					}
				}
			}
		} // end of for loop 
}


/*
* Method: ExploreEarth
* Description:
* This method displays the messages to the user related to "Planet Explorer"
* portion of game. Then returns energy points to user's ship if they requested
* them.
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::ExploreEarth()
{
	
	Earth.EarthMessage();
	Enterprise.energyLevel = Earth.GenerateEnergyPoints();
	Enterprise.sciencePoints = Earth.GenerateSciencePoints();
}


/*
* Method: ExploreMars
* Description:
* This method displays the messages to the user related to "Planet Explorer"
* portion of game. Then returns energy points to user's ship if they requested
* them.
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::ExploreMars()
{
	Mars.MarsMessage();
	Enterprise.energyLevel = Mars.GenerateEnergyPoints();
	Enterprise.sciencePoints = Mars.GenerateSciencePoints();
}


/*
* Method: ExploreSaturn
* Description:
* This method displays the messages to the user related to "Planet Explorer"
* portion of game. Then returns energy points to user's ship if they requested
* them.
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::ExploreSaturn()
{
	Saturn.SaturnMessage();
	Enterprise.energyLevel = Saturn.GenerateEnergyPoints();
	Enterprise.sciencePoints = Saturn.GenerateSciencePoints();
}





//=============================================================================
// SectorMap1 - Sector Map/Grid Related Methods
//=============================================================================

/*
* Method: Reset_Sector_Map
* Description:
* This method is used to reset the grid upon the start of the game,
* and when player has collided with enemy ship. 
* Parameters: N/A
* Returns: N/A
*/
void SectorMap1::Reset_Sector_Map()
{
	Enterprise.engaged = false;
	//Set the grid to zero
	gameBoard.Reset_Grid();
	//
	gameBoard.Randomize_Grid();

	//Player and enemy ship positions
	Enterprise.angle = 0;
	Enterprise.x_ship_pos = 0;
	Enterprise.y_ship_pos = 100;
	Klingon.y_ship_pos = 100;
	Klingon.x_ship_pos = 910;

	//Bool flags determine if planet has been visited
	Enterprise.earthVisited = false;
	Enterprise.marsVisited = false;
	Enterprise.saturnVisited = false;

}



//=============================================================================
// Bitmap Handling
//=============================================================================
/*
* Method: load_Background_Bitmap
* Description:
* This method
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::load_Background_Bitmap()
{
	SpaceSectorMapBackground.backgroundBmp = new SpriteSheet(
		L"test.bmp",
		gfx
	); //This is where we can specify our file system object!
}


/*
* Method: load_Ship_Bitmap
* Description:
* This method can specifies our file system object (ship bitmap)
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::load_Ship_Bitmap()
{
	Enterprise.enterpriseShipBMP = new SpriteSheet(
		L"ShipBase.bmp",
		gfx,
		(gfx->GetRenderTarget()->GetSize().width / 10),  // width
		(gfx->GetRenderTarget()->GetSize().height / 10)    // height
	); //This is where we can specify our file system object!

	EDetail.enterpriseShipBMP = new SpriteSheet(
		L"ShipDetail.bmp",
		gfx,
		(gfx->GetRenderTarget()->GetSize().width / 10),  // width
		(gfx->GetRenderTarget()->GetSize().height / 10)    // height
	);
}


/*
* Method: load_EnemyShip_Bitmap
* Description:
* This method
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::load_EnemyShip_Bitmap()
{
	Klingon.EnemyShipBMP = new SpriteSheet(
		L"EnemyShip.bmp",
		gfx,
		(gfx->GetRenderTarget()->GetSize().width / 10),  // width
		(gfx->GetRenderTarget()->GetSize().height / 10)    // height
	); //This is where we can specify our file system object!
}


/*
* Method: load_Planets_Bitmap
* Description:
* This method
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::load_Planets_Bitmap()
{
	//This is where we can specify our file system object!
	Earth.earthBMP = new SpriteSheet(
		L"Planet1.bmp",
		gfx,
		(gfx->GetRenderTarget()->GetSize().width / 10), // width
		(gfx->GetRenderTarget()->GetSize().height / 10)   // height
	);

	//This is where we can specify our file system object!
	Mars.marsBMP = new SpriteSheet(
		L"Planet2.bmp",
		gfx,
		(gfx->GetRenderTarget()->GetSize().width / 10), // width
		(gfx->GetRenderTarget()->GetSize().height / 10)   // height
	);

	//This is where we can specify our file system object!
	Saturn.saturnBMP = new SpriteSheet(
		L"Planet3.bmp",
		gfx,
		(gfx->GetRenderTarget()->GetSize().width / 10), // width
		(gfx->GetRenderTarget()->GetSize().height / 10)   // height
	);
}

//=============================================================================
// SectorMap1 - Energy Point Related Methods
//=============================================================================
/*
* Method: energyDetection
* Description:
* This method is incomplete and has been defered. 
* Parameters: N/A
* Returns: N/A
*
*/
void SectorMap1::energyDetection()
{
	LPCTSTR Caption = "Application Programming Interface";

	//if (energyLevelsGlob == 600)
	//{
	//	MessageBox(NULL,
	//		"Welcome to Win32 Application Development\n"
	//		"You will learn about functions, classes, "
	//		"communication, and other cool stuff\n"
	//		"Are you ready to rumble!!!!!!!!!!!!!!",
	//		Caption,
	//		MB_YESNOCANCEL | MB_ICONQUESTION);
	//	Reset_Sector_Map();
	//}
	//else if (energyLevelsGlob == 300)
	//{
	//	Reset_Sector_Map();
	//}
	//else if (energyLevelsGlob == 0)
	//{
	//	MessageBox(NULL,
	//		"GAME OVER DUDE",
	//		Caption,
	//		MB_YESNOCANCEL | MB_ICONQUESTION);
	//}

	//if (Enterprise.energyLevel == MAX_ENERGY_POINTS) //Enterprise is at 900
	//{
	//	//MessageBox(NULL, "Collision Detected!\n Warning you only have 600/900 Energy Points Left.\n Avoid Damadge!", NULL, NULL);

	//}
	//else if (Enterprise.energyLevel == ENERGY_LEVELS_LOW) //Enterprise is at 600 energy levels 
	//{
	//	MessageBox(NULL, "Collision Detected!\n Warning you only have 300/900 Energy Points Left.\n Avoid Damadge!", NULL, NULL);
	//}
	//else if (Enterprise.energyLevel == ENERGY_DANGER_LEVELS) //Enterprise is at 0 energy levels 
	//{

	//	MessageBox(NULL, "Collision Detected!\n Enterprise Destroyed!\n\nGAME OVER ", NULL, NULL);
	//	Enterprise.energyLevel == FULL_ENERGY_DAMADGE;
	//	exit(EXIT_FAILURE);
	//}


}
