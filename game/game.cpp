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
#include "WindowSize.h"
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



int main()
{
    //const int WINDOW_WIDTH = 800; //dont need these now that WindowSize.h exists
    //const int WINDOW_HEIGHT = 600;

    srand(time(NULL)); //for random numbers later in loop
    int randNum;

    int lives = 5; //lives of human
    int destroyedAliens = 0; //number of aliens destroyed


    bool isWelcomeScreen = true; //the screen options for the game. if statements will switch through the states of the game in the loop
    bool isGameScreen = false;
    bool isWinnerScreen = false;

    //enum SCREEN_STATE = {START, GAME, GAMEOVER, LEVEL 2};
    


	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	window.setFramerateLimit(60); //Limit the framerate to 60 frames per second


	// load textures from file into memory. This doesn't display anything yet.
	// Notice we do this *before* going into animation loop.

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
            //else if (event.type == Event::MouseButtonReleased)
            //{
            //    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            //    //bool temp = userInterface.detectStart(mousePos);
            //    if (userInterface.detectStart(mousePos))
            //    {
            //        isWelcomeScreen = false;
            //        isGameScreen = true;
            //    }
            //}
		}

		//===========================================================
		// Everything from here to the end of the loop is where you put your
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================

		// draw background first, so everything that's drawn later 
		// will appear on top of background
        if (isWelcomeScreen)
        {

        }
        if (isGameScreen)
        {
            userInterface.drawGameScreen(window, lives, destroyedAliens);

            humanShip.isShipHitByAnyBombs(manyBombs.getBombList(), lives);
            cout << "Lives: " << lives << endl; //TESTING CODE
            humanShip.moveShip(window, WINDOW_WIDTH); //ship movement
            humanShip.drawShip(window);

            alienGroup.detectHitAliens(manyMissiles.getMissileList(), destroyedAliens); //see who got hit
            cout << "Destoryed Aliens: " << destroyedAliens << endl; //TESTING CODE
            alienGroup.moveAlienArmy(); //move aliens down
            alienGroup.drawAlienArmy(window);

            manyMissiles.moveMissileGroup(); //move missiles up
            manyMissiles.drawMissileGroup(window);

            //add code here that makes the bombs faster for level 2
            randNum = rand() % 10 - 1; //random new bombs
            if (randNum == 3)
            {
                Vector2f tempPos = alienGroup.getRandomAlienPos(window);
                cout << "Game pos: " << endl;
                //cout << tempPos.x << endl;
                //cout << tempPos.y << endl;
                manyBombs.newBomb(tempPos);
            }
            manyBombs.moveBombGroup();
            manyBombs.drawBombGroup(window);
        }
        else if (isWinnerScreen)
        {

        }


		window.display();

	}

	return 0;
}

