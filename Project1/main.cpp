#include <SFML/Graphics.hpp>

#include"entity.h"
#include"camera.h"
#include"map.h"
#include"sim.h"

#include<string>
#include<iostream>


using namespace sf;

using std::string;

//https://kychka-pc.ru/sfml/urok-6-sfml-rabota-so-vremenem-obyazatelnaya-chast-sfml.html

RenderWindow window(VideoMode(800, 800), L"Новый проект", Style::Default);
Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

std::vector<Sim> all_sim;

Camera camera;

Map my_map_l1("Map/start.txt", window);


void keyboard(sf::Event e ) {
    if (e.KeyPressed) {
        if (e.key.code == Keyboard::A) {
            all_sim[0].setTarget(Vector2f(3 * 360, 2 * 360), 'f');
            all_sim[0].changeSimState(_state::Hungry);
        }
        if (e.key.code == Keyboard::B) {
            all_sim[1].setTarget(Vector2f(3 * 360, 2 * 360), 'f');
            all_sim[1].changeSimState(_state::Hungry);
        }
    }
}

void updateAllSimPosition() {
    for (int i = 0; i < all_sim.size(); ++i) {
        if (all_sim[i].getState() == _state::Hungry) {
            if (!all_sim[i].hasTarget()) {
                all_sim[i].setPath(my_map_l1.pathSearch(all_sim[i].x + 360 * int(all_sim[i].getAnimState() == 2), all_sim[i].y + 360 * int(all_sim[i].getAnimState() == 0),
                    all_sim[i].getTargetPos().x, all_sim[i].getTargetPos().y));
            }
            all_sim[i].move();
        }
        else {


            if (!my_map_l1.isColide(all_sim[i].x - (1 - 2 * int(all_sim[i].getAnimState() == 3)) * 10 * int(all_sim[i].getAnimState() == 2 || all_sim[i].getAnimState() == 3),
                all_sim[i].y - (1 - 2 * int(all_sim[i].getAnimState() == 0)) * 10 * int(all_sim[i].getAnimState() == 0 || all_sim[i].getAnimState() == 1),
                all_sim[i]._animator.getSprite().getTextureRect().getSize()))
            {
                all_sim[i].move();
            }
            else {
                all_sim[i].nextState();
            }
        }
    }
}

void drawAllSim() {
    for (int i = 0; i < all_sim.size(); ++i) {
        
        all_sim[i]._animator.draw();
    }
}

void updateAllSimSprites() {
    for (int i = 0; i < all_sim.size(); ++i) {
        all_sim[i]._animator.update();
    }
}

int main()
{
    Clock clock;
    window.setVerticalSyncEnabled(true);

    State front("front", 400, 4, "./Animation/front.png");
    State back("back", 400, 4, "./Animation/back.png");

    State right("right", 400, 4, "./Animation/right.png");
    State left("right", 400, 4, "./Animation/left.png");

    all_sim.push_back(Sim(0, 0, window));
    all_sim.push_back(Sim(0, 0, window));

    all_sim[0]._animator.addState(front);
    all_sim[0]._animator.addState(back);
    all_sim[0]._animator.addState(right);
    all_sim[0]._animator.addState(left);
    all_sim[1]._animator.addState(front);
    all_sim[1]._animator.addState(back);
    all_sim[1]._animator.addState(right);
    all_sim[1]._animator.addState(left);


    float timer_to_test_anim = 0;

    
    sf::View def_view = window.getView();

    Vector2i mousePixelPos = Mouse::getPosition(window);//забираем коорд курсора
    
    //all_sim[0].move(550, 550);
    // //all_sim[1].move(550, 550);
    all_sim[0].move(360,360);
    all_sim[1].move(720, 720);
    
    bool _pressed = false;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
    
        clock.restart();
        time = time / 1000;
        timer_to_test_anim += time;
        //update mouse position
        mousePixelPos = Mouse::getPosition(window);
        mousePos = window.mapPixelToCoords(mousePixelPos);
       // обновить кадр анимаций
        if (timer_to_test_anim >= 100) {
            timer_to_test_anim = 0;
            updateAllSimSprites();
            updateAllSimPosition();
           // all_sim[0].move(0, 10);
        }
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                keyboard(event);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                camera.setLastPosition(mousePixelPos);
                _pressed = true;

            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                camera.setLastPosition( Vector2f(mousePos.x - mousePixelPos.x * camera.getView().getSize().x / 800 + camera.getView().getSize().x/2, int(mousePos.y) - mousePixelPos.y * camera.getView().getSize().x / 800 + camera.getView().getSize().y/2));
                _pressed = false;
            }
            if (event.type == sf::Event::MouseWheelMoved)
            {
                camera.updateZoom(event.mouseWheel.delta);
            }
        }

        window.clear(Color::Blue);
        my_map_l1.draw_map();
        drawAllSim();
        window.setView(camera.getView());

        if (_pressed)
            camera.update(mousePixelPos);
        else
            camera.update();
        window.display();
    }
    return 0;
}