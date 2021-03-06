#include "MainGame.h"

MainGame::MainGame(Statemachine* st,sf::RenderWindow &window) : State(st) {
    switch (difficulty) {
        case 0:
            max_speed_var = 200;
        case 1:
            max_speed_var = 300;
        case 2:
            max_speed_var = 400;
    }
    window.setMouseCursorVisible(false);
    newBackground.start(window,"data/Background/space-1.png");
    newPlanet.start(window);
    font.loadFromFile("data/Fonts/Kenney Rocket.ttf");
    scoreText.setFont(font);
    trailtext.setFont(font);
    scoreText.setCharacterSize(window.getSize().x*0.04f);
    trailtext.setCharacterSize(window.getSize().x*0.04f);
    trailtext.setPosition(0.f,window.getSize().x*0.06f);
    scoreText.setFillColor(sf::Color::Yellow);
    trailtext.setFillColor(sf::Color::Magenta);
    window.setMouseCursorVisible(false);
    m_window = &window;
    player.start(window,"data/Ships/playerShip3_green.png","data/Scripts/shotgun.json","data/Bullets/laserRed12.png","data/Bullets/laserGreen12.png");
    coin.start(Coins::CoinType::BRONZE,window);
    shield.start("data/Drops/shield_silver.png",{window.getSize().x*0.07f,window.getSize().x*0.07f},50.f);
    health.start("data/Drops/powerupred_bolt.png",{window.getSize().x*0.07f,window.getSize().x*0.07f},50.f);
    health.transform->setX(rand()%window.getSize().x);
    shield.transform->setX(rand()%window.getSize().x);

    for(auto& e:allEnemies)
    {
        e.start(window,"data/AnimationAtlas/asteroid_grey_atlas.png","data/Particles/meteorBrown_tiny2.png");
        e.transform->setX(rand()%window.getSize().x);
    }
}

MainGame::~MainGame() {
    std::cout << "Main Game goes out of scope" << std::endl;
}


void MainGame::update(float deltaTime) {

    newPlanet.update(deltaTime);
    player.update(deltaTime);
    player.lateUpdate(deltaTime);
    coin.update(deltaTime);

    if(coin.transform->getY()>m_window->getSize().y)
    {
        coin.transform->setPosition(rand()%m_window->getSize().x,0.f);
    }

    if(coin.hitbox->AABBCollisionTest(player.hitbox))
    {
        coin.transform->setPosition(rand()%m_window->getSize().x,0.f);
        player.cash+=coin.getValue();
        player.gun->restockAmmo(10);
    }
    if(player.transform->getY()<0.f || player.transform->getY()>m_window->getSize().y ||
    player.transform->getX()<0.f ||player.transform->getX()>m_window->getSize().x)
        player.health->inflictDamagePercent(1.f);

    for(auto& e:allEnemies)
    {
        e.update(deltaTime);

        player.gun->check_for_hitbox(e.hitbox,e.health);


        if(!player.invmode->isInvisible())
            if(e.hitbox->AABBCollisionTest(player.hitbox))
            {
                e.transform->setPosition(rand()%m_window->getSize().x,0.f);
                player.health->inflictDamagePercent(25);
            }
        if(e.transform->getY()>m_window->getSize().y || !e.health->isAlife())
        {
            e.transform->setPosition(rand()%m_window->getSize().x,0.f);
            e.mover->speed=getAddSpeed(score,max_speed_var,startSpeed);
            e.health->rechargePercent(100);
            score++;
        }
    }



    health.update(deltaTime);
    if(health.hitbox->AABBCollisionTest(player.hitbox))
    {
        player.health->rechargePercent(10);
        health.transform->setPosition(rand()%m_window->getSize().x,0.f);
    }

    if(health.transform->getY()>m_window->getSize().y*3) //gets reset very late
    {
        health.transform->setPosition(rand()%m_window->getSize().x,-rand()%500);
    }

    shield.update(deltaTime);
    if(shield.transform->getY()>m_window->getSize().y)
        shield.transform->setPosition(rand()%m_window->getSize().x,-rand()%1000);
    if(shield.hitbox->AABBCollisionTest(player.hitbox))
    {
        player.invmode->trigger();
        shield.transform->setPosition(rand()%m_window->getSize().x,-rand()%1000);
    }
    player.aura->active = player.invmode->isInvisible();
    player.afterburner->active =  player.invmode->isInvisible();
    player.smoke->active = player.health->getHealthPercent()<10.f;

    scoreText.setString("Score:"+std::to_string(score)+ " Cash: "+std::to_string(player.cash));
    //player.health_text->setText("Health: "+ std::to_string(player.health->getHealthPercent())+ "%");
    player.health_text->setText("AMMO: "+ std::to_string(player.gun->getAmmo()));
    if(!player.health->isAlife())
    {
        auto s = std::make_shared<TestState>(stm,*m_window);
        s->score = score;
        s->name = name;
        s->dif = difficulty;
        stm->setNextState(s);
    }

}

void MainGame::draw(sf::RenderWindow &window) {
    window.clear();

    newBackground.draw(window);
    newPlanet.draw(window);
    player.draw(window);

    for(auto& e:allEnemies)
    {
        e.draw(window);
    }

    health.draw(window);
    shield.draw(window);
    coin.draw(window);
    window.draw(scoreText);
    window.draw(trailtext);
    window.display();

    sf::Event e;
    while (window.pollEvent(e))
        if(e.type == sf::Event::Closed)
            window.close();

}

void MainGame::inputs() {
    player.transform->setX(sf::Mouse::getPosition(*m_window).x);
    player.transform->setY(sf::Mouse::getPosition(*m_window).y);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        m_window->close();
}



float MainGame::getAddSpeed(int stage, float max_speed_control, float offset) {
    return offset+log10(stage)*max_speed_control;
}




