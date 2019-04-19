#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Bomb.h"
#include <list>

class BombGroup
{
    Texture BombTexture;
    list<Bomb> multipleBombs; //list to keep track of bombs
public:
    //Constructor: loads bomb texture
    BombGroup()
    {
        if (!BombTexture.loadFromFile("FruitMissile.png"))
        {
            cout << "Unable to load Bomb texture!" << endl;
            exit(EXIT_FAILURE);
        }
    }

    //add new bomb to list
    //Parameters: Vector2f (position that you want the bomb to start at)
    //Returns: void
    void newBomb(Vector2f pos)
    {
        Bomb temp(pos, BombTexture);
        multipleBombs.push_back(temp);
    }

    //draw the list of bombs
    //Parameters: RenderWindow&
    //Returns: void
    void drawBombGroup(RenderWindow &window)
    {
        list<Bomb>::iterator iter;
        for (iter = multipleBombs.begin(); iter != multipleBombs.end(); iter++)
        {
            iter->drawBomb(window);
        }
    }

    //move the list of bombs down the screen
    //Parameters: none
    //Returns: void
    void moveBombGroup()
    {
        list<Bomb>::iterator iter;
        for (iter = multipleBombs.begin(); iter != multipleBombs.end(); iter++)
        {
            iter->moveBomb();
        }
    }

    //get list of bombs to pass to other checking functions
    //Parameters: none
    //Returns: list<Bomb>
    list<Bomb> &getBombList()
    {
        return multipleBombs;
    }

//clear out all bombs to start fresh
//Parameters: none
//Returns: void
    void clearBombs()
    {
        multipleBombs.clear();
    }
};