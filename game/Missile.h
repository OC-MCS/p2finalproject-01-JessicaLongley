#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Missile
{
    Sprite missileSprite;
    //bool isMissileInFlight;
public:
    //constructor
    Missile(Vector2f pos, Texture &missileTexture)
    {
        //set texture to sprite
        missileSprite.setTexture(missileTexture);
        missileSprite.setPosition(pos);
    }
    Sprite getSprite() //get sprite for the draw missile group function in MissileGroup
    {
        return missileSprite;
    }
    void drawMissile(RenderWindow &window)
    {
        window.draw(missileSprite);
    }
    void setPosition(float x, float y)
    {
        missileSprite.setPosition(x, y);
    }
    void moveMissile()
    {
        const float DIST = 5.0f; //(will move 5 pixles every 60th of a second)
        missileSprite.move(0, -DIST); //move it up in the y direction
    }
    FloatRect getGlobalBounds()//for checking if missile has hit an alien
    {
        return missileSprite.getGlobalBounds();
    }
    bool isMissileOnScreen()
    {
        bool onScreen = false;
        if (missileSprite.getPosition().y < 0)  //missile is on screen
        {
            onScreen = true;
        }
        return onScreen;
    }
    Vector2f getPosition()
    {
        return missileSprite.getPosition();
    }
};
