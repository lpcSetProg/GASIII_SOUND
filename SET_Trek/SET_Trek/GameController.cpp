/*
* Filename:         GameController.cpp
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description:
* This source file contains the GameController class that originally was sourced
* from the "Whats a Creel" Direct2D tutorial and the example supplied in GAS
* class. It has been modified and appended with extra methods to fit the requirements
* in assingment 2. As well, this class borrows from Kitty's Code Blog on how to implement
* Direct2D graphic objects. These methods are used in the SectorMap and in WinMain file
* to trigger events in game related to graphics and gameplay. 
* NOTE: For Assigment 2, this class has been modified to take in mouse events from user 
* (source from winMain) to control the player (Enterprise Ship) the game.
*/


#include "GameController.h"

//Global values for game controller.
GameLevel* GameController::currentLevel;
bool GameController::Loading;



/*
* Method: Init
* Description:
* This method was originally from the "What's a Kreel" tutorial and the
* the example file provided in class.
* Parameters: N/A
* Returns: N/A
*
*/
void GameController::Init()
{
	Loading = true;
	currentLevel = 0;
}




/*
* Method: LoadInitialLevel
* Description:
* This method was originally from the "What's a Kreel" tutorial and the
* the example file provided in class.
* Parameters: GameLevel* lev
* Returns: N/A
*
*/
void GameController::LoadInitialLevel(GameLevel* lev)
{
	Loading = true; //This can help us avoid loading activity while rendering
	currentLevel = lev;
	currentLevel->Load();
	Loading = false;
}




/*
* Method: SwitchLevel
* Description:
* This method was originally from the "What's a Kreel" tutorial and the
* the example file provided in class.
* Parameters: GameLevel* lev
* Returns: N/A
*
*/
void GameController::SwitchLevel(GameLevel* lev)
{
	Loading = true;
	currentLevel->Unload();
	lev->Load();
	delete currentLevel;
	currentLevel = lev;
	Loading = false;
}



/*
* Method: Render
* Description:
* This method was originally from the "What's a Kreel" tutorial and the
* the example file provided in class.
* Parameters: N/A
* Returns: N/A
*
*/
void GameController::Render()
{
	if (Loading) return;//nice! Do not update or render if the scene is loading.
	currentLevel->Render();
}



/*
* Method: Update
* Description:
* This method was originally from the "What's a Kreel" tutorial and the
* the example file provided in class. It has been modified for Assignment 2 
* to take in mouse events from user (source from winMain) to control the player
* (Enterprise Ship) the game.
* Parameters: int xPosCord, int yPosCord (mouse coordinates)
* Returns: N/A
*
*/
void GameController::Update(int xPosCord, int yPosCord) //x and y 
{
	if (Loading) return; //nice! Do not update or render if the scene is loading.
	currentLevel->Update(xPosCord, yPosCord); //pass cordinates to update function.s

}