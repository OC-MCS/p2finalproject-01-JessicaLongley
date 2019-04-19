#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Missile
{
    Sprite missileSprite;
public:
    //constructor
    Missile(Vector2f pos, Texture &missileTexture)
    {
        //set texture to sprite
        missileSprite.setTexture(missileTexture);
        missileSprite.setPosition(pos);
    }

    //draw one missile
    //Parameters: RenderWindow&
    //Returns: void
    void drawMissile(RenderWindow &window)
    {
        window.draw(missileSprite);
    }

    //move one missile up screen
    //Parameters: none
    //Returns: void
    void moveMissile()
    {
        const float DIST = 5.0f; //(will move 5 pixles every 60th of a second)
        missileSprite.move(0, -DIST); //move it up in the y direction
    }

    //get GlobalBounds of one missile for checking for hits later
    //Parameters: none
    //Returns: FloatRect (missile bounds)
    FloatRect getGlobalBounds()
    {
        return missileSprite.getGlobalBounds();
    }

    //check if missile is on screen
    //Parameters: none
    //Returns: bool (is missile on screen)
    bool isMissileOnScreen()
    {
        bool onScreen = false;
        if (missileSprite.getPosition().y < 0)  //missile is on screen
        {
            onScreen = true;
        }
        return onScreen;
    }

};
