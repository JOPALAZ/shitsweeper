#include "GameField.h" 
#include <fstream>
std::map< std::string, sf::Texture*>* GameField::LoadTextures(std::string path)
{
    if (textures!=nullptr) {
        for (auto& k : *textures) {
            if (k.second != nullptr) {
                k.second->~Texture();
                k.second = nullptr;
            }
        }
        textures->clear();
        delete textures;
        textures = nullptr;
    }
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
void GameField::loadSoundTrack()
{
    unloadSoundTrack();
    SoundTrack.openFromFile(path + "\\soundtrack");
    SoundTrack.setLoop(true);
    SoundTrack.play();
    if (path == "BARBARIKI")
        SoundTrack.setVolume(6.f); // íåâåðîÿòíî ãðîìêî, âûøå 20 ñòàâèòü âîîáùå íåëüçÿ
    else if (path == "SEREGA PIRAT")
        SoundTrack.setVolume(0.f); 
    //Íà ìóçûêå ìåíÿ ó÷èëè ÷òî ìóçûêà  ó÷èò ñàìûì ëó÷øèì ÷óâñòâàì ëþáâè òàì, äðóæáå. Âîñïèòûâàåò â íàñ âêóñ, âåñåëèò. 
    //Ñåð¸ãà ïîêàçûâàåò íà ñâîåì ïðèìåðå ÷òî ìóçûêà åù¸ è ìîæåò çàñòàâèòü ÷åëîâåêà çàäóìàòüñÿ î ñìûñëå æèçíè,
    //îêîí÷àòåëüíî óáåäèâ ÷òî ëó÷øå óìåðåòü, ÷åì ñëóøàòü ïèðàòà
    //Ñïàñèáî, Ñåðåãà, ÿ âêëþ÷èë ýòó ïåñíè ïðè äðóçüÿõ è âñåì îíà íàñòîëüêî ïîíðàâèëàñü, ÷òî ìåíÿ ïîãëàäèëè áèòîé è òåïåðü ÿ îòäûõàþ â áîëüíèöå
    //ß ñëóøàë ýòîò òðåê íà óëèöå è ó áîìæà ëîïíóëà áàðàáàííàÿ ïåðåïîíêà è åãî ïîâåçëè â áîëüíèöó. Ñïàñèáî, Ñåðåãà, òåïåðü ó áîìæà åñòü õîòü ìåñòî ïðîæèâàíèÿ
    //×åëîâåê, êîòîðûé óçíàë î ñåðåãå ïèðàòå  áûë õóäîæíèêîì. Îí ïîñëóøàë åå è âäîõíîâèëñÿ èäååé. Ýòèì õóäîæíèêîì áûë àäîëüô ãèòëåð
    //Äóìàë ÷òî ñëóõ—ýòî äàð, ïîòîì âêëþ÷èë òðýê ñåðåãè è ïîíÿë, ÷òî ýòî íå òàê.
    //Òðåê íàñòîëüêî âçðûâíîé ÷òî ó ìåíÿ âçîðâàëèñü ïåðåïîíêè
    //Ñåð¸ãà, ïîñëå ïðîñëóøèâàíèå òâîåãî òðåêà, âðà÷è âåðíóëè ðàêàâóþ îïóõîëü îáðàòíî
    //Ñåð¸ãà ñïàñèáî çà òâî¸ òâîð÷åñòâî, âêëþ÷èë êîãäà ìàìà áûëà äîìà, âñåãäà áûëî èíòåðåñíî êàê æèâ¸òñÿ íà óëèöå!
    //Ñïàñèáî âàì Ñåðãåé! Âû ñïàñëè ìîþ æèçíü. Íà äíÿõ ìåíÿ îêðóæèëà òîëïà ãîïíèêîâ, è âîò êîãäà ÿ óæå áûë ãîòîâ îùóòèòü áîòèíîê íà ñâîåì ëèöå,
    //ÿ óñëûøàë ýòó ïåñíþ. Ãîïíèêè ñðàçó æå îòñòàëè ìåíÿ è ïîøëè èçáèâàòü êîãî òî äðóãîãî!
    else
        SoundTrack.setVolume(50.f);
}
void GameField::unloadSoundTrack()
{
    if(SoundTrack.Playing)
        SoundTrack.stop();
    if (WinLoseSound.Playing)
        WinLoseSound.stop();
}
void GameField::MakeGameField(std::string path,int difficulty){
    headerTexture.loadFromFile(path+"header.png");
    textures = LoadTextures(path);
    header.setTexture(headerTexture, true);
    header.setPosition(sf::Vector2f(0, 0));
    scaleX = WINDOW_RES.first / (float)header.getTexture()->getSize().x*0.6f;
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
    ShitField.deleteUnique();
    ShitField.create(difficulty*minefieldScaleY, difficulty * minefieldScaleX,
        textures, std::make_pair(WINDOW_RES.second * MARGIN_SCALE, 0),
        std::make_pair(WINDOW_RES.second, WINDOW_RES.first));
    if (!Font.loadFromFile("Font.TTF")) { std::cout << "fddfd"; }
    bombAmount.setFont(Font);
    screenSpaceAllocatedForText = WINDOW_RES.first - headerTexture.getSize().x * scaleX;
    bombAmountString = "BOMBS LEFT: " + std::to_string(ShitField.getBombAmount());
    bombAmount.setString(bombAmountString);
    this->charSizeHeight = screenSpaceAllocatedForText*(1-2*marginFromHeader)*2 / bombAmountString.size();
    while (bombAmount.getLocalBounds().width <= WINDOW_RES.first * 0.32f && bombAmount.getLocalBounds().height <= WINDOW_RES.first * MARGIN_SCALE * 0.8f)
    {
        charSizeHeight++;
        bombAmount.setCharacterSize(charSizeHeight);
    }
    while (bombAmount.getLocalBounds().width>WINDOW_RES.first*0.32f|| bombAmount.getLocalBounds().height > WINDOW_RES.first*MARGIN_SCALE*0.8f)
    {
        charSizeHeight--;
        bombAmount.setCharacterSize(charSizeHeight);
    }

    bombAmount.setOrigin(bombAmount.getLocalBounds().left + bombAmount.getLocalBounds().width / 2.0f,
        bombAmount.getLocalBounds().top + bombAmount.getLocalBounds().height / 2.0f);
    bombAmount.setPosition(WINDOW_RES.first * 0.8f, WINDOW_RES.second * MARGIN_SCALE / 2.f);
    bombAmount.setFillColor(sf::Color::White);
    loadSoundTrack();
    gameIsOn = true;
    
}
void GameField::drawAllElements(sf::RenderWindow* window) {
    if (draw) {
        if (gameIsOn) {

            bombAmount.setString(bombAmountString);
            window->draw(header);
            window->draw(bombAmount);
            ShitField.drawMap(window);

        }
        else if(drawGameMenu) {
            menu.draw(window);
        }
    }

}
bool GameField::leftClickOnField(sf::RenderWindow* window)
{

    if (gameIsOn) {
        int x = sf::Mouse::getPosition(*window).x;
        int y = sf::Mouse::getPosition(*window).y;
        if (!ShitField.leftClickOnMap(x, y))
        {

            bombAmountString = "YOU LOST";
            bombAmount.setString(bombAmountString);
            while (bombAmount.getLocalBounds().width <= WINDOW_RES.first * 0.32f && bombAmount.getLocalBounds().height <= WINDOW_RES.first * MARGIN_SCALE * 0.8f)
            {
                charSizeHeight++;
                bombAmount.setCharacterSize(charSizeHeight);
            }
            while (bombAmount.getLocalBounds().width > WINDOW_RES.first * 0.32f || bombAmount.getLocalBounds().height > WINDOW_RES.first * MARGIN_SCALE * 0.8f)
            {
                charSizeHeight--;
                bombAmount.setCharacterSize(charSizeHeight);
            }

            bombAmount.setOrigin(bombAmount.getLocalBounds().left + bombAmount.getLocalBounds().width / 2.0f,
                bombAmount.getLocalBounds().top + bombAmount.getLocalBounds().height / 2.0f);
            bombAmount.setPosition(WINDOW_RES.first * 0.8f, WINDOW_RES.second * MARGIN_SCALE / 2.f);
            bombAmount.setFillColor(sf::Color(128, 64, 48)); // KORICHNEVY 
            ShitField.openAllMap();
            window->clear();
            drawAllElements(window);
            window->display();
            playWinLooseSound(false);
            gameIsOn = false;
            
            return false;
        }
        if (ShitField.checkWinState()) {
            bombAmountString = "YOU WON";
            bombAmount.setString(bombAmountString);
            while (bombAmount.getLocalBounds().width <= WINDOW_RES.first * 0.32f && bombAmount.getLocalBounds().height <= WINDOW_RES.first * MARGIN_SCALE * 0.8f)
            {
                charSizeHeight++;
                bombAmount.setCharacterSize(charSizeHeight);
            }
            while (bombAmount.getLocalBounds().width > WINDOW_RES.first * 0.32f || bombAmount.getLocalBounds().height > WINDOW_RES.first * MARGIN_SCALE * 0.8f)
            {
                charSizeHeight--;
                bombAmount.setCharacterSize(charSizeHeight);
            }

            bombAmount.setOrigin(bombAmount.getLocalBounds().left + bombAmount.getLocalBounds().width / 2.0f,
                bombAmount.getLocalBounds().top + bombAmount.getLocalBounds().height / 2.0f);
            bombAmount.setPosition(WINDOW_RES.first * 0.8f, WINDOW_RES.second * MARGIN_SCALE / 2.f);
            bombAmount.setFillColor(sf::Color(9, 121, 105)); // ZELENIY
            ShitField.openAllMap();
            window->clear();
            drawAllElements(window);
            window->display();
            playWinLooseSound(true);
            gameIsOn = false;
            return true;
        }
        bombAmountString = "BOMBS LEFT: " + std::to_string(ShitField.getBombAmount());
        return true;
    }
    else
    {
        this->path = menu.leftClick(window);
        if (this->path.size() != 0) {
            MakeGameField(this->path+"\\",getDifficulty());
        }

    
    
    }
    return false;
}
unsigned GameField::getDifficulty()
{
    std::ifstream file(path+"\\dif");
    unsigned difficulty;
    file >> difficulty;
    return difficulty;
}
void GameField::playWinLooseSound(bool win) {
    unloadSoundTrack();
    sf::sleep(sf::milliseconds(250));
    if (win) { WinLoseSound.openFromFile("win.flac"); }
    else { WinLoseSound.openFromFile("lose.flac"); }
    WinLoseSound.setVolume(50.f);
    WinLoseSound.setLoop(false);
    WinLoseSound.play();
    sf::sleep(sf::seconds(3));
}
void GameField::rightClickOnField(sf::RenderWindow* window) {
    if (gameIsOn) {
        float x = sf::Mouse::getPosition(*window).x;
        float y = sf::Mouse::getPosition(*window).y;
        ShitField.rightClickOnMap(x, y);
        if (ShitField.getBombAmount() == 0) {
            if (ShitField.checkWinState()) {
                bombAmountString = "YOU WON";
                bombAmount.setString(bombAmountString);
                while (bombAmount.getLocalBounds().width <= WINDOW_RES.first * 0.32f && bombAmount.getLocalBounds().height <= WINDOW_RES.first * MARGIN_SCALE * 0.8f)
                {
                    charSizeHeight++;
                    bombAmount.setCharacterSize(charSizeHeight);
                }
                while (bombAmount.getLocalBounds().width > WINDOW_RES.first * 0.32f || bombAmount.getLocalBounds().height > WINDOW_RES.first * MARGIN_SCALE * 0.8f)
                {
                    charSizeHeight--;
                    bombAmount.setCharacterSize(charSizeHeight);
                }

                bombAmount.setOrigin(bombAmount.getLocalBounds().left + bombAmount.getLocalBounds().width / 2.0f,
                    bombAmount.getLocalBounds().top + bombAmount.getLocalBounds().height / 2.0f);
                bombAmount.setPosition(WINDOW_RES.first * 0.8f, WINDOW_RES.second * MARGIN_SCALE / 2.f);
                bombAmount.setFillColor(sf::Color(9, 121, 105)); // ZELENIY
                ShitField.openAllMap();
                window->clear();
                drawAllElements(window);
                window->display();
                playWinLooseSound(true);
                gameIsOn = false;
                return;
            }
        }
        bombAmountString = "BOMBS LEFT: " + std::to_string(ShitField.getBombAmount());
    }
}
void GameField::drawMenu(sf::RenderWindow* window) {
    menu.draw(window);
}
void GameField::wait(unsigned msec) {
    sf::sleep(sf::milliseconds(msec)); // ãåíèé)
}
GameField::~GameField() {
    if(textures)
    textures->clear();
    //îñòàëüíîå óäàëèòñÿ ñàìî
}
