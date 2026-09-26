// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/campaignmanagerascii /Igame/Libraries/Source/WWVegas/WWLib
// Address-derived owner kept until the caller evidence is integrated.

#include "Common/AsciiString.h"

#define BFME_VOID_SLOT(n) virtual void slot##n() = 0;

class InGameUI
{
public:
    BFME_VOID_SLOT(0)  BFME_VOID_SLOT(1)  BFME_VOID_SLOT(2)  BFME_VOID_SLOT(3)
    BFME_VOID_SLOT(4)  BFME_VOID_SLOT(5)  BFME_VOID_SLOT(6)  BFME_VOID_SLOT(7)
    BFME_VOID_SLOT(8)  BFME_VOID_SLOT(9)  BFME_VOID_SLOT(10) BFME_VOID_SLOT(11)
    BFME_VOID_SLOT(12) BFME_VOID_SLOT(13) BFME_VOID_SLOT(14) BFME_VOID_SLOT(15)
    BFME_VOID_SLOT(16) BFME_VOID_SLOT(17) BFME_VOID_SLOT(18) BFME_VOID_SLOT(19)
    BFME_VOID_SLOT(20) BFME_VOID_SLOT(21) BFME_VOID_SLOT(22) BFME_VOID_SLOT(23)
    BFME_VOID_SLOT(24) BFME_VOID_SLOT(25) BFME_VOID_SLOT(26) BFME_VOID_SLOT(27)
    BFME_VOID_SLOT(28) BFME_VOID_SLOT(29) BFME_VOID_SLOT(30) BFME_VOID_SLOT(31)
    BFME_VOID_SLOT(32) BFME_VOID_SLOT(33) BFME_VOID_SLOT(34) BFME_VOID_SLOT(35)
    BFME_VOID_SLOT(36) BFME_VOID_SLOT(37) BFME_VOID_SLOT(38) BFME_VOID_SLOT(39)
    BFME_VOID_SLOT(40) BFME_VOID_SLOT(41) BFME_VOID_SLOT(42) BFME_VOID_SLOT(43)
    BFME_VOID_SLOT(44) BFME_VOID_SLOT(45) BFME_VOID_SLOT(46) BFME_VOID_SLOT(47)
    BFME_VOID_SLOT(48) BFME_VOID_SLOT(49) BFME_VOID_SLOT(50) BFME_VOID_SLOT(51)
    BFME_VOID_SLOT(52) BFME_VOID_SLOT(53) BFME_VOID_SLOT(54) BFME_VOID_SLOT(55)
    BFME_VOID_SLOT(56) BFME_VOID_SLOT(57) BFME_VOID_SLOT(58) BFME_VOID_SLOT(59)
    BFME_VOID_SLOT(60) BFME_VOID_SLOT(61) BFME_VOID_SLOT(62) BFME_VOID_SLOT(63)
    BFME_VOID_SLOT(64) BFME_VOID_SLOT(65) BFME_VOID_SLOT(66) BFME_VOID_SLOT(67)
    BFME_VOID_SLOT(68) BFME_VOID_SLOT(69) BFME_VOID_SLOT(70) BFME_VOID_SLOT(71)
    BFME_VOID_SLOT(72) BFME_VOID_SLOT(73) BFME_VOID_SLOT(74) BFME_VOID_SLOT(75)
    BFME_VOID_SLOT(76) BFME_VOID_SLOT(77) BFME_VOID_SLOT(78) BFME_VOID_SLOT(79)
    BFME_VOID_SLOT(80) BFME_VOID_SLOT(81) BFME_VOID_SLOT(82) BFME_VOID_SLOT(83)
    virtual void slot84(int) = 0;
    virtual bool slot85() = 0;
};

class Display
{
public:
    BFME_VOID_SLOT(0)  BFME_VOID_SLOT(1)  BFME_VOID_SLOT(2)  BFME_VOID_SLOT(3)
    BFME_VOID_SLOT(4)  BFME_VOID_SLOT(5)  BFME_VOID_SLOT(6)  BFME_VOID_SLOT(7)
    BFME_VOID_SLOT(8)  BFME_VOID_SLOT(9)  BFME_VOID_SLOT(10) BFME_VOID_SLOT(11)
    BFME_VOID_SLOT(12) BFME_VOID_SLOT(13) BFME_VOID_SLOT(14) BFME_VOID_SLOT(15)
    BFME_VOID_SLOT(16) BFME_VOID_SLOT(17) BFME_VOID_SLOT(18) BFME_VOID_SLOT(19)
    BFME_VOID_SLOT(20) BFME_VOID_SLOT(21) BFME_VOID_SLOT(22) BFME_VOID_SLOT(23)
    BFME_VOID_SLOT(24) BFME_VOID_SLOT(25) BFME_VOID_SLOT(26) BFME_VOID_SLOT(27)
    BFME_VOID_SLOT(28) BFME_VOID_SLOT(29) BFME_VOID_SLOT(30) BFME_VOID_SLOT(31)
    BFME_VOID_SLOT(32) BFME_VOID_SLOT(33) BFME_VOID_SLOT(34) BFME_VOID_SLOT(35)
    BFME_VOID_SLOT(36) BFME_VOID_SLOT(37) BFME_VOID_SLOT(38) BFME_VOID_SLOT(39)
    BFME_VOID_SLOT(40) BFME_VOID_SLOT(41) BFME_VOID_SLOT(42) BFME_VOID_SLOT(43)
    BFME_VOID_SLOT(44) BFME_VOID_SLOT(45) BFME_VOID_SLOT(46) BFME_VOID_SLOT(47)
    BFME_VOID_SLOT(48) BFME_VOID_SLOT(49) BFME_VOID_SLOT(50) BFME_VOID_SLOT(51)
    BFME_VOID_SLOT(52) BFME_VOID_SLOT(53) BFME_VOID_SLOT(54) BFME_VOID_SLOT(55)
    BFME_VOID_SLOT(56) BFME_VOID_SLOT(57) BFME_VOID_SLOT(58) BFME_VOID_SLOT(59)
    BFME_VOID_SLOT(60) BFME_VOID_SLOT(61) BFME_VOID_SLOT(62) BFME_VOID_SLOT(63)
    BFME_VOID_SLOT(64) BFME_VOID_SLOT(65) BFME_VOID_SLOT(66) BFME_VOID_SLOT(67)
    BFME_VOID_SLOT(68) BFME_VOID_SLOT(69) BFME_VOID_SLOT(70) BFME_VOID_SLOT(71)
    BFME_VOID_SLOT(72) BFME_VOID_SLOT(73) BFME_VOID_SLOT(74) BFME_VOID_SLOT(75)
    BFME_VOID_SLOT(76)
    virtual bool slot77() = 0;
    virtual bool slot78() = 0;
};

class Mouse
{
public:
    BFME_VOID_SLOT(0)  BFME_VOID_SLOT(1)  BFME_VOID_SLOT(2)  BFME_VOID_SLOT(3)
    BFME_VOID_SLOT(4)  BFME_VOID_SLOT(5)  BFME_VOID_SLOT(6)  BFME_VOID_SLOT(7)
    BFME_VOID_SLOT(8)  BFME_VOID_SLOT(9)  BFME_VOID_SLOT(10) BFME_VOID_SLOT(11)
    BFME_VOID_SLOT(12) BFME_VOID_SLOT(13)
    virtual void slot14(int) = 0;
};

#undef BFME_VOID_SLOT

class GameWindowTransitionsHandler
{
public:
    bool isFinished();
};

class Shell
{
public:
    void showShell(bool);
    void push(AsciiString, bool);
};

class BfmeThingFGA
{
public:
    int bfmeGoFGA();
    char m_pad[0x69];
    char m_flag;
};

class Rva0005C5E0
{
public:
    int isEither() const;
    char m_lead[0x10c];
    int m_state;
};

class BfmeGameLogicPause
{
public:
    void setGamePaused(bool, int, bool);
};

class GameLogicPortraitShim
{
public:
    bool isInMultiplayerOrSkirmishGame();
};

class Rva0052B2A0
{
public:
    void step();
};

extern Display *TheDisplay;
extern void __cdecl HideInGameChat();

#define g_obj12F49E4 (*(void **)0x012F49E4)

void Rva0052B2A0::step()
{
    if (g_obj12F49E4 != 0)
        return;

    if ((*(InGameUI **)0x012F148C)->slot85())
        return;

    if ((unsigned char)((BfmeThingFGA *)*(void **)0x012F0898)->bfmeGoFGA())
        return;

    if ((*(BfmeThingFGA **)0x012F0898)->m_flag)
        return;

    if (*(int *)((char *)*(void **)0x012F076C + 0x17080) >= 0)
        return;

    if ((*(GameWindowTransitionsHandler **)0x012F3330)->isFinished() == false)
        return;

    if (TheDisplay != 0) {
        if (TheDisplay->slot78())
            return;
        if (TheDisplay->slot77())
            return;
    }

    {
        Rva0005C5E0 *logic = (Rva0005C5E0 *)*(void **)0x012F0898;
        if ((unsigned char)logic->isEither() == false)
            ((BfmeGameLogicPause *)logic)->setGamePaused(true, 0, true);
    }

    if (*(void **)0x012F4964 != 0)
        return;

    HideInGameChat();
    (*(Mouse **)0x012F4C5C)->slot14(2);
    (*(Shell **)0x012F4B58)->showShell(false);

    int playerStatus;
    if (((GameLogicPortraitShim *)*(void **)0x012F0898)->isInMultiplayerOrSkirmishGame()) {
        playerStatus = 1;
        (*(Shell **)0x012F4B58)->push(AsciiString("PlayerStatus.apt"), false);
    } else {
        playerStatus = 0;
        (*(Shell **)0x012F4B58)->push(AsciiString("Objectives.apt"), false);
    }

    if (g_obj12F49E4 != 0)
        *(int *)((char *)g_obj12F49E4 + 0x264) = playerStatus;

    (*(InGameUI **)0x012F148C)->slot84(1);
}
