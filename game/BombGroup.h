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
    list<Bomb> multipleBombs;
public:
    BombGroup()
    {
        //load bomb texture
        if (!BombTexture.loadFromFile("FruitMissile.png"))
        {
            cout << "Unable to load Bomb texture!" << endl;
            exit(EXIT_FAILURE);
        }
        //random stuff for aliens shooting bombs, will use new bomb function to add a bomb to the vector
    }
    void newBomb(Vector2f pos)
    {
        Bomb temp(pos, BombTexture);
        multipleBombs.push_back(temp);
    }
    void drawBombGroup(RenderWindow &window)
    {
        list<Bomb>::iterator iter;
        for (iter = multipleBombs.begin(); iter != multipleBombs.end(); iter++)
        {
            iter->drawBomb(window);
        }
    }
};