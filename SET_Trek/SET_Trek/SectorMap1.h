/*
* Filename:         SectorMap1.h
* Project:          PROG2215 - G.A.S. - Assignment - 02 - SET Trek II
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description:
* This source file contains the defintion for the SectorMap1 class, which is derived
* from GameLevel//Game event methods used by Game Controller and Game Level (SectorMap1)
* Source: Planet events for "Exploration Game". 
*/


#pragma once
#include "GameLevel.h"
#include "Ship.h"
#include "EnemyShip.h"
#include "Planet.h"
#include "Background.h"


class SectorMap1 : public GameLevel
{
	//Datamembers for SectorMap1
	int frame;
		
	//Assets used in SectorMap1
	Planet Mars;
	Planet Saturn;
	Planet Earth;
	Ship Enterprise; 
	Ship EDetail;
	EnemyShip Klingon;
	Background SpaceSectorMapBackground;
	Grid gameBoard;

public:
	//Game event methods used by Game Controller and Game Level (SectorMap1)
	void Load() override;
	void Unload() override;
	void Update(int xPosCord, int yPosCord) override; //modified to take in mouse events
	void Render() override;

	//Drawing methods related to graphic objects
	void load_Background_Bitmap();
	void load_Ship_Bitmap();
	void load_EnemyShip_Bitmap();
	void load_Planets_Bitmap();	
	void ApplyChromaKeyEffects();
	void Render_Planets();
	void Reset_Sector_Map();

	//Player and enemy position related methods
	void move_ship_position(int xPosCord, int yPosCord, int velocity);
	void move_enemy_ship_position(int xStartCord, int yStartCord, int velocity);
	void Determine_Enterprise_Distance();
	void Determine_Enemy_Distance();
	void shipLocationInGrid();
	void EnemyShipLocationInGrid();

	//Detection methods 
	void collisionDetection();
	void boundsDetection();
	void energyDetection();
	void boosterDetection();
	void planetCollisionDetection();

	//Planet events for "Exploration Game"
	void ExploreEarth();
	void ExploreMars();
	void ExploreSaturn();

};
