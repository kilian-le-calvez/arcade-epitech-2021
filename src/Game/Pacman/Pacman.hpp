/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <regex>
#include <fstream>
#include <chrono>
#include <memory>
#include "Object/concrete/Static.hpp"
#include "Object/concrete/Dynamic.hpp"
#include "Object/concrete/Consumable.hpp"
#include "Enum/Type.hpp"
#include "Enum/Event.hpp"
#include "Object/model/IObject.hpp"

namespace Lib
{
    class Pacman
    {
        public:
            Pacman();
            ~Pacman();
            void addObjectList(std::vector<std::string> map);
            
            std::vector<std::unique_ptr<Object::Model::IObject>> _objects;
            std::map<std::string, std::pair<std::string, std::string>> _objConfig;
        protected:
        private:
    };
} // namespace Lib

#endif /* !PACMAN_HPP_ */
