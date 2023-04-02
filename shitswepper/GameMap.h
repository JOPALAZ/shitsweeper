#pragma once
#include"MapPoint.h"
#include"constants.h"
#include <queue>

using MapSize = short;
using MapPosition = MapSize;

class GameMap
	
{
public:
	GameMap();
	void create(MapSize y, MapSize x, std::map<std::string, sf::Texture*>* textures, std::pair<unsigned short, unsigned short>p1, std::pair<unsigned short, unsigned short>p2);
	void drawMap(sf::RenderWindow* window);
	void prepareMap(MapPosition y_pos, MapPosition x_pos);
	bool checkWinState();
	void openCellsNear(MapPosition y, MapPosition x);
	bool openCell(MapPosition y, MapPosition x);
	void debugPrint();
	void debugPrintBool();
	bool isAllFlagCorrect();
	bool leftClickOnMap(int x, int y);
	void rightClickOnMap(int x, int y);
	unsigned short getBombAmount() { return bombAmount; }
	void openAllMap();
	void deleteUnique();
	~GameMap();
	
private:
	bool isMapPrepaired = false;
	MapPoint** map;
	MapSize MatrixMapSizeY;
	MapSize MatrixMapSizeX;
	double CellSizeX;
	double CellSizeY;
	int deltaX;
	int deltaY;
	unsigned short bombAmount;
	unsigned short bombAmount_;
	
};

