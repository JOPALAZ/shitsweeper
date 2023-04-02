#include "GameField.h" 
#include <fstream>
std::map< std::string, sf::Texture*>* GameField::LoadTextures(std::string path)
{
    if(textures)
    textures->clear();
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
        SoundTrack.setVolume(6.f); // невероятно громко, выше 20 ставить вообще нельзя
    else if (path == "SEREGA PIRAT")
        SoundTrack.setVolume(0.f); 
    //На музыке меня учили что музыка  учит самым лучшим чувствам любви там, дружбе. Воспитывает в нас вкус, веселит. 
    //Серёга показывает на своем примере что музыка ещё и может заставить человека задуматься о смысле жизни,
    //окончательно убедив что лучше умереть, чем слушать пирата
    //Спасибо, Серега, я включил эту песни при друзьях и всем она настолько понравилась, что меня погладили битой и теперь я отдыхаю в больнице
    //Я слушал этот трек на улице и у бомжа лопнула барабанная перепонка и его повезли в больницу. Спасибо, Серега, теперь у бомжа есть хоть место проживания
    //Человек, который узнал о твоей песней  был художником. Он послушал ее и вдохновился идеей. Этим художником был адольф гитлер
    //Думал что слух—это дар, потом включил твой трэк и понял, что это не так.
    //Трек настолько взрывной что у меня взорвались перепонки
    //Серёга, после прослушивание твоего трека, врачи вернули ракавую опухоль обратно
    //Серёга спасибо за твоё творчество, включил когда мама была дома, всегда было интересно как живётся на улице!
    //Спасибо вам Сергей! Вы спасли мою жизнь. На днях меня окружила толпа гопников, и вот когда я уже был готов ощутить ботинок на своем лице,
    //я услышал эту песню. Гопники сразу же отстали меня и пошли избивать кого то другого!
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
    //Магическая константа 1.773 это отношение высоты к ширине одного символа.
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
            //while (bombAmount.getLocalBounds().width <= WINDOW_RES.second * 0.32f && bombAmount.getLocalBounds().height <= WINDOW_RES.first * MARGIN_SCALE * 0.8f)
            //{
            //    charSizeHeight++;
            //    bombAmount.setCharacterSize(charSizeHeight);
            //}
            //while (bombAmount.getLocalBounds().width > WINDOW_RES.second * 0.32f || bombAmount.getLocalBounds().height > WINDOW_RES.first * MARGIN_SCALE * 0.8f)
            //{
            //    charSizeHeight--;
            //    bombAmount.setCharacterSize(charSizeHeight);
            //}
            //
            //bombAmount.setOrigin(bombAmount.getGlobalBounds().left + bombAmount.getGlobalBounds().width / 2.0f,
            //    bombAmount.getGlobalBounds().top + bombAmount.getGlobalBounds().height / 2.0f);
            //bombAmount.setPosition(WINDOW_RES.first * 0.8f, WINDOW_RES.second * MARGIN_SCALE / 2.f);
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
    sf::sleep(sf::milliseconds(msec)); // гений)
}
GameField::~GameField() {
    if(textures)
    textures->clear();
    //остальное удалится само
}