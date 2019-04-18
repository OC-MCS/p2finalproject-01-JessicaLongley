#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class UI
{
    RectangleShape startBtn; //will be the start button
    Font font; //will be the font for all printed words
    //Text title;
    Texture starsTexture;
    Sprite background;
    //Text title();



public:
    //load everything that will be used for the gmame
    UI(RenderWindow & window)
    {
        if (!starsTexture.loadFromFile("stars.jpg"))
            die("Unable to load stars texture!");

        background.setTexture(starsTexture);
        background.setScale(1.5, 1.5);	// The texture file is 640x480, so scale it up a little to cover 800x600 window

        //draw start button
        if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) //load font
            die("couldn't load font");
        Text title("Start", font, 50); //tell font what to print
        //title("Start", font, 25);
        //title.setColor(Color::Cyan);
        title.setPosition(350, 275); //tell font where to print
        window.draw(title); //draw the font

    }

    void drawGameScreen(RenderWindow & window, int lives, int aliensDestroyed)
    {
        window.draw(background);
        //string tempLives = "Lives: " + to_string(lives);
        Text livesCounter("Lives: " + to_string(lives), font, 15);
        livesCounter.setPosition(740, 2);
        window.draw(livesCounter);
        Text aliensCounter("Aliens Destroyed: " + to_string(aliensDestroyed), font, 15);
        aliensCounter.setPosition(3, 2);
        window.draw(aliensCounter);
    }
    //bool detectStart(Vector2f mouse)
    //{
    //    bool isPressed = false;
    //    if (title.getGlobalBounds().contains(mouse))
    //    {
    //        isPressed = true;
    //    }
    //    return isPressed;
    //}

//a utility function to call any time we need to bail out
//parameters: error msg as string
//returns: void
    void die(string msg)
    {
        cout << msg << endl;
        exit(-1);
    }
};