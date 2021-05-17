/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** AObject
*/

#include "AObject.hpp"

Object::Model::AObject::AObject()
{
}
     
Object::Model::AObject::~AObject()
{
}

Enum::Type Object::Model::AObject::getType(void) const
{
    return this->_type;
}

void Object::Model::AObject::setPosition(std::pair<std::size_t, std::size_t> vec)
{
    this->_pos.first = vec.first;
    this->_pos.second = vec.second;
}

std::pair<std::size_t, std::size_t> Object::Model::AObject::getPosition(void) const
{
    return this->_pos;
}

std::string Object::Model::AObject::getFilePath(void) const
{
    return this->_filePath;
}

bool Object::Model::AObject::getIsTraversable(void) const
{
    return this->_isTraversable;
}

void Object::Model::AObject::setVisibility(bool isVisible)
{
    this->_visible = isVisible;
}

void Object::Model::AObject::setIsTraversable(bool isTraversable)
{
    this->_isTraversable = isTraversable;
}

void Object::Model::AObject::setIsVisible(bool isVisible)
{
    this->_visible = isVisible;
}

bool Object::Model::AObject::getVisibility(void) const
{
    return this->_visible;
}

std::pair<std::size_t, std::size_t> Object::Model::AObject::getSpritePos(void) const
{
    return this->_spritePos;
}
