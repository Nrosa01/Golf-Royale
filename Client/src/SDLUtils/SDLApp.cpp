#include "SDLApp.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <dirent.h>
#include "Texture.h"
#include "../Network/Client.h"
#include "../Network/NetworkMessage.h"


SDLApp::SDLApp(int width, int height, const char *title)
{
    // Init sdl and create window
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        quit();
        return;
    }
    else
        std::cout << "SDL initialized!" << std::endl;

    // Create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        quit();
        return;
    }
    else
        std::cout << "Window created!" << std::endl;

    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        quit();
        return;
    }
    else
        std::cout << "Renderer created!" << std::endl;

    if (TTF_Init() != 0)
    {
        std::cout << "TTF could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        quit();
        return;
    }
    else
        std::cout << "TTF_Init" << std::endl;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    {
        std::cout << "SDL_mixer could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        quit();
        return;
    }
    else
        std::cout << "SDL_mixer initialized!" << std::endl;

    // Change downscale method to jagged because the game is pixelart
    // It should be nearest by default, but I prefer to make it sure
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    // Disable screensaver, so the game doesn't lock the screen
    SDL_DisableScreenSaver();

    // Init game state machine
    gameStateMachine = new GameStateMachine();
    this->width = width;
    this->height = height;
    input = new InputSystem();
    exitRequested = false;
    newState = nullptr;

    // Resource Managers
    textureManager = new TextureManager(renderer);
    fontManager = new FontManager(MAX_FONT_SIZE);
    soundsManager = new SoundsManager();
}

SDLApp::~SDLApp()
{
    delete gameStateMachine;
    delete input;

    if (client != nullptr)
        delete client;

    // Free resources and close SDL
    delete textureManager;
    delete fontManager;
    delete soundsManager;

    Mix_CloseAudio();
    TTF_Quit();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void SDLApp::pushState(GameState *stateToPush)
{
    gameStateMachine->pushState(stateToPush);
}

void SDLApp::changeState(GameState *stateToPush)
{
    gameStateMachine->changeState(stateToPush);
}

void SDLApp::popState()
{
    gameStateMachine->popState();
}

void SDLApp::update(float deltaTime)
{
    checkPendingNetworkMessage();
    gameStateMachine->update(deltaTime);
}

void SDLApp::render()
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Render entities
    gameStateMachine->render();

    // Update screen
    SDL_RenderPresent(renderer);
}

void SDLApp::initNetClient(const char *address, const char *port)
{
    client = new Client(address, port);
}

void SDLApp::loadTextures(const char *pathName)
{
    textureManager->load(pathName);
}

void SDLApp::loadFonts(const char *pathName)
{
    fontManager->load(pathName);
}

TTF_Font *SDLApp::getFont(std::string fontName) const
{
    return fontManager->get(fontName);
}

Texture *SDLApp::getTexture(std::string name) const
{
    return textureManager->get(name);
}

void SDLApp::loadAudio(const char *pathName)
{
    soundsManager->load(pathName);
}

void SDLApp::playAudio(std::string name)
{
    soundsManager->play(name);
}

SDL_DisplayMode SDLApp::getDisplayMOde() const
{
    SDL_DisplayMode displayMode;
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0)
    {
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        return displayMode;
    }
    return displayMode;
}

int SDLApp::getWidth() const
{
    return this->width;
}

int SDLApp::getHeight() const
{
    return this->height;
}

void SDLApp::renderText(float p_x, float p_y, const char *p_text, std::string fontName, int size, SDL_Color textColor)
{
    this->renderText(p_x, p_y, p_text, getFont(fontName), size, textColor);
}

void SDLApp::renderText(float p_x, float p_y, const char *p_text, TTF_Font *font, int size, SDL_Color textColor)
{
    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, p_text, textColor);
    SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage->w;
    src.h = surfaceMessage->h;

    float fontSize = (float)size / MAX_FONT_SIZE;
    int fontSizeX = src.w * fontSize;
    int fontSizeY = src.h * fontSize;

    SDL_Rect dst;
    dst.x = p_x - fontSizeX / 2;
    dst.y = p_y - fontSizeY / 2;
    dst.w = fontSizeX;
    dst.h = fontSizeY;

    SDL_RenderCopy(renderer, message, &src, &dst);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void SDLApp::renderTextCenter(float p_x, float p_y, const char *p_text, std::string fontName, int size, SDL_Color textColor)
{
    this->renderTextCenter(p_x, p_y, p_text, getFont(fontName), size, textColor);
}

void SDLApp::renderTextCenter(float p_x, float p_y, const char *p_text, TTF_Font *font, int size, SDL_Color textColor)
{
    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, p_text, textColor);
    SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage->w;
    src.h = surfaceMessage->h;

    int fontSize = size / MAX_FONT_SIZE;
    int fontSizeX = src.w * fontSize;
    int fontSizeY = src.h * fontSize;

    SDL_Rect dst;
    dst.x = this->getWidth() / 2 - fontSizeX / 2 + p_x;
    dst.y = this->getHeight() / 2 - fontSizeY / 2 + p_y;
    dst.w = fontSizeX;
    dst.h = fontSizeY;

    SDL_RenderCopy(renderer, message, &src, &dst);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void SDLApp::quit()
{
    this->exitRequested = true;
}

bool SDLApp::isExitRequested() const
{
    return this->exitRequested;
}

void SDLApp::sendNetworkMessage(NetworkMessage &message)
{
    this->client->send(message);
}

void SDLApp::rcvNetMessage(NetworkMessage *message)
{
    this->gameStateMachine->receiveNetworkMessage(message);
}

void SDLApp::checkPendingNetworkMessage()
{
    NetworkMessage *message = client->consumeMessage();
    if (message != nullptr)
    {
        this->rcvNetMessage(message);
        delete message;
    }
}

void SDLApp::setPlayerName(std::string name)
{
    this->playerName = name;
}

std::string SDLApp::getPlayerName() const
{
    return this->playerName;
}
