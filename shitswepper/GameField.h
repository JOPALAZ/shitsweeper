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
	~GameField();
private:
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

