/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Consumable
*/

#include "Consumable.hpp"

Object::Concrete::Consumable::Consumable(std::size_t x, std::size_t y, bool isTraversable, std::string filePath, Enum::Type type)
{
    this->_pos.first = x;
    this->_pos.second = y;
    this->_isTraversable = isTraversable;
    this->_filePath = filePath;
    this->_type = type;
    this->_visible = true;
}

Object::Concrete::Consumable::~Consumable()
{
}

bool Object::Concrete::Consumable::doEvent(Enum::Event event, std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    (void) event;
    (void) objects;
    return true;
}

void Object::Concrete::Consumable::setScore(Enum::Eat eat)
{
    (void) eat;
}

int Object::Concrete::Consumable::getScore() const
{
    return 0;
}