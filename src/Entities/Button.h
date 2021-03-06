#pragma once
#include "Entity.h"
#include "MouseOver.h"
#include "SimpleSprite.h"
#include "Text.h"
#include "support/color_loader.h"

class Button : public Entity{
public:
    Button();

    void start(sf::RenderWindow& window,sf::Vector2f pos, sf::Vector2f size,std::string font, std::string background,std::string buttonText);
    void start(sf::RenderWindow& window,color_loader* loader,sf::Vector2f pos, sf::Vector2f size,std::string font, std::string background,std::string buttonText);
    void setColorLoader(color_loader* loader);

    void update(float deltaTime);

    void draw(sf::RenderWindow &window) override;

    std::shared_ptr<MouseOver> mouse;

    void setTextColor(sf::Color newCol)
    {
        text->setColor(newCol);
    }

    bool leftClicked_t=false;
    bool rightClicked_t= false;
    bool hover= false;

    bool change_on_hover = true;


    void setDebounceTime(float newTime)
    {
        debouncetime = newTime;
    }
    void setTextToMax();

    void setText(std::string text);
private:
    std::shared_ptr<SimpleSprite> body;
    float timer=0.f;
    float debouncetime=0.2f;
    std::shared_ptr<Text> text;
    color_loader* colorLoader = nullptr;
};


