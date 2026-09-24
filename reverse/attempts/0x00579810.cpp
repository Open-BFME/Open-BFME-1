// ?d_00579810@@YAXXZ
// partial score=0.93 date=2026-09-24
// Retail 0x00579810, 266 bytes. Matched caller 0x00579960 at +0x0E
// passes ILT 0x000487C0 (which jumps here) as the start callback.
// The physical call/branch sequence matches the Zero Hour reallyDoStart
// implementation and the BFME source at SkirmishGameOptionsMenu.cpp:455.
// No semantic owner is asserted by the address-qualified exported name.
// The 266/266 probe has 18 non-relocation differences and one relocation-layout
// mismatch. The first is +0x4F (destination +8 versus source push order);
// +0x86 loads the current-game global before constructing the by-value getMap
// argument, whereas retail loads it after; virtual-call temps swap EAX/EDX.
// Strict relocation resolution remains unverified. The clearGameData body is
// physically 0x00396B00 via ILT 0x0001C46D; its GameLogic ABI is two Bools.
// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

// BFME calls the StringBase<char> release body directly at scope exit.
inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}

struct Rva00579160Current;
extern Rva00579160Current *Rva00579160TheCurrent;

struct Rva00367E30Logic;
extern Rva00367E30Logic *TheBfmeGameLogic;
class GameLogic
{
public:
    void clearGameData(bool showScoreScreen, bool unknown);
};

struct Rva006C9270GlobalData;
extern Rva006C9270GlobalData *TheWritableGlobalData;

class GameInfo
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void startGame(int gameID);
    AsciiString getMap() const;
};

class SkirmishPreferences
{
public:
    SkirmishPreferences();
    virtual ~SkirmishPreferences();
private:
    char m_data[0x14];
};

class MapMetaData
{
public:
    char m_data[0x24];
    bool m_isMultiplayer;
};
class MapCache
{
public:
    const MapMetaData *findMap(AsciiString mapName);
};
extern MapCache *TheMapCache;

class GameMessage
{
public:
    void appendIntegerArgument(int value);
};
class MessageStream
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12();
    virtual GameMessage *appendMessage(int type);
};
extern MessageStream *TheMessageStream;
extern void InitGameLogicRandom(unsigned int seed);

void Rva00579810StartSkirmish()
{
    SkirmishPreferences preferences;
    ((GameLogic *)TheBfmeGameLogic)->clearGameData(false, false);
    ((AsciiString *)((char *)TheWritableGlobalData + 8))->set(((GameInfo *)Rva00579160TheCurrent)->getMap());
    ((GameInfo *)Rva00579160TheCurrent)->startGame(0);
    InitGameLogicRandom(*(unsigned int *)((char *)Rva00579160TheCurrent + 0x4c));
    const MapMetaData *map = TheMapCache->findMap(((GameInfo *)Rva00579160TheCurrent)->getMap());
    bool isSkirmish = true;
    if (map)
        isSkirmish = map->m_isMultiplayer;
    if (isSkirmish) {
        GameMessage *message = TheMessageStream->appendMessage(0x1e);
        message->appendIntegerArgument(2);
        message->appendIntegerArgument(1);
        message->appendIntegerArgument(0);
    } else {
        GameMessage *message = TheMessageStream->appendMessage(0x1e);
        message->appendIntegerArgument(0);
        message->appendIntegerArgument(1);
        message->appendIntegerArgument(0);
    }
}
