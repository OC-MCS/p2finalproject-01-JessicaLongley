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
    //define texture object 

    Texture enemyTextureL1;
    Texture enemyTextureL2;
    //list of enemies
    list<Alien> alienGroup; //this will hold the group of 10 aliens
    Vector2f pos; //for setting the position of the aliens as they are created

    
    //move down the screen
    //detect hit
public:
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

        ////first alien's posiion
        //pos.x = 20;
        //pos.y = 10;
        ////spin through list to create 10 new aliens
        //for (int i = 0; i < 10; i++)
        //{
        //    Alien temp(pos, enemyTextureL1);
        //    alienGroup.push_back(temp);
        //    pos.x += 80;
        //}
    }
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
    void clearAliens()
    {
        alienGroup.clear();
    }
    void drawAlienArmy(RenderWindow &window)
    {
        list<Alien>::iterator iter;
        for (iter = alienGroup.begin(); iter != alienGroup.end(); iter++)
        {
            //window.draw(iter->getSprite());
            iter->drawAlien(window); //what is the syntax for drawing one of the aliens in the list
        }
    }
    void moveAlienArmy()
    {
        //move all aliens down the screen
        list<Alien>::iterator iter;
        for (iter = alienGroup.begin(); iter != alienGroup.end(); iter++)
        {
            iter->moveAlien(); //what is the syntax for calling functions from the alien class
            cout << "moving" << endl;
        }
    }
    //check if alien is hit by missile
    void detectHitAliens(list<Missile> &multipleMissiles, int &destroyedAliens)
    {
        bool isHit = false; //to check each alien's hit status regarding missiles
        list<Alien>::iterator alienIter;
        list<Missile>::iterator missileIter;

        for (alienIter = alienGroup.begin(); alienIter != alienGroup.end();)
        {
            isHit = false;
            for(missileIter = multipleMissiles.begin(); missileIter != multipleMissiles.end()&& !isHit;)
            {
                isHit = alienIter->isAlienHit(missileIter->getGlobalBounds());
                if (isHit)
                {
                    //remove missile
                    missileIter = multipleMissiles.erase(missileIter);
                }
                else
                {
                    missileIter++;
                }
            }
            if (isHit)
            {
                //remove alien
                alienIter = alienGroup.erase(alienIter);
                destroyedAliens += 1;
            }
            else
            {
                alienIter++;
            }
        }
    }
    Vector2f getRandomAlienPos(RenderWindow &window, int destroyedAliens)
    {
        Vector2f returnValue;
        int randAlien = rand() % alienGroup.size(); //10 FOR NUMBER OF ALIENS
        list<Alien>::iterator Iter;
        Iter = alienGroup.begin();
        advance(Iter, randAlien);
        //cout << "Function pos: " << endl;
        //cout << "x: " << returnValue.x << endl;
        //cout << "y: " << returnValue.y << endl;
        return Iter->getPosition();
    }
    void resetAliensPos()
    {
        list<Alien>::iterator iter;
        for (iter = alienGroup.begin(); iter != alienGroup.end(); iter++)
        {
            iter->resetYPos();
        }
    }
    bool haveAliensReachedShip(int &lives)
    {
        bool isReached = false;
        list<Alien>::iterator iter;
        if (alienGroup.size() > 0)
        {
            if (alienGroup.begin()->hasAlienReachedShip())
            {
                lives -= 1;
                resetAliensPos();
            }
        }

        return isReached;
    }

};