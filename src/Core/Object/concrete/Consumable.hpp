/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Consumable
*/

#ifndef CONSUMABLE_HPP_
#define CONSUMABLE_HPP_

#include "Object/model/AObject.hpp"
#include "Enum/Event.hpp"
#include "Enum/Type.hpp"

namespace Object
{
    namespace Concrete
    {
        class Consumable : public Object::Model::AObject
        {
            public:
                Consumable(std::size_t x, std::size_t y, bool isTraversable, std::string filePath, Enum::Type type);
                ~Consumable();
                
                void setScore(Enum::Eat eat) override final;
                int getScore() const override final;
                bool doEvent(Enum::Event event, std::vector<std::unique_ptr<Object::Model::IObject>> &objects);
            protected:
            private:
        };
    } // namespace Consumable
} // namespace Object

#endif /* !CONSUMABLE_HPP_ */