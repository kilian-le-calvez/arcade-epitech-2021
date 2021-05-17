/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Dynamic
*/

#ifndef DYNAMIC_HPP_
#define DYNAMIC_HPP_

#include "Object/model/AObject.hpp"

namespace Object
{
    namespace Concrete
    {
        class Dynamic : public Object::Model::AObject
        {
            public:
                Dynamic(std::size_t x, std::size_t y, bool isTraversable, std::string filePath, Enum::Type type);
                ~Dynamic();
              
                void setScore(Enum::Eat eat) override final;
                int getScore(void) const override final;
                bool doEvent(Enum::Event event, std::vector<std::unique_ptr<Object::Model::IObject>> &objects) override final;
            protected:
            int _score;
        };
        
    } // namespace Concrete
    
} // namespace Object


#endif /* !DYNAMIC_HPP_ */