#include "EndState.h"
#include "../EC/Entity.h"
#include "../EC/Components/TextRenderer.h"
#include "../EC/Components/Button.h"
#include "../SDLUtils/SDLApp.h"

EndState::EndState(SDLApp *app, uint8_t playerScore, uint8_t enemyScore) : GameState(app)
{
    createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2), Vector2D(1, 1), "menuBg");

    std::string endExt;
    if(playerScore > enemyScore)
    {
        endExt = "Ganaste :D";
    }
    else if(playerScore < enemyScore)
    {
        endExt = "Perdiste :(";
    }
    else
    {
        endExt = "Empate!";
    }

    Entity *text = createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2 - 50), Vector2D(1, 1), "button");
    text->addComponent(new TextRenderer(endExt, "toonFont", 72));

    Entity *returnButton = createEntity(Vector2D(app->getWidth() / 2, app->getHeight() / 2 + 50), Vector2D(0.5, 0.75));
    returnButton->addComponent(new Button(app->getTexture("button"), "Volver al Menu", "toonFont", 36, [this]()
                                          { startExitTransitionTimer(popState); }));

    addTransitioner(text);
    addTransitioner(returnButton);
}

EndState::~EndState() {}

void EndState::onStateEnter()
{
    GameState::onStateEnter();

    NetworkMessage logout = NetworkMessage(LOGOUT);
    this->sendNetworkMessage(logout);
}