#pragma once
#include<iostream>
#include<map>
#include <SFML/Graphics.hpp>
class ShitPoint {
public:
	ShitPoint();
	ShitPoint(std::map<std::string, sf::Texture>* textures);
	ShitPoint(int num, std::map<std::string, sf::Texture*>* textures);
	bool step();
	char flag();
	int getNum();
	void setNum(int num);
	bool isntOpened();
	~ShitPoint() = default;
	void setTextures(std::map<std::string, sf::Texture*>* texturesIn);
	void setSize(float x, float y);
	void setCellSizes(float x, float y);
	void setPosition(float x, float y);
	char unflag();
	sf::Sprite getSprite();
protected:
	int number=0;
	bool flagged=false;
	bool sure=true;
	bool opened=false;
	float sizeX, sizeY;
	std::map<std::string, sf::Texture*>* textures;
	sf::Sprite body;
};