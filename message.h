#ifndef MESSAGE_H
#define MESSAGE_H

const short MSG_ENGINE = 1 << 10; // flag "da li je ovo poruka za engine"

const short MSG_START = 1;
struct MsgStart
{
    int player_i, n_players;
    MsgStart(int i, int n) { player_i = i; n_players = n; }
} ;

const short MSG_END = 2;
// nema data

const short MSG_HASH = 3;
struct MsgHash
{
    unsigned hash;
    MsgHash(int h) { hash = h; }
} ;

const short MSG_SET_TARGET = 1 | MSG_ENGINE;
struct MsgSetTarget
{
    int x, y;
    MsgSetTarget(int xx, int yy) { x = xx; y = yy; }
} ;

const short MSG_RESIZE = 2 | MSG_ENGINE;
struct MsgResize
{
    int delta;
    MsgResize(int d) { delta = d; }
} ;

class Message
{
public:
    Message();
    Message(unsigned char[], int);
    Message(int ty, int t) { type = ty; tick = t; }

    Message(MsgStart d, int t) { tick = t; type = MSG_START; d_start = d; }
    Message(MsgSetTarget d, int t) { tick = t; type = MSG_SET_TARGET; d_set_target = d; }
    Message(MsgResize d, int t) { tick = t; type = MSG_RESIZE; d_resize = d; }
    Message(MsgHash d, int t) { tick = t; type = MSG_HASH; d_hash = d; }

    void toCString(unsigned char[], int&);
    void fromCString(unsigned char[], int);

    void setSender(int s) { sender = s; }

    int getTick() const { return tick; }
    short getType() const { return type; }
    short getSender() const { return sender; }

    const MsgStart getStart() const { return d_start; }
    const MsgSetTarget getSetTarget() const { return d_set_target; }
    const MsgResize getResize() const { return d_resize; }
    const MsgHash getHash() const { return d_hash; }


    const static int LEN = 128;
private:
    const static int DATA_LEN = 64;

    unsigned tick;
    unsigned short type, sender;

    union
    {
        unsigned char bin[DATA_LEN];
        MsgStart d_start;
        MsgSetTarget d_set_target;
        MsgResize d_resize;
        MsgHash d_hash;
    } ;
};

bool operator<(Message a, Message b);

#endif // MESSAGE_H
