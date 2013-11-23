#include "communicator.h"

Communicator::Communicator()
{
    connected = false;
}

void Communicator::waitForConnection(int port)
{
    sf::TcpListener l;
    if(l.listen(port) != sf::Socket::Done)
        throw "Listening failed";
    if(l.accept(socket) != sf::Socket::Done)
        throw "Cannot accept client";
    socket.setBlocking(false);
}

void Communicator::connectTo(char *ip, int port)
{
    if(socket.connect(ip, port) != sf::Socket::Done)
        throw "Cannot connect to server";
    socket.setBlocking(false);
}

void Communicator::send(Message m)
{
    unsigned char data[m.LEN];
    int len;
    m.toCString(data, len);
    sf::Socket::Status s = socket.send(data, len);
    if(s != sf::Socket::Done)
    {
        if(s == sf::Socket::Disconnected)
            throw "Cannot send data: socket is disconnected";
        else if(s == sf::Socket::Error)
            throw "Cannot send data: unexpected error";
        else throw "Cannot send data";
    }
}

bool Communicator::receive(Message &m)
{
    unsigned char data[m.LEN];
    int len;
    sf::Socket::Status s = socket.receive(data, (std::size_t)m.LEN, (std::size_t&)len);
    if(s == sf::Socket::NotReady)
        return false;
    else if(s != sf::Socket::Done)
    {
        if(s == sf::Socket::Disconnected)
            throw "Cannot receive data: socket is disconnected";
        else if(s == sf::Socket::Error)
            throw "Cannot receive data: unexpected error";
        else throw "Cannot receive data";
    }
    m.fromCString(data, len);
    return true;
}
