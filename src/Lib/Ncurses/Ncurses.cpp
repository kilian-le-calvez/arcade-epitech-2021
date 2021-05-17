/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

Lib::Ncurses *ncurses_object;

Lib::Ncurses::Ncurses()
{
    _window = newwin(LINES, COLS, 0, 0);
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
}

Lib::Ncurses::~Ncurses()
{
}

std::pair<std::size_t, std::size_t> Lib::Ncurses::getObjectPos(std::pair<std::size_t, std::size_t> pos)
{
    std::pair<std::size_t, std::size_t> newpos;

    newpos.first = 43 + pos.first * SPRITE_SIZE;
    newpos.second = pos.second * SPRITE_SIZE;
    return newpos;
}

std::string Lib::Ncurses::readFile(std::string filePath)
{
    std::stringstream file;
    std::ifstream is(filePath);

    if (is.is_open()) {
        file << is.rdbuf();
        return file.str();
    }
    return "default";
}

std::string Lib::Ncurses::findRessourcePath(std::string filePath)
{
    std::string buffer = readFile(filePath);
    std::string libPathBegin = "-NCURSES:(";
    std::string libPathEnd = "):NCURSES-";

    std::size_t sfmlBegin = buffer.find(libPathBegin) + libPathBegin.size();
    std::size_t sfmlEnd = buffer.find(libPathEnd);
    return buffer.substr(sfmlBegin, sfmlEnd - sfmlBegin);
}

std::string Lib::Ncurses::createSprite(std::string filePath)
{
    std::string sprite = findRessourcePath(filePath).c_str();
    return sprite; 
}

void Lib::Ncurses::addSpriteToList(std::string filePath)
{
    std::string newSprite = createSprite(filePath);

    this->_sprites.insert(_sprites.end(), {filePath, newSprite});
}

void init_color() 
{
    start_color();

    init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(2, COLOR_RED, COLOR_RED);
    init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(4, COLOR_CYAN, COLOR_CYAN);
    init_pair(5,COLOR_BLUE, COLOR_BLACK);
}

void printScore(int score)
{
    // attron(A_BOLD | A_UNDERLINE);
    // mvprintw(8, 148, "%s ", "S  C  O  R  E:");
    // attroff(A_BOLD | A_UNDERLINE);
    attron(A_BOLD | COLOR_PAIR(5));
    mvprintw(11, 154, "%d", score);
    attroff(A_BOLD | COLOR_PAIR(5));
}

void Lib::Ncurses::printObject(std::unique_ptr<Object::Model::IObject> &object, int score)
{
    std::pair<std::size_t, std::size_t> pixelPos = getObjectPos(object.get()->getPosition());
    std::string filePath = object.get()->getFilePath();
    std::string val;

    if (this->_sprites.find(filePath) == this->_sprites.end())
        addSpriteToList(filePath);
    for (auto X : _sprites) {
        if (X.first == filePath) {
            val = X.second; 
            break;
        }
    }
    init_color();
    if (object.get()->getType() == Enum::Type::DECOR) {
        attron(A_BOLD);
        mvprintw(pixelPos.second, pixelPos.first, "%c ", val.c_str()[0]);
        attroff(A_BOLD);
    } else if (object.get()->getType() == Enum::Type::PLAYER) {
        attron(A_BOLD | COLOR_PAIR(1));
        mvprintw(pixelPos.second, pixelPos.first, "%c ", val.c_str()[0]);
        _score = object.get()->getScore();
        attroff(A_BOLD | COLOR_PAIR(1)); 
    } else if (object.get()->getType() == Enum::Type::ENNEMY) {
        attron(A_BOLD | COLOR_PAIR(2));
        mvprintw(pixelPos.second, pixelPos.first, "%c ", val.c_str()[0]);
        attroff(A_BOLD | COLOR_PAIR(2));
        printScore(_score);
    } else if (object.get()->getType() == Enum::Type::ENNEMY && object.get()->getIsTraversable() == true) {
        attron(A_BOLD | COLOR_PAIR(4));
        mvprintw(pixelPos.second, pixelPos.first, "%c ", val.c_str()[0]);
        attroff(A_BOLD | COLOR_PAIR(4));
    } else if (object.get()->getType() == Enum::Type::GUM) {
        attron(COLOR_PAIR(3));
        mvprintw(pixelPos.second, pixelPos.first, "%c ", val.c_str()[0]);
        attroff(COLOR_PAIR(3));
    } else 
        mvprintw(pixelPos.second, pixelPos.first, "%c ", val.c_str()[0]);
}



extern "C" void printGame(std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    static int score = 0;

    clear();
    for (std::size_t i = 0; i < objects.size(); i++)
        if (objects[i].get()->getVisibility() == true)
            ncurses_object->printObject(objects[i], score);
    refresh();
}

extern "C" Enum::Event getEvent(void)
{
    int key = 0;

    key = getch(); 
    if (key == ESCAPE)
        return Enum::Event::GOMENU;
    if (key == KEY_BACKSPACE)
        return Enum::Event::QUIT;
    if (key == KEY_UP)
        return Enum::UP;
    if (key == KEY_DOWN)
        return Enum::DOWN;
    if (key == KEY_RIGHT)
        return Enum::RIGHT;
    if (key == KEY_LEFT)
        return Enum::LEFT;
    if (key == ' ')
        return Enum::PAUSE;
    if (key == 'a')
        return Enum::SFML;
    if (key == 'z')
        return Enum::SDL;
    if (key == 'e')
        return Enum::NCURSES;
    if (key == 'q')
        return Enum::GOPACMAN;
    if (key == 's')
        return Enum::GOSNAKE;
    return Enum::Event::NOEVENT;
}

extern "C" void borabora(std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    static int score = 0;

    clear();
    for (std::size_t i = 0; i < objects.size(); i++)
        if (objects[i].get()->getVisibility() == true)
            ncurses_object->printObject(objects[i], score);
    refresh();
}

extern "C" void init(void)
{
    ncurses_object = new Lib::Ncurses();
}

extern "C" void destroy(void)
{
    delwin(ncurses_object->_window);
    endwin();
}