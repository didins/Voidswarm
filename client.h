#ifndef CLIENT_H
#define CLIENT_H

#include "communicator.h"
#include <SFML/Graphics.hpp>

namespace Client
{
    int id; // redni broj igraca
    const int N_CIRCLES = 5;

    int main()
    {
        printf("Started client.\n");
        printf("Server IP: ");
        char ip[20];
        scanf(" %s", &ip);

        Communicator comm;
        comm.connectTo(ip, 53252);

        printf("Waiting for the game to start . . . ");

        Message start;
        while(start.getType() != MSG_START)
            while(!comm.receive(start)) ;
        id = start.getStart().player_i;

        printf("Started!\n Player ID: %i\n", id);

        sf::RenderWindow Game(sf::VideoMode(800, 600), ".voidswarm");
        sf::CircleShape circles[N_CIRCLES];
        for (int i=0; i<N_CIRCLES; i++)
            circles[i].setRadius(50);
        circles[1].setPosition(200, 200);
        circles[1].setFillColor(sf::Color::Blue);
        circles[2].setFillColor(sf::Color::Green);
        circles[3].setFillColor(sf::Color::Yellow);
        circles[4].setFillColor(sf::Color::Red);
        circles[5].setFillColor(sf::Color::White);
        sf::Vector2i localPos1;

        while (Game.isOpen())
        {
            Message move2;
            while(comm.receive(move2))
            {
                if(move2.getType() == MSG_CLICK)
                    circles[move2.getSender()].setPosition(move2.getClick().x-circles[move2.getSender()].getRadius(), move2.getClick().y-circles[move2.getSender()].getRadius());
                if(move2.getType() == MSG_WHEEL)
                    if(move2.getWheel().x) circles[move2.getSender()].setRadius(circles[move2.getSender()].getRadius()+5);
                    else circles[move2.getSender()].setRadius(circles[move2.getSender()].getRadius()-5);
            }

            sf::Event event;
            while (Game.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    Game.close();
                if (event.type == sf::Event::MouseWheelMoved)
                {
                    //if(event.mouseWheel.delta>0) circles[1].setRadius(circles[1].getRadius()+5);
                    //else circles[1].setRadius(circles[1].getRadius()-5);
                    Message resize1(MsgWheel(event.mouseWheel.delta>0), 0);
                    comm.send(resize1);
                }
                if(event.type == sf::Event::MouseButtonPressed)
                {
                    //localPos1=sf::Mouse::getPosition(Game);
                    //circles[1].setPosition(localPos1.x-circles[1].getRadius(), localPos1.y-circles[1].getRadius());
                    Message move1(MsgClick(localPos1.x, localPos1.y), 0);
                    comm.send(move1);
                }
            }

            Game.clear();
            Game.draw(circles[1]);
            Game.draw(circles[2]);
            Game.display();
        }

        return 0;
    }
}

#endif // CLIENT_H
