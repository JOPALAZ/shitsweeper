#pragma once
#include"ShitPoint.h"


using ShitSize = unsigned short;
using ShitPosition = ShitSize;

class ShitMap
{
public:
	ShitMap(ShitSize y, ShitSize x, std::map<std::string, sf::Texture*>* textures,std::pair<unsigned short, unsigned short>p1, std::pair<unsigned short, unsigned short>p2) {
		MatrixMapSizeY = y;
		MatrixMapSizeX = x;
		srand(0);
		unsigned short bombPlanted = 0;
		map = new ShitPoint * [y];
		float sizeY = (std::max(p1.first, p2.first) - std::min(p1.first, p2.first)) / y;
		float sizeX = (std::max(p1.second, p2.second) - std::min(p1.second, p2.second)) / x;
		CellSizeX = sizeX;
		CellSizeY = sizeY;
		deltaY = p1.first;
		deltaX = p1.second;
		for (ShitSize i{}; i < y; ++i) {
			map[i] = new ShitPoint[x];
			for (ShitSize j{}; j < x; ++j) {
				map[i][j].setSize(sizeX, sizeY);
				map[i][j].setTextures(textures);
				map[i][j].setPosition(j * sizeX+p1.second, i * sizeY+p1.first);
			}
		}
	}
	void drawShit(sf::RenderWindow* window){
		for (ShitSize i{}; i < MatrixMapSizeY; ++i) {
			for (ShitSize j{}; j < MatrixMapSizeX; ++j) {
				//window->clear();
				window->draw(*map[i][j].getRekt());
				//window->display();
				//system("pause");
			}
		}
	}
	void prepareKaban(ShitPosition y_pos, ShitPosition x_pos, unsigned char bombAmount) 
	{
		unsigned char bombPlanted=0;
		while (bombAmount > bombPlanted) {
			for (ShitSize i{}; i < MatrixMapSizeY; ++i) {
				if (bombPlanted >= bombAmount)
					break;
				for (ShitSize j{}; j < MatrixMapSizeX; ++j) {
					if (bombPlanted < bombAmount) {
						if (i != y_pos && j != x_pos && map[i][j].getNum() != -1) {
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
		isKabanPrepaired = true;
	}
	void ZhidkiyStul(ShitPosition y, ShitPosition x){
		map[y][x].step();
		/*debugPrintBulldog();
		std::cout << "\n";*/
		if (map[y][x].getNum() == 0) {
			if (x - 1 >= 0 && x - 1 < MatrixMapSizeX && y >= 0 && y < MatrixMapSizeY && map[y][x - 1].getNum() != -1 && map[y][x - 1].isntOpened())
			{
				ZhidkiyStul(y, x - 1);
			}
			if (x + 1 >= 0 && x + 1 < MatrixMapSizeX && y >= 0 && y < MatrixMapSizeY && map[y][x + 1].getNum() != -1 && map[y][x + 1].isntOpened())
			{
				ZhidkiyStul(y, x + 1);
			}
			if (x >= 0 && x < MatrixMapSizeX && y - 1 >= 0 && y - 1 < MatrixMapSizeY && map[y - 1][x].getNum() != -1 && map[y - 1][x].isntOpened())
			{
				ZhidkiyStul(y - 1, x);
			}
			if (x >= 0 && x < MatrixMapSizeX && y + 1 >= 0 && y + 1 < MatrixMapSizeY && map[y + 1][x].getNum() != -1 && map[y + 1][x].isntOpened())
			{
				ZhidkiyStul(y + 1, x);
			}
		}
	}
	bool openShitExlodeKabaniWeWeWeAhaha(ShitPosition y, ShitPosition x) {
		if (!map[y][x].step())
		{
			return false;
		}
		else {
			ZhidkiyStul(y, x);
		}
		return true;
	}
	void debugPrint() {
		for (ShitSize i{}; i < MatrixMapSizeY; ++i) {
			for (ShitSize j{}; j < MatrixMapSizeX; ++j) {
				if (map[i][j].getNum() >= 0) { std::cout << " "; };
				std::cout << map[i][j].getNum();
				std::cout << " ";
			}
			std::cout << std::endl;
		}
	}
	void debugPrintBulldog () {
		for (ShitSize i{}; i < MatrixMapSizeY; ++i) {
			for (ShitSize j{}; j < MatrixMapSizeX; ++j) {
				std::cout << map[i][j].isntOpened() << "  ";
			}
			std::cout << std::endl;
		}
	}
	bool clickOnShit(int x, int y, unsigned char bomb = 0 ) {
		
		if (x > deltaX && x  < CellSizeX * MatrixMapSizeX+deltaX  && y> deltaY && y < CellSizeY * MatrixMapSizeY+deltaY)
		{
			
			/*std::cout << x - deltaX << '\t';
			std::cout << y - deltaY << "\n\n";
			std::cout << (int)((x - deltaX) / CellSizeX) << '\t';
			std::cout << (int)((x - deltaX) / CellSizeX) << '\n';*/
			unsigned short y_ = (y - deltaY) / CellSizeY;
			unsigned short x_ = (x - deltaX) / CellSizeX;
			if (!isKabanPrepaired) {
				prepareKaban(y_, x_, bomb);
			}
			debugPrint();
			debugPrintBulldog();
			if (map[y_][x_].step())
			{
				openShitExlodeKabaniWeWeWeAhaha(y_, x_);
				debugPrintBulldog();
				return true;
			}
			else
				return false;

		}
		return 1;
	}
private:
	bool isKabanPrepaired = false;
	ShitPoint** map;
	ShitSize MatrixMapSizeY;
	ShitSize MatrixMapSizeX;
	float CellSizeX;
	float CellSizeY;
	int deltaX;
	int deltaY;

};

