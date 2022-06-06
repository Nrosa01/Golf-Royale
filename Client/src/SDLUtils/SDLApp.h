#ifndef SDLAppH
#define SDLAppH

#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>
#include "../GameState/GameStateMachine.h"
#include "InputSytem.h"
#include <SDL2/SDL_mixer.h>
#include "../ResourceManager/TextureManager.h"
#include "../ResourceManager/FontManager.h"
#include "../ResourceManager/SoundsManager.h"

class Client;
class NetworkMessage;
class TextureManager;
class FontManager;
class SDLTextRenderer;

class SDLApp
#define MAX_FONT_SIZE 240

{
public:
    SDLApp(int width, int height, const char *title);
    ~SDLApp();

    void initNetClient(const char *address, const char *port);
    void loadTextures(const char *pathName);
    Texture *getTexture(std::string name) const;
    void loadFonts(const char *pathName);
    TTF_Font *getFont(std::string name) const;
    void loadAudio(const char *pathName);
    void playAudio(std::string name);
    void update(float deltaTime);
    void render();
    void renderText(float p_x, float p_y, const char *p_text, TTF_Font *font, int size, SDL_Color textColor);
    void renderText(float p_x, float p_y, const char *p_text, std::string fontName, int size, SDL_Color textColor);
    void renderTextCenter(float p_x, float p_y, const char *p_text, std::string fontName, int size, SDL_Color textColor);
    void renderTextCenter(float p_x, float p_y, const char *p_text, TTF_Font *font, int size, SDL_Color textColor);
    void pushState(GameState *stateToPush);
    void changeState(GameState *stateToPush);
    void popState();
    int getWidth() const;
    int getHeight() const;
    void quit();
    bool isExitRequested() const;

    SDL_Renderer *getRenderer() const { return renderer; };

    // Network
    void sendNetworkMessage(NetworkMessage &msg);
    void rcvNetMessage(NetworkMessage* msg);
    void checkPendingNetworkMessage();
    
    // Game
    void setPlayerName(std::string name);
    std::string getPlayerName() const;

private:
    SDL_DisplayMode getDisplayMOde() const;

    SDL_Window *window;
    SDL_Renderer *renderer;
    GameStateMachine *gameStateMachine;
    GameState *newState;
    TextureManager* textureManager;
    FontManager* fontManager;
    SoundsManager* soundsManager;
    SDLTextRenderer* textRenderer;
    int width;
    int height;
    InputSystem *input;
    bool exitRequested;
    Client* client;
    std::string playerName;
};

#endif