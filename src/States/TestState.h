#pragma once
#include "Engine/StateMachine/State.h"
#include "StateMachine/Statemachine.h"
#include "MainGame.h"

class TestState : public State {
public:
    TestState(Statemachine* st,sf::RenderWindow& window);

    void update(float deltaTime) override;

    void draw(sf::RenderWindow &window) override;
    int score=0;
    void inputs() override;
    ~TestState();
private:
    sf::Font font;
    sf::Text text;
    sf::RectangleShape rect;
    sf::RenderWindow* m_window;
};

