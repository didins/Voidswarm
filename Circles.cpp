#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow Game(sf::VideoMode(800, 600), ".voidswarm");
    sf::CircleShape Circle1(50.f);
    sf::CircleShape Circle2(50.f);
    Circle2.setPosition(200, 200);
    Circle1.setFillColor(sf::Color::Blue);
    Circle2.setFillColor(sf::Color::Green);
    sf::Vector2i localPos1;
    sf::Vector2i localPos2;
    sf::Event::MouseWheelEvent Wheel_Event;
    Wheel_Event.delta=0;
    while (Game.isOpen())
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            localPos1=sf::Mouse::getPosition(Game);
            Circle1.setPosition(localPos1.x-Circle1.getRadius(), localPos1.y-Circle1.getRadius());
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            localPos2=sf::Mouse::getPosition(Game);
            Circle2.setPosition(localPos2.x-Circle2.getRadius(), localPos2.y-Circle1.getRadius());
        }

        sf::Event event;
        while (Game.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Game.close();
            if (event.type == sf::Event::MouseWheelMoved)
            {
                if(event.mouseWheel.delta>0) Circle1.setRadius(Circle1.getRadius()+5);
                else Circle1.setRadius(Circle1.getRadius()-5);
            }
        }

        Game.clear();
        Game.draw(Circle1);
        Game.draw(Circle2);
        Game.display();
    }

    return 0;
}
