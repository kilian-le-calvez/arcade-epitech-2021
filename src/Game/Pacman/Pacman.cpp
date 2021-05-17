/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** Pacman
*/

#include "Pacman.hpp"

Lib::Pacman pac;

Lib::Pacman::Pacman()
{
}

Lib::Pacman::~Pacman()
{
}

Enum::Win checkConsumables(std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    for (std::size_t i = 0; i < objects.size(); i++) {
        if (objects[i].get()->getType() == Enum::Type::CONSO && objects[i].get()->getVisibility() == true)
            return Enum::Win::CONTINUE;
        else if (objects[i].get()->getType() == Enum::Type::GUM && objects[i].get()->getVisibility() == true)
            return Enum::Win::CONTINUE;
    }
    return Enum::Win::WIN;
}

Enum::Event doEventGhost(std::vector<Enum::Event> &events,
std::vector<std::unique_ptr<Object::Model::IObject>> &objects, std::unique_ptr<Object::Model::IObject> &ghost)
{
    for (std::size_t i = 0; i < events.size(); i++)
        if (ghost.get()->doEvent(events[i], objects))
            return events[i];
    return Enum::Event::NOEVENT;
}

std::size_t indexEvent(std::vector<Enum::Event> &events, Enum::Event defaultEvent)
{
    std::size_t i;

    for (i = 0; i < events.size(); i++)
        if (events[i] == defaultEvent)
            return i;
    return 0;
}

void ghostMove(std::vector<std::unique_ptr<Object::Model::IObject>> &objects, std::unique_ptr<Object::Model::IObject> &ghost,
Enum::Event event1, Enum::Event event2, Enum::Event event3, Enum::Event event4, int gumGum)
{
    if (gumGum == 0) {
        if (ghost.get()->doEvent(event1, objects)) {}
        else if (ghost.get()->doEvent(event2, objects)) {}
        else if (ghost.get()->doEvent(event3, objects)) {}
        else if (ghost.get()->doEvent(event4, objects)) {}
    } else {
        if (ghost.get()->doEvent(event4, objects)) {}
        else if (ghost.get()->doEvent(event3, objects)) {}
        else if (ghost.get()->doEvent(event2, objects)) {}
        else if (ghost.get()->doEvent(event1, objects)) {}    
    }
}

void findGhostMove(std::pair<std::size_t, std::size_t> pacPos, std::pair<std::size_t, std::size_t> ghostPos,
std::vector<std::unique_ptr<Object::Model::IObject>> &objects, std::unique_ptr<Object::Model::IObject> &ghost, int gumGum)
{
    if (ghostPos.first < pacPos.first) {
        if (ghostPos.second == pacPos.second) {
            ghostMove(objects, ghost, Enum::RIGHT, Enum::UP, Enum::DOWN, Enum::LEFT, gumGum);
        } else if (ghostPos.second > pacPos.second) {
            ghostMove(objects, ghost, Enum::UP, Enum::RIGHT, Enum::LEFT, Enum::DOWN, gumGum);
        } else if (ghostPos.second < pacPos.second) {
            ghostMove(objects, ghost, Enum::RIGHT, Enum::DOWN, Enum::LEFT, Enum::UP, gumGum);
        }
    } else if (ghostPos.first > pacPos.first) {
        if (ghostPos.second == pacPos.second) {
            ghostMove(objects, ghost, Enum::LEFT, Enum::DOWN, Enum::UP, Enum::RIGHT, gumGum);
        } else if (ghostPos.second < pacPos.second) {
            ghostMove(objects, ghost, Enum::DOWN, Enum::LEFT, Enum::RIGHT, Enum::UP, gumGum);
        } else if (ghostPos.second > pacPos.second) {
            ghostMove(objects, ghost, Enum::LEFT, Enum::UP, Enum::RIGHT, Enum::DOWN, gumGum);
        }
    } else if (ghostPos.first == pacPos.first) {
        if (ghostPos.second < pacPos.second) {
            ghostMove(objects, ghost, Enum::DOWN, Enum::RIGHT, Enum::LEFT, Enum::UP, gumGum);
        } else if (ghostPos.second > pacPos.second) {
            ghostMove(objects, ghost, Enum::UP, Enum::LEFT, Enum::RIGHT, Enum::DOWN, gumGum);
        }
    }
}

void moveGhosts(std::pair<std::size_t, std::size_t> pacPos, std::vector<std::unique_ptr<Object::Model::IObject>> &objects, bool gumGum)
{
    for (std::size_t i = 0; i < objects.size(); i++)
        if (objects[i].get()->getType() == Enum::Type::ENNEMY)
            findGhostMove(pacPos, objects[i].get()->getPosition(), objects, objects[i], gumGum);
}

Enum::Win checkGhostKill(std::pair<std::size_t, std::size_t> pos, std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    for (std::size_t i = 0; i < objects.size(); i++)
        if (objects[i].get()->getType() == Enum::Type::ENNEMY && objects[i].get()->getPosition() == pos && objects[i].get()->getIsTraversable() == false)
            return Enum::Win::LOOSE;
    return Enum::Win::CONTINUE;
}

bool checkGumGum(std::pair<std::size_t, std::size_t> pos, std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    for (std::size_t i = 0; i < objects.size(); i++)
        if (pos == objects[i].get()->getPosition() && objects[i].get()->getType() == Enum::Type::GUM)
            return true;
    return false;
}

void setGhostIsTraversable(std::vector<std::unique_ptr<Object::Model::IObject>> &objects, bool traverse)
{
    for (std::size_t i = 0; i < objects.size(); i++)
        if (objects[i].get()->getType() == Enum::Type::ENNEMY)
            objects[i].get()->setIsTraversable(traverse);
}

void setMenuVisibility(std::vector<std::unique_ptr<Object::Model::IObject>> &objects, bool visible)
{
    for (std::size_t i = 0; i < objects.size(); i++)
        if (objects[i].get()->getType() == Enum::Type::MENU)
            objects[i].get()->setIsVisible(visible);
}

Enum::Eat eat(std::vector<std::unique_ptr<Object::Model::IObject>> &objects, std::pair<std::size_t, std::size_t> pos)
{
    Enum::Eat whatEated = Enum::Eat::NOEAT;

    for (std::size_t i = 0; i < objects.size(); i++) {
        if (objects[i].get()->getPosition() == pos && objects[i].get()->getVisibility() == true) {
            if (objects[i].get()->getType() == Enum::Type::CONSO) {
                objects[i].get()->setVisibility(false);
                whatEated = Enum::Eat::LITTLE;
            }
            if (objects[i].get()->getType() == Enum::Type::GUM) {
                objects[i].get()->setVisibility(false);
                whatEated = Enum::Eat::MEDIUM;
            }
            if (objects[i].get()->getType() == Enum::Type::ENNEMY && objects[i].get()->getIsTraversable() == true) {
                objects[i].get()->setPosition(std::pair<std::size_t, std::size_t>(30, 15));
                whatEated = Enum::Eat::BIG;
            }
        }
    }
    return whatEated;
}

void Lib::Pacman::addObjectList(std::vector<std::string> map)
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
            if (type.compare("gate") == 0)
                this->_objects.emplace_back(std::make_unique<Object::Concrete::Static>(x, y, false, filePath, Enum::Type::GATE));
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
    if (pac._objects.size() > 0)
        pac._objects.clear();
    std::string name = "assets/fileConfig/pacman.paths";
    std::vector<std::string> paths = parseFileWithRegex(name, "[\\n]+");
    std::vector<std::string> staticMap = parseFileWithRegex(paths[0], "[\\n]+");
    std::vector<std::string> dynamicMap = parseFileWithRegex(paths[1], "[\\n]+");
    std::vector<std::string> consumableMap = parseFileWithRegex(paths[2], "[\\n]+");
    std::vector<std::string> menuMap = parseFileWithRegex(paths[3], "[\\n]+");

    pac._objConfig = loadObjectConfig(paths[4]);
    pac.addObjectList(staticMap);
    pac.addObjectList(consumableMap);
    pac.addObjectList(dynamicMap);
    pac.addObjectList(menuMap);
}

extern "C" std::vector<std::unique_ptr<Object::Model::IObject>> &getObjects(void)
{
    return pac._objects;
}

extern "C" Enum::Win playGame(Enum::Event event)
{
    static bool gumGum = false;
    static std::chrono::_V2::system_clock::time_point t;
    static std::chrono::_V2::system_clock::time_point clock_pacman = std::chrono::system_clock::now();
    static std::chrono::_V2::system_clock::time_point clock_ghost = std::chrono::system_clock::now();
    static Enum::Event staticEvent = Enum::Event::NOEVENT;
    static Enum::Event pause = Enum::Event::NOEVENT;

    if (event != Enum::Event::NOEVENT && event != Enum::Event::PAUSE)
        staticEvent = event;
    if (event == Enum::Event::PAUSE) {
        if (pause == Enum::Event::NOEVENT) {
            pause = Enum::Event::PAUSE;
            setMenuVisibility(pac._objects, true);
        } else {
            pause = Enum::Event::NOEVENT;
            setMenuVisibility(pac._objects, false);
        }
        return Enum::Win::CONTINUE;
    }
    if (pause == Enum::Event::PAUSE)
        return Enum::Win::CONTINUE;
    for (std::size_t i = 0; i < pac._objects.size(); i++)
        if (pac._objects[i].get()->getType() == Enum::Type::PLAYER) {    
            if (std::chrono::system_clock::now() >= clock_pacman + std::chrono::milliseconds(140)) {
                if (checkGhostKill(pac._objects[i].get()->getPosition(), pac._objects) == Enum::Win::LOOSE)
                    return Enum::Win::LOOSE;
                if (checkGumGum(pac._objects[i].get()->getPosition(), pac._objects)) {
                    gumGum = true;
                    t = std::chrono::system_clock::now();
                    setGhostIsTraversable(pac._objects, true);
                }
                pac._objects[i].get()->doEvent(staticEvent, pac._objects);
                Enum::Eat scoreEat = eat(pac._objects, pac._objects[i].get()->getPosition());
                pac._objects[i].get()->setScore(scoreEat);
                if (checkConsumables(pac._objects) == Enum::Win::WIN)
                    return Enum::Win::WIN;
                clock_pacman = std::chrono::system_clock::now();
            }
            if (std::chrono::system_clock::now() >= clock_ghost + std::chrono::milliseconds(300)) {
                if (std::chrono::system_clock::now() < t + std::chrono::seconds(10)) {
                    moveGhosts(pac._objects[i].get()->getPosition(), pac._objects, 1);
                } else {
                    if (gumGum == true) {
                        gumGum = false;
                        setGhostIsTraversable(pac._objects, false);
                    }
                    moveGhosts(pac._objects[i].get()->getPosition(), pac._objects, 0);    
                }
                clock_ghost = std::chrono::system_clock::now();
            }
        }
    return Enum::Win::CONTINUE;
}