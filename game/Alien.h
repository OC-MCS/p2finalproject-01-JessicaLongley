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
    //Constructor: initialize one alien
    //Parameters; Vector2f (desired position), Texture&)
    Alien(Vector2f pos, Texture &tex)
    {
        enemySprite.setTexture(tex); //set the Alien's texture to the same texture passed by reference
        enemySprite.setPosition(pos.x, pos.y); //set the Alien's position to the position handed to the constructor
    }

    //reset one alien's y position
    //Parameters: none
    //Returns: void
    void resetYPos()
    {
        Vector2f temp = enemySprite.getPosition();
        enemySprite.setPosition(temp.x, 0);
    }

    //draw one alien
    //Parameters: RenderWindow&
    //Returns: void
    void drawAlien(RenderWindow &window)
    {
        window.draw(enemySprite);
    }

    //check if one alien is hit by one missile
    //Parameters: Float Rect missile Bounds
    //Returns: void
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

    //move one alien down the screen
    //parameters: none
    //Returns: void
    void moveAlien()
    {
        const float DIST = 0.52f; //(will move 0.2 pixles every 60th of a second)
        enemySprite.move(0, DIST);
    }

    //get the position of one alien (for bounds checking)
    //Parameters: none
    //Returns: Vector2f (position of ship)
    Vector2f getPosition()
    {
        return enemySprite.getPosition();
    }

    //checks if alien has reached the level that the ship is on
    //Parameters: none
    //Returns: bool (has the alien reached the ship's level?)
    bool hasAlienReachedShip()
    {
        bool hasReached = false;
        if (getPosition().y > ((WINDOW_HEIGHT / 4) * 3)-48) //three fourths down the screen is where the ship is located - 48 the enemy's face
        {
            hasReached = true;
        }
        return hasReached;
    }
};