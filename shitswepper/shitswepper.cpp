// shitswepper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"ShitMap.h"
#include <ctime>
#include <random>
#include <cmath>
#include <string>
const std::pair<int, int> windowRes(500, 600);
 std::map< std::string, sf::Texture*>* shitLoad(std::string path) {
     sf::Texture* buf = new sf::Texture;
    std::map<std::string, sf::Texture*>* exhaust=new std::map<std::string, sf::Texture*>;
    for (short i{-1}; i < 9; ++i) {
        buf->loadFromFile(path + "N" + std::to_string(i) + ".png");
        exhaust->insert(std::make_pair("N" + std::to_string(i),buf));
        buf = nullptr;
        buf = new sf::Texture;
    }
    buf->loadFromFile(path + "UNKNOWN.png");
    exhaust->insert(std::make_pair("UNKNOWN",buf));
    buf = nullptr;
    buf = new sf::Texture;
    buf->loadFromFile(path + "QUESTION.png");
    exhaust->insert(std::make_pair("QUESTION", buf));
    buf = nullptr;
    buf = new sf::Texture;
    buf->loadFromFile(path + "QUESTIONUS.png");
    exhaust->insert(std::make_pair("QUESTIONUS",buf));
    buf = nullptr;
    return exhaust;

}
int main()
{
    //ShitMap shit(20,20,5,5,shitLoad(""), 50);
    //shit.debugPrint();
    //shit.openShitExlodeKabaniWeWeWeAhaha(19, 0);
    std::cout << "\n\n\n\n";
    //shit.debugPrintBulldog();
    sf::Texture bobr1;
    bobr1.loadFromFile("33.png");
    auto shiiit = shitLoad("");
    const auto shiit = shiiit;
    const sf::Texture* bobr = &bobr1;
    sf::RenderWindow* window=new sf::RenderWindow(sf::VideoMode(windowRes.first, windowRes.second), "SFML works!");
    sf::RectangleShape rect(sf::Vector2f(windowRes.first,std::max(windowRes.first, windowRes.second) -
        std::min(windowRes.first, windowRes.second)));
    int remainingSpaceY = windowRes.second - (std::max(windowRes.first, windowRes.second) - std::min(windowRes.first, windowRes.second));
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
    rect.setTexture(bobr);
    rect.setPosition(sf::Vector2f(0, 0));
    window->setFramerateLimit(600);
    //shape.setFillColor(sf::Color::Green);
    ShitMap shit(5, 5, shiit, std::make_pair(200, 10), std::make_pair(600, 490));
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
                shit.clickOnShit(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y,4);
                //f[0].setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));

            }
        }

        window->clear();
        window->draw(rect);
        shit.drawShit(window);
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
