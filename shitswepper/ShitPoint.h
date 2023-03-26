#pragma once
class ShitPoint {
public:
	ShitPoint() { number = 0; };
	ShitPoint(std::map<std::string, sf::Texture>* textures) 
	{
		const sf::Texture texture = textures->at("UNKNOWN"); 
	}
	ShitPoint(int num, std::map<std::string, sf::Texture*>* textures):textures(textures) 
	{
		opened = false; number = num; const sf::Texture* texture = textures->at("UNKNOWN");
	}
	bool step() 
	{
		opened = true;
		const sf::Texture* texture = textures->at("N"+std::to_string(number));
		body.setTexture(texture);
		if (number == -1)
			return 0;
		return 1;
	};
	void flag() 
	{
		if (!opened) 
		{
			if (flagged) 
			{
				if (!sure)
				{
					sure = true;
					flagged = false;
					const sf::Texture* texture = textures->at("UNKNOWN.png");
					return;
				}
				sure = false;
				const sf::Texture* texture = textures->at("QUESTIONUS.png");
				return;
			}
			flagged = true;
			const sf::Texture* texture = textures->at("QUESTION.png");
			return;
		}
		return;
	
	}
	int getNum() { return number; }
	void setNum(int num) { number = num;}
	bool isntOpened() { return !opened; }

	~ShitPoint() = default;
	void setTextures(std::map<std::string, sf::Texture*>* texturesIn) {
		textures = texturesIn;
		const sf::Texture* texture = texturesIn->at("UNKNOWN");
		body.setTexture(texture);
	}
	void setSize(float x, float y) {
		body.setSize(sf::Vector2f(x, y));
	}
	void setPosition(float x, float y) {
		body.setPosition(sf::Vector2f(x, y));
	}
	sf::RectangleShape* getRekt() { return &body;}
protected:
	int number=0;
	bool flagged=false;
	bool sure=true;
	bool opened=false;
	std::map<std::string, sf::Texture*>* textures;
	sf::RectangleShape body;
};