/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "Game/IGame.hpp"
#include "DLgame.hpp"

namespace Game
{
    class Game : public ::Game::IGame
    {
        public:
            Game();
            ~Game();
            
            std::string getName(void) const override final;
            void initGame(std::string name) override final;
            Enum::Win playGame(Enum::Event event) override final;
            std::vector<std::unique_ptr<Object::Model::IObject>> &getObjects(void) override final;   
        protected:
            std::string _name;
            DLgame _dl;
    };
} // namespace Game

#endif /* !GAME_HPP_ */