/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-anne.mboke
** File description:
** DLgame
*/

#ifndef DLgame_HPP_
#define DLgame_HPP_

#include "Game/IGame.hpp"

class DLgame {
    public:
        DLgame();
        ~DLgame();
    /* FUNCTIONS */
        void open(std::string name);
    /* VARIABLES */
        void *handle;
        Enum::Win (*playGame)(Enum::Event event);
        void (*initObjects)(void);
        std::vector<std::unique_ptr<Object::Model::IObject>> &(*getObjects)(void);
    protected:
    private:
};

#endif /* !DLgame_HPP_ */