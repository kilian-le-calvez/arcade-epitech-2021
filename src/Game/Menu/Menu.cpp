/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-anne.mboke
** File description:
** Menu
*/

#include "Menu.hpp"

Lib::Menu menu;

Lib::Menu::Menu()
{
}

Lib::Menu::~Menu()
{
}

void Lib::Menu::addObjectList(std::vector<std::string> map, Enum::Type enumType)
{
    std::string filePath;
    std::string type;

    for (std::size_t y = 0; y < map.size(); y++) {
        for (std::size_t x = 0; x < map[y].size(); x++) {
            filePath = this->_objConfig[map[y].substr(x, 1)].first;
            type = this->_objConfig[map[y].substr(x, 1)].second;
            if (type.compare("menu") == 0)
                this->_objects.emplace_back(std::make_unique<Object::Concrete::Consumable>(x, y, true, filePath, enumType));
            else if (type.compare("player") == 0)
                this->_objects.emplace_back(std::make_unique<Object::Concrete::Dynamic>(x, y, true, filePath, Enum::Type::PLAYER));
            else if (type.compare("wall") == 0)
                this->_objects.emplace_back(std::make_unique<Object::Concrete::Static>(x, y, false, filePath, Enum::Type::DECOR));
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
    if (menu._objects.size() > 0)
        menu._objects.clear();
    std::string name = "assets/fileConfig/menu.paths";
    std::vector<std::string> paths = parseFileWithRegex(name, "[\\n]+");
    std::vector<std::string> pacmanMap = parseFileWithRegex(paths[0], "[\\n]+");
    std::vector<std::string> snakeMap = parseFileWithRegex(paths[1], "[\\n]+");
    std::vector<std::string> sfmlMap = parseFileWithRegex(paths[2], "[\\n]+");
    std::vector<std::string> sdlMap = parseFileWithRegex(paths[3], "[\\n]+");
    std::vector<std::string> ncurseMap = parseFileWithRegex(paths[4], "[\\n]+");
    std::vector<std::string> exitMap = parseFileWithRegex(paths[5], "[\\n]+");
    std::vector<std::string> boraboraMap = parseFileWithRegex(paths[6], "[\\n]+");
    
    menu._objConfig = loadObjectConfig(paths[7]);
    menu.addObjectList(pacmanMap, Enum::Type::BUTTON_PACMAN);
    menu.addObjectList(snakeMap, Enum::Type::BUTTON_SNAKE);
    menu.addObjectList(sfmlMap, Enum::Type::BUTTON_SFML);
    menu.addObjectList(sdlMap, Enum::Type::BUTTON_SDL);
    menu.addObjectList(ncurseMap, Enum::Type::BUTTON_NCURSES);
    menu.addObjectList(exitMap, Enum::Type::BUTTON_EXIT);
    menu.addObjectList(boraboraMap, Enum::Type::BUTTON_BORABORA);
}

extern "C" std::vector<std::unique_ptr<Object::Model::IObject>> &getObjects(void)
{
    return menu._objects;
}

void eat(std::vector<std::unique_ptr<Object::Model::IObject>> &objects, std::pair<std::size_t, std::size_t> pos)
{
    for (std::size_t i = 0; i < objects.size(); i++) {
        if (objects[i].get()->getPosition() == pos) {
            if (objects[i].get()->getType() == Enum::Type::BUTTON_PACMAN)
                objects[i].get()->setVisibility(false);
            else if (objects[i].get()->getType() == Enum::Type::BUTTON_SNAKE)
                objects[i].get()->setVisibility(false);
            else if (objects[i].get()->getType() == Enum::Type::BUTTON_SFML)
                objects[i].get()->setVisibility(false);
            else if (objects[i].get()->getType() == Enum::Type::BUTTON_SDL)
                objects[i].get()->setVisibility(false);
            else if (objects[i].get()->getType() == Enum::Type::BUTTON_NCURSES)
                objects[i].get()->setVisibility(false);
            else if (objects[i].get()->getType() == Enum::Type::BUTTON_EXIT)
                objects[i].get()->setVisibility(false);   
            else if (objects[i].get()->getType() == Enum::Type::BUTTON_BORABORA)
                objects[i].get()->setVisibility(false);   
        }            
    }
}

Enum::Win whatToDo(std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    int pacCount = 0;
    int snakeCount = 0;
    int exitCount = 0;
    int sfmlCount = 0;
    int sdlCount = 0;
    int ncursesCount = 0;
    int boraboraCount = 0;

    for (std::size_t i = 0; i < objects.size(); i++) {
        if (objects[i].get()->getVisibility() == true) {
            if (objects[i].get()->getType() == Enum::Type::BUTTON_PACMAN)
                pacCount += 1;
            else if (objects[i].get()->getType() == Enum::Type::BUTTON_SNAKE)
                snakeCount += 1;
            else if (objects[i].get()->getType() == Enum::Type::BUTTON_EXIT)
                exitCount += 1;
            else if (objects[i].get()->getType() == Enum::Type::BUTTON_SFML)
                sfmlCount += 1;
            else if (objects[i].get()->getType() == Enum::Type::BUTTON_SDL)
                sdlCount += 1;
            else if (objects[i].get()->getType() == Enum::Type::BUTTON_NCURSES)
                ncursesCount += 1;
            else if (objects[i].get()->getType() == Enum::Type::BUTTON_BORABORA)
                boraboraCount += 1;
        }
    }
    if (pacCount == 0)
        return Enum::Win::B_PACMAN;
    if (snakeCount == 0)
        return Enum::Win::B_SNAKE;
    if (exitCount == 0)
        return Enum::Win::B_EXIT;
    if (sfmlCount == 0)
        return Enum::Win::B_SFML;
    if (sdlCount == 0)
        return Enum::Win::B_SDL;
    if (ncursesCount == 0)
        return Enum::Win::B_NCURSES;
    if (boraboraCount == 0)
        return Enum::Win::B_BORABORA;
    return Enum::Win::CONTINUE;
}

extern "C" Enum::Win playGame(Enum::Event event)
{
    static std::chrono::_V2::system_clock::time_point clock_pacman = std::chrono::system_clock::now();
    Enum::Win toDo = Enum::Win::CONTINUE;
    
    if (std::chrono::system_clock::now() >= clock_pacman + std::chrono::milliseconds(140)) {
        for (std::size_t i = 0; i < menu._objects.size(); i++) {
            if (menu._objects[i].get()->getType() == Enum::Type::PLAYER) {    
                toDo = whatToDo(menu._objects);
                menu._objects[i].get()->doEvent(event, menu._objects);
                eat(menu._objects, menu._objects[i].get()->getPosition());
            }
        }
        clock_pacman = std::chrono::system_clock::now();
    }
    return toDo;
}