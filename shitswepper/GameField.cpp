#include "GameField.h" 
std::map< std::string, sf::Texture*>* GameField::LoadTextures(std::string path)
{
    sf::Texture* buf = new sf::Texture;
    std::map<std::string, sf::Texture*>* exhaust = new std::map<std::string, sf::Texture*>;
    for (short i{ -1 }; i < 9; ++i) 
        {
            buf->loadFromFile(path + "N" + std::to_string(i) + ".png");
            exhaust->insert(std::make_pair("N" + std::to_string(i), buf));
            buf = nullptr;
            buf = new sf::Texture;
        }
        buf->loadFromFile(path + "UNKNOWN.png");
        exhaust->insert(std::make_pair("UNKNOWN", buf));
        buf = nullptr;
        buf = new sf::Texture;
        buf->loadFromFile(path + "QUESTION.png");
        exhaust->insert(std::make_pair("QUESTION", buf));
        buf = nullptr;
        buf = new sf::Texture;
        buf->loadFromFile(path + "QUESTIONUS.png");
        exhaust->insert(std::make_pair("QUESTIONUS", buf));
        buf = nullptr;
        return exhaust;
}
GameField::GameField(std::string path,int difficulty){
    headerTexture.loadFromFile(path+"header.png");
    textures = LoadTextures(path);
    header.setTexture(headerTexture, true);
    header.setPosition(sf::Vector2f(0, 0));
    scaleX = WINDOW_RES.first / (float)header.getTexture()->getSize().x*0.6;
    scaleY = (WINDOW_RES.second * MARGIN_SCALE) / header.getTexture()->getSize().y;
    header.setScale(scaleX, scaleY);
    float minefieldScaleX,minefieldScaleY;
    if (WINDOW_RES.first > WINDOW_RES.second) {
        minefieldScaleX = 1.f;
        minefieldScaleY = WINDOW_RES.second / (float)WINDOW_RES.first;
    }
    else {
        minefieldScaleY=1.f;
        minefieldScaleX= WINDOW_RES.first / (float)WINDOW_RES.second;
    }
    ShitField.create(difficulty*minefieldScaleY, difficulty * minefieldScaleX,
        textures, std::make_pair(WINDOW_RES.second * MARGIN_SCALE, 0),
        std::make_pair(WINDOW_RES.second, WINDOW_RES.first));
    Font.loadFromFile("Font.ttf");
    bombAmount.setFont(Font);
    screenSpaceAllocatedForText = WINDOW_RES.first - headerTexture.getSize().x * scaleX;
    bombAmount.setFillColor(sf::Color::White);
    bombAmountString = "BOMBS LEFT: " + std::to_string(ShitField.getBombAmount());
    int charSizeHeight = screenSpaceAllocatedForText*(1-2*marginFromHeader)*2 / bombAmountString.size();
    //ћагическа€ константа 1.773 это отношение высоты к ширине одного символа.

    while (headerTexture.getSize().y * scaleY < charSizeHeight)
    {
        charSizeHeight--;
    }
    bombAmount.setCharacterSize(charSizeHeight);
    int middlePoint = (headerTexture.getSize().y *scaleY - charSizeHeight)/2;
    bombAmount.setPosition(headerTexture.getSize().x * scaleX + screenSpaceAllocatedForText * marginFromHeader, middlePoint);
    bombAmount.setString(bombAmountString);
    
}
void GameField::drawAllElements(sf::RenderWindow* window) {
    window->draw(header);
    ShitField.drawMap(window);
    bombAmountString = "BOMBS LEFT: " + std::to_string(ShitField.getBombAmount());
    float charSizeHeight = screenSpaceAllocatedForText * (1 - 2 * marginFromHeader) * 1.776f / bombAmountString.size();
    //ћагическа€ константа 1.776 это отношение высоты к ширине одного символа.

    while (headerTexture.getSize().y * scaleY < charSizeHeight)
    {
        charSizeHeight--;
    }
    bombAmount.setCharacterSize(charSizeHeight);
    int middlePoint = (headerTexture.getSize().y * scaleY - charSizeHeight) / 2;
    bombAmount.setPosition(headerTexture.getSize().x * scaleX + screenSpaceAllocatedForText * marginFromHeader, middlePoint);
    bombAmount.setString(bombAmountString);
    window->draw(bombAmount);

}
GameField::~GameField() {
    textures->clear();
    //остальное удалитс€ само
}