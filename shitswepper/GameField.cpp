#include "GameField.h" 
#include <fstream>
GameField::GameField() {
    isOK = menu.isOk();
}
std::map< std::string, sf::Texture*>* GameField::LoadTextures(std::string path)
{
    if (textures != nullptr) {
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
        if (!buf->loadFromFile(path + "N" + std::to_string(i) + ".png")) {
            std::string exception_text = "DIDN'T FIND " + path + "N" + std::to_string(i) + ".png";
            throw std::invalid_argument(exception_text);
        }
        exhaust->insert(std::make_pair("N" + std::to_string(i), buf));
        buf = nullptr;
        buf = new sf::Texture;
    }
    if (!buf->loadFromFile(path + "UNKNOWN.png")){
        std::string exception_text = "DIDN'T FIND "+path + "UNKNOWN.png";
        throw std::invalid_argument(exception_text);
    }
    exhaust->insert(std::make_pair("UNKNOWN", buf));
    buf = nullptr;
    buf = new sf::Texture;
    if (!buf->loadFromFile(path + "QUESTION.png")) {
        std::string exception_text = "DIDN'T FIND " + path + "QUESTION.png";
        throw std::invalid_argument(exception_text);
    }
    exhaust->insert(std::make_pair("QUESTION", buf));
    buf = nullptr;
    buf = new sf::Texture;
    if (!buf->loadFromFile(path + "QUESTIONUS.png")) {
        std::string exception_text = "DIDN'T FIND " + path + "QUESTIONUS.png";
        throw std::invalid_argument(exception_text);
    }
    exhaust->insert(std::make_pair("QUESTIONUS", buf));
    buf = nullptr;
    return exhaust;
}
void GameField::loadSoundTrack()
{
    unloadSoundTrack();
    if (!SoundTrack.openFromFile(path + "\\soundtrack")) {
        
        throw std::invalid_argument("THERE IS NO " + path + "\\soundtrack");
    }
    SoundTrack.setLoop(true);
    SoundTrack.play();
    if (path == "BARBARIKI")
        SoundTrack.setVolume(6.f); // невероятно громко, выше 20 ставить вообще нельзя
    else if (path == "SEREGA PIRAT")
        SoundTrack.setVolume(0.f);
    //На музыке меня учили что музыка  учит самым лучшим чувствам любви там, дружбе. Воспитывает в нас вкус, веселит. 
    //Серёга показывает на своем примере что музыка ещё и может заставить человека задуматься о смысле жизни,
    //окончательно убедив что лучше умереть, чем слушать пирата
    //Спасибо, Серега, я включил эту песни при друзьях и всем она настолько понравилась, что меня погладили битой и теперь я отдыхаю в больнице
    //Я слушал этот трек на улице и у бомжа лопнула барабанная перепонка и его повезли в больницу. Спасибо, Серега, теперь у бомжа есть хоть место проживания
    //Человек, который узнал о сереге пирате  был художником. Он послушал ее и вдохновился идеей. Этим художником был адольф гитлер
    //Думал что слух—это дар, потом включил трэк сереги и понял, что это не так.
    //Трек настолько взрывной что у меня взорвались перепонки
    //Серёга, после прослушивание твоего трека, врачи вернули ракавую опухоль обратно
    //Серёга спасибо за твоё творчество, включил когда мама была дома, всегда было интересно как живётся на улице!
    //Спасибо вам Сергей! Вы спасли мою жизнь. На днях меня окружила толпа гопников, и вот когда я уже был готов ощутить ботинок на своем лице,
    //я услышал эту песню. Гопники сразу же отстали меня и пошли избивать кого то другого!    else
    else  SoundTrack.setVolume(50.f);
}
void GameField::unloadSoundTrack()
{
    if (SoundTrack.Playing)
        SoundTrack.stop();
    if (WinLoseSound.Playing)
        WinLoseSound.stop();
}
bool GameField::MakeGameField(std::string path, int difficulty) {
    if (!headerTexture.loadFromFile(path + "header.png")) 
    {
        isOK = false; std::cout << "Not all texturese were loaded \n"; return false;
    }
    try
    {
        textures = LoadTextures(path);
    }
    catch (const std::exception&)
    {
        isOK = false;
        std::cout << "Not all texturese were loaded \n";
        return false;
    } 
    header.setTexture(headerTexture, true);
    header.setPosition(sf::Vector2f(0, 0));
    scaleX = WINDOW_RES.first / (float)header.getTexture()->getSize().x * 0.6f;
    scaleY = (WINDOW_RES.second * MARGIN_SCALE) / header.getTexture()->getSize().y;
    header.setScale(scaleX, scaleY);
    float minefieldScaleX, minefieldScaleY;
    if (WINDOW_RES.first > WINDOW_RES.second) {
        minefieldScaleX = 1.f;
        minefieldScaleY = WINDOW_RES.second / (float)WINDOW_RES.first;
    }
    else {
        minefieldScaleY = 1.f;
        minefieldScaleX = WINDOW_RES.first / (float)WINDOW_RES.second;
    }
    gameMap.deleteUnique();
    gameMap.create(difficulty * minefieldScaleY, difficulty * minefieldScaleX,
        textures, std::make_pair(WINDOW_RES.second * MARGIN_SCALE, 0),
        std::make_pair(WINDOW_RES.second, WINDOW_RES.first));
    if (!Font.loadFromFile("Font.TTF")) { std::cout << "FONT WASN'T LOADED\n"; }
    bombAmount.setFont(Font);
    screenSpaceAllocatedForText = WINDOW_RES.first - headerTexture.getSize().x * scaleX;
    bombAmountString = "BOMBS LEFT: " + std::to_string(gameMap.getBombAmount());
    bombAmount.setString(bombAmountString);
    this->charSizeHeight = screenSpaceAllocatedForText * (1 - 2 * marginFromHeader) * 2 / bombAmountString.size();
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
    bombAmount.setFillColor(sf::Color::White);
    loadSoundTrack();
    gameIsOn = true;
    return true;
}
void GameField::drawAllElements(sf::RenderWindow* window) {
    if (draw) {
        if (gameIsOn) {

            bombAmount.setString(bombAmountString);
            window->draw(header);
            window->draw(bombAmount);
            gameMap.drawMap(window);

        }
        else if (drawGameMenu) {
            menu.draw(window);
        }
    }

}
bool GameField::leftClickOnField(sf::RenderWindow* window)
{

    if (gameIsOn) {
        int x = sf::Mouse::getPosition(*window).x;
        int y = sf::Mouse::getPosition(*window).y;
        if (!gameMap.leftClickOnMap(x, y))
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
            gameMap.openAllMap();
            window->clear();
            drawAllElements(window);
            window->display();
            playWinLooseSound(false);
            gameIsOn = false;
            gameMap.deleteUnique();
            return false;
        }
        if (gameMap.checkWinState()) {
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
            gameMap.openAllMap();
            window->clear();
            drawAllElements(window);
            window->display();
            playWinLooseSound(true);
            gameIsOn = false;
            gameMap.deleteUnique();
            return true;
        }
        bombAmountString = "BOMBS LEFT: " + std::to_string(gameMap.getBombAmount());
        return true;
    }
    else
    {
        this->path = menu.leftClick(window);
        if (this->path.size() != 0) {
            if (!MakeGameField(this->path + "\\", getDifficulty()))
                throw std::invalid_argument("NOT ALL FILES WERE LOADED");
        }



    }
    return false;
}
unsigned GameField::getDifficulty()
{
    std::ifstream file(path + "\\dif");
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
        gameMap.rightClickOnMap(x, y);
        if (gameMap.getBombAmount() == 0) {
            if (gameMap.checkWinState()) {
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
                gameMap.openAllMap();
                window->clear();
                drawAllElements(window);
                window->display();
                playWinLooseSound(true);
                gameIsOn = false;
                gameMap.deleteUnique();
                return;
            }
        }
        bombAmountString = "BOMBS LEFT: " + std::to_string(gameMap.getBombAmount());
    }
}
void GameField::drawMenu(sf::RenderWindow* window) {
    menu.draw(window);
}
void GameField::wait(unsigned msec) {
    sf::sleep(sf::milliseconds(msec)); // гений)
}
GameField::~GameField() {
    if (textures != nullptr) {
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
    //остальное удалится само, 
}
