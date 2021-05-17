/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** Sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#define SPRITE_SIZE 30

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <regex>
#include "Object/model/IObject.hpp"
#include "Enum/Event.hpp"

namespace Lib
{
    class Sfml {
        public:
            Sfml();
            ~Sfml();

        void printObject(std::unique_ptr<Object::Model::IObject> &object);
        sf::Vector2f getObjectPos(std::pair<std::size_t, std::size_t> pos);
        void addSpriteToList(std::string filePath);
        std::string findRessourcePath(std::string filePath);
        std::string readFile(std::string filePath);
        sf::Texture createTextureFromFile(std::string filePath);
        sf::Sprite createSpriteFromTexture(sf::Texture &texture);
        void setScoreText(int scor);
        void initBorabora(void);
        sf::RenderWindow _window;
        std::map<std::string, std::pair<sf::Texture, sf::Sprite>> _sprites;
        sf::Text _score;
        sf::Font _font;
        sf::Texture _boraTexture;
        sf::Sprite _boraSprite;
        protected:
        private:
    };
} // namespace Lib

#endif /* !SFML_HPP_ */