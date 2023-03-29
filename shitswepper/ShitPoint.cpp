#include"ShitPoint.h"
ShitPoint::ShitPoint() { number = 0; };
ShitPoint::ShitPoint(std::map<std::string, sf::Texture>* textures)
{
	const sf::Texture texture = textures->at("UNKNOWN");
}
ShitPoint::ShitPoint(int num, std::map<std::string, sf::Texture*>* textures) :textures(textures)
{
	opened = false; number = num;
}
bool ShitPoint::step()
{
	opened = true;

	body.setTexture(*textures->at("N" + std::to_string(number)), true);
	setSize(sizeX, sizeY);
	if (number == -1)
		return 0;
	return 1;
};
char ShitPoint::flag()
{
	if (!opened)
	{
		if (flagged)
		{
			if (!sure)
			{
				sure = true;
				flagged = false;
				body.setTexture(*textures->at("UNKNOWN"), true);
				setSize(sizeX, sizeY);
				return -1;
			}
			sure = false;
			body.setTexture(*textures->at("QUESTIONUS"), true);
			setSize(sizeX, sizeY);
			return 0;
		}
		flagged = true;
		body.setTexture(*textures->at("QUESTION"), true);
		setSize(sizeX, sizeY);
		return 1;
	}
	return 0;

}
int ShitPoint::getNum() { return number; }
void ShitPoint::setNum(int num) { number = num; }
bool ShitPoint::isntOpened() { return !opened; }
void ShitPoint::setTextures(std::map<std::string, sf::Texture*>* texturesIn) {
	textures = texturesIn;

	body.setTexture(*textures->at("UNKNOWN"), true);
}
void ShitPoint::setSize(float x, float y) {
	double scaleX = sizeX / body.getTexture()->getSize().x;
	double scaleY = sizeY / body.getTexture()->getSize().y;
	//body.setTextureRect(sf::IntRect(0, 0, body.getTexture()->getSize().x, body.getTexture()->getSize().y));
	body.setScale(scaleX, scaleY);
}
void ShitPoint::setCellSizes(float x, float y) {
	sizeX = x;
	sizeY = y;
}
void ShitPoint::setPosition(float x, float y) {
	body.setPosition(sf::Vector2f(x, y));
}
sf::Sprite ShitPoint::getSprite() {


	return body;
}
char ShitPoint::unflag() {
	if (flagged) {
		flagged = false;
		sure = true;
		return -1;
	}
	flagged = false;
	sure = true;
	return 0;
}