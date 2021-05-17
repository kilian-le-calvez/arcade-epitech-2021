/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** Static
*/

#include "Static.hpp"

Object::Concrete::Static::Static(std::size_t x, std::size_t y, bool isTraversable, std::string filePath, Enum::Type type)
{
    this->_pos.first = x;
    this->_pos.second = y;
    this->_isTraversable = isTraversable;
    this->_filePath = filePath;
    this->_type = type;
    this->_visible = true;
    this->_spritePos = std::pair<std::size_t, std::size_t>(0, 0);
}

Object::Concrete::Static::~Static()
{
}

bool Object::Concrete::Static::doEvent(Enum::Event event, std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    (void) event;
    (void) objects;
    return true;
}


void Object::Concrete::Static::setScore(Enum::Eat eat)
{
    (void) eat;
}

int Object::Concrete::Static::getScore() const
{
    return 0;
}