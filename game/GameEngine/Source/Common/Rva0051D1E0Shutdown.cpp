// ?Rva0051D1E0Shutdown@@YAH_NPAX0@Z
// Reset the display and game services before returning the next display state.
typedef bool Bool;

class WindowManager
{
public:
    void unidentified_000144bb(int value);
};

class Shell
{
public:
    void hide(Bool value);
};

class Display
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot0A() = 0;
    virtual void slot0B() = 0;
    virtual void slot0C() = 0;
    virtual void slot0D() = 0;
    virtual void slot0E() = 0;
    virtual void slot0F() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot1A() = 0;
    virtual void slot1B() = 0;
    virtual void slot1C() = 0;
    virtual void slot1D() = 0;
    virtual void slot1E() = 0;
    virtual void slot1F() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual void slot2A() = 0;
    virtual void slot2B() = 0;
    virtual void slot2C() = 0;
    virtual void slot2D() = 0;
    virtual void slot2E() = 0;
    virtual void slot2F() = 0;
    virtual void slot30() = 0;
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual void slot33() = 0;
    virtual void slot34() = 0;
    virtual void slot35() = 0;
    virtual void slot36() = 0;
    virtual void slot37() = 0;
    virtual void slot38() = 0;
    virtual void slot39() = 0;
    virtual void slot3A() = 0;
    virtual void slot3B() = 0;
    virtual Bool slot3C() = 0;

    char m_pad[0x10c];
    Bool m_displayFlag;
};

class VideoPlayer
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot0A() = 0;
    virtual void slot0B() = 0;
    virtual void slot0C() = 0;
    virtual void slot0D() = 0;
    virtual void slot0E() = 0;
    virtual void slot0F() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
};

class BfmeHost961
{
public:
    void bfmeFallback961(int first, int second);
};

class GameLogic : public BfmeHost961
{
};

class Gen_00609320
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04(int value) = 0;
};

class GameMessage
{
public:
    void appendBooleanArgument(Bool value);
};

class MessageStream
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot0A() = 0;
    virtual void slot0B() = 0;
    virtual void slot0C() = 0;
    virtual GameMessage *appendMessage(int type) = 0;
};

extern WindowManager *g_theWindowManager;
extern Shell *TheShell;
extern Display *TheDisplay;
extern VideoPlayer *TheVideoPlayer;
extern GameLogic *TheBfmeGameLogic;
extern Gen_00609320 *g_bfmeStateDF;
extern MessageStream *TheMessageStream;

int Rva0051D1E0Shutdown(Bool mode, void *unused, Bool enabled)
{
    int result = 1;

    if (enabled)
    {
        g_theWindowManager->unidentified_000144bb(-1);
        TheShell->hide(true);
        TheDisplay->m_displayFlag = true;
        TheVideoPlayer->slot17();
        TheBfmeGameLogic->bfmeFallback961(0, 0);
        g_bfmeStateDF->slot04(result);
        GameMessage *message = TheMessageStream->appendMessage(0x1f);
        if (message != 0)
            message->appendBooleanArgument(mode);
    }
    else if (!TheDisplay->slot3C())
    {
        result = 3;
    }
    return result;
}
