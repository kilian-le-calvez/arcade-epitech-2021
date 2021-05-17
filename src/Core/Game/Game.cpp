/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** AGame
*/

#include "Game.hpp"

Game::Game::Game()
{
}
           
Game::Game::~Game()
{
}

std::string Game::Game::getName(void) const
{
    return this->_name;
}

std::vector<std::unique_ptr<Object::Model::IObject>> &Game::Game::getObjects(void)
{
    return this->_dl.getObjects();
}

Enum::Win Game::Game::playGame(Enum::Event event)
{
    return this->_dl.playGame(event);
}

void Game::Game::initGame(std::string name)
{
    this->_name = name;
    this->_dl.open(name);
    this->_dl.initObjects();
}