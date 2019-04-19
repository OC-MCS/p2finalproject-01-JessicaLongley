#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Missile.h"
using namespace sf;

class MissileGroup
{
    Texture missileTexture;
    list<Missile> multipleMissiles; //list to keep track of missiles
public:
    //Constructor: load missile texture
    MissileGroup()
    {
        if (!missileTexture.loadFromFile("missile.png"))
        {
            cout << "Unable to load Missile texture!" << endl;
            exit(EXIT_FAILURE);
        }
    }

    //add new missile to list
    //Parameters: Vector2f (position you want missile to be added at)
    //Returns: void
    void newMissile(Vector2f pos)
    {
        Missile temp(pos, missileTexture);
        multipleMissiles.push_back(temp);
    }

    //draw list of missiles
    //Parameters: RenderWindow&
    //Returns: void
    void drawMissileGroup(RenderWindow &window)
    {
        list<Missile>::iterator iter;
        for (iter = multipleMissiles.begin(); iter != multipleMissiles.end(); iter++)
        {
            iter->drawMissile(window);
        }
    }

    //move list of missiles up the screen
    //Parameters: none
    //Returns: void
    void moveMissileGroup()
    {
        //while there are lives left

        //move all aliens down the screen
        list<Missile>::iterator iter;
        for (iter = multipleMissiles.begin(); iter != multipleMissiles.end(); iter++)
        {
            iter->moveMissile();
        }

    }

    //return list of missiles (to pass to other functions and see if the missiles hit anything)
    //Parameters: none
    //Returns: list<Missile>
    list<Missile> &getMissileList()
    {
        return multipleMissiles;
    }

//clear out all missiles to start fresh
//Parameters: none
//Returns: void
    void clearMissiles()
    {
        multipleMissiles.clear();
    }
};