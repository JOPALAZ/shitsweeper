
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "GameField.h"
#include <random>
#include <cmath>
#include <string>


int main()
{


    GameField gameField;
    if(!gameField.isOk()){
        std::cout << "NOT ALL FILES WERE LOADED";
        //for (;;) { std::cout << "\nHAHAHAHHAHAHAHHAHAHAHHAAHHAHAHAHHAHAHAHAHHA"; } //schizophrenia
        return -1;
    }
    sf::RenderWindow* window=new sf::RenderWindow(sf::VideoMode(WINDOW_RES.first, WINDOW_RES.second), "Shitsweeper");
    window->setSize(sf::Vector2u(WINDOW_RES.first, WINDOW_RES.second));


    window->setFramerateLimit(60); 
   
    while (window->isOpen())
    {
      
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    gameField.leftClickOnField(window);
                }
                else if (event.mouseButton.button == sf::Mouse::Right) 
                {
                    gameField.rightClickOnField(window);

                }
                

            }
        }

        window->clear();
        gameField.drawAllElements(window);
        window->display();
    }

    return 0;
}
