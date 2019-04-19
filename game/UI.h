#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class UI
{
    RectangleShape startBtn, playAgainBtn; //will be the start button
    Font font; //will be the font for all printed words
    Texture starsTexture;
    Sprite background;

public:
    //load everything that will be used for the game
    //and display the first screen
    UI(RenderWindow & window)
    {
        if (!starsTexture.loadFromFile("stars.jpg"))
            die("Unable to load stars texture!");
        if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) //load font
            die("couldn't load font");

        background.setTexture(starsTexture);
        background.setScale(1.5, 1.5);	// The texture file is 640x480, so scale it up a little to cover 800x600 window

        //start button
        startBtn.setFillColor(Color::Green);
        startBtn.setPosition(350, 275);
        Vector2f buttonSize1{ 110,60 };
        startBtn.setSize(buttonSize1);

        //play again button
        playAgainBtn.setFillColor(Color::Green);
        playAgainBtn.setPosition(300, 270);
        Vector2f buttonSize2{ 270, 60 };
        playAgainBtn.setSize(buttonSize2);
    }
    void drawStartScreen(RenderWindow & window)
    {
        Text game("aliens!", font, 50);
        game.setPosition(330, 50);
        Text title("Start", font, 50); //tell font what to print
        //title.setColor(Color::Cyan);
        title.setPosition(350, 275); //tell font where to print

        window.draw(game);
        window.draw(startBtn);
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
    bool detectStart(Vector2f mouse)
    {
        bool isPressed = false;
        if (startBtn.getGlobalBounds().contains(mouse))
        {
            isPressed = true;
        }
        return isPressed;
    }

    
    void drawWinnerScreen(RenderWindow & window, string thisGuy) //not yet tested
    {
        Text winner("Winner: ", font, 50);
        winner.setPosition(330, 50);
        Text specifically(thisGuy, font, 50);
        specifically.setPosition(330, 100);


        Text title("Play Again", font, 50); //tell font what to print
        title.setPosition(315, 265); //tell font where to print

        window.draw(winner);
        window.draw(specifically);
        window.draw(playAgainBtn);
        window.draw(title);

    }

//a utility function to call any time we need to bail out
//parameters: error msg as string
//returns: void
    void die(string msg)
    {
        cout << msg << endl;
        exit(-1);
    }
};