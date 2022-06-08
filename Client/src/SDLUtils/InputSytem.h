#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <SDL2/SDL.h>
#include <vector>
#include "../MathUtils/Vector2D.h"
#include <iostream>

class InputSystem
{
private:
    struct key
    {
        bool wasPressed;
        bool down;
        bool wasReleased;
    };

    struct MouseButton
    {
        key right, left, middle;
    };

    std::vector<key> keys;
    MouseButton mouseButtonState;
    std::pair<Sint32, Sint32> mousePos_;
    int keyNums;
    bool KEY_WAS_PRESSED = false;
    bool KEY_DOWN = false;
    bool KEY_WAS_RELEASED = false;
    Vector2D mouseMotion;
    char lastChar = '\0';

public:
    InputSystem();
    ~InputSystem();
    static InputSystem *instance;
    void init();
    void updateState();
    void clearState();
    int getId(SDL_Keycode key); // keycode

    // UPDATE KEY STATE
    void onKeyDown(SDL_Keycode key);
    void onKeyUp(SDL_Keycode key);

    // CONSULT KEY STATE
    bool keyWasPressed(SDL_Keycode key);
    bool isKeyDown(SDL_Keycode key);
    bool keyWasReleased(SDL_Keycode key);

    bool anyKeyWasPressed();
    bool anyKeyIsDown();
    bool anyKeyWasReleased();

    void onMouseButtonDown(SDL_MouseButtonEvent buttonEvent);
    void onMouseButtonUp(SDL_MouseButtonEvent buttonEvent);

    bool isMouseButtonDown(int button);
    bool isMouseButtonPressed(int button);
    bool isMouseButtonReleased(int button);

    void setMouseMotion(Vector2D motion);
    Vector2D getMouseMotion() const;
    Vector2D getMousePosition();

    char getLastKeyPressed();
};

inline InputSystem *Input()
{
    return InputSystem::instance;
}

#endif //