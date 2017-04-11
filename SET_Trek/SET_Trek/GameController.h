/*
* Filename:         GameController.h
* Project:          PROG2215 - G.A.S. - Assignment - 01 - SET Trek
* Programmer:       Lev Cocarell
* Date:             2017-02-01
* Description:
* The contents of this class are based on "What's a Kreel" tutorial. 
*/

#pragma once

#include "GameLevel.h"
#include "Graphics.h"


//NOTE: This will be a Singleton class (constructor is private)
class GameController
{


	GameController() {}
	static GameLevel* currentLevel;
public:
	static bool Loading;
	static void Init();
	static void LoadInitialLevel(GameLevel* lev);
	static void SwitchLevel(GameLevel* lev);
	static void Render();
	static void Update(int xPosCord, int yPosCord);
};