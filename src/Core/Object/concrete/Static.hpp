/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** Static
*/

#ifndef STATIC_HPP_
#define STATIC_HPP_

#include "Object/model/AObject.hpp"

namespace Object
{
    namespace Concrete
    {
        class Static : public Object::Model::AObject
        {
            public:
                Static(std::size_t x, std::size_t y, bool isTraversable, std::string filePath, Enum::Type type);
                ~Static();

                bool doEvent(Enum::Event event, std::vector<std::unique_ptr<Object::Model::IObject>> &objects) override final;
                void setScore(Enum::Eat eat) override final;
                int getScore() const override final;
                //doevent (event, liste objets statics / map [pos]->obj)
                //drink consumable (liste objets consumables / map [pos]->obj)
                //kill or die (liste objets dynamic / map [pos]->obj)
            protected:
            private:
        };
    } // namespace Conrete
} // namespace Object

#endif /* !STATIC_HPP_ */