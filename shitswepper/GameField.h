#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"GameMap.h"
#include"constants.h"
#include "menu.h"
//#include "ShitMap.h"

class GameField
{
public:
	GameField();
	bool isOk() { return isOK; }
	bool MakeGameField(std::string path,int difficulty);
	GameMap* getMapField() { return &gameMap;}
	sf::Sprite* getHeader() { return &header; }
	sf::Text* getTextOfBombAmount() { return &bombAmount; };
	void drawAllElements(sf::RenderWindow* window);
	std::map< std::string, sf::Texture*>* LoadTextures(std::string path);
	void loadSoundTrack();
	void unloadSoundTrack();
	void playWinLooseSound(bool win);
	bool leftClickOnField(sf::RenderWindow* window);
	void rightClickOnField(sf::RenderWindow* window);
	void drawMenu(sf::RenderWindow* window);
	bool isGameIsOn() { return gameIsOn; }
	void wait(unsigned msec);
	unsigned getDifficulty();
	void mute();
	void hint(sf::RenderWindow* window) {
		if (gameIsOn) {
			if (!gameMap.giveHint() && gameMap.getBombAmount() != 0)
				std::cout << "NOTHING CAN BE DONE\n";
			bombAmountString = "BOMBS LEFT: " + std::to_string(gameMap.getBombAmount());
			if (gameMap.getBombAmount() == 0)
				isWin(window);
		}
	}
	void superHint(sf::RenderWindow* window) {
		if (gameIsOn) {
		if (!gameMap.giveSuperHint() && gameMap.getBombAmount() != 0)
			std::cout << "NOTHING CAN BE DONE\n";
		bombAmountString = "BOMBS LEFT: " + std::to_string(gameMap.getBombAmount());
		if (gameMap.getBombAmount() == 0)
			isWin(window);
		}
	}
	~GameField();
	bool isWin(sf::RenderWindow* window);
private:
	float volume;
	bool muted;
	bool isOK = true;
	bool gameIsOn=false;
	bool drawGameMenu = true;
	bool draw=true;
	unsigned charSizeHeight;
	float scaleX, scaleY;
	int screenSpaceAllocatedForText;
	std::string bombAmountString;
	Menu menu;
	sf::Music WinLoseSound;
	std::string path;
	sf::Texture headerTexture;
	std::map<std::string, sf::Texture*>* textures;
	sf::Sprite header;
	sf::Font Font;
	sf::Music SoundTrack;
	GameMap gameMap;
	sf::Text bombAmount;
};

