// shitswepper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    
    
    GameField gameField("default\\",23);
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

    window->setFramerateLimit(24); 
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
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (gameField.leftClickOnField(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)) 
                    {
                        if (gameField.getMapField()->checkWinState())
                        {
                            std::cout << "≈бать копать\n";
                        }
                    }
                    else 
                    {

                    }

                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    gameField.rightClickOnField(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
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


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
