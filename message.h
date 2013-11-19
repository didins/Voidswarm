#ifndef MESSAGE_H
#define MESSAGE_H

const short MSG_ENGINE = 1 << 10; // flag "da li je ovo poruka za engine"

const short MSG_START = 1;
struct MsgStart
{
    int player_i;
    MsgStart(int i) { player_i = i; }
} ;

const short MSG_END = 2;
// nema data

const short MSG_CLICK = 1 | MSG_ENGINE;
struct MsgClick
{
    int x, y;
    MsgClick(int xx, int yy) { x = xx; y = yy; }
} ;

const short MSG_WHEEL = 2 | MSG_ENGINE;
struct MsgWheel
{
    int x;
    MsgWheel(int xx) { x = xx; }
} ;

class Message
{
public:
    Message();
    Message(char[], int);
    Message(int ty, int t) { type = ty; tick = t; }
    Message(MsgStart d, int t) { tick = t; type = MSG_START; d_start = d; }
    Message(MsgClick d, int t) { tick = t; type = MSG_CLICK; d_click = d; }
    Message(MsgWheel d, int t) { tick = t; type = MSG_WHEEL; d_wheel = d; }

    void toCString(char[], int&);
    void fromCString(char[], int);

    void setSender(int s) { sender = s; }

    int getTick() { return tick; }
    short getType() { return type; }
    short getSender() { return sender; }

    const MsgStart getStart() { return d_start; }
    const MsgClick getClick() { return d_click; }
    const MsgWheel getWheel() { return d_wheel; }


    const static int LEN = 1024;
private:
    const static int DATA_LEN = 64;

    int tick;
    short type, sender;

    union
    {
        char bin[DATA_LEN];
        MsgStart d_start;
        MsgClick d_click;
        MsgWheel d_wheel;
    } ;
};

#endif // MESSAGE_H
