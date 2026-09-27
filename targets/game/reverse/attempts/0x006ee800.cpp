// ?run@Rva006EE800W3DDisplay@@QAEXXZ
// partial score=0.13 date=2026-09-27
// Retail BFME display status updater at RVA 0x006EE800.
// The caller and receiver are proven; the semantic method name remains opaque.
// cl: /O2 /Ob0 /EHsc

typedef unsigned char Bool;
typedef unsigned short WideChar;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

template <typename T> class StringBase;
class AsciiString;
class UnicodeString;

template <typename T>
class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;

    struct Header
    {
        Int refCount;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

public:
    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &source);
    ~StringBase() {}
    void releaseBuffer();
    void concat(const T *text, Int length);
    void set(const T *text, Int length);

protected:
    Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const UnicodeString &source);
    ~AsciiString() { releaseBuffer(); }
};

class UnicodeString : private StringBase<WideChar>
{
public:
    UnicodeString() : StringBase<WideChar>() {}
    UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
    UnicodeString(const UnicodeString &source)
        : StringBase<WideChar>(source)
    {
    }
    ~UnicodeString() { releaseBuffer(); }
    void format(UnicodeString format, ...);
    void concat(const WideChar *text, Int length)
    {
        StringBase<WideChar>::concat(text, length);
    }
    void set(const WideChar *text, Int length)
    {
        StringBase<WideChar>::set(text, length);
    }
    void releaseBuffer()
    {
        StringBase<WideChar>::releaseBuffer();
    }
    const WideChar *str() const
    {
        return m_data ? m_data->data : reinterpret_cast<const WideChar *>(0x0107388C);
    }
};

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
    UnicodeString playerName;
};

class GameLogic
{
public:
    PlayerLeaveStatus *getPlayerLeaveStatus(Int playerIndex);
    char m_padding00[0x3c];
    Int m_frame;
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
    virtual Int getLocalPlayerID() = 0;
    virtual void slot94() = 0; virtual void slot98() = 0;
    virtual UnicodeString *getPlayerName(UnicodeString *name, Int player) = 0;
    virtual void slota0() = 0; virtual void slota4() = 0;
    virtual void slota8() = 0; virtual void slotac() = 0;
    virtual Real slotb0() = 0;
    virtual Real getPacketsPerSecondIn() = 0;
    virtual Real getBytesPerSecondIn() = 0;
    virtual Real getPacketsPerSecondOut() = 0;
    virtual Real getBytesPerSecondOut() = 0;
    virtual void slotc4() = 0; virtual void slotc8() = 0;
    virtual Int getFramesBehindPacketRouter() = 0;
    virtual Int getRunAheadFrames() = 0;
    virtual Int getSequentialBuffers(Int player) = 0;
    virtual Int getPlayerLatestFrame(Int player) = 0;
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

#define BFME_AT(type, address) (*reinterpret_cast<type *>(address))

void Rva006EE800W3DDisplay::run()
{
    DisplayString **strings = m_displayStrings;
    GameFont *font;
    UnicodeString text;
    UnicodeString aux;

    if (strings[0] == 0)
    {
        void *language = BFME_AT(void *, 0x012F1484);
        if (language != 0 && *reinterpret_cast<void **>(static_cast<char *>(language) + 0xc4) != 0 &&
            *reinterpret_cast<unsigned short *>(*reinterpret_cast<char **>(static_cast<char *>(language) + 0xc4) + 4) != 0)
        {
            AsciiString *name = reinterpret_cast<AsciiString *>(static_cast<char *>(language) + 0xc4);
            font = BFME_AT(FontLibraryBFMERetail *, 0x012F1B38)->getFont(
                name,
                (Real)*reinterpret_cast<Int *>(static_cast<char *>(language) + 0xc8),
                *reinterpret_cast<unsigned char *>(static_cast<char *>(language) + 0xcc));
        }
        else
        {
            AsciiString name("FixedSys");
            font = BFME_AT(FontLibraryBFMERetail *, 0x012F1B38)->getFont(&name, 8.0f, 0);
        }

        for (Int i = 0; i < 17; ++i)
        {
            if (strings[i] == 0)
            {
                strings[i] = BFME_AT(DisplayStringManager *, 0x012F12CC)->newDisplayString();
                strings[i]->setFont(font);
            }
        }
    }

    char *globalData = static_cast<char *>(BFME_AT(void *, 0x012ED5C8));
    Int frameTime = *reinterpret_cast<Int *>(globalData + 0x24);
    Real frameSeconds = (Real)frameTime * BFME_AT(Real, 0x012F8050);
    Int slept = (Int)(frameSeconds * 1000.0f);
    Int delta = (Int)((Real)(bfme_timeGetTime() - BFME_AT(UnsignedInt, 0x012ED51C)) * 0.001f);
    Int skipped = BFME_AT(Int, 0x012ED504);
    Real maxPercentSource = frameSeconds * BFME_AT(Real, 0x0107FAC4);
    Real fps = BFME_AT(Real, 0x012A72A4);
    Real scalar = BFME_AT(Real, 0x012A72A4);

    {
        if (BFME_AT(Bool, 0x012ED520))
        {
            Int maxFps = BFME_AT(GameEngine *, 0x012ED524)->getFramesPerSecondLimit();
            text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111ECF0)), fps,
                (Int)maxPercentSource, maxFps, scalar, skipped, slept, delta);
        }
        else
            text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111EC18)), fps,
                (Int)maxPercentSource, scalar, skipped, slept, delta);
        aux.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111EBA8)),
            BFME_AT(Int, 0x012ED514), BFME_AT(Int, 0x012ED510), skipped,
            BFME_AT(Int, 0x012ED504), BFME_AT(Int, 0x012ED510), BFME_AT(Int, 0x012ED514));
        text.concat(aux.str(), 0);
        strings[0]->setText(text);
    }

    {
        text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111EB38)),
            BFME_AT(GameLogic *, 0x012F0898)->m_frame,
            *reinterpret_cast<Int *>(globalData + 0xbd0),
            *reinterpret_cast<Int *>(globalData + 0xbc8),
            *reinterpret_cast<Int *>(globalData + 0xbd4));
        strings[1]->setText(text);
    }

    NetworkInterface *network = BFME_AT(NetworkInterface *, 0x012F7714);
    {
        if (network != 0)
            text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111EAC8)),
                network->getBytesPerSecondIn(), network->getPacketsPerSecondIn());
        strings[2]->setText(text);
    }

    {
        if (network != 0)
            text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111EA50)),
                network->getBytesPerSecondOut(), network->getPacketsPerSecondOut());
        strings[3]->setText(text);
    }

    if (network != 0)
    {
        Int localPlayer = network->getLocalPlayerID();
        if (localPlayer < 8 && network->isPacketRouter())
        {
            network->getPlayerName(&aux, localPlayer);
            AsciiString asciiName(aux);
            text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111E9E0)),
                localPlayer, asciiName);
            strings[7]->setText(text);
        }
    }

    if (network != 0)
    {
        text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111E8E0)),
            network->getFramesBehindPacketRouter());
        strings[8]->setText(text);
    }

    if (network != 0)
    {
        text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111E828)),
            BFME_AT(Int, 0x012F7724), network->getFramesBehindPacketRouter());
        strings[9]->setText(text);
    }

    for (Int playerIndex = 1; playerIndex < 8; ++playerIndex)
    {
        PlayerLeaveStatus *player = BFME_AT(GameLogic *, 0x012F0898)->getPlayerLeaveStatus(playerIndex);
        if (player == 0 || player->notPresent)
            continue;

        const WideChar *name = player->playerName.str();
        if (player->status == 0)
            text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111E5EC)), playerIndex, name);
        else if (player->status == 2)
            text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111E7C8)), playerIndex, name, player->quitFrame);
        else if (player->isHuman == 1)
            text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111E738)), playerIndex, name);
        else if (network != 0 && network->isPacketRouter())
        {
            Int frame = network->getPlayerLatestFrame(playerIndex);
            text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111E628)), playerIndex, name,
                frame, frame - BFME_AT(GameLogic *, 0x012F0898)->m_frame);
        }
        else
            text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111E628)), playerIndex, name,
                BFME_AT(GameLogic *, 0x012F0898)->m_frame, 0);
        strings[10 + playerIndex - 1]->setText(text);
    }

    {
        GameLogic *logic = BFME_AT(GameLogic *, 0x012F0898);
        Int currentFrame = logic->m_frame;
        Int runAhead = network != 0 ? network->getRunAheadFrames() : 0;
        if (network != 0 && runAhead != BFME_AT(Int, 0x012F81C0) && currentFrame > 5)
        {
            BFME_AT(Int, 0x012F81C0) = runAhead;
            BFME_AT(Int, 0x012F8054) = currentFrame;
        }
        text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111E58C)), currentFrame);
        strings[4]->setText(text);
    }

    {
        text.set(reinterpret_cast<const WideChar *>(0x0111E55C), 19);
        for (Int playerIndex = 0; playerIndex < 9; ++playerIndex)
        {
            aux.format(UnicodeString(reinterpret_cast<const WideChar *>(0x0111E550)),
                network != 0 ? network->getSequentialBuffers(playerIndex) : 0);
            text.concat(aux.str(), 0);
        }
        strings[5]->setText(text);
    }

    {
        text.format(UnicodeString(reinterpret_cast<const WideChar *>(0x01088AF4)),
            BFME_AT(Int, 0x012F8054));
        strings[2]->setText(text);
        strings[3]->setText(text);
        strings[4]->setText(text);
        strings[6]->setText(text);
    }

}

#undef BFME_AT
