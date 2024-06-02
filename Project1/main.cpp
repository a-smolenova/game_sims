#include <SFML/Graphics.hpp>

#include"entity.h"
#include"camera.h"

#include<string>
#include<iostream>


using namespace sf;

using std::string;

//https://kychka-pc.ru/sfml/urok-6-sfml-rabota-so-vremenem-obyazatelnaya-chast-sfml.html

RenderWindow window(VideoMode(800, 800), L"Ќовый проект", Style::Default);
Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

Camera camera;


void keyboard(sf::Event e ) {
    if (e.KeyPressed) {
        int a = 0;
    }
}

void drawAll(std::vector<Entity>& objects) {
    for (int i = 0; i < objects.size(); ++i) {
        
        objects[i]._animator.draw();
    }
}

void updateSprites(std::vector<Entity>& objects) {
    for (int i = 0; i < objects.size(); ++i) {
        objects[i]._animator.update();
    }
}

int main()
{
    Clock clock;

    window.setVerticalSyncEnabled(true);

    State test("front", 400, 4, "./Animation/front.png");
    State test1("back", 400, 4, "./Animation/back.png");


    Entity player(1,0,window);
    Entity player1(1,0, window);
    player._animator.addState(test);
    player1._animator.addState(test1);

    float timer_to_test_anim = 0;

    
    Vector2i mousePixelPos = Mouse::getPosition(window);//забираем коорд курсора
    
    player.move(100, 100);
    player1.move(0, 100);
    bool _pressed = false;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее врем€ в микросекундах
    
        clock.restart();
        time = time / 1000;
        timer_to_test_anim += time;
        //update mouse position
        mousePixelPos = Mouse::getPosition(window);
        mousePos = window.mapPixelToCoords(mousePixelPos);
       // std::cout << mousePos.x << " - " << mousePos.y << "\n";
        if (timer_to_test_anim >= 100) {
            timer_to_test_anim = 0;
            player._animator.update();
            player.move(0,1);
            player1._animator.update();
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
                std::cout << 1;
                camera.setLastPosition(mousePixelPos);
                _pressed = true;

            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                camera.setLastPosition(mousePixelPos);
                _pressed = false;
            }
            if (event.type == sf::Event::MouseWheelMoved)
            {
                std::cout << event.mouseWheel.delta << '\n';
                camera.updateZoom(event.mouseWheel.delta);
            }
        }

        window.setView(camera.getView());

        window.clear(Color::Blue);

        player._animator.draw();
        player1._animator.draw();
        //drawAll();
        if(_pressed)
            camera.update(mousePixelPos);

        window.display();
    }
    return 0;
}