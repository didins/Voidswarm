#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <SFML/Network.hpp>
#include "message.h"

class Communicator
{
public:
    Communicator();

    void waitForConnection(int);
    void connectTo(char*, int);

    void send(Message);
    bool receive(Message&);
private:
    sf::TcpSocket socket;
    bool connected;
};

#endif // COMMUNICATOR_H
