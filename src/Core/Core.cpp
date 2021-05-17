/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-anne.mboke
** File description:
** Core
*/

#include "Core.hpp"

Core::Core::Core(std::string name, std::string username)
{
    this->_clockGame = std::chrono::system_clock::now();
    this->_clockLib = std::chrono::system_clock::now();
    for (int i = 0; i < NB_LIB; i++) {
        if (i < GAME_INDEX) {
            this->_libList.emplace_back(LIBNAME[i]);
        } else {
            this->_gameList.emplace_back(LIBNAME[i]);
        }
    }
    this->setLib(name);
    this->setGame(LIBNAME[LIB_MENU]);
    this->_username = username;
}

Core::Core::~Core()
{
    this->_lib.reset();
    this->_game.reset();
}

void Core::Core::setLib(std::string name)
{
    this->_lib.reset(new Display::Display());
    this->_lib.get()->initLib(name);
}

void Core::Core::setGame(std::string name)
{
    this->_game.reset(new Game::Game());
    this->_game.get()->initGame(name);
}

void Core::Core::changeLib(Enum::Event event)
{
    if (event == Enum::Event::SFML)
        this->setLib(this->_libList[0]);
    else if (event == Enum::Event::SDL)
        this->setLib(this->_libList[1]);
    else if (event == Enum::Event::NCURSES)
        this->setLib(this->_libList[2]);
}

void Core::Core::changeGame(Enum::Event event)
{
    if (event == Enum::Event::GOMENU)
        this->setGame(this->_gameList[0]);
    else if (event == Enum::Event::GOPACMAN)
        this->setGame(this->_gameList[1]);
    else if (event == Enum::Event::GOSNAKE)
        this->setGame(this->_gameList[2]);
}

void Core::Core::runApp(void)
{
    Enum::Event event = Enum::NOEVENT;
    Enum::Event evToDo = Enum::NOEVENT;
    Enum::Win win = Enum::Win::CONTINUE;
    static bool borabora = false;
   
    while (win == Enum::Win::CONTINUE) {
        if (std::chrono::milliseconds(20) + this->_clockLib < std::chrono::system_clock::now()) {
            this->_clockLib = std::chrono::system_clock::now();
            event = this->_lib.get()->getEvent();
            if (event != Enum::Event::NOEVENT)
                evToDo = event;
            if (evToDo == Enum::Event::SFML || evToDo == Enum::Event::SDL || evToDo == Enum::Event::NCURSES) {
                changeLib(evToDo);
                evToDo = Enum::Event::NOEVENT;
            }
            if (evToDo == Enum::Event::GOPACMAN || evToDo == Enum::Event::GOSNAKE || evToDo == Enum::Event::GOMENU) {
                if (evToDo == Enum::Event::GOMENU)
                    borabora = false;
                changeGame(evToDo);
                evToDo = Enum::Event::NOEVENT;
            }
            if (evToDo == Enum::Event::QUIT) {
                return;
            }
        }
        if (std::chrono::milliseconds(20) + this->_clockGame < std::chrono::system_clock::now()) {
            this->_clockGame = std::chrono::system_clock::now();
            if (borabora)
                this->_lib.get()->borabora(this->_game.get()->getObjects());
            else
                this->_lib.get()->printGame(this->_game.get()->getObjects());
            win = this->_game.get()->playGame(evToDo);
            if (evToDo == Enum::Event::PAUSE)
                evToDo = Enum::Event::NOEVENT;
            if (win == Enum::Win::B_PACMAN) {
                changeGame(Enum::Event::GOPACMAN);
                win = Enum::Win::CONTINUE;
            }
            if (win == Enum::Win::B_SNAKE) {
                changeGame(Enum::Event::GOSNAKE);
                win = Enum::Win::CONTINUE;
            }
            if (win == Enum::Win::B_SFML) {
                changeLib(Enum::Event::SFML);
                changeGame(Enum::Event::GOMENU);
                win = Enum::Win::CONTINUE;
            }
            if (win == Enum::Win::B_SDL) {
                changeLib(Enum::Event::SDL);
                changeGame(Enum::Event::GOMENU);
                win = Enum::Win::CONTINUE;
            }
            if (win == Enum::Win::B_NCURSES) {
                changeLib(Enum::Event::NCURSES);
                changeGame(Enum::Event::GOMENU);
                win = Enum::Win::CONTINUE;
            }
            if (win == Enum::Win::B_BORABORA) {
                borabora = true;
                win = Enum::Win::CONTINUE;
            }
            if (win == Enum::Win::B_EXIT)
                return;
            if (win == Enum::Win::LOOSE || win == Enum::Win::WIN) {
                changeGame(Enum::Event::GOMENU);
                evToDo = Enum::Event::NOEVENT;
                win = Enum::Win::CONTINUE;
            }

        }
    }
}