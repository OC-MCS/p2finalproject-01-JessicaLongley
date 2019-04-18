#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <list>
#include "Alien.h";
#include "Missile.h"
#include "MissileGroup.h"
using namespace sf;

class AlienArmy
{
    //define texture object 

    Texture enemyTexture;
    //list of enemies
    list<Alien> alienGroup; //this will hold the group of 10 aliens
    Vector2f pos; //for setting the position of the aliens as they are created
    
    //move down the screen
    //detect hit
public:
    AlienArmy()
    {
        //load alien texture
        if (!enemyTexture.loadFromFile("enemy.png"))
        {
            cout << "Unable to load enemy texture!" << endl;
            exit(EXIT_FAILURE);
        }

        //first alien's posiion
        pos.x = 20;
        pos.y = 10;
        //spin through list to create 10 new aliens
        for (int i = 0; i < 10; i++)
        {
            Alien temp(pos, enemyTexture);
            alienGroup.push_back(temp);
            pos.x += 80;
        }
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
        //while there are lives left

        //move all aliens down the screen
        list<Alien>::iterator iter;
        for (iter = alienGroup.begin(); iter != alienGroup.end(); iter++)
        {
            iter->moveAlien(); //what is the syntax for calling functions from the alien class
        }
    }
    //check if alien is hit by missile
    void detectHitAliens(list<Missile> &multipleMissiles)
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
                    //remove alien
                    //alienIter = alienGroup.erase(alienIter);

                    //remove missile
                    missileIter = multipleMissiles.erase(missileIter);
                }
                else
                {
                    //alienIter++;
                    missileIter++;
                }
            }
            if (isHit)
            {
                //remove alien
                alienIter = alienGroup.erase(alienIter);
            }
            else
            {
                alienIter++;
                //missileIter++;
            }
        }
    }
};