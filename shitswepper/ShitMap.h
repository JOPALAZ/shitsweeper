#pragma once
#include"ShitPoint.h"
#include <queue>

using ShitSize = short;
using MapPosition = ShitSize;

class ShitMap
	
{
public:
	ShitMap();
	void create(ShitSize y, ShitSize x, std::map<std::string, sf::Texture*>* textures, std::pair<unsigned short, unsigned short>p1, std::pair<unsigned short, unsigned short>p2);
	void drawMap(sf::RenderWindow* window);
	void prepareMap(MapPosition y_pos, MapPosition x_pos);
	bool checkWinState();
	void openCellsNear(MapPosition y, MapPosition x);
	bool openCell(MapPosition y, MapPosition x);
	void debugPrint();
	void debugPrintBool();
	bool leftClickOnMap(int x, int y);
	void rightClickOnMap(int x, int y);
	unsigned short getBombAmount() { return bombAmount; }
	void openAllMap();
	~ShitMap();
	
private:
	bool isMapPrepaired = false;
	ShitPoint** map;
	ShitSize MatrixMapSizeY;
	ShitSize MatrixMapSizeX;
	float CellSizeX;
	float CellSizeY;
	int deltaX;
	int deltaY;
	unsigned short bombAmount;
	
};

