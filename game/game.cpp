//=========================================================
// This is just the starting point for your final project.
// You are expected to modify and add classes/files as needed.
// The code below is the original code for our first graphics
// project (moving the little green ship). 
//========================================================
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf; 
#include "GlobalConstants.h"
#include <time.h>
#include "Ship.h"
#include "Alien.h"
#include "AlienArmy.h"
#include "Missile.h"
#include "MissileGroup.h"
#include "Bomb.h"
#include "BombGroup.h"
#include "UI.h"

//============================================================
// YOUR HEADER WITH YOUR NAME GOES HERE. PLEASE DO NOT FORGET THIS
//============================================================

// note: a Sprite represents an image on screen. A sprite knows and remembers its own position
// ship.move(offsetX, offsetY) adds offsetX, offsetY to 
// the current position of the ship. 
// x is horizontal, y is vertical. 
// 0,0 is in the UPPER LEFT of the screen, y increases DOWN the screen

GameStateEnum resetState(int lives, int &destroyedAliens, GameStateEnum &currentState, AlienArmy &alienGroup);


int main()
{
    //const int WINDOW_WIDTH = 800; //dont need these now that WindowSize.h exists
    //const int WINDOW_HEIGHT = 600;

    srand(time(NULL)); //for random numbers later in loop
    int randNum;

    int lives = 5; //lives of human
    int destroyedAliens = 0; //number of aliens destroyed

    GameStateEnum currentState = WELCOME; //options include: WELCOME, LEVEL_ONE, LEVEL_TWO, ALIEN_WON, HUMAN_WON

 	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	window.setFramerateLimit(60); //Limit the framerate to 60 frames per second

    UI userInterface(window);
    Ship humanShip(window);
    AlienArmy alienGroup;
    MissileGroup manyMissiles;
    BombGroup manyBombs;

	while (window.isOpen())
	{
		Event event;
  		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) // "close requested" event: we close the window
   				window.close();
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
				{
                    manyMissiles.newMissile(humanShip.getPosition()); //handle space bar
				}
			}
            else if (event.type == Event::MouseButtonReleased)
            {
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                if (userInterface.detectStart(mousePos))
                {
                    currentState = LEVEL_ONE;

                    alienGroup.populateAlienList(currentState); //populate the alienArmy after pressing Start
                }
            }
		}

		//===========================================================
		// Everything from here to the end of the loop is where you put your
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================

		// draw background first, so everything that's drawn later 
		// will appear on top of background
        if (currentState == WELCOME)
        {
            userInterface.drawStartScreen(window);
        }
        else if (currentState == LEVEL_ONE || currentState == LEVEL_TWO)
        {
                userInterface.drawGameScreen(window, lives, destroyedAliens);//draw game labels

                if (humanShip.isShipHitByAnyBombs(manyBombs.getBombList(), lives)) //if the ship is hit by any bombs
                {
                    alienGroup.resetAliensPos(); //bring aliens to top
                    humanShip.resetShipPos(window); //bring ship to center
                }
                humanShip.moveShip(window, WINDOW_WIDTH); //ship movement
                humanShip.drawShip(window); 

                if (alienGroup.haveAliensReachedShip(lives)) //automatically resets the ship if reached by aliens
                {
                    humanShip.resetShipPos(window);
                }

                alienGroup.detectHitAliens(manyMissiles.getMissileList(), destroyedAliens); //see who got hit

                alienGroup.moveAlienArmy(); //move aliens down
                alienGroup.drawAlienArmy(window);

                manyMissiles.moveMissileGroup(); //move missiles up
                manyMissiles.drawMissileGroup(window);

                //add code here that makes the bombs faster for level 2
                randNum = rand() % 60 - 1; //random new bombs
                if (randNum == 3)
                {
                    Vector2f tempPos = alienGroup.getRandomAlienPos(window, destroyedAliens);
                    //cout << "Game pos: " << endl;
                    //cout << tempPos.x << endl;
                    //cout << tempPos.y << endl;
                    manyBombs.newBomb(tempPos);
                }
                manyBombs.moveBombGroup();
                manyBombs.drawBombGroup(window);

                currentState = resetState(lives, destroyedAliens, currentState, alienGroup);


        }
        //else if (currentState == ALIEN_WON)
        //{

        //}
        //else if (currentState == HUMAN_WON)
        //{

        //}

		window.display();
   	}

	return 0;
}


//look for winners
//reset current state of the enums if needed
GameStateEnum resetState(int lives, int &destroyedAliens, GameStateEnum &currentState, AlienArmy &alienGroup)
{
    if (lives < 1)
    {
        currentState = ALIEN_WON;
    }
    else if (destroyedAliens == 10)
    {
        if (currentState == LEVEL_TWO)
        {
            currentState == HUMAN_WON;
        }
        else
        {
            currentState = LEVEL_TWO;
            //make changes for transitioning from level one to level two
            alienGroup.clearAliens();//clear out list
            alienGroup.populateAlienList(currentState);
            destroyedAliens = 0; //back to having hit no aliens
        }
    }
    return currentState;
}
