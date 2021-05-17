/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** Sfml
*/

#include "Sfml.hpp"

Lib::Sfml *lib;

void Lib::Sfml::setScoreText(int scor)
{
    sf::Vector2f pos;

    this->_font.loadFromFile("assets/ressources/COMICATE.TTF");
    pos.x = 54 * SPRITE_SIZE;
    pos.y = 5 * SPRITE_SIZE;
    this->_score.setFont(this->_font);
    this->_score.setString(std::to_string(scor));
    this->_score.setCharacterSize(30);
    this->_score.setFillColor(sf::Color::White);
    this->_score.setStyle(sf::Text::Bold | sf::Text::Underlined);
    this->_score.setPosition(pos);
}

void Lib::Sfml::initBorabora(void)
{
    this->_boraTexture.loadFromFile("assets/ressources/borabora.jpg");
    this->_boraSprite.setTexture(this->_boraTexture);
}

Lib::Sfml::Sfml()
{
    this->_window.create(sf::VideoMode(1920, 1080), "ARCADE");
    this->setScoreText(0);
    this->initBorabora();
}

Lib::Sfml::~Sfml()
{
}

sf::Vector2f Lib::Sfml::getObjectPos(std::pair<std::size_t, std::size_t> pos)
{
    sf::Vector2f pixelPos;

    pixelPos.x = pos.first * SPRITE_SIZE;
    pixelPos.y = pos.second * SPRITE_SIZE;
    return pixelPos;
}

std::string Lib::Sfml::readFile(std::string filePath)
{
    std::stringstream file;
    std::ifstream is(filePath);

    if (is.is_open()) {
        file << is.rdbuf();
        return file.str();
    }
    return "default"; ////
}

std::string Lib::Sfml::findRessourcePath(std::string filePath)
{
    std::string buffer = readFile(filePath);
    std::string libPathBegin = "-SFML:(";
    std::string libPathEnd = "):SFML-";

    std::size_t sfmlBegin = buffer.find(libPathBegin) + libPathBegin.size();
    std::size_t sfmlEnd = buffer.find(libPathEnd);
    return buffer.substr(sfmlBegin, sfmlEnd - sfmlBegin);
}

sf::Texture Lib::Sfml::createTextureFromFile(std::string filePath)
{
    sf::Texture texture;
    
    texture.loadFromFile(filePath.c_str());
    return texture;
}

sf::Sprite Lib::Sfml::createSpriteFromTexture(sf::Texture &texture)
{
    sf::Sprite sprite;

    sprite.setTexture(texture);
    return sprite;
}

void Lib::Sfml::addSpriteToList(std::string filePath)
{
    std::pair<sf::Texture, sf::Sprite> newSprite;
    std::string ressourcePath = findRessourcePath(filePath);

    this->_sprites.emplace(std::make_pair(filePath, newSprite));
    this->_sprites[filePath].first = createTextureFromFile(ressourcePath);
    this->_sprites[filePath].second = createSpriteFromTexture(this->_sprites[filePath].first);
}

sf::IntRect getSubSprite(std::pair<std::size_t, std::size_t> pos)
{
    sf::IntRect rect;

    rect.left = pos.first * SPRITE_SIZE;
    rect.top = pos.second * SPRITE_SIZE;
    rect.height = SPRITE_SIZE;
    rect.width = SPRITE_SIZE;
    return rect;
}

void Lib::Sfml::printObject(std::unique_ptr<Object::Model::IObject> &object)
{
    sf::Vector2f pixelPos = getObjectPos(object.get()->getPosition());
    std::string filePath = object.get()->getFilePath();
    sf::IntRect rect;

    if (this->_sprites.find(filePath) == this->_sprites.end())
        addSpriteToList(filePath);
    if (object.get()->getType() == Enum::Type::PLAYER) {
        rect = getSubSprite(object.get()->getSpritePos());
        this->_sprites[filePath].second.setTextureRect(rect);
        this->_score.setString(std::to_string(object.get()->getScore()));
    }
    if (object.get()->getType() == Enum::Type::ENNEMY)
        _window.draw(_score);
    this->_sprites[filePath].second.setPosition(pixelPos);
    this->_window.draw(this->_sprites[filePath].second);
}

extern "C" void printGame(std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    lib->_window.clear();
    for (std::size_t i = 0; i < objects.size(); i++)
        if (objects[i].get()->getVisibility() == true) {
            lib->printObject(objects[i]);
        }
    lib->_window.display();    
}

extern "C" Enum::Event getEvent(void)
{
    sf::Event event;
    while (lib->_window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Escape)
                return Enum::GOMENU;
            if (event.key.code == sf::Keyboard::BackSpace)
                return Enum::Event::QUIT;
            if (event.key.code == sf::Keyboard::Space)
                return Enum::PAUSE;
            if (event.key.code == sf::Keyboard::Up)
                return Enum::UP;
            if (event.key.code == sf::Keyboard::Down)
                return Enum::DOWN;
            if (event.key.code == sf::Keyboard::Right)
                return Enum::RIGHT;
            if (event.key.code == sf::Keyboard::Left)
                return Enum::LEFT;
            if (event.key.code == sf::Keyboard::A)
                return Enum::SFML;
            if (event.key.code == sf::Keyboard::Z)
                return Enum::SDL;
            if (event.key.code == sf::Keyboard::E)
                return Enum::NCURSES;
            if (event.key.code == sf::Keyboard::Q)
                return Enum::GOPACMAN;
            if (event.key.code == sf::Keyboard::S)
                return Enum::GOSNAKE;
        }
        if (event.type == sf::Event::Closed)
            lib->_window.close();
    }
    return Enum::Event::NOEVENT;
}

extern "C" void borabora(std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    lib->_window.clear();
    lib->_window.draw(lib->_boraSprite);
    for (std::size_t i = 0; i < objects.size(); i++)
        if (objects[i].get()->getVisibility() == true) {
            lib->printObject(objects[i]);
        }
    lib->_window.display();    
}

extern "C" void init(void)
{
    lib = new Lib::Sfml();
}

extern "C" void destroy(void)
{
    lib->_window.close();
}