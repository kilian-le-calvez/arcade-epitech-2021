/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Dynamic
*/

#include "Dynamic.hpp"

Object::Concrete::Dynamic::Dynamic(std::size_t x, std::size_t y, bool isTraversable, std::string filePath, Enum::Type type)
{
    this->_pos.first = x;
    this->_pos.second = y;
    this->_isTraversable = isTraversable;
    this->_filePath = filePath;
    this->_type = type;
    this->_visible = true;
    this->_score = 0;
}

Object::Concrete::Dynamic::~Dynamic()
{
}


void Object::Concrete::Dynamic::setScore(Enum::Eat eat)
{
    if (eat == Enum::Eat::LITTLE)
        this->_score += 10;
    else if (eat == Enum::Eat::MEDIUM)
        this->_score += 15;
    else if (eat == Enum::Eat::BIG)
        this->_score += 30;
}

int Object::Concrete::Dynamic::getScore() const
{
    return this->_score;
}

bool isBlocked(std::vector<std::unique_ptr<Object::Model::IObject>> &objects, std::pair<std::size_t, std::size_t> pos, Enum::Type type)
{
    for (std::size_t i = 0; i < objects.size(); i++) {
        if (objects[i].get()->getPosition() == pos) {
            if (type == Enum::Type::ENNEMY && objects[i].get()->getType() == Enum::Type::GATE)
                return false;
            if (objects[i].get()->getIsTraversable() == false && objects[i].get()->getType() != Enum::Type::PLAYER)
                return true;
        }

    }
    return false;
}

bool Object::Concrete::Dynamic::doEvent(Enum::Event event, std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    std::pair<std::size_t, std::size_t> pos = this->_pos;
    std::pair<std::size_t, std::size_t> spritePos = this->_spritePos;
    bool couldMove = false;

    if (event == Enum::Event::RIGHT) {
        pos.first += 1;
        spritePos.second = 1; 
    }
    if (event == Enum::Event::DOWN) {
        pos.second += 1;
        spritePos.second = 2; 
    }
    if (event == Enum::Event::LEFT) {
        pos.first -= 1;
        spritePos.second = 3; 
    }
    if (event == Enum::Event::UP) {
        pos.second -= 1;
        spritePos.second = 4; 
    }
    if (isBlocked(objects, pos, this->getType()) == false) {
        if (spritePos.first == 1)
            spritePos.first = 0;
        else
            spritePos.first = 1;
        this->_spritePos = spritePos;
        this->_pos = pos;
        couldMove = true;
    }
    return couldMove;
}
