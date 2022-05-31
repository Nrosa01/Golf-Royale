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
    void Init();
    void UpdateState();
    void ClearState();
    int getId(SDL_Keycode key); // keycode

    // UPDATE KEY STATE
    void OnKeyDown(SDL_Keycode key);
    void OnKeyUp(SDL_Keycode key);

    // CONSULT KEY STATE
    bool keyWasPressed(SDL_Keycode key);
    bool isKeyDown(SDL_Keycode key);
    bool keyWasReleased(SDL_Keycode key);

    bool anyKeyWasPressed();
    bool anyKeyIsDown();
    bool anyKeyWasReleased();

    void OnMouseButtonDown(SDL_MouseButtonEvent buttonEvent);
    void OnMouseButtonUp(SDL_MouseButtonEvent buttonEvent);

    bool IsMouseButtonDown(int button);
    bool IsMouseButtonPressed(int button);
    bool IsMouseButtonReleased(int button);

    void SetMouseMotion(Vector2D motion);
    Vector2D GetMouseMotion() const;
    Vector2D GetMousePosition();

    char GetLastKeyPressed();
};

inline InputSystem *Input()
{
    return InputSystem::instance;
}

#endif //