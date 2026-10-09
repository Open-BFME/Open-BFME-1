// ?run@Rva006EE800W3DDisplay@@QAEXXZ
// partial score=0.463 date=2026-10-09
// ?run@Rva006EE800W3DDisplay@@QAEXXZ
// cl: /O2 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/stringbaseunicode
// Retail network overlay updater with the bank's retained address identity.
#include <wchar.h>
#include "ascii_string.h"
#include "Common/UnicodeString.h"

typedef unsigned char Bool;
typedef unsigned short WideChar;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;


template <typename T>
inline bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}


template <>
inline void StringBase<WideChar>::set(const WideChar *text)
{
    set(text, (Int)wcslen(text));
}

inline UnicodeString::~UnicodeString() { ((StringBase<WideChar> *)this)->clear(); }
class GameFont;

class FontLibraryBFMERetail
{
public:
    GameFont *getFont(AsciiString *name, Real size, unsigned char style);
};

class DisplayString
{
public:
    virtual ~DisplayString();
    virtual void setText(UnicodeString text);
    virtual UnicodeString getText();
    virtual Int getTextLength();
    virtual void notifyTextChanged();
    virtual void reset();
    virtual void setFont(GameFont *font);
};

class DisplayStringManager
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1c() = 0;
    virtual void slot20() = 0;
    virtual DisplayString *newDisplayString();
};

struct PlayerLeaveStatus
{
    Int status;
    Int quitFrame;
    Int defeatFrame;
    Int victoryFrame;
    Bool notPresent;
    char padding[3];
    Int isHuman;
    AsciiString playerName;
};

class GameLogic
{
public:
    PlayerLeaveStatus *getPlayerLeaveStatus(Int playerIndex);
    char m_padding00[0x3c];
    UnsignedInt m_frame;
};

class NetworkInterface
{
public:
    virtual void slot00() = 0; virtual void slot04() = 0;
    virtual void slot08() = 0; virtual void slot0c() = 0;
    virtual void slot10() = 0; virtual void slot14() = 0;
    virtual void slot18() = 0; virtual void slot1c() = 0;
    virtual void slot20() = 0; virtual void slot24() = 0;
    virtual void slot28() = 0; virtual void slot2c() = 0;
    virtual void slot30() = 0; virtual void slot34() = 0;
    virtual void slot38() = 0; virtual void slot3c() = 0;
    virtual void slot40() = 0; virtual void slot44() = 0;
    virtual void slot48() = 0; virtual void slot4c() = 0;
    virtual void slot50() = 0; virtual void slot54() = 0;
    virtual void slot58() = 0; virtual void slot5c() = 0;
    virtual void slot60() = 0; virtual void slot64() = 0;
    virtual void slot68() = 0; virtual void slot6c() = 0;
    virtual void slot70() = 0; virtual void slot74() = 0;
    virtual void slot78() = 0; virtual void slot7c() = 0;
    virtual void slot80() = 0; virtual void slot84() = 0;
    virtual void slot88() = 0;
    virtual Bool isPacketRouter() = 0;
    virtual UnsignedInt getLocalPlayerID() = 0;
    virtual void slot94() = 0; virtual void slot98() = 0;
    virtual UnicodeString getPlayerName(Int player) = 0;
    virtual void slota0() = 0; virtual void slota4() = 0;
    virtual void slota8() = 0; virtual void slotac() = 0;
    virtual Real slotb0() = 0;
    virtual Real getBytesPerSecondIn() = 0;
    virtual Real getPacketsPerSecondIn() = 0;
    virtual Real getBytesPerSecondOut() = 0;
    virtual Real getPacketsPerSecondOut() = 0;
    virtual void slotc4() = 0; virtual void slotc8() = 0;
    virtual Int getFramesBehindPacketRouter() = 0;
    virtual Int getRunAheadFrames() = 0;
    virtual Int getSequentialBuffers(Int player) = 0;
    virtual UnsignedInt getPlayerLatestFrame(Int player) = 0;
};

class GameEngine
{
public:
    virtual void slot00() = 0; virtual void slot04() = 0;
    virtual void slot08() = 0; virtual void slot0c() = 0;
    virtual void slot10() = 0; virtual void slot14() = 0;
    virtual void slot18() = 0; virtual void slot1c() = 0;
    virtual void slot20() = 0; virtual void slot24() = 0;
    virtual void slot28() = 0; virtual void slot2c() = 0;
    virtual Int getFramesPerSecondLimit() = 0;
};

extern "C" UnsignedInt __stdcall bfme_timeGetTime();

class Rva006EE800W3DDisplay
{
public:
    void run();

private:
    char m_padding00[0x22c];
    DisplayString *m_displayStrings[17];
};



struct Rva006EE800Language
{
    char m_padding00[0xc4];
    AsciiString m_fieldc4;
    Int m_fieldc8;
    unsigned char m_fieldcc;
};

struct Rva006EE800GlobalData
{
    char m_padding00[0x24];
    Int m_framesPerSecondLimit;
    char m_padding28[0xbc8 - 0x28];
    Int m_fieldbc8;
    Int m_fieldbcc;
    Int m_fieldbd0;
    Int m_fieldbd4;
};

extern void *Rva012F1484;
extern void *Rva012F1B38;
extern void *TheWritableGlobalData;
extern DisplayStringManager *TheDisplayStringManager;
extern GameLogic *TheGameLogic;
extern NetworkInterface *TheNetwork;
extern GameEngine *TheGameEngine;
extern Int BfmeSkippedClientFrames;
extern UnsignedInt g_012ED50C;
extern UnsignedInt g_012ED510;
extern UnsignedInt g_012ED514;
extern UnsignedInt g_012ED51C;
extern Bool g_012ED520;
extern Real g_012F8050;
extern Real g_012A72A4;
extern Int g_012F8054;
extern Int g_012F81C0;

void Rva006EE800W3DDisplay::run()
{
    UnicodeString text;
    UnicodeString aux;
    if (m_displayStrings[0] == 0)
    {
        GameFont *font;
        Rva006EE800Language *language = static_cast<Rva006EE800Language *>(Rva012F1484);
        if (language != 0 && !language->m_fieldc4.isEmpty())
            font = static_cast<FontLibraryBFMERetail *>(Rva012F1B38)->getFont(
                &language->m_fieldc4,
                (Real)language->m_fieldc8,
                language->m_fieldcc);
        else
        {
            AsciiString name("FixedSys");
            font = static_cast<FontLibraryBFMERetail *>(Rva012F1B38)->getFont(&name, 8.0f, 0);
        }
        for (Int i = 0; i < 17; ++i)
            if (m_displayStrings[i] == 0)
            {
                m_displayStrings[i] = TheDisplayStringManager->newDisplayString();
                m_displayStrings[i]->setFont(font);
            }
    }
    {
        Real fps = (Real)static_cast<Rva006EE800GlobalData *>(TheWritableGlobalData)->m_framesPerSecondLimit * g_012F8050;
        Real sleepTime = (Real)g_012ED50C;
        Int sleepMinutes = (Int)(sleepTime * (1.0f / 60000.0f));
        Int sleepSeconds = (Int)((sleepTime - sleepMinutes * 60000.0f) * 0.001f);
        Int sleepTenths = (Int)((sleepTime - (sleepSeconds * 1000.0f + sleepMinutes * 60000.0f)) * 0.1f);
        Real totalTime = (Real)(bfme_timeGetTime() - g_012ED51C);
        Int totalMinutes = (Int)(totalTime * (1.0f / 60000.0f));
        Int totalSeconds = (Int)((totalTime - totalMinutes * 60000.0f) * 0.001f);
        Int totalTenths = (Int)((totalTime - (totalSeconds * 1000.0f + totalMinutes * 60000.0f)) * 0.1f);
        if (g_012ED520)
            text.format(UnicodeString(L"FPS:%2.2f (%3d%% max) FPSLimit:%d, SCALAR:%1.2f, FSkipped:%d, Slept:%02dms, Delta:%02dms"),
                fps, (Int)(g_012F8050 * 100.0f), TheGameEngine->getFramesPerSecondLimit(), g_012A72A4,
                BfmeSkippedClientFrames, g_012ED510, g_012ED514);
        else
            text.format(UnicodeString(L"FPS:%2.2f (%3d%% max) FPSLimit:NA, SCALAR:%1.2f, FSkipped:%d, Slept:%02dms, Delta:%02dms"),
                fps, (Int)(g_012F8050 * 100.0f), g_012A72A4, BfmeSkippedClientFrames, g_012ED510, g_012ED514);
        aux.format(UnicodeString(L", TSlept:%02d:%02d:%02d, Total:%02d:%02d:%02d"), sleepMinutes, sleepSeconds, sleepTenths,
            totalMinutes, totalSeconds, totalTenths);
        text.concat(aux);
    }
    m_displayStrings[0]->setText(text);
    Rva006EE800GlobalData *globalData = static_cast<Rva006EE800GlobalData *>(TheWritableGlobalData);
    text.format(UnicodeString(L"Frame: %d -- exeCRC=%d, iniCRC=%d, cmdCRC=%d"), TheGameLogic->m_frame,
        globalData->m_fieldbcc, globalData->m_fieldbd0,
        globalData->m_fieldbc8, globalData->m_fieldbd4);
    m_displayStrings[1]->setText(text);
    if (TheNetwork)
    {
        text.format(UnicodeString(L"Bandwidth IN: %.2f bytes/sec, %.2f packets/sec"),
            TheNetwork->getBytesPerSecondIn(), TheNetwork->getPacketsPerSecondIn());
        m_displayStrings[2]->setText(text);
        text.format(UnicodeString(L"Bandwidth OUT: %.2f bytes/sec, %.2f packets/sec"),
            TheNetwork->getBytesPerSecondOut(), TheNetwork->getPacketsPerSecondOut());
        m_displayStrings[3]->setText(text);
        UnsignedInt localPlayer = TheNetwork->getLocalPlayerID();
        if (localPlayer >= 8)
            return;
        if (TheNetwork->isPacketRouter())
        {
            UnicodeString name;
            AsciiString asciiName(TheNetwork->getPlayerName(localPlayer));
            text.format(UnicodeString(L"**** I (Slot %d:%S) am the packet router ****"), localPlayer, asciiName.str());
            m_displayStrings[7]->setText(text);
            text.format(UnicodeString(L"Frame: %d"), TheGameLogic->m_frame);
            m_displayStrings[9]->setText(text);
        }
        else
        {
            AsciiString asciiName(TheNetwork->getPlayerName(localPlayer));
            text.format(UnicodeString(L"---- Other machine (Slot %d:%S) is the packet router ----"), localPlayer, asciiName.str());
            m_displayStrings[7]->setText(text);
            text.format(UnicodeString(L"Frames behind the packet router: %d"), TheNetwork->getFramesBehindPacketRouter());
            m_displayStrings[8]->setText(text);
            text.format(UnicodeString(L"Total # of times we've hit the run-ahead ceiling: %d times within %d frames"),
                TheNetwork->getRunAheadFrames(), TheGameLogic->m_frame);
            m_displayStrings[9]->setText(text);
        }
        for (Int playerIndex = 1; playerIndex < 8; ++playerIndex)
        {
            PlayerLeaveStatus *player = TheGameLogic->getPlayerLeaveStatus(playerIndex);
            if (player->notPresent)
                continue;
            if (player->status)
            {
                if (player->status == 2)
                    text.format(UnicodeString(L"Player %d(%S) was voted out on frame %d"), playerIndex, player->playerName.str(), player->quitFrame);
                else if (player->status == 1)
                    text.format(UnicodeString(L"Player %d(%S) quit gracefully on frame %d"), playerIndex, player->playerName.str(), player->quitFrame);
            }
            else
            {
                if (player->isHuman == 1)
                    text.format(UnicodeString(L"AIPlayer %d(%S)"), playerIndex, player->playerName.str());
                else if (TheNetwork->isPacketRouter())
                {
                    Int currentFrame = TheGameLogic->m_frame;
                    Int frame = TheNetwork->getPlayerLatestFrame(playerIndex) + (1 - currentFrame);
                    if (frame == -10)
                        text.format(UnicodeString(L"Player %d(%S) is on frame#: %d (%d) -- NETWORK SIGNAL FLATLINED (WAITING...)"),
                            playerIndex, player->playerName.str(), TheNetwork->getPlayerLatestFrame(playerIndex), frame);
                    else
                        text.format(UnicodeString(L"Player %d(%S) is on frame#: %d (%d)"),
                            playerIndex, player->playerName.str(), TheNetwork->getPlayerLatestFrame(playerIndex), frame);
                }
                else
                    text.format(UnicodeString(L"Player %d(%S) is active"), playerIndex, player->playerName.str());
                if (player->victoryFrame)
                    aux.format(UnicodeString(L" -- Victorious on frame %d"), player->victoryFrame);
                else if (player->defeatFrame)
                {
                    if (player->isHuman == 0)
                        aux.format(UnicodeString(L" -- Defeated on frame %d (OBSERVING)"), player->defeatFrame);
                    else
                        aux.format(UnicodeString(L" -- Defeated on frame %d"), player->defeatFrame);
                }
                text.concat(aux);
            }
            m_displayStrings[10 + playerIndex - 1]->setText(text);
        }
        if (g_012F81C0 != TheNetwork->getRunAheadFrames() && (UnsignedInt)TheGameLogic->m_frame > 5)
        {
            g_012F81C0 = TheNetwork->getRunAheadFrames();
            g_012F8054 = TheGameLogic->m_frame;
        }
        text.format(UnicodeString(L"No Run Ahead"));
        m_displayStrings[4]->setText(text);
        text.set(L"SequentialBuffers: ");
        for (Int playerIndex = 0; playerIndex < 9; ++playerIndex)
        {
            aux.format(UnicodeString(L"%d "), TheNetwork->getSequentialBuffers(playerIndex));
            text.concat(aux);
        }
        m_displayStrings[5]->setText(text);
    }
    else
    {
        text.format(UnicodeString(L""));
        m_displayStrings[3]->setText(text);
        m_displayStrings[2]->setText(text);
        m_displayStrings[4]->setText(text);
        m_displayStrings[6]->setText(text);
    }
}
