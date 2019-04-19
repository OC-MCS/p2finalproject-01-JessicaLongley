#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include <list>
#include "Bomb.h"
#include "GlobalConstants.h"

class Ship
{
    Texture shipTexture; 
    Sprite shipSprite;
    Vector2u shipSize; //this is a vector2u and not a Vector2f because the shipTexture.getSize() returns a Vector2u

public:
    //Constructor: load texture, set to sprite, initializie position of ship
    //Parameters: RenderWindow&
    Ship(RenderWindow &window)
    {
        //load ship texture
        if (!shipTexture.loadFromFile("ship.png"))
        {
            cout << "Unable to load ship texture!" << endl;
            exit(EXIT_FAILURE);
        }
        shipSize = shipTexture.getSize(); //this returns the size of the ship that will be passed into the moveShip function

        //set the texture to a sprite (ship)
        shipSprite.setTexture(shipTexture);

        //initial position of the ship will be approx middle of screen
        float shipX = window.getSize().x / 2.0f;
        float shipY = (window.getSize().y / 4.0f) * 3; //places alien 3/4ths down the screen
        shipSprite.setPosition(shipX, shipY);
    }

    //reset the ship's position to the middle of the screen
    //Parameters: RenderWindow&
    //Returns: void
    void resetShipPos(RenderWindow &window)
    {
        //initial position of the ship will be approx middle of screen
        float shipX = window.getSize().x / 2.0f;
        float shipY = (window.getSize().y / 4.0f) * 3; //places alien 3/4ths down the screen
        shipSprite.setPosition(shipX, shipY);
    }

    //handle ship moving left and right
    //Parameters: RenderWindow&
    //Returns: void
    void moveShip(RenderWindow &window)
    {
        const float DISTANCE = 5.0;

        if (Keyboard::isKeyPressed(Keyboard::Left) && (shipSprite.getPosition().x > 0)) //keeps ship from going off the left of the screen)
        {
            // left arrow is pressed: move our ship left 5 pixels
            // 2nd parm is y direction. We don't want to move up/down, so it's zero.
            shipSprite.move(-DISTANCE, 0);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) && (shipSprite.getPosition().x < (WINDOW_WIDTH - shipSize.x)))
        {
            // right arrow is pressed: move our ship right 5 pixels
            shipSprite.move(DISTANCE, 0);
        }
    }

    //handle drawing the ship
    //Parameters: RenderWindow&
    //Returns: void
    void drawShip(RenderWindow &window)
    {
        window.draw(shipSprite);
    }
    
    //get the ship's position
    //Parameters: none
    //Returns: Vector2f position of ship
    Vector2f getPosition()
    {
        return shipSprite.getPosition();

    }

    //compares one bomb's bounds to the ship's bounds
    //Parmeters: FloadRect (the bomb's bounds)
    //Returns: bool (is the ship hit)
    bool isShipHitByOneBomb(FloatRect bombBounds)
    {
        bool isHit = false;
        FloatRect shipBounds = shipSprite.getGlobalBounds();
        if (bombBounds.intersects(shipBounds))
        {
            isHit = true;
        }
        return isHit;
    }

//compares many bombs' bounds to the ship's bounds, decrements lives if necessisary
//Parmeters: list<Bomb> &multipleBombs, int lives
//Returns: bool (is the ship hit)
    bool isShipHitByAnyBombs(list<Bomb> &multipleBombs, int &lives)
    {
        list<Bomb>::iterator Iter; //iterator walks through list of bombs
        bool isHit = false;
        for (Iter = multipleBombs.begin(); Iter != multipleBombs.end() && !isHit;)
        {
            isHit = isShipHitByOneBomb(Iter->getGlobalBounds());
            if (isHit)
            {
                Iter = multipleBombs.erase(Iter);
                lives -= 1;
            }
            else
            {
                Iter++; //we incriment this here because the erase function also incriments
            }
        }
        return isHit;
    }
   
};