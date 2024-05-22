#include <SFML/Graphics.hpp>

#include "state.h"

#include<string>

using namespace sf;

using std::string;

int main()
{

    RenderWindow window(VideoMode(400, 400), L"Новый проект", Style::Default);
    Clock clock;

    window.setVerticalSyncEnabled(true);

    State test("front", 400, 4, "./Animation/front.png");

    CircleShape shape(100.f, 3);
    shape.setPosition(100, 100);
    shape.setFillColor(Color::Magenta);

    float timer_to_test_anim = 0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
    
        clock.restart();
        time = time / 800;
        timer_to_test_anim += time;
        if (timer_to_test_anim >= test.getDuration()) {
            timer_to_test_anim = 0;
            test.nextFrame();
        }
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Blue);
        //window.draw(shape);
        window.draw(test.getSprite());
        window.display();
    }
    return 0;
}