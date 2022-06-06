#include "InputSytem.h"
#include <SDL2/SDL_stdinc.h>

#define SDL_clamp(x, a, b) (((x) < (a)) ? (a) : (((x) > (b)) ? (b) : (x)))

InputSystem* InputSystem::instance = nullptr;

InputSystem::InputSystem()
{
    // No es un singleton, pero es una clase que se instancia una sola vez.
    InputSystem::instance = this;
    Init();
}

InputSystem::~InputSystem()
{
}

void InputSystem::Init()
{
    keyNums = 322;
    keys = std::vector<key>(keyNums, {false, false, false});
}

void InputSystem::UpdateState()
{

    KEY_WAS_PRESSED = false;
    KEY_WAS_RELEASED = false;
    KEY_DOWN = false;

    // This code is ugly, we have to refactor it later
    mouseButtonState.left.wasReleased = false;
    if (mouseButtonState.left.wasPressed)
    {
        mouseButtonState.left.wasPressed = false;
        mouseButtonState.left.down = true;
    }

    mouseButtonState.right.wasReleased = false;
    if (mouseButtonState.right.wasPressed)
    {
        mouseButtonState.right.wasPressed = false;
        mouseButtonState.right.down = true;
    }

    mouseButtonState.middle.wasReleased = false;
    if (mouseButtonState.middle.wasPressed)
    {
        mouseButtonState.middle.wasPressed = false;
        mouseButtonState.middle.down = true;
    }

    for (int i = 0; i < keyNums; i++)
    {
        keys[i].wasReleased = false;
        if (keys[i].wasPressed)
        {
            keys[i].wasPressed = false;
            keys[i].down = true;
            KEY_DOWN = true;
        }
    }

    mouseMotion = Vector2D();
}

void InputSystem::ClearState()
{
    for (int i = 0; i < keyNums; i++)
    {
        keys[i].wasPressed = false;
        keys[i].down = false;
        keys[i].wasReleased = false;
    }
}

int InputSystem::getId(SDL_Keycode key)
{
    // Se clampea porque teclas especiales como Shift tienen valores fuera del array
    return SDL_clamp(key, 0, keyNums - 1);
}

// UPDATE KEY STATE-------------------------------------------------------
void InputSystem::OnKeyDown(SDL_Keycode key)
{
    int i = getId(key);

    // SE PULSA POR PRIMERA VEZ
    if (!keys[i].wasPressed && !keys[i].down)
    {
        // std::cout << "111111\n";
        keys[i].wasPressed = true;
        KEY_WAS_PRESSED = true;
        this->lastChar = key;
    }

    // YA ESTBA PULSADA ==> QUEREMOS MANTENERLA
}

void InputSystem::OnKeyUp(SDL_Keycode key)
{
    // std::cout << "33333333333\n";
    int i = getId(key);
    keys[i].wasPressed = false;
    keys[i].down = false;
    keys[i].wasReleased = true;
    KEY_WAS_RELEASED = true;
}

// MOUSE

void InputSystem::setMouseMotion(Vector2D motion)
{
    this->mouseMotion = motion;
}

Vector2D InputSystem::getMouseMotion() const
{
    return mouseMotion;
}

void InputSystem::onMouseButtonDown(SDL_MouseButtonEvent buttonEvent)
{
    switch (buttonEvent.button)
    {
    case SDL_BUTTON_LEFT:
        if (!mouseButtonState.left.wasPressed && !mouseButtonState.left.down)
        {
            mouseButtonState.left.wasPressed = true;
        }
        break;
    case SDL_BUTTON_RIGHT:
        if (!mouseButtonState.right.wasPressed && !mouseButtonState.right.down)
        {
            mouseButtonState.right.wasPressed = true;
        }
        break;
    case SDL_BUTTON_MIDDLE:
        if (!mouseButtonState.middle.wasPressed && !mouseButtonState.middle.down)
        {
            mouseButtonState.middle.wasPressed = true;
        }
        break;
    default:
        break;
    }
}

void InputSystem::onMouseButtonUp(SDL_MouseButtonEvent buttonEvent)
{
    switch (buttonEvent.button)
    {
    case SDL_BUTTON_LEFT:
        mouseButtonState.left.down = false;
        mouseButtonState.left.wasPressed = false;
        mouseButtonState.left.wasReleased = true;
        break;
    case SDL_BUTTON_RIGHT:
        mouseButtonState.right.down = false;
        mouseButtonState.right.wasPressed = false;
        mouseButtonState.right.wasReleased = true;
        break;
    case SDL_BUTTON_MIDDLE:
        mouseButtonState.middle.down = false;
        mouseButtonState.middle.wasPressed = false;
        mouseButtonState.middle.wasReleased = true;
        break;
    default:
        break;
    }
}

// CONSULTA GLOBAL----------------------------
bool InputSystem::anyKeyWasPressed()
{
    return KEY_WAS_PRESSED;
}

bool InputSystem::anyKeyIsDown()
{
    return KEY_DOWN;
}

bool InputSystem::anyKeyWasReleased()
{
    return KEY_WAS_RELEASED;
}

// CONSULT KEY STATE------------------------------------------------------------
bool InputSystem::keyWasPressed(SDL_Keycode key)
{
    int i = getId(key);
    return keys[i].wasPressed;
}

bool InputSystem::isKeyDown(SDL_Keycode key)
{
    int i = getId(key);
    return keys[i].down;
}

bool InputSystem::keyWasReleased(SDL_Keycode key)
{
    int i = getId(key);
    return keys[i].wasReleased;
}

bool InputSystem::isMouseButtonDown(int button)
{
	switch (button)
	{
	case 0:
		return mouseButtonState.left.down;
		break;
	case 1:
		return mouseButtonState.right.down;
		break;
	case 2:
		return mouseButtonState.middle.down;
		break;
	default:
		return false;
		break;
	}
}

bool InputSystem::isMouseButtonPressed(int button)
{
	switch (button)
	{
	case 0:
		return mouseButtonState.left.wasPressed;
		break;
	case 1:
		return mouseButtonState.right.wasPressed;
		break;
	case 2:
		return mouseButtonState.middle.wasPressed;
		break;
	default:
		return false;
		break;
	}
}

bool InputSystem::isMouseButtonReleased(int button)
{
	switch (button)
	{
	case 0:
		return mouseButtonState.left.wasReleased;
		break;
	case 1:
		return mouseButtonState.right.wasReleased;
		break;
	case 2:
		return mouseButtonState.middle.wasReleased;
		break;
	default:
		return false;
		break;
	}
}

Vector2D InputSystem::getMousePosition()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return Vector2D(x, y);
}

char InputSystem::getLastKeyPressed()
{
    return lastChar;
}