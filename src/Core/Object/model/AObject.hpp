/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** AObject
*/

#ifndef AOBJECT_HPP_
#define AOBJECT_HPP_

#include "Object/model/IObject.hpp"

namespace Object
{
    namespace Model
    {
        class AObject : public Object::Model::IObject
        {
            public:
                AObject();
                ~AObject();

                void setPosition(std::pair<std::size_t, std::size_t> pos) override final;
                std::pair<std::size_t, std::size_t> getPosition(void) const override final;
                void setVisibility(bool isVisible) override final;
                bool getVisibility(void) const override final;
                std::string getFilePath(void) const override final;
                bool getIsTraversable(void) const override final;
                void setIsTraversable(bool isTraversable) override final;
                void setIsVisible(bool isVisible) override final;
                Enum::Type getType(void) const override final;
                std::pair<std::size_t, std::size_t> getSpritePos(void) const;

        protected:
                std::pair<std::size_t, std::size_t> _pos;
                std::string _filePath;
                std::pair<std::size_t, std::size_t> _spritePos;
                bool _isTraversable;
                Enum::Type _type;
                bool _visible;
                //int _score;
        };
    } // namespace Model
} // namespace Object

#endif /* !AOBJECT_HPP_ */