/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** Display
*/

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include "Display/IDisplay.hpp"
#include "DLlib.hpp"

namespace Display
{
    class Display : public ::Display::IDisplay
    {
        public:
            Display();
            ~Display();

            void initLib(std::string name) override final;
            void printGame(std::vector<std::unique_ptr<Object::Model::IObject>> &objects) override final;
            Enum::Event getEvent(void) override final;
            void borabora(std::vector<std::unique_ptr<Object::Model::IObject>> &objects) override final;
            std::string getName(void) const override final;
        private:
            std::string _name;
            DLlib _dl;
    };
} // namespace Display


#endif /* !DISPLAY_HPP_ */