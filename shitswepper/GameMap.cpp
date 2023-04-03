#include "GameMap.h"
GameMap::GameMap() {};
void GameMap::create(MapSize y, MapSize x, std::map<std::string, sf::Texture*>* textures, std::pair<unsigned short, unsigned short>p1, std::pair<unsigned short, unsigned short>p2) {
	MatrixMapSizeY = y;
	MatrixMapSizeX = x;
	bombAmount_ = x*y/(std::min(WINDOW_RES.first,WINDOW_RES.second)/69);
	bombAmount = bombAmount_;
	srand(time(0));
	unsigned short bombPlanted = 0;
	map = new MapPoint * [y];
	double sizeY = (std::max(p1.first, p2.first) - std::min(p1.first, p2.first)) / (float)y;
	double sizeX = (std::max(p1.second, p2.second) - std::min(p1.second, p2.second)) / (float)x;
	CellSizeX = sizeX;
	CellSizeY = sizeY;
	deltaY = p1.first;
	deltaX = p1.second;
	for (MapSize i{}; i < y; ++i) {
		map[i] = new MapPoint[x];
		for (MapSize j{}; j < x; ++j) {
			map[i][j].setCellSizes(sizeX, sizeY);
			map[i][j].setTextures(textures);
			map[i][j].setSize(sizeX, sizeY);
			map[i][j].setPosition(j * sizeX + p1.second, i * sizeY + p1.first);
		}
	}
	
}
void GameMap::drawMap(sf::RenderWindow* window) {
	for (MapSize i{}; i < MatrixMapSizeY; ++i) {
		for (MapSize j{}; j < MatrixMapSizeX; ++j) {
			window->draw(map[i][j].getSprite());
		}
	}
}
void GameMap::prepareMap(MapPosition y_pos, MapPosition x_pos)
{
	auto isBounded = [&](MapSize i, MapSize j)->bool
	{
		for (short k = i - 1; k < i + 2; ++k)
		{
			for (short p = j - 1; p < j + 2; ++p)
			{
				if ((p < MatrixMapSizeX && p >= 0) && (k < MatrixMapSizeY && k >= 0))
				{
					if (k == y_pos && p == x_pos) {
						return true;
					}
				}
			}
		}

		return false;
	};
	unsigned char bombPlanted = 0;
	while (bombAmount_ > bombPlanted) {
		for (MapSize i{}; i < MatrixMapSizeY; ++i) {
			if (bombPlanted >= bombAmount_)
				break;
			for (MapSize j{}; j < MatrixMapSizeX; ++j) {
				if (bombPlanted < bombAmount_) {
					if (i != y_pos && j != x_pos && map[i][j].getNum() != -1&&!isBounded(i,j)) {
						if (rand() % MatrixMapSizeX * MatrixMapSizeY <= 1) {

							map[i][j].setNum(-1);
							bombPlanted++;
						}
					}
				}
				else
					break;

			}
		}
	}
	for (MapSize i{}; i < MatrixMapSizeY; ++i) // ß èçâèíÿþñü çà ýòó ÷àñòü êîäà,
		//ÿ íå ìîã íàïèñàòü ýòî òàê ÷òîáû ýòî âûãëÿäåëî õîòü ÷óòü - ÷óòü ÷èòàáåëüíî
		// åñëè ÿ ïðèäóìàþ êàê ýòî ïåðåïèñàòü, òî âû íå óâèäèòå ýòîò êîììåíòàðèé
	{
		for (MapSize j{}; j < MatrixMapSizeX; ++j)
		{

			if (map[i][j].getNum() == -1)
			{
				for (short k = i - 1; k < i + 2; ++k)
				{
					for (short p = j - 1; p < j + 2; ++p)
					{
						if ((p < MatrixMapSizeX && p >= 0) && (k < MatrixMapSizeY && k >= 0))
						{
							if (map[k][p].getNum() != -1)
							{
								map[k][p].setNum(map[k][p].getNum() + 1);
							}
						}
					}
				}
			}
		}
	}
	isMapPrepaired = true;
}
bool GameMap::isAllFlagCorrect() {
	if (bombAmount == 0) {
		for (MapSize i{}; i < MatrixMapSizeY; ++i) {
			for (MapSize j{}; j < MatrixMapSizeX; ++j) {
				if (map[i][j].isFlagged() && map[i][j].getNum() != -1) {
					return false;
				}
			}
		}
		return true;
	}
	return false;
}
bool GameMap::checkWinState()
{
	if (isAllFlagCorrect()) {
		return true;
	}
	for (MapSize i{}; i < MatrixMapSizeY; ++i) {
		for (MapSize j{}; j < MatrixMapSizeX; ++j) {
			if (map[i][j].isntOpened() && map[i][j].getNum() != -1) {
				return false;
			}
		}
	}
	return true;
}
void GameMap::openCellsNear(MapPosition y, MapPosition x) {
	map[y][x].step();
	bombAmount -= map[y][x].unflag();
	if (map[y][x].getNum() == 0) {
		for (short i{ y - 1 }; i <= y + 1; ++i) {
			for (short j{ x - 1 }; j <= x + 1; ++j) {
				if (j>= 0 && j < MatrixMapSizeX && i >= 0 && i < MatrixMapSizeY && map[i][j].getNum() != -1 && map[i][j].isntOpened())
			{
					openCellsNear(i, j);
			}
			}
		}
	}
}
bool GameMap::openCell(MapPosition y, MapPosition x) {
	if (!map[y][x].step())
	{
		return false;
	}
	else {
		
		openCellsNear(y, x);
	}
	return true;
}
void GameMap::debugPrint() {
	for (MapSize i{}; i < MatrixMapSizeY; ++i) {
		for (MapSize j{}; j < MatrixMapSizeX; ++j) {
			if (map[i][j].getNum() >= 0) { std::cout << " "; };
			std::cout << map[i][j].getNum();
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}
void GameMap::debugPrintBool() {
	for (MapSize i{}; i < MatrixMapSizeY; ++i) {
		for (MapSize j{}; j < MatrixMapSizeX; ++j) {
			std::cout << map[i][j].isntOpened() << "  ";
		}
		std::cout << std::endl<<'\n';
	}
}
bool GameMap::leftClickOnMap(int x, int y) {

	if (x > deltaX && x  < CellSizeX * MatrixMapSizeX + deltaX && y> deltaY && y < CellSizeY * MatrixMapSizeY + deltaY)
	{
		unsigned short y_ = (y - deltaY) / CellSizeY;
		unsigned short x_ = (x - deltaX) / CellSizeX;
		if (!isMapPrepaired) {
			prepareMap(y_, x_);
		}
		if (map[y_][x_].step())
		{
			openCell(y_, x_);
			bombAmount -= map[y_][x_].unflag();
			return true;
		}
		else
			return false;

	}
	return true;
}
void GameMap::rightClickOnMap(int x, int y)
{
	if (x > deltaX && x  < CellSizeX * MatrixMapSizeX + deltaX && y> deltaY && y < CellSizeY * MatrixMapSizeY + deltaY && bombAmount>0)
	{
		unsigned short y_ = (y - deltaY) / CellSizeY;
		unsigned short x_ = (x - deltaX) / CellSizeX;
		bombAmount-=map[y_][x_].flag();
	}
	else if(x > deltaX && x  < CellSizeX * MatrixMapSizeX + deltaX && y> deltaY && y < CellSizeY * MatrixMapSizeY + deltaY)
	{
		unsigned short y_ = (y - deltaY) / CellSizeY;
		unsigned short x_ = (x - deltaX) / CellSizeX;
		if (map[y_][x_].isFlagged())
			bombAmount -= map[y_][x_].flag();
	}
}
void GameMap::openAllMap() {
	for (unsigned short i{}; i < MatrixMapSizeY; ++i)
	{
		for(unsigned short j{}; j < MatrixMapSizeX; ++j)
		{
			if (!map[i][j].isFlagged())
				map[i][j].step();
			else if (map[i][j].getNum() != -1)
				map[i][j].step();
		}
	}
}
void GameMap::deleteUnique() {
	isMapPrepaired = false;
	if (map!=nullptr) {
		
		for (unsigned i{}; i < MatrixMapSizeY && map[i]; ++i)
		{
			delete[] map[i];
		}

		delete[] map;
		map = nullptr;

	}
}
GameMap::~GameMap() {
	CellSizeX = 0;
	CellSizeY = 0;
	deltaY = 0;
	deltaX = 0;
	bombAmount_ = 0;
	deleteUnique();
	MatrixMapSizeX = 0;
	MatrixMapSizeY = 0;

}
