#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <list>
#include "Alien.h";
#include "Missile.h"
#include "MissileGroup.h"
#include "Bomb.h"
#include "GlobalConstants.h"
using namespace sf;

class AlienArmy
{
    //define texture objects
    Texture enemyTextureL1;
    Texture enemyTextureL2;
    list<Alien> alienGroup; //this will hold the group of 10 aliens
    Vector2f pos; //for setting the position of the aliens as they are created

public:
    //Constructor: loads enemy textures
    //Parameters: none
    AlienArmy()
    {
        //load alien texture
        if (!enemyTextureL1.loadFromFile("enemy.png"))
        {
            cout << "Unable to load enemy texture!" << endl;
            exit(EXIT_FAILURE);
        }

        //load alien texture for level 2
        if (!enemyTextureL2.loadFromFile("NewAlien.png"))
        {
            cout << "Unable to load enemy texture!" << endl;
            exit(EXIT_FAILURE);
        }
    }

    //fill the alien list with aliens
    //Parameters: GameStateEnum (the current level)
    //Returns: void
    void populateAlienList(GameStateEnum currentState)
    {
        //first alien's posiion
        pos.x = 20;
        pos.y = 10;
        //spin through list to create 10 new aliens
        for (int i = 0; i < 10; i++)
        {
            if (currentState == LEVEL_ONE)
            {
                Alien temp(pos, enemyTextureL1);
                alienGroup.push_back(temp);
            }
            else if (currentState == LEVEL_TWO)
            {
                Alien temp(pos, enemyTextureL2);
                alienGroup.push_back(temp);
            }
            pos.x += 80;
        }
    }

    //clear out all aliens to start fresh
    //Parameters: none
    //Returns: void
    void clearAliens()
    {
        alienGroup.clear();
    }

    //draw the list of aliens
    //Parameters: RenderWindow&
    //Returns: void
    void drawAlienArmy(RenderWindow &window)
    {
        list<Alien>::iterator iter;
        for (iter = alienGroup.begin(); iter != alienGroup.end(); iter++)
        {
            //window.draw(iter->getSprite());
            iter->drawAlien(window); //what is the syntax for drawing one of the aliens in the list
        }
    }

    //move the list of aliens
    //Parameters: none
    //Returns: void
    void moveAlienArmy()
    {
        //move all aliens down the screen
        list<Alien>::iterator iter;
        for (iter = alienGroup.begin(); iter != alienGroup.end(); iter++)
        {
            iter->moveAlien(); //what is the syntax for calling functions from the alien class
            //cout << "moving" << endl; //test code
        }
    }

    //check if alien is hit by missile
    //Parameters: list<Missile> &(list of missiles), int &destroyedAliens
    void detectHitAliens(list<Missile> &multipleMissiles, int &destroyedAliens)
    {
        bool isHit = false; //to check each alien's hit status regarding missiles
        list<Alien>::iterator alienIter; //for stepping through the list of aliens
        list<Missile>::iterator missileIter; //for stepping through the list of missiles
        for (alienIter = alienGroup.begin(); alienIter != alienGroup.end();)
        {
            isHit = false;
            for(missileIter = multipleMissiles.begin(); missileIter != multipleMissiles.end()&& !isHit;)
            {
                isHit = alienIter->isAlienHit(missileIter->getGlobalBounds());
                if (isHit)
                {
                    missileIter = multipleMissiles.erase(missileIter); //remove missile and point to next thing in list

                }
                else
                {
                    missileIter++; //move to the next thing in the list
                }
            }
            if (isHit)
            {
                alienIter = alienGroup.erase(alienIter); //remove alien and point to the next thing in the list
                destroyedAliens += 1; //one less alien
            }
            else
            {
                alienIter++; //move to the next thing in the list
            }
        }
    }

    //determind if the list is empty
    //Parameters: none
    //Returns: bool (is the list empty)
    bool isListEmpty()
    {
        bool isEmpty = false;
        if (alienGroup.size() < 1)
        {
            isEmpty = true;
        }
        return isEmpty;
    }

    //get a random alien's position
    //Parameters: RenderWindow &, int destroyedAlines
    //Returns: Vector2f (the random postion)
    Vector2f getRandomAlienPos(RenderWindow &window, int destroyedAliens)
    {
        Vector2f returnValue; //will hold the position being returned
        int randAlien = rand() % alienGroup.size(); //just consider the aliens that remain
        list<Alien>::iterator Iter; //iterate through the list and find the random one
        Iter = alienGroup.begin();
        advance(Iter, randAlien);
        return Iter->getPosition();
    }

    //reset the list of aliens to the top of the screen
    //Parameters: none
    //Returns: void
    void resetAliensPos()
    {
        list<Alien>::iterator iter;
        for (iter = alienGroup.begin(); iter != alienGroup.end(); iter++)
        {
            iter->resetYPos();
        }
    }

    //check if the list of aliens have reached the ship
    //Parameters: int &lives
    //Return: bool (have they reached)
    bool haveAliensReachedShip(int &lives)
    {
        bool isReached = false;
        list<Alien>::iterator iter;
        if (alienGroup.size() > 0) //as long as there are actually aliens in the group
        {
            if (alienGroup.begin()->hasAlienReachedShip())
            {
                lives -= 1; //take away one life
                resetAliensPos(); //put aliens at the top of the screen
            }
        }

        return isReached;
    }

};