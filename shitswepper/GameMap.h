#pragma once
#include"SmartArray.h"
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
	void checkAllFlags();
	bool isAllFlagCorrect();
	bool leftClickOnMap(int x, int y);
	void rightClickOnMap(int x, int y);
	unsigned short getBombAmount() { return bombAmount; }
	void openAllMap();
	bool giveHint();
	bool giveSuperHint();
	void deleteUnique();
	~GameMap();
	bool mapPrepaired() { return this->isMapPrepaired; }
	
private:
	unsigned char flagAllAround(std::pair<short, short>& coordinates);
	bool isAtLeastOneCellCorrect(SmartArray<std::pair<MapSize, MapSize>>& toCheck);
	bool isBordering(MapSize& y, MapSize& x);
	SmartArray<std::pair<MapSize, MapSize>> isNearOpened(std::pair<MapSize, MapSize>& coordinates);
	bool stepOnAllAround(std::pair<MapSize, MapSize>& coordinates);
	std::pair<unsigned, unsigned> calculateCountOfUnknownCellsNear(std::pair<short, short>& coordinates);
	bool isMapPrepaired = false;
	SmartArray<std::pair<MapSize, MapSize>> sureFlags;
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

