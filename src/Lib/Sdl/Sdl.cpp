/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Sdl
*/

#include "Sdl.hpp"

Lib::Sdl *sdl_object;

Lib::Sdl::Sdl()
{
    SDL_Init(SDL_INIT_VIDEO);
    int img_Flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (IMG_Init(img_Flags) == 0) {
        std::cout << SDL_GetError() << std::endl;
        return;
    }
    if (TTF_Init() < 0) {
        std::cout << "Could not init TTF" << std::endl;
        return;
    }
    SDL_CreateWindowAndRenderer(1920, 1080, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN, &_window, &rend);
    SDL_SetWindowTitle(_window, "ARCADE");
    font = TTF_OpenFont("assets/ressources/COMICATE.TTF", 30);
    if (font == nullptr) {
        std::cout << "Could not create font" << std::endl;
        return;
    }
}

Lib::Sdl::~Sdl()
{
}

SDL_Rect Lib::Sdl::getObjectPos(std::pair<std::size_t, std::size_t> pos)
{
    SDL_Rect newpos;

    newpos.x = pos.first * SPRITE_SIZE;
    newpos.y = pos.second * SPRITE_SIZE;
    newpos.h = SPRITE_SIZE;
    newpos.w = SPRITE_SIZE;
    return newpos;
}

std::string Lib::Sdl::readFile(std::string filePath)
{
    std::stringstream file;
    std::ifstream is(filePath);

    if (is.is_open()) {
        file << is.rdbuf();
        return file.str();
    }
    return "default";
}

std::string Lib::Sdl::findRessourcePath(std::string filePath)
{
    std::string buffer = readFile(filePath);
    std::string libPathBegin = "-SDL:(";
    std::string libPathEnd = "):SDL-";

    std::size_t sfmlBegin = buffer.find(libPathBegin) + libPathBegin.size();
    std::size_t sfmlEnd = buffer.find(libPathEnd);
    return buffer.substr(sfmlBegin, sfmlEnd - sfmlBegin);
}

SDL_Texture *Lib::Sdl::createSprite(std::string filePath)
{
    SDL_Surface *sprite = IMG_Load(findRessourcePath(filePath).c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, sprite);
    if (texture == NULL) {
        std::cout << SDL_GetError() << std::endl;
        return NULL;
    }
    if (sprite)
        SDL_FreeSurface(sprite);
    return texture;
}

SDL_Texture *Lib::Sdl::CreateText(std::string str)
{
    SDL_Surface *text = TTF_RenderText_Blended(font, str.c_str(), SDL_Color{ 0, 255, 0, 255 });
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, text);

    if (text == NULL || texture == NULL) {
        std::cout << SDL_GetError() << std::endl;
        return NULL;
    }
    return texture;
}

void Lib::Sdl::printText(std::string str, int x, int y)
{
    SDL_Texture* texture = CreateText(str);
    SDL_Rect pos = {x * SPRITE_SIZE, y * SPRITE_SIZE};

    if (texture == NULL)
        return;
    if (SDL_QueryTexture(texture, nullptr, nullptr, &pos.w, &pos.h) < 0) {
        std::cout << "Invalid texture" << std::endl;
        return;
    }
    SDL_RenderCopy(rend, texture, nullptr, &pos);
    SDL_DestroyTexture(texture);
}

void Lib::Sdl::addSpriteToList(std::string filePath)
{
    SDL_Texture *newSprite = createSprite(filePath);

    if (newSprite == NULL)
        return;
    this->_sprites.insert(_sprites.end(), {filePath, newSprite});
}

SDL_Rect Lib::Sdl::getSubSprite(std::pair<std::size_t, std::size_t> pos)
{
    SDL_Rect rect;

    rect.x = pos.first * SPRITE_SIZE;
    rect.y = pos.second * SPRITE_SIZE;
    rect.w = SPRITE_SIZE;
    rect.h = SPRITE_SIZE;
    return rect;
}

void Lib::Sdl::printObject(std::unique_ptr<Object::Model::IObject> &object)
{
    SDL_Rect pixelPos = getObjectPos(object.get()->getPosition());
    std::string filePath = object.get()->getFilePath();
    SDL_Rect rect;

    if (this->_sprites.find(filePath) == this->_sprites.end())
        addSpriteToList(filePath);
    if (object.get()->getType() == Enum::Type::PLAYER) {
        rect = getSubSprite(object.get()->getSpritePos());
        _score = std::to_string(object.get()->getScore());
        if (SDL_RenderCopy(rend, _sprites[filePath], &rect, &pixelPos) == -1) {
            std::cout << SDL_GetError() << std::endl;
            return;
        }
    } else {
        if (object.get()->getType() == Enum::Type::ENNEMY)
            printText(_score, 54, 5);
        if (SDL_RenderCopy(rend, _sprites[filePath], nullptr, &pixelPos) == -1) {
            std::cout << SDL_GetError() << std::endl;
            return;
        }
    }
}

extern "C" void printGame(std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    SDL_RenderClear(sdl_object->rend);
    for (std::size_t i = 0; i < objects.size(); i++)
        if (objects[i].get()->getVisibility() == true) {
            sdl_object->printObject(objects[i]);
        }
    SDL_RenderPresent(sdl_object->rend);   
}

extern "C" Enum::Event getEvent(void)
{
    SDL_Event event;

     while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT)
            return Enum::QUIT;
        if (SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                return Enum::GOMENU;
            if (event.key.keysym.sym == SDLK_BACKSPACE)
                return Enum::QUIT;
            if (event.key.keysym.sym == SDLK_SPACE)
                return Enum::PAUSE;
            if (event.key.keysym.sym == SDLK_UP)
                return Enum::UP;
            if (event.key.keysym.sym == SDLK_DOWN)
                return Enum::DOWN;
            if (event.key.keysym.sym == SDLK_RIGHT)
                return Enum::RIGHT;
            if (event.key.keysym.sym == SDLK_LEFT)
                return Enum::LEFT;
            if (event.key.keysym.sym == SDLK_a)
                return Enum::SFML;
            if (event.key.keysym.sym == SDLK_z)
                return Enum::SDL;
            if (event.key.keysym.sym == SDLK_e)
                return Enum::NCURSES;
            if (event.key.keysym.sym == SDLK_q)
                return Enum::GOPACMAN;
            if (event.key.keysym.sym == SDLK_s)
                return Enum::GOSNAKE;
        }
    }
    return Enum::Event::NOEVENT;
}

extern "C" void borabora(std::vector<std::unique_ptr<Object::Model::IObject>> &objects)
{
    SDL_RenderClear(sdl_object->rend);
    for (std::size_t i = 0; i < objects.size(); i++)
        if (objects[i].get()->getVisibility() == true) {
            sdl_object->printObject(objects[i]);
        }
    SDL_RenderPresent(sdl_object->rend);   
}

extern "C" void init(void)
{
    sdl_object = new Lib::Sdl();
}

extern "C" void destroy(void)
{
    if (sdl_object->font)
        TTF_CloseFont(sdl_object->font);
    if (sdl_object->rend)
        SDL_DestroyRenderer(sdl_object->rend);
    if (sdl_object->_window)
        SDL_DestroyWindow(sdl_object->_window);
    TTF_Quit();
    SDL_Quit();
}