#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Alien
{
    //Texture enemyTexture;
    Sprite enemySprite;
    Vector2u enemySize;

public:
    Alien(Vector2f pos, Texture &tex)
    {
        enemySprite.setTexture(tex); //set the Alien's texture to the same texture passed by reference
        enemySprite.setPosition(pos.x, pos.y); //set the Alien's position to the position handed to the constructor
    }

    //draw one alien
    void drawAlien(RenderWindow &window)
    {
        window.draw(enemySprite);
    }

    //check if one alien is hit by one missile
    bool isAlienHit(FloatRect missileBounds)
    {
        bool isHit = false;
        FloatRect enemyBounds = enemySprite.getGlobalBounds();
        if (missileBounds.intersects(enemyBounds))
        {
            isHit = true;
        }
        return isHit;
    }

    //return sprite
    //Sprite getSprite()
    //{
    //    return enemySprite;
    //}

    //move alien down the screen
    void moveAlien()
    {
        const float DIST = 0.2f; //(will move 0.2 pixles every 60th of a second)
        //Vector2f enemyPos = enemySprite.getPosition();
        //while (enemyPos.y < 600) //HARDCODING IS BAD
        //{
            enemySprite.move(0, DIST);
    //    }
    }
    Vector2f getPosition()
    {
        return enemySprite.getPosition();
    }
};