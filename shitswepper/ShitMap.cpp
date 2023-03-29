#include "ShitMap.h"
ShitMap::ShitMap() {};
void ShitMap::create(ShitSize y, ShitSize x, std::map<std::string, sf::Texture*>* textures, std::pair<unsigned short, unsigned short>p1, std::pair<unsigned short, unsigned short>p2) {
	MatrixMapSizeY = y;
	MatrixMapSizeX = x;
	bombAmount = std::max(MatrixMapSizeX, MatrixMapSizeY) * 1.3f;
	srand(0);
	unsigned short bombPlanted = 0;
	map = new ShitPoint * [y];
	float sizeY = (std::max(p1.first, p2.first) - std::min(p1.first, p2.first)) / (float)y;
	float sizeX = (std::max(p1.second, p2.second) - std::min(p1.second, p2.second)) / (float)x;
	CellSizeX = sizeX;
	CellSizeY = sizeY;
	deltaY = p1.first;
	deltaX = p1.second;
	for (ShitSize i{}; i < y; ++i) {
		map[i] = new ShitPoint[x];
		for (ShitSize j{}; j < x; ++j) {
			map[i][j].setCellSizes(sizeX, sizeY);
			map[i][j].setTextures(textures);
			map[i][j].setSize(sizeX, sizeY);
			map[i][j].setPosition(j * sizeX + p1.second, i * sizeY + p1.first);
		}
	}
}
void ShitMap::drawMap(sf::RenderWindow* window) {
	for (ShitSize i{}; i < MatrixMapSizeY; ++i) {
		for (ShitSize j{}; j < MatrixMapSizeX; ++j) {
			//window->clear();
			window->draw(map[i][j].getSprite());
			//window->display();
			//system("pause");
		}
	}
}
void ShitMap::prepareMap(MapPosition y_pos, MapPosition x_pos)
{
	auto isBounded = [&](ShitSize i, ShitSize j)->bool
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
	while (bombAmount > bombPlanted) {
		for (ShitSize i{}; i < MatrixMapSizeY; ++i) {
			if (bombPlanted >= bombAmount)
				break;
			for (ShitSize j{}; j < MatrixMapSizeX; ++j) {
				if (bombPlanted < bombAmount) {
					if (i != y_pos && j != x_pos && map[i][j].getNum() != -1&&!isBounded(i,j)) {
						if (rand() % MatrixMapSizeX * MatrixMapSizeY <= 1) {

							map[i][j].setNum(-1);
							bombPlanted++;
							//this->debugPrint();
						}
					}
				}
				else
					break;

			}
		}
	}
	for (ShitSize i{}; i < MatrixMapSizeY; ++i) // Я извиняюсь за эту часть кода,
		//я не мог написать это так чтобы это выглядело хоть чуть - чуть читабельно
		// если я придумаю как это переписать, то вы не увидите этот комментарий
	{
		for (ShitSize j{}; j < MatrixMapSizeX; ++j)
		{
			//debugPrint();
			if (map[i][j].getNum() == -1)
			{
				for (short k = i - 1; k < i + 2; ++k)
				{
					for (short p = j - 1; p < j + 2; ++p)
					{
						if ((p < MatrixMapSizeX && p >= 0) && (k < MatrixMapSizeY && k >= 0))
						{
							//std::cout << k << " " << p << '\n';
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
bool ShitMap::checkWinState()
{
	for (ShitSize i{}; i < MatrixMapSizeY; ++i) {
		for (ShitSize j{}; j < MatrixMapSizeX; ++j) {
			if (map[i][j].getNum() != -1 && map[i][j].isntOpened())
				return false;
		}
	}
	return true;
}
void ShitMap::openCellsNear(MapPosition y, MapPosition x) {
	map[y][x].step();
	bombAmount -= map[y][x].unflag();
	/*debugPrintBulldog();
	std::cout << "\n";*/
	if (map[y][x].getNum() == 0) {
		for (short i{ y - 1 }; i <= y + 1; ++i) {
			for (short j{ x - 1 }; j <= x + 1; ++j) {
				if (j>= 0 && j < MatrixMapSizeX && i >= 0 && i < MatrixMapSizeY && map[i][j].getNum() != -1 && map[i][j].isntOpened())
			{
					openCellsNear(i, j);
			}
			}
		}
		//if (x - 1 >= 0 && x - 1 < MatrixMapSizeX && y >= 0 && y < MatrixMapSizeY && map[y][x - 1].getNum() != -1 && map[y][x - 1].isntOpened())
		//{
		//	openCellsNear(y, x - 1);
		//}
		//if (x + 1 >= 0 && x + 1 < MatrixMapSizeX && y >= 0 && y < MatrixMapSizeY && map[y][x + 1].getNum() != -1 && map[y][x + 1].isntOpened())
		//{
		//	openCellsNear(y, x + 1);
		//}
		//if (x >= 0 && x < MatrixMapSizeX && y - 1 >= 0 && y - 1 < MatrixMapSizeY && map[y - 1][x].getNum() != -1 && map[y - 1][x].isntOpened())
		//{
		//	openCellsNear(y - 1, x);
		//}
		//if (x >= 0 && x < MatrixMapSizeX && y + 1 >= 0 && y + 1 < MatrixMapSizeY && map[y + 1][x].getNum() != -1 && map[y + 1][x].isntOpened())
		//{
		//	openCellsNear(y + 1, x);
		//}
	}
}
bool ShitMap::openCell(MapPosition y, MapPosition x) {
	if (!map[y][x].step())
	{
		return false;
	}
	else {
		
		openCellsNear(y, x);
	}
	return true;
}
void ShitMap::debugPrint() {
	for (ShitSize i{}; i < MatrixMapSizeY; ++i) {
		for (ShitSize j{}; j < MatrixMapSizeX; ++j) {
			if (map[i][j].getNum() >= 0) { std::cout << " "; };
			std::cout << map[i][j].getNum();
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}
void ShitMap::debugPrintBool() {
	for (ShitSize i{}; i < MatrixMapSizeY; ++i) {
		for (ShitSize j{}; j < MatrixMapSizeX; ++j) {
			std::cout << map[i][j].isntOpened() << "  ";
		}
		std::cout << std::endl<<'\n';
	}
}
bool ShitMap::leftClickOnMap(int x, int y) {

	if (x > deltaX && x  < CellSizeX * MatrixMapSizeX + deltaX && y> deltaY && y < CellSizeY * MatrixMapSizeY + deltaY)
	{

		/*std::cout << x - deltaX << '\t';
		std::cout << y - deltaY << "\n\n";
		std::cout << (int)((x - deltaX) / CellSizeX) << '\t';
		std::cout << (int)((x - deltaX) / CellSizeX) << '\n';*/

		unsigned short y_ = (y - deltaY) / CellSizeY;
		unsigned short x_ = (x - deltaX) / CellSizeX;
		if (!isMapPrepaired) {
			prepareMap(y_, x_);
		}
		debugPrint();
		debugPrintBool();
		if (map[y_][x_].step())
		{
			openCell(y_, x_);
			bombAmount -= map[y_][x_].unflag();
			debugPrintBool();
			return true;
		}
		else
			return false;

	}
	return 1;
}
void ShitMap::rightClickOnMap(int x, int y)
{
	if (x > deltaX && x  < CellSizeX * MatrixMapSizeX + deltaX && y> deltaY && y < CellSizeY * MatrixMapSizeY + deltaY && bombAmount>0)
	{
		unsigned short y_ = (y - deltaY) / CellSizeY;
		unsigned short x_ = (x - deltaX) / CellSizeX;
		bombAmount-=map[y_][x_].flag();
	}
}
ShitMap::~ShitMap() {
	CellSizeX = 0;
	CellSizeY = 0;
	deltaY = 0;
	deltaX = 0;
	bombAmount = 0;
	isMapPrepaired = false;
	for (unsigned i{};i<MatrixMapSizeY&&map[i];++i)
	{
		delete[] map[i];
	}
	if(map)
	delete[] map;
	MatrixMapSizeX = 0;
	MatrixMapSizeY = 0;

}