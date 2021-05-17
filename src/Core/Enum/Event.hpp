/*
** EPITECH PROJECT, 2021
** Actual_Projects
** File description:
** Event
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_

namespace Enum
{
    enum Event {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        GOPACMAN,
        GOSNAKE,
        QUIT,
        PAUSE,
        GOMENU,
        SFML,
        SDL,
        NCURSES,
        NOEVENT
    };

    enum Win {
        B_PACMAN,
        B_SNAKE,
        B_EXIT,
        B_SFML,
        B_SDL,
        B_NCURSES,
        B_BORABORA,
        WIN,
        LOOSE,
        CONTINUE
    };

    enum Eat {
        LITTLE,
        MEDIUM,
        BIG,
        NOEAT
    };
} // namespace Enum

#endif /* !EVENT_HPP_ */