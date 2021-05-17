/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Sdl
*/

#ifndef SDL_HPP_
#define SDL_HPP_

#define SPRITE_SIZE 30

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Object/model/IObject.hpp"
#include "Enum/Event.hpp"

namespace Lib 
{
    class Sdl {
        public:
            Sdl();
            ~Sdl();

            void printObject(std::unique_ptr<Object::Model::IObject> &object);
            SDL_Rect getObjectPos(std::pair<std::size_t, std::size_t> pos);
            SDL_Texture *createSprite(std::string filePath);
            std::string findRessourcePath(std::string filePath);
            std::string readFile(std::string filePath);
            void addSpriteToList(std::string filePath);
            SDL_Rect getSubSprite(std::pair<std::size_t, std::size_t> pos);
            void destroySurfaceToQuit(void);
            SDL_Texture *CreateText(std::string str);
            void printText(std::string str, int x, int y);
            SDL_Window* _window;
            SDL_Renderer* rend;
            TTF_Font* font;
            std::string _score;
            std::map<std::string, SDL_Texture *> _sprites;
        protected:
        private:
    };
} // namespace Lib

#endif /* !SDL_HPP_ */
