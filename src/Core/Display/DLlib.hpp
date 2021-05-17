/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-anne.mboke
** File description:
** DLlib
*/

#ifndef DLlib_HPP_
#define DLlib_HPP_

#include "Display/IDisplay.hpp"

class DLlib {
    public:
        DLlib();
        ~DLlib();
    /* FUNCTIONS */
        void open(std::string name);
    /* VARIABLES */
        void *handle;
        void (*printGame)(std::vector<std::unique_ptr<Object::Model::IObject>> &);
        Enum::Event (*getEvent)(void);
        void (*borabora)(std::vector<std::unique_ptr<Object::Model::IObject>> &);
        void (*destroy)(void);
        void (*init)(void);
    protected:
    private:
};

#endif /* !DLlib_HPP_ */