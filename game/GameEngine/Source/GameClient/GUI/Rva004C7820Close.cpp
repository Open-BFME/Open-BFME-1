// cl: /O2
// Exit the download UI and send a message unless GameLogic is in state eight.
class GameEngine;
class MessageStream;
class GameLogic;
extern GameEngine *TheGameEngine;
extern MessageStream *TheMessageStream;
extern GameLogic *TheGameLogic;
void closeDownloadWindow();

struct Rva004C7820Slot13
{
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6(); virtual void slot7(); virtual void slot8();
    virtual void slot9(); virtual void slot10(); virtual void slot11();
    virtual void slot12();
    virtual void send(int value);
};

void Rva004C7820Close()
{
    reinterpret_cast<Rva004C7820Slot13 *>(TheGameEngine)->send(1);
    closeDownloadWindow();
    if (*(int *)((char *)TheGameLogic + 0x10C) != 8)
        reinterpret_cast<Rva004C7820Slot13 *>(TheMessageStream)->send(0x1D);
}
