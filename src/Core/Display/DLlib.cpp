/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-anne.mboke
** File description:
** DLlib
*/

#include "DLlib.hpp"

DLlib::DLlib()
{
}

DLlib::~DLlib()
{
    this->destroy();
    dlclose(this->handle);
}

void DLlib::open(std::string name)
{
    this->handle = dlopen(name.c_str(), RTLD_NOW);
    if (!this->handle) {
        std::cerr << "Error opening " << name << std::endl;
        exit(EXIT_FAILURE);
    }
    this->printGame = (void(*)(std::vector<std::unique_ptr<Object::Model::IObject>> &)) dlsym(this->handle, "printGame");
    this->getEvent = (Enum::Event(*)()) dlsym(this->handle, "getEvent");
    this->borabora = (void(*)(std::vector<std::unique_ptr<Object::Model::IObject>> &)) dlsym(this->handle, "borabora");
    this->destroy = (void(*)(void)) dlsym(this->handle, "destroy");
    this->init = (void (*)(void)) dlsym(this->handle, "init");
    if (!this->printGame || !this->getEvent || !this->borabora || !this->destroy || !this->init) {
        std::cerr << dlerror() << std::endl;
        std::cerr << "Error linking lib symbol" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->init();
}