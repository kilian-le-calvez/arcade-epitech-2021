/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-anne.mboke
** File description:
** main
*/

#include <iostream>
#include <chrono>
#include "Display/Display.hpp"
#include "Core.hpp"

int main(int ac, char **av)
{
    std::string username;
    int len = 0;

    if (ac != 2) {
        std::cerr << "Invalid number of arguments" << std::endl;
        return 84;
    }
    std::cout << "Enter you username (size max : 12):" << std::endl;
    std::getline(std::cin, username);
    len = username.size();
    while (len >= 12 || len == 0) {
        std::cout << "Error :" << username << " size max of your username is 12 " << std::endl;
        std::getline(std::cin, username);
        len = username.size();
    }
    Core::Core core(av[1], username);
    
    core.runApp();
    return 0;
}