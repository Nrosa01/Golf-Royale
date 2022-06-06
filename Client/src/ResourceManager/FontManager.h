#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "ResourceManager.h"
#include <SDL2/SDL_ttf.h>

class FontManager : public ResourceManager<TTF_Font>
{
public:
    FontManager(uint32_t MaxFontSize) : ResourceManager("font", {"ttf", "otf"}, [MaxFontSize](std::string filePath)
                                                        { return TTF_OpenFont(filePath.c_str(), MaxFontSize); }) {}

    ~FontManager() { clear(); }

    virtual void freeResource(TTF_Font *font)
    {
        TTF_CloseFont(font);
    }
};

#endif