/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** Display
*/

#include "Display.hpp"

Display::Display::Display()
{
}

Display::Display::~Display()
{
}

void Display::Display::printGame(std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    this->_dl.printGame(objects);
}

Enum::Event Display::Display::getEvent(void)
{
    return this->_dl.getEvent();
}

std::string Display::Display::getName(void) const
{
    return this->_name;
}

void Display::Display::borabora(std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    this->_dl.borabora(objects);
}

void Display::Display::initLib(std::string name)
{
    this->_name = name;
    this->_dl.open(name);
}