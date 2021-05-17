/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <vector>
#include <iostream>
#include <memory>
#include <dlfcn.h>

#include "Object/model/IObject.hpp"
#include "Enum/Event.hpp"

namespace Game
{
    class IGame
    {
    public:
        virtual ~IGame() = default;
        virtual void initGame(std::string name) = 0;
        virtual Enum::Win playGame(Enum::Event event) = 0;
        virtual std::string getName(void) const = 0;
        virtual std::vector<std::unique_ptr<Object::Model::IObject>> &getObjects(void) = 0;   
    };  
} // namespace Game

#endif /* !IGAME_HPP_ */