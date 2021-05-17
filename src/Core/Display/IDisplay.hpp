/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include <iostream>
#include <vector>
#include <dlfcn.h>
#include <memory>
#include <map>
#include <exception>

#include "Enum/Event.hpp"
#include "Object/model/IObject.hpp"

namespace Display
{
    class IDisplay
    {
    public:
        virtual ~IDisplay() = default;
        virtual void initLib(std::string name) = 0;
        virtual void printGame(std::vector<std::unique_ptr<Object::Model::IObject>> &objects) = 0;
        virtual Enum::Event getEvent(void) = 0;
        virtual void borabora(std::vector<std::unique_ptr<Object::Model::IObject>> &objects) = 0;
        virtual std::string getName(void) const = 0;
    };
} // namespace Display

#endif /* !IDISPLAY_HPP_ */