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
        return;
    }
    else
        std::cout << "SDL initialized!" << std::endl;

    // Create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    else
        std::cout << "Window created!" << std::endl;

    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    else
        std::cout << "Renderer created!" << std::endl;

    if (TTF_Init() != 0)
    {
        std::cout << "TTF could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    else
        std::cout << "TTF_Init" << std::endl;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    {
        std::cout << "SDL_mixer could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
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

    client = new Client("0.0.0.0", "13000");
}

SDLApp::~SDLApp()
{
    delete gameStateMachine;
    delete input;
    delete client;

    // Free resources and close SDL
    for (auto &texture : textures)
        delete texture.second;

    for (auto &font : fonts)
        TTF_CloseFont(font.second);

    for (auto &sound : sounds)
        Mix_FreeChunk(sound.second);

    Mix_CloseAudio();
    TTF_Quit();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void SDLApp::pushState(GameState *stateToPush)
{
    newState = stateToPush;
}

void SDLApp::popState()
{
    gameStateMachine->popState();
}

void SDLApp::update(float deltaTime)
{
    checkPendingNetworkMessage();
    checkStateChanged();
    gameStateMachine->update(deltaTime);
}

void SDLApp::checkStateChanged()
{
    if (newState != nullptr)
    {
        gameStateMachine->pushState(newState);
        newState = nullptr;
    }
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

void SDLApp::loadTextures(const char *pathName)
{
    // Load textures
    std::cout << "Loading textures from " << pathName << "..." << std::endl;

    // Using dirent, check if pathName is a directory
    DIR *dir = opendir(pathName);

    // If it is a directory, load all files in it with extension .png or .jpg
    if (dir != nullptr)
    {
        // Get all files in directory
        struct dirent *ent;
        while ((ent = readdir(dir)) != nullptr)
        {
            // Get file extension
            std::string fileName = ent->d_name;
            std::string ext = fileName.substr(fileName.find_last_of(".") + 1);
            std::string fileNameWithoutExt = fileName.substr(0, fileName.find_last_of("."));

            // If file extension is .png or .jpg, load texture
            if (ext == "png" || ext == "jpg")
            {
                std::string filePath = pathName;
                filePath.append("/");
                filePath.append(fileName);

                // Load texture
                Texture *texture = new Texture(renderer);
                // As this is simple project, there are no animations so all textures are 1*1, they are not spritesheets
                // If I had more time, I would load these settings from a json
                texture->load(filePath.c_str(), 1, 1);
                std::cout << "Loaded texture " << fileNameWithoutExt << std::endl;
                textures.insert(std::pair<std::string, Texture *>(fileNameWithoutExt, texture));
            }
        }

        std::cout << "Textures loaded!" << std::endl;
    }
    else // If pathName is not a directory, we throw an error message
        std::cout << "Path " << pathName << " is not a directory!" << std::endl;
}

void SDLApp::loadFonts(const char *pathName)
{
    // Load fonts
    std::cout << "Loading fonts from " << pathName << "..." << std::endl;

    // Using dirent, check if pathName is a directory
    DIR *dir = opendir(pathName);

    // If it is a directory, load all files in it with extension .ttf
    if (dir != nullptr)
    {
        // Get all files in directory
        struct dirent *ent;
        while ((ent = readdir(dir)) != nullptr)
        {
            // Get file extension
            std::string fileName = ent->d_name;
            std::string ext = fileName.substr(fileName.find_last_of(".") + 1);
            std::string fileNameWithoutExt = fileName.substr(0, fileName.find_last_of("."));

            // If file extension is .ttf, load font
            if (ext == "ttf" || ext == "otf")
            {
                std::string filePath = pathName;
                filePath.append("/");
                filePath.append(fileName);

                // Load font with size 12, 24, 36, 48, 60, 72, 84, 96, 108, 120
                TTF_Font *font = TTF_OpenFont(filePath.c_str(), MAX_FONT_SIZE);
                if (font == nullptr)
                {
                    std::cout << "Font could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
                    return;
                }
                else
                    std::cout << "Loaded font " << fileNameWithoutExt << " with size " << MAX_FONT_SIZE << std::endl;
                fonts.insert(std::pair<std::string, TTF_Font *>(fileNameWithoutExt, font));
            }
        }

        std::cout << "Fonts loaded!" << std::endl;
    }
    else // If pathName is not a directory, we throw an error message
        std::cout << "Path " << pathName << " is not a directory!" << std::endl;
}

TTF_Font *SDLApp::getFont(std::string fontName) const
{
    // Get font from map
    std::unordered_map<std::string, TTF_Font *>::const_iterator it = fonts.find(fontName);
    if (it != fonts.end())
        return it->second;
    else
        return nullptr;
}

Texture *SDLApp::getTexture(std::string name) const
{
    // Get texture from map
    std::unordered_map<std::string, Texture *>::const_iterator it = textures.find(name);
    if (it != textures.end())
        return it->second;
    else
        return nullptr;
}

void SDLApp::loadAudio(const char *pathName)
{
    // Load audio
    std::cout << "Loading audio from " << pathName << "..." << std::endl;

    // Using dirent, check if pathName is a directory
    DIR *dir = opendir(pathName);

    // If it is a directory, load all files in it with extension .wav
    if (dir != nullptr)
    {
        // Get all files in directory
        struct dirent *ent;
        while ((ent = readdir(dir)) != nullptr)
        {
            // Get file extension
            std::string fileName = ent->d_name;
            std::string ext = fileName.substr(fileName.find_last_of(".") + 1);
            std::string fileNameWithoutExt = fileName.substr(0, fileName.find_last_of("."));

            // If file extension is .wav, load audio
            if (ext == "wav" || ext == "mp3")
            {
                std::string filePath = pathName;
                filePath.append("/");
                filePath.append(fileName);

                // Load audio
                Mix_Chunk *chunk = Mix_LoadWAV(filePath.c_str());
                if (chunk == nullptr)
                {
                    std::cout << "Audio could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
                    return;
                }
                else
                    std::cout << "Loaded audio " << fileNameWithoutExt << std::endl;
                sounds.insert(std::pair<std::string, Mix_Chunk *>(fileNameWithoutExt, chunk));
            }
        }

        std::cout << "Audio loaded!" << std::endl;
    }
    else // If pathName is not a directory, we throw an error message
        std::cout << "Path " << pathName << " is not a directory!" << std::endl;
}

void SDLApp::playAudio(std::string name)
{
    // Get audio from map
    std::unordered_map<std::string, Mix_Chunk *>::const_iterator it = sounds.find(name);
    if (it != sounds.end())
        Mix_PlayChannel(-1, it->second, 0);
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

void SDLApp::rcvNetMessage(NetworkMessage &message)
{
    this->gameStateMachine->receiveNetworkMessage(message);
}

void SDLApp::checkPendingNetworkMessage()
{
    NetworkMessage* message = client->consumeMessage();
    if (message != nullptr)
    {
        this->rcvNetMessage(*message);
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
