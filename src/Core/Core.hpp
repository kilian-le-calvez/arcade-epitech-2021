/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-anne.mboke
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "ICore.hpp"
#include <fstream>
#include <sstream>

#define LIB_LEN_MAX 128
#define LIB_SFML 0
#define LIB_SDL 1
#define LIB_NCURSES 2
#define LIB_MENU 3
#define LIB_PACMAN 4
#define LIB_NIBBLER 5
#define GAME_INDEX 3
#define NB_LIB 6

static const char LIBNAME[NB_LIB][LIB_LEN_MAX] = {
    "lib/arcade_sfml.so",
    "lib/arcade_sdl.so",
    "lib/arcade_ncurses.so",
    "lib/arcade_menu.so",
    "lib/arcade_pacman.so",
    "lib/arcade_nibbler.so"
};

namespace Core
{
    class Core : public ::Core::ICore
    {
        public:
            Core(std::string name, std::string username);
            ~Core();

            void setLib(std::string name) override final;
            void setGame(std::string name) override final;
            void runApp(void) override final;
        protected:
            void changeLib(Enum::Event event);
            void changeGame(Enum::Event event);
            std::unique_ptr<Game::IGame> _game;
            std::unique_ptr<Display::IDisplay> _lib;
            std::vector<std::string> _libList;
            std::vector<std::string> _gameList;
            std::chrono::_V2::system_clock::time_point _clockGame;
            std::chrono::_V2::system_clock::time_point _clockLib;
        private:
            std::string _username;
    }; 
} // namespace Core

#endif /* !CORE_HPP_ */