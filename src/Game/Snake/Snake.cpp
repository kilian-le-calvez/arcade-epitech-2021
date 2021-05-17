/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-anne.mboke
** File description:
** Snake
*/

#include "Snake.hpp"

Lib::Snake snake;

Lib::Snake::Snake()
{
}

Lib::Snake::~Snake()
{
}

void addConso(std::vector<std::unique_ptr<Object::Model::IObject>> &objects, std::map<std::string, std::pair<std::string, std::string>> &config)
{
    std::srand(std::time(0));
    std::size_t x = std::rand() % 35 + 17;
    std::size_t y = std::rand() % 28 + 2;

    std::string filePath = config["."].first;
    std::string type = config["."].second;
    objects.emplace_back(std::make_unique<Object::Concrete::Consumable>(x, y, true, filePath, Enum::Type::CONSO));
}

void addTail(std::vector<std::unique_ptr<Object::Model::IObject>> &objects, std::map<std::string, std::pair<std::string, std::string>> &config, std::pair<std::size_t, std::size_t> pos)
{
    std::srand(std::time(0));
    std::size_t x = pos.first;
    std::size_t y = pos.second;

    std::string filePath = config["E"].first;
    std::string type = config["E"].second;
    objects.emplace_back(std::make_unique<Object::Concrete::Dynamic>(x, y, true, filePath, Enum::Type::ENNEMY));
}

void setMenuVisible(std::vector<std::unique_ptr<Object::Model::IObject>> &objects, bool visible)
{
    for (std::size_t i = 0; i < objects.size(); i++)
        if (objects[i].get()->getType() == Enum::Type::MENU)
            objects[i].get()->setVisibility(visible);
}

Enum::Eat eatt(std::vector<std::unique_ptr<Object::Model::IObject>> &objects, std::pair<std::size_t, std::size_t> pos)
{
    for (std::size_t i = 0; i < objects.size(); i++) {
        if (objects[i].get()->getPosition() == pos && objects[i].get()->getType() == Enum::Type::CONSO) {
            objects[i].get()->setVisibility(false);
            return Enum::Eat::LITTLE;
        }
        if (objects[i].get()->getPosition() == pos && objects[i].get()->getType() == Enum::Type::GUM) {
            objects[i].get()->setVisibility(false);
            return Enum::Eat::MEDIUM;
        }
    }
    return Enum::Eat::NOEAT;
}

bool checkDieTail(std::vector<std::unique_ptr<Object::Model::IObject>> &objects, std::pair<std::size_t, std::size_t> pos)
{
    for (std::size_t i = 0; i < objects.size(); i++)
        if (objects[i].get()->getPosition() == pos && objects[i].get()->getType() == Enum::Type::ENNEMY)
            return true;
    return false;
}

void Lib::Snake::addObjectList(std::vector<std::string> map)
{
    std::string filePath;
    std::string type;

    for (std::size_t y = 0; y < map.size(); y++) {
        for (std::size_t x = 0; x < map[y].size(); x++) {
            filePath = this->_objConfig[map[y].substr(x, 1)].first;
            type = this->_objConfig[map[y].substr(x, 1)].second;
            if (type.compare("player") == 0)
                this->_objects.emplace_back(std::make_unique<Object::Concrete::Dynamic>(x, y, false, filePath, Enum::Type::PLAYER));
            if (type.compare("enemy") == 0)
                this->_objects.emplace_back(std::make_unique<Object::Concrete::Dynamic>(x, y, false, filePath, Enum::Type::ENNEMY));
            if (type.compare("wall") == 0)
                this->_objects.emplace_back(std::make_unique<Object::Concrete::Static>(x, y, false, filePath, Enum::Type::DECOR));
            if (type.compare("conso") == 0)
                this->_objects.emplace_back(std::make_unique<Object::Concrete::Consumable>(x, y, true, filePath, Enum::Type::CONSO));
            if (type.compare("gum") == 0)
                this->_objects.emplace_back(std::make_unique<Object::Concrete::Consumable>(x, y, true, filePath, Enum::Type::GUM));
            if (type.compare("menu") == 0) {
                this->_objects.emplace_back(std::make_unique<Object::Concrete::Static>(x, y, false, filePath, Enum::Type::MENU));
                this->_objects[this->_objects.size() - 1].get()->setVisibility(false);
            }
        }
    }
}

std::vector<std::string> parseFileWithRegex(std::string filePath, std::string regex)
{
    std::stringstream file;
    std::string content;
    std::ifstream is(filePath);
    std::regex reg(regex);

    try {
        file << is.rdbuf();
        content = file.str();
    } catch (...) {
        std::cerr << "Can't load the Map..." << std::endl;
    }
    std::vector<std::string> res {
        std::sregex_token_iterator(content.begin(), content.end(), reg, -1), {}
    };
    return res;
}

std::map<std::string, std::pair<std::string, std::string>> loadObjectConfig(std::string filePathConfig)
{
    std::vector<std::string> fileParsed = parseFileWithRegex(filePathConfig, "[:|\\n]+");
    std::map<std::string, std::pair<std::string, std::string>> objectConfig;
    std::pair<std::string, std::string> config;

    for (std::size_t i = 0; i < fileParsed.size(); i += 3) {
        config.first = fileParsed[i + 1];
        config.second = fileParsed[i + 2];
        objectConfig[fileParsed[i]] = config;
    }
    return objectConfig;
}

extern "C" void initObjects(void)
{
    if (snake._objects.size() > 0)
        snake._objects.clear();
    std::string name = "assets/fileConfig/snake.paths";
    std::vector<std::string> paths = parseFileWithRegex(name, "[\\n]+");
    std::vector<std::string> staticMap = parseFileWithRegex(paths[0], "[\\n]+");
    std::vector<std::string> dynamicMap = parseFileWithRegex(paths[1], "[\\n]+");
    std::vector<std::string> consumableMap = parseFileWithRegex(paths[2], "[\\n]+");
    std::vector<std::string> menuMap = parseFileWithRegex(paths[3], "[\\n]+");

    snake._objConfig = loadObjectConfig(paths[4]);
    snake.addObjectList(staticMap);
    snake.addObjectList(consumableMap);
    snake.addObjectList(dynamicMap);
    snake.addObjectList(menuMap);
}

extern "C" std::vector<std::unique_ptr<Object::Model::IObject>> &getObjects(void)
{
    return snake._objects;
}

extern "C" Enum::Win playGame(Enum::Event event)
{
    static Enum::Event staticEvent = Enum::Event::NOEVENT;
    static Enum::Event pause = Enum::Event::NOEVENT;
    static std::chrono::_V2::system_clock::time_point clock_snake = std::chrono::system_clock::now();
    static std::chrono::_V2::system_clock::time_point clock_itemSpawn = std::chrono::system_clock::now();
    Enum::Eat eated;
    std::pair<std::size_t, std::size_t> oldSize;
    std::pair<std::size_t, std::size_t> newSize;

    if (event != Enum::Event::NOEVENT && event != Enum::Event::PAUSE)
        staticEvent = event;
    if (event == Enum::Event::PAUSE) {
        if (pause == Enum::Event::NOEVENT) {
            pause = Enum::Event::PAUSE;
            setMenuVisible(snake._objects, true);
        } else {
            pause = Enum::Event::NOEVENT;
            setMenuVisible(snake._objects, false);
        }
        return Enum::Win::CONTINUE;
    }
    if (pause == Enum::Event::PAUSE)
        return Enum::Win::CONTINUE;
    if (std::chrono::system_clock::now() >= clock_snake + std::chrono::milliseconds(140)) {
        for (std::size_t i = 0; i < snake._objects.size(); i++) {
            if (snake._objects[i].get()->getType() == Enum::Type::PLAYER) {   
                    oldSize = snake._objects[i].get()->getPosition();
                    if (!snake._objects[i].get()->doEvent(staticEvent, snake._objects))
                        return Enum::Win::LOOSE;
                    eated = eatt(snake._objects, snake._objects[i].get()->getPosition());
                    snake._objects[i].get()->setScore(eated);
                    if (checkDieTail(snake._objects, snake._objects[i].get()->getPosition()))
                        return Enum::Win::LOOSE;
                    if (eated != Enum::Eat::NOEAT)
                        addTail(snake._objects, snake._objConfig, snake._objects[i].get()->getPosition());
                    clock_snake = std::chrono::system_clock::now();
            }
        }
        for (std::size_t i = 0; i < snake._objects.size(); i++) {
            if (snake._objects[i].get()->getType() == Enum::Type::ENNEMY) {
                newSize = oldSize;
                oldSize = snake._objects[i].get()->getPosition();
                snake._objects[i].get()->setPosition(newSize);
            }
        }
    }
    if (std::chrono::system_clock::now() >= clock_itemSpawn + std::chrono::milliseconds(1000)) {
            addConso(snake._objects, snake._objConfig);
            clock_itemSpawn = std::chrono::system_clock::now();
    }
    
    return Enum::Win::CONTINUE;
}