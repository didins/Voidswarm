#ifndef CLIENT_H
#define CLIENT_H

#include "communicator.h"
#include "engine.h"
#include <SFML/Graphics.hpp>
#include <queue>

namespace Client
{
    int id; // redni broj igraca
    const int N_CIRCLES = 5;

    const sf::Time TICK_DURATION = sf::milliseconds(40);
    const int TICK_GAP = 10; // 400ms for now

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
        int n_players = start.getStart().n_players;

        printf("Started!\n Player ID: %i\n", id);

        sf::RenderWindow window(sf::VideoMode(800, 600), ".voidswarm", sf::Style::Close);
        Engine engine(n_players);
        std::priority_queue<Message> messageBuffer;
        sf::Clock clock;

        unsigned lastHash;

        while(window.isOpen())
        {
            if(clock.getElapsedTime() > TICK_DURATION * (sf::Int64)engine.getTick())
            {
                engine.tick();
                if(!(engine.getTick() & 31))
                {
                    lastHash = engine.hash();
                    Message msg(MsgHash(lastHash), engine.getTick() + TICK_GAP);
                    comm.send(msg);
                }
            }

            Message msg;
            while(comm.receive(msg))
                messageBuffer.push(msg);

            while(!messageBuffer.empty() && messageBuffer.top().getTick() <= engine.getTick())
            {
                msg = messageBuffer.top();
                messageBuffer.pop();
                if(msg.getTick() != engine.getTick())
                    printf("[CLIENT] Received old message (%i) - ping too high!\n", engine.getTick() - msg.getTick());

                if(msg.getType() & MSG_ENGINE)
                    engine.process(msg);

                switch(msg.getType())
                {
                case MSG_START:
                    throw "MSG_START received; game already started";
                    break;

                case MSG_END:
                    return 0;
                    break;

                case MSG_HASH:
                    if(msg.getHash().hash != lastHash)
                        throw "Desync";
                }
            }

            sf::Event event;
            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();
                else if(event.type == sf::Event::MouseWheelMoved)
                {
                    Message msg(MsgResize(event.mouseWheel.delta), engine.getTick() + TICK_GAP);
                    comm.send(msg);
                }
                else if(event.type == sf::Event::MouseButtonPressed)
                {
                    Message msg(MsgSetTarget(event.mouseButton.x, event.mouseButton.y), engine.getTick() + TICK_GAP);
                    comm.send(msg);
                }
            }

            engine.draw(window);
            window.display();
        }

        comm.send(Message(MSG_END, 0));

        return 0;
    }
}

#endif // CLIENT_H
