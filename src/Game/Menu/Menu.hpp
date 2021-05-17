/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-anne.mboke
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

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
    class Menu {
        public:
            Menu();
            ~Menu();
            void addObjectList(std::vector<std::string> map, Enum::Type enumType);
            
            std::vector<std::unique_ptr<Object::Model::IObject>> _objects;
            std::map<std::string, std::pair<std::string, std::string>> _objConfig;
        protected:
        private:
    }; 
} // namespace Lib

#endif /* !MENU_HPP_ */