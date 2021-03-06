//
// Created by micha on 10.06.2020.
//

#include "Player.h"

void Player::start(sf::RenderWindow& window, std::string ship, std::string gun_script,std::string particle1, std::string particle2)
{
    sprite->setSize({window.getSize().x*0.1f,window.getSize().x*0.1f});
    sprite->load(ship);
    health->start(1000);
    effect->start(1000,{250, 130, 0},{250, 25, 0},3.f,2.f);
    effect->gravity_direction = {0.f,5.f};
    effect->setParticleTexture(particle1);
    effect2->start(100,{196, 196, 196},{196, 196, 196},3.f,2.f);
    effect2->gravity_direction = {0.f,6.f};
    effect2->offset = {sprite->getSize().x/2,sprite->getSize().y};
    effect->offset = {sprite->getSize().x/2,sprite->getSize().y};
    effect2->setParticleTexture(particle2);
    healthbar->start();
    energycore->start();
    afterburner->start(50,{194, 244, 255},{36, 217, 255},0.06f,0.05f);
    afterburner->offset = {sprite->getSize().x/2,sprite->getSize().y/2.f};
    afterburner->gravity_direction={0.f,0.f};
    afterburner->gravity = 2000.f;
    afterburner->active = false;
    hitbox->start(sprite->getSize());
    aura->start();
    invmode->start(5.f);
    invmode->trigger();
    gun->loadGun(gun_script,window);
    gun->offset = {sprite->getSize().x/2.f,0.f};
    smoke->load("data/AnimationAtlas/explosion.png");
    smoke->setSize({sprite->getSize().x,sprite->getSize().y});
    smoke_animation->start(smoke);
    smoke_animation->configureTextureAtlas("data/AnimationAtlas/explosion.png",{5,5},0.1f,0);
    health_text->start(sprite->getSize().y*0.2f,"Hello","data/Fonts/Kenney Rocket.ttf",sf::Color::Red);
}
