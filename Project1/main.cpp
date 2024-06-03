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

Map my_map("Map/start.txt", window);


void keyboard(sf::Event e ) {
    if (e.KeyPressed) {
        int a = 0;
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
    all_sim[1]._animator.addState(back);


    float timer_to_test_anim = 0;

    
    sf::View def_view = window.getView();

    Vector2i mousePixelPos = Mouse::getPosition(window);//забираем коорд курсора
    
    all_sim[0].move(100, -100);
    all_sim[1].move(0, 100);
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
            all_sim[0].move(0, 10);
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

        //std::cout << int(mousePos.x) % 800 + 400 << " - " << int(mousePos.y) % 800 + 400 << "\n";

        std::cout << mousePixelPos.x*camera.getView().getSize().x/800 << " - " << mousePixelPos.y * camera.getView().getSize().x / 800 << "\n";

        window.clear(Color::Blue);
        my_map.draw_map();
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