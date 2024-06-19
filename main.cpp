#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include "username.h"

using namespace sf;
int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    
    Texture obj1, obj2, obj3;
   
    obj1.loadFromFile("assets/tiles.png");
    obj2.loadFromFile("assets/background.png");   
    obj3.loadFromFile("assets/frame.png");
      
    Sprite sprite(obj1), background(obj2), frame(obj3);
    
    int delta_x=0, colorNum=1;
    float timer=0, delay=0.4;
    bool rotate=0;
    
    int score=0;
    std::string scoreOutput;
    
    Music music;
    music.openFromFile("assets/Tetris.ogg");
    music.setLoop(true);     // Set music to loop
    music.play();            // Start playing music

    Font font;
    font.loadFromFile("assets/Roboto.ttf");    //For the font

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time; 

        //---Event Listening Part---//
        
        Event e;
        while (window.pollEvent(e))                     //Event is occurring - until the game is in running state
        {                
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
            {    
                music.stop();
                window.close();                            //Opened window disposes
            }
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
                else if(e.key.code == Keyboard::Escape || e.key.code == Keyboard::X  )     //exit game
                {    
                    music.stop();
                    window.close(); // Close the window
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))       // Another way to detect key presses without event listener
            delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05


        ///*** FUNCTIONS CALLS ***///
        fallingPiece(timer, delay, colorNum);//This function is responsible for downward movement. Takes timer,delay and colorNum as inputs
        move( delta_x) ;                     // This function checks to see if left or right key is pressed. Takes delta_x as input to check it
        rotation(rotate);                    // This function checks to see if up key is pressed. Takes rotate as input to check it        
        checklines(score);                   // This function checks if any line is filled by blocks
        //bomb();                            //The bomb has a one in six chanace of dropping
        
        delay=0.4;                           // Resetting the delay

        window.clear(Color::Black);
        window.draw(background);
        for (int i=0; i<M; i++)
        {
            for (int j=0; j<N; j++)
            {
                if (gameGrid[i][j]==0)
                    continue;
                    
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                
                sprite.setPosition(j*18,i*18);
                
                sprite.move(28,31);             //offset
                
                window.draw(sprite);
            }
        }
        for (int i=0; i<4; i++)
        {
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            
            sprite.move(28,31);
            
            window.draw(sprite);
            
        }

        scoreOutput="Score\n "+std::to_string(score);
        Text scoreText(scoreOutput,font,20);
        scoreText.setPosition(240,190);           //Draw score
        window.draw(scoreText);

        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();

    }
    return 0;
}
