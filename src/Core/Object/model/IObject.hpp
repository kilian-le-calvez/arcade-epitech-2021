/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** IObject
*/

#ifndef IOBJECT_HPP_
#define IOBJECT_HPP_

#include <utility>
#include <vector>
#include <iostream>
#include <memory>
#include "Enum/Type.hpp"
#include "Enum/Event.hpp"

namespace Object
{
    namespace Model
    {
        class IObject
        {
        public:
            virtual ~IObject() = default;
            virtual void setPosition(std::pair<std::size_t, std::size_t> pos) = 0;
            virtual std::pair<std::size_t, std::size_t> getPosition(void) const = 0;
            virtual void setVisibility(bool isVisible) = 0;
            virtual bool getVisibility(void) const = 0;
            virtual std::string getFilePath(void) const = 0;
            virtual bool getIsTraversable(void) const = 0;
            virtual void setIsTraversable(bool isTraversable) = 0;
            virtual void setIsVisible(bool isVisible) = 0;
            virtual Enum::Type getType(void) const = 0;
            virtual bool doEvent(Enum::Event event, std::vector<std::unique_ptr<Object::Model::IObject>> &objects) = 0;
            virtual std::pair<std::size_t, std::size_t> getSpritePos(void) const = 0;
            virtual void setScore(Enum::Eat eat) = 0;
            virtual int getScore(void) const = 0;
        };    
    } // namespace Model
} // namespace Object


#endif /* !IOBJECT_HPP_ */