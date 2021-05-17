/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include "Object/model/IObject.hpp"
#include "Enum/Event.hpp"

#define SPRITE_SIZE 2
#define ESCAPE 27
#define ctrl(x)           ((x) & 0x1f)
#define LINES 1080
#define COLS 1920

namespace Lib 
{
    class Ncurses {
        public:
            Ncurses();
            ~Ncurses();

            WINDOW* _window;
            std::pair<std::size_t, std::size_t> getObjectPos(std::pair<std::size_t, std::size_t> pos);
            std::string readFile(std::string filePath);
            std::string findRessourcePath(std::string filePath);
            std::string createSprite(std::string filePath);
            void addSpriteToList(std::string filePath);
            void printObject(std::unique_ptr<Object::Model::IObject> &object, int score);
            std::map<std::string, std::string> _sprites;
            int _score;
        protected:
        private:
    };
}

#endif /* !NCURSES_HPP_ */
