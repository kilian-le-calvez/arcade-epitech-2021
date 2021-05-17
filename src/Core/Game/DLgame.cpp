/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-anne.mboke
** File description:
** DLgame
*/

#include "DLgame.hpp"

DLgame::DLgame()
{
}

DLgame::~DLgame()
{
    dlclose(this->handle);
}

void DLgame::open(std::string name)
{
    this->handle = dlopen(name.c_str(), RTLD_NOW);
    if (!this->handle) {
        std::cerr << "Error opening " << name << std::endl;
        exit(EXIT_FAILURE);
    }
    this->playGame = (Enum::Win(*)(Enum::Event)) dlsym(this->handle, "playGame");
    this->initObjects = (void(*)(void)) dlsym(this->handle, "initObjects");
    this->getObjects = (std::vector<std::unique_ptr<Object::Model::IObject>> &(*)(void)) dlsym(this->handle, "getObjects");
    if (!this->playGame || !this->initObjects || !this->getObjects) {
        std::cerr << dlerror() << std::endl;
        std::cerr << "Error linking game symbol" << std::endl;
        exit(EXIT_FAILURE);
    }
}