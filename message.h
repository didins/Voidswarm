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

class Message
{
public:
    Message();
    Message(char[], int);
    Message(int ty, int t) { type = ty; tick = t; }
    Message(MsgStart d, int t) { tick = t; type = MSG_START; d_start = d; }
    Message(MsgClick d, int t) { tick = t; type = MSG_CLICK; d_click = d; }

    void toCString(char[], int&);
    void fromCString(char[], int);

    int getTick() { return tick; }
    int getType() { return type; }

    const MsgStart getStart() { return d_start; }
    const MsgClick getClick() { return d_click; }

    const static int LEN = 1024;
private:
    const static int DATA_LEN = 64;

    int tick;
    short type;

    union
    {
        char bin[DATA_LEN];
        MsgStart d_start;
        MsgClick d_click;
    } ;
};

#endif // MESSAGE_H