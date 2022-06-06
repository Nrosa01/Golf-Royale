#include "SDLTextRenderer.h"
#include "Texture.h"

SDLTextRenderer::SDLTextRenderer(SDL_Renderer *renderer, uint32_t maxFontSize)
{
    this->renderer = renderer;
    this->maxFontSize = maxFontSize;
}

SDLTextRenderer::~SDLTextRenderer()
{
    clear();
}

Texture *SDLTextRenderer::createTextTexture(const char *p_text, TTF_Font *font)
{
    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, p_text, {255, 255, 255, 255});
    Texture *message = new Texture(renderer);
    message->loadFromSurface(surfaceMessage);

    // Check if key font already exists in cache
    auto it = fontCache.find(font);
    if (it == fontCache.end())
        fontCache.insert(std::make_pair(font, std::unordered_map<std::string, Texture *>()));

    fontCache.at(font).insert(std::make_pair(std::string(p_text), message));

    return message;
}

Texture *SDLTextRenderer::getTexture(const char *p_text, TTF_Font *font)
{
    // Check if key font already exists in cache
    auto it = fontCache.find(font);
    if (it == fontCache.end())
        return nullptr;

    std::string textString = p_text;

    // Check if key text already exists in cache
    auto it2 = fontCache.at(font).find(textString);
    if (it2 == fontCache.at(font).end())
        return nullptr;

    return fontCache.at(font).at(textString);
}

void SDLTextRenderer::renderText(float p_x, float p_y, const char *p_text, TTF_Font *font, int size, SDL_Color textColor)
{
    Texture *message = getTexture(p_text, font);
    if (message == nullptr)
        message = createTextTexture(p_text, font);

    SDL_SetTextureColorMod(message->getTexture(), textColor.r, textColor.g, textColor.b);
    SDL_SetTextureAlphaMod(message->getTexture(), textColor.a);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = message->getW();
    src.h = message->getH();

    float fontSize = (float)size / maxFontSize;
    int fontSizeX = src.w * fontSize;
    int fontSizeY = src.h * fontSize;

    SDL_Rect dst;
    dst.x = p_x - fontSizeX / 2;
    dst.y = p_y - fontSizeY / 2;
    dst.w = fontSizeX;
    dst.h = fontSizeY;

    SDL_RenderCopy(renderer, message->getTexture(), &src, &dst);
}

void SDLTextRenderer::clear()
{
    for (auto font : fontCache)
        for (auto texture : font.second)
            delete texture.second;

    fontCache.clear();
}

int SDLTextRenderer::getNumOfLoadedTextures() const
{
    int numOfTextures = 0;
    for (auto font : fontCache)
        for (auto texture : font.second)
            numOfTextures++;

    return numOfTextures;
}