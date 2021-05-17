/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-anne.mboke
** File description:
** ICore
*/

#ifndef ICORE_HPP_
#define ICORE_HPP_

#include <iostream>
#include <chrono>
#include <memory>
#include "Game/Game.hpp"
#include "Display/Display.hpp"

namespace Core
{
    class ICore
    {
        public:
            virtual ~ICore() = default;

            virtual void setLib(std::string name) = 0;
            virtual void setGame(std::string name) = 0;
            virtual void runApp(void) = 0;
    };
} // namespace Core

#endif /* !ICORE_HPP_ */