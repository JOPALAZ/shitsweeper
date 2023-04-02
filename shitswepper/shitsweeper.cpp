// shitswepper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>

//#include "ShitMap.h"
#include <ctime>
#include "GameField.h"
#include <random>
#include <cmath>
#include <string>


int main()
{
    setlocale(LC_ALL, "ru-RU");
    //ShitMap shit(20,20,5,5,shitLoad(""), 50);
    //shit.debugPrint();
    //shit.openShitExlodeKabaniWeWeWeAhaha(19, 0);
    //shit.debugPrintBulldog();
    
    
    GameField gameField;
    sf::RenderWindow* window=new sf::RenderWindow(sf::VideoMode(WINDOW_RES.first, WINDOW_RES.second), "Shitsweeper");
    window->setSize(sf::Vector2u(WINDOW_RES.first, WINDOW_RES.second));
    
    //std::vector<sf::RectangleShape> f;
    //for (int i{}; i < 20; i++) {
    //    for (int j{}; j < 20; j++) {
    //        sf::RectangleShape rec(sf::Vector2f(remainingSpaceY / 20, remainingSpaceY / 20));
    //        rec.setPosition(sf::Vector2f(remainingSpaceY * j / 20, remainingSpaceY * i / 20+ std::max(windowRes.first, windowRes.second) -
    //            std::min(windowRes.first, windowRes.second)));
    //        rec.setTexture(shiit->at("UNKNOWN"));
    //        f.push_back(rec);
    //    }
    //}

    window->setFramerateLimit(60); 
    //shape.setFillColor(sf::Color::Green);
    
    while (window->isOpen())
    {
        //window->clear();
        
        //window->display();
        //system("pause");
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
                    if (gameField.getMapField()->checkWinState())
                    {
                        std::cout << "≈бать копать\n";
                    }
                }
                //f[0].setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));

            }
        }

        window->clear();
        //window->draw(*gameField.getHeader());
        //gameField.getMapField()->drawMap(window);
        
        gameField.drawAllElements(window);

        //for (auto t : f) {
        //    //window->clear();
        //    window->draw(t);
        //    shit.drawShit(window);
        //    //window->display();
        //    //system("pause");
        //    
        //}
        window->display();
    }

    return 0;
}
