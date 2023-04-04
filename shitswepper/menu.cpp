#include "menu.h"
Menu::Menu() {
	try
	{
		if (!font.loadFromFile("Font.TTF")) { throw std::exception("FONT WASN'T LOADED"); }
	}
	catch (const std::exception&)
	{
 		isOK = false;
		return;
	}
	
	textureSOAD.loadFromFile("Armyane.png");
	textureSOAD.setSmooth(true);
	SystemOfADown.setTexture(textureSOAD, true);
	scaleSOADY = (WINDOW_RES.second * allocatedSpaceForArmenians) / textureSOAD.getSize().y;
	scaleSOADX = scaleSOADY;
	SystemOfADown.setScale(scaleSOADX, scaleSOADY);
	SystemOfADown.setOrigin(0, SystemOfADown.getTexture()->getSize().y / 2.f);
	SystemOfADown.setPosition(0 - SystemOfADown.getTexture()->getSize().x * scaleSOADX,
		WINDOW_RES.second - textureSOAD.getSize().y * scaleSOADY / 2.f);

	textureSlipknot.loadFromFile("Pendosi.png");
	textureSlipknot.setSmooth(true);
	Slipknot.setTexture(textureSlipknot, true);
	scaleSlipY = (WINDOW_RES.second * allocatedSpaceForArmenians) / textureSlipknot.getSize().y;
	scaleSlipX = SystemOfADown.getTexture()->getSize().x * scaleSOADX / Slipknot.getTexture()->getSize().x;
	Slipknot.setScale(scaleSlipX, scaleSlipY);
	Slipknot.setOrigin(0, Slipknot.getTexture()->getSize().y / 2.f);
	Slipknot.setPosition((float)SystemOfADown.getPosition().x - (float)WINDOW_RES.first,
		WINDOW_RES.second - textureSlipknot.getSize().y * scaleSlipY / 2.f);
	title.setString("SHITSWEEPER");
	title.setFont(font);
	title.setCharacterSize(titleSize);
	title.setFillColor(sf::Color::White);
	while (title.getLocalBounds().height < WINDOW_RES.second * allocatedSpaceForArmenians * 0.75f && title.getLocalBounds().width < -1.f * Slipknot.getPosition().x - 2*Slipknot.getGlobalBounds().width) {
		titleSize++;
		title.setCharacterSize(titleSize);
	}
	while (title.getLocalBounds().top > WINDOW_RES.second * allocatedSpaceForArmenians * 0.75
			|| title.getLocalBounds().width > -1.f * Slipknot.getPosition().x - Slipknot.getGlobalBounds().width) {
		titleSize--;
		title.setCharacterSize(titleSize);
	}
	title.setOrigin(title.getLocalBounds().left + title.getLocalBounds().width/2.f, title.getLocalBounds().top + title.getLocalBounds().height / 2.f);
	title.setPosition(2*WINDOW_RES.first,
		WINDOW_RES.second - textureSlipknot.getSize().y * scaleSlipY / 2.f);
	
	menuText.setFont(font);
	menuText.setCharacterSize(titleSize);
	menuText.setFillColor(sf::Color::White);
	menuText.setString("MENU");
	menuText.setOrigin(menuText.getLocalBounds().left + menuText.getLocalBounds().width / 2.f, menuText.getLocalBounds().top + menuText.getLocalBounds().height / 2.f);
	menuText.setPosition(-1.f*WINDOW_RES.first/2.F-textureSlipknot.getSize().x*scaleSlipX/2.f,WINDOW_RES.second - textureSlipknot.getSize().y * scaleSlipY / 2.f);


	sf::Text* text;
	sf::RectangleShape* rect;

	float sizeOfAButtonX = WINDOW_RES.first - DISTANCE_BETWEEN_BUTTONS * 2;
	float sizeOfAButtonY = (WINDOW_RES.second * (1 - allocatedSpaceForArmenians) - DISTANCE_BETWEEN_BUTTONS * 2) 
		/ Levels.size()- DISTANCE_BETWEEN_BUTTONS;
	unsigned buttonIndex = 0;
	for (std::string str : Levels) 
	{

		unsigned char_size = 1;
		text = new sf::Text;
		text->setString(str);
		text->setFont(font);
		text->setCharacterSize(char_size);
		rect = new sf::RectangleShape;
		rect->setFillColor(sf::Color::White);
		rect->setSize(sf::Vector2f(sizeOfAButtonX, sizeOfAButtonY));
		rect->setOrigin(sf::Vector2f(sizeOfAButtonX / 2, sizeOfAButtonY/2));
		rect->setPosition(WINDOW_RES.first / 2,
			buttonIndex * (sizeOfAButtonY+DISTANCE_BETWEEN_BUTTONS) + DISTANCE_BETWEEN_BUTTONS+ sizeOfAButtonY / 2);
		while (text->getLocalBounds().height < rect->getLocalBounds().height/1.5f)
		{
			char_size++;
			text->setCharacterSize(char_size);
			
		}
		text->setCharacterSize(char_size);
		while (text->getLocalBounds().width > rect->getLocalBounds().width) 
		{
			char_size--;
			text->setCharacterSize(char_size);
		}
		text->setFillColor(sf::Color::Black);
		text->setPosition(rect->getGlobalBounds().left + rect->getGlobalBounds().width / 2 - text->getLocalBounds().width / 2,
			rect->getGlobalBounds().top + rect->getGlobalBounds().height / 2 - text->getLocalBounds().height / 2-DISTANCE_BETWEEN_BUTTONS);
		Buttons[text] = rect;
		buttonIndex++;
		
		
	}
	rect = nullptr;
	text = nullptr;

}

void Menu::draw(sf::RenderWindow* win) {
	win->draw(SystemOfADown);
	win->draw(Slipknot);
	win->draw(title);
	win->draw(menuText);
	if (SystemOfADown.getPosition().x<= WINDOW_RES.first&& Slipknot.getPosition().x <= WINDOW_RES.first)
	{
		
		SystemOfADown.setPosition(SystemOfADown.getPosition() + sf::Vector2f(animationSpeed, 0));
		Slipknot.setPosition(Slipknot.getPosition() + sf::Vector2f(animationSpeed, 0));
		title.setPosition(title.getPosition() + sf::Vector2f(animationSpeed, 0));
		menuText.setPosition(menuText.getPosition() + sf::Vector2f(animationSpeed, 0));
	}
	else if (SystemOfADown.getPosition().x <= WINDOW_RES.first)
	{
		Slipknot.setPosition((float)SystemOfADown.getPosition().x - (float)WINDOW_RES.first,
			Slipknot.getPosition().y);
		
		SystemOfADown.setPosition(SystemOfADown.getPosition() + sf::Vector2f(animationSpeed, 0));

		title.setPosition(title.getPosition() + sf::Vector2f(animationSpeed, 0));
		menuText.setPosition(title.getPosition().x - WINDOW_RES.first,
			WINDOW_RES.second - textureSlipknot.getSize().y * scaleSlipY / 2.f);
	}
	else if (Slipknot.getPosition().x <= WINDOW_RES.first) {
		SystemOfADown.setPosition((float)Slipknot.getPosition().x - (float)WINDOW_RES.first,
			SystemOfADown.getPosition().y);
		menuText.setPosition(menuText.getPosition() + sf::Vector2f(animationSpeed, 0));
		Slipknot.setPosition(Slipknot.getPosition() + sf::Vector2f(animationSpeed, 0));
		title.setPosition((Slipknot.getPosition().x + Slipknot.getGlobalBounds().width + SystemOfADown.getPosition().x) / 2.f,
			WINDOW_RES.second - textureSlipknot.getSize().y * scaleSlipY / 2.f);

	}
	for (auto i : Buttons) {
	
		win->draw(*i.second);
		win->draw(*i.first);
	}
	
	
}
std::string Menu::leftClick(sf::RenderWindow* win)
{
	sf::Vector2i pos = sf::Mouse::getPosition(*win);
	sf::Vector2f casted = static_cast<sf::Vector2f>(pos); // Àâòîð ñôìë ïî÷åìó-òî íå äîáàâèë ïðåãðóçêó äëÿ ôëîàòîâ â âåêòîð èíòîâ nice git poter kirilicu, ya uje ne pomnyu pochemu ya tak sdelal(
	for(auto button : Buttons)
	{
		if (button.second->getGlobalBounds().contains(casted)) {
			return button.first->getString();
		}
	}
	return "";
}
