#pragma once
#include<iostream>
#include<map>
#include <SFML/Graphics.hpp>
class MapPoint {
public:
	MapPoint();
	MapPoint(std::map<std::string, sf::Texture>* textures);
	MapPoint(int num, std::map<std::string, sf::Texture*>* textures);
	bool step();
	char flag();
	int getNum();
	void setNum(int num);
	bool isntOpened();
	~MapPoint() = default;
	void setTextures(std::map<std::string, sf::Texture*>* texturesIn);
	void setSize(double x, double y);
	void setCellSizes(double x, double y);
	void setPosition(float x, float y);
	char unflag();
	
	bool isFlagged() { return flagged; }
	sf::Sprite getSprite();
protected:
	int number=0;
	
	bool flagged=false;
	bool sure=true;
	bool opened=false;
	float sizeX=0, sizeY=0;
	std::map<std::string, sf::Texture*>* textures;
	sf::Sprite body;
};