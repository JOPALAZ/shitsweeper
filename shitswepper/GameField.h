#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include"ShitMap.h"
#include"constants.h"
//#include "ShitMap.h"

class GameField
{public:
	GameField(std::string path,int difficulty);
	ShitMap* getMapField() { return &ShitField;}
	sf::Sprite* getHeader() { return &header; }
	sf::Text* getTextOfBombAmount() { return &bombAmount; };
	void drawAllElements(sf::RenderWindow* window);
	std::map< std::string, sf::Texture*>* LoadTextures(std::string path);
	bool leftClickOnField(int x, int y);
	void rightClickOnField(int x, int y);
	bool isGameIsOn() { return gameIsOn; }
	~GameField();
private:
	bool gameIsOn=true;
	bool draw=true;
	float scaleX, scaleY;
	int screenSpaceAllocatedForText;
	std::string bombAmountString;
	sf::Texture headerTexture;
	std::map<std::string, sf::Texture*>* textures;
	sf::Sprite header;
	sf::Font Font;
	ShitMap ShitField;
	sf::Text bombAmount;
};

