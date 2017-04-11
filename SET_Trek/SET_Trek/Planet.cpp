/*
* Filename:         Planet.cpp
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description:
* This source file contains the class defintion  for the Planet object used to
* render the Planet bitmaps to the screen. There are three seperate planets (Earth,
* Mars, Saturn) and each planet has different attributes and methods related to the game.
* Messages are generated for each planet. 
*/

#include "Planet.h"
#include <string.h>
#include "proto.h"
#include <string>


//=============================================================================
// Planet Constructor
//=============================================================================
Planet::Planet()
{
	x_pos = 0.0f;
	y_pos = 0.0f;
	planet_id = 0;
	int planet_1 = 1;
	int planet_2 = 2;
	int planet_3 = 3;	
}


//=============================================================================
// Planet Getters and Setters
//=============================================================================
//Setters for Planet bitmaps
void Planet::SetEarthBmp(SpriteSheet* earthbitmap)
{
	earthBMP = earthbitmap;
}
void Planet::SetMarsBmp(SpriteSheet* marsbitmap)
{
	marsBMP = marsbitmap;
}
void Planet::SetSaturnBmp(SpriteSheet* saturnbitmap)
{
	saturnBMP = saturnbitmap;
}

//Getters for Planet bitmaps.
SpriteSheet* Planet::GetEarthBmp() { return earthBMP; }
SpriteSheet* Planet::GetMarsBmp() { return marsBMP; }
SpriteSheet* Planet::GetSaturnBmp() { return saturnBMP; }


//=============================================================================
// Planet Methods
//=============================================================================

/*
* Method: GenerateEnergyPoints
* Description:
* This method returns a randomly generetaed amount of
* energy points between 0 and 300 (the max amount of energy 
* points). They are collected from a planet and sent 
* to the ship.
* Parameters: N/A
* Returns: int energyPoints
*
*/
int Planet::GenerateEnergyPoints()
{
	int xRan;
	xRan = rand() % 300 + 0; // Randomizing the number of energy points 

	int energyPoints = xRan;
	return energyPoints; // return energy points to Enterprise ship. 
}

/*
* Method: GenerateSciencePoints
* Description:
* This method returns a randomly generetaed amount of
* energy points between 0 and 100 (the max amount of science point on a planet).
* They are collected from a planet and sent
* to the ship.
* Parameters: N/A
* Returns: int energyPoints
*
*/
int Planet::GenerateSciencePoints()
{
	int xRan;
	xRan = rand() % 100 + 0; // Randomizing the number of energy points 

	int sciencePoints = xRan;
	return sciencePoints; // return energy points to Enterprise ship. 
}


//FIX THIS METHOD
/*
* Method: EarthMessage
* Description:
* Earth dialogue.
* Parameters: N/A
* Returns: N/A
*
*/
void Planet::EarthMessage()
{

	Planet pointsGenerator;
	int energyPoints = pointsGenerator.GenerateEnergyPoints();

	/*bool landingOnPlanet = false;*/

	/*if (landingOnPlanet = true)
	{*/
		std::string ScannerMessage = "Planetary Scan\n\nPlanet: EARTH\n\nEnergy Levels: " + std::to_string(energyPoints);
		MessageBoxA(NULL, ScannerMessage.c_str(), "PLANETARY SCAN", MB_OK);
		//landingOnPlanet = false;


		LPCTSTR Caption = "Orders Captain?";
		std::string test1 = "1. Replenish Energy?\n\n";
		int msgboxID = MessageBox(NULL, test1.c_str(), "Orders Captain?", MB_YESNO);

		switch (msgboxID)
		{
		case IDYES:
			MessageBox(NULL,
				"Energy Replenished!\n\n2.Gather Science?",
				Caption,
				MB_YESNO);
			//return energyPoints; //return e-points back to user 
			break;
		case IDNO:
			MessageBox(NULL, "2.Gather Science?", "Orders Captain?", MB_YESNO);
			if (IDYES)
			{
				MessageBox(NULL, "2.Science Gathered!\nLeave Orbit?", "Orders Captain?", MB_YESNO);
			}
			if (IDYES)
			{
				MessageBox(NULL, "BACK TO MISSION!", "Orders Captain?", MB_OK);
			}
			break;
		}
	//}
}


/*
* Method: MarsMessage
* Description:
* Mars dialogue
* Parameters: N/A
* Returns: N/A
*
*/
void Planet::MarsMessage()
{
	Planet pointsGenerator;
	int energyPoints = pointsGenerator.GenerateEnergyPoints();

	/*bool landingOnPlanet = false;

	if (landingOnPlanet = true)
	{*/
		std::string ScannerMessage = "Planetary Scan\n\nPlanet: MARS\n\nEnergy Levels: " + std::to_string(energyPoints);
		MessageBoxA(NULL, ScannerMessage.c_str(), "PLANETARY SCAN", MB_OK);
		//landingOnPlanet = false;


		LPCTSTR Caption = "Orders Captain?";
		std::string test1 = "1. Replenish Energy?\n\n";
		int msgboxID = MessageBox(NULL, test1.c_str(), "Orders Captain?", MB_YESNO);

		switch (msgboxID)
		{
		case IDYES:
			MessageBox(NULL,
				"Energy Replenished!\n\n2.Gather Science?",
				Caption,
				MB_YESNO);
			//return energyPoints; //return e-points back to user 
			break;
		case IDNO:
			MessageBox(NULL, "2.Gather Science?", "Orders Captain?", MB_YESNO);
			if (IDYES)
			{
				MessageBox(NULL, "2.Science Gathered!\nLeave Orbit?", "Orders Captain?", MB_YESNO);
			}
			if (IDYES)
			{
				MessageBox(NULL, "BACK TO MISSION!", "Orders Captain?", MB_OK);
			}
			break;
		}
	//}

}


/*
* Method: SaturnMessage
* Description:
* Saturn dialogue.
* Parameters: N/A
* Returns: N/A
*
*/
void Planet::SaturnMessage()
{
	Planet pointsGenerator;
	int energyPoints = pointsGenerator.GenerateEnergyPoints();

	//landing planet
	//bool landingOnPlanet = false;

	//if (landingOnPlanet = true)
	//{
		std::string ScannerMessage = "Planetary Scan\n\nPlanet: SATURN\n\nEnergy Levels: " + std::to_string(energyPoints);
		MessageBoxA(NULL, ScannerMessage.c_str(), "PLANETARY SCAN", MB_OK);
		/*landingOnPlanet = false;
*/

		LPCTSTR Caption = "Orders Captain?";
		std::string test1 = "1. Replenish Energy?\n\n";
		int msgboxID = MessageBox(NULL, test1.c_str(), "Orders Captain?", MB_YESNO);

		switch (msgboxID)
		{
		case IDYES:
			MessageBox(NULL,
				"Energy Replenished!\n\n2.Gather Science?",
				Caption,
				MB_YESNO);
			//return energyPoints; //return e-points back to user 
			break;
		case IDNO:
			MessageBox(NULL, "2.Gather Science?", "Orders Captain?", MB_YESNO);
			if (IDYES)
			{
				MessageBox(NULL, "2.Science Gathered!\nLeave Orbit?", "Orders Captain?", MB_YESNO);
			}
			if (IDYES)
			{
				MessageBox(NULL, "BACK TO MISSION!", "Orders Captain?", MB_OK);
			}
			break;
		}
	/*}*/
}


//=============================================================================
// Planet Destructor
//=============================================================================
Planet::~Planet()
{

}

