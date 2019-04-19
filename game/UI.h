//================================================
//Jessica Longley
//April 19, 2019
//Programming II Final Assignment
//Description: aliens!
//================================================
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class UI
{
    RectangleShape startBtn, playAgainBtn, blackScreen; //will be the buttons and boxes
    Font font; //will be the font for all printed words
    Texture starsTexture; 
    Sprite background; 

public:
    //constructor: loads everything that will be used for the game
    //Parameters: window
    UI(RenderWindow & window)
    {
        if (!starsTexture.loadFromFile("stars.jpg")) //load stars texture
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

        //big black box
        blackScreen.setFillColor(Color::Black);
        Vector2f blackScreenSize{ 800, 600 };
        blackScreen.setScale(blackScreenSize);
        Vector2f blackScreenPos{ 0,0 };
        blackScreen.setPosition(blackScreenPos);
    }

    //draws the first screen with the title and start button
    //Parameters: window
    //Returns: void
    void drawStartScreen(RenderWindow & window)
    {
        Text game("aliens!", font, 50);
        game.setPosition(330, 50);
        Text title("Start", font, 50); //tell font what to print
        title.setPosition(350, 275); //tell font where to print

        window.draw(game);
        window.draw(startBtn);
        window.draw(title);
    }

    //draws the level one and two screen. This displays the scores
    //Parameters: window, int lives, int aliensDestroyed
    //Returns: void
    void drawGameScreen(RenderWindow & window, int lives, int aliensDestroyed)
    {
        window.draw(background);
        Text livesCounter("Lives: " + to_string(lives), font, 15);
        livesCounter.setPosition(740, 2);
        window.draw(livesCounter);
        Text aliensCounter("Aliens Destroyed: " + to_string(aliensDestroyed), font, 15);
        aliensCounter.setPosition(3, 2);
        window.draw(aliensCounter);
    }

    //detects if the start or play again button are pressed
    //Parameters: Vector2f mouse
    //Returns: true or false (if the button is pressed)
    bool detectStart(Vector2f mouse)
    {
        bool isPressed = false; 
        if (startBtn.getGlobalBounds().contains(mouse) || playAgainBtn.getGlobalBounds().contains(mouse)) 
        {
            isPressed = true;
        }
        return isPressed;
    }

    //draws the screen for either winner
    //Parameters: window, string ( the name of the winner ie. aliens or human)
    //Returns: void
    void drawWinnerScreen(RenderWindow & window, string thisGuy)
    {
        Text winner("Winner: ", font, 50); //generic title
        winner.setPosition(330, 50);
        Text specifically(thisGuy, font, 50); //specific winner
        specifically.setPosition(330, 100);


        Text title("Play Again", font, 50); //tell font what to print
        title.setPosition(315, 265); //tell font where to print

        window.draw(background); //redraw the stars over the ugly
        window.draw(winner);
        window.draw(specifically);
        window.draw(playAgainBtn);
        window.draw(title);
    }

    //a utility function to call any time we need to bail out
    //Parameters: error msg as string
    //Returns: void
    void die(string msg)
    {
        cout << msg << endl;
        exit(-1);
    }
};