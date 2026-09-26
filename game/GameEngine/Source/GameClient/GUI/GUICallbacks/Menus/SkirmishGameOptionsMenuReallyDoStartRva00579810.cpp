// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00579810, 266 bytes: the BFME counterpart of Zero Hour's
// reallyDoStart (inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/
// Source/GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp:418).
// The matched caller 0x00579960 passes ILT 0x000487C0 (jmp here) as its start
// callback. BFME drops the game-speed slider, clears game data unconditionally
// with its two-Bool clearGameData, and keeps a SkirmishPreferences in scope.
// The Zero Hour port in SkirmishGameOptionsMenu.cpp already defines
// reallyDoStart, so this body keeps its address token.
//
// Levers: the TU is built WITHOUT /Ob0 (the bank's /Ob0 swapped the GlobalData
// +8 receiver and the getMap result push), and the seed is read through the
// inline accessor Zero Hour calls here (GameInfo::getSeed); a raw member read
// picks ECX for the seed and hoists the getMap receiver above the by-value
// argument setup.
#include "ascii_string.h"

// BFME calls the StringBase<char> release body directly at scope exit.
inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}

// Two Bools in BFME (ZH has one); the const spelling is the one the ledger pins
// for body 0x00396B00, as Rva003855F0Transition.cpp already calls it.
class GameLogic
{
public:
    void clearGameData(const bool showScoreScreen, bool second);
};
extern GameLogic *TheGameLogic;

// Only +0x08 is witnessed (name_oracle: GlobalData+0x8 m_mapName).
class GlobalData
{
    char m_unmodelled00[8];
public:
    AsciiString m_mapName;
};
extern GlobalData *TheWritableGlobalData;

// Slot 3 is GameInfo::startGame (SkirmishGameInfo vtable 0x011171DC slot 3 ->
// ILT 0x0001868D -> 0x0061E880).
class GameInfo
{
public:
    virtual void vslot00();
    virtual void vslot01();
    virtual void vslot02();
    virtual void startGame(int gameID);
    AsciiString getMap() const;
    int getSeed() const { return m_seed; }
private:
    char m_unmodelled04[0x48];
    int m_seed;
};
// The 0x012F7094 global the ledger pins under this address-derived type.
struct Rva00579160Current : public GameInfo
{
};
extern Rva00579160Current *Rva00579160TheCurrent;

class SkirmishPreferences
{
public:
    SkirmishPreferences();
    virtual ~SkirmishPreferences();
private:
    char m_unmodelled04[0x14];
};

class MapMetaData
{
public:
    char m_unmodelled00[0x24];
    bool byte_24;
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
    virtual void vslot00(); virtual void vslot01(); virtual void vslot02();
    virtual void vslot03(); virtual void vslot04(); virtual void vslot05();
    virtual void vslot06(); virtual void vslot07(); virtual void vslot08();
    virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
    virtual void vslot12();
    virtual GameMessage *appendMessage(int type);
};
extern MessageStream *TheMessageStream;
extern void InitGameLogicRandom(unsigned int seed);

void Rva00579810ReallyDoStart()
{
    SkirmishPreferences preferences;
    TheGameLogic->clearGameData(false, false);
    TheWritableGlobalData->m_mapName = Rva00579160TheCurrent->getMap();
    Rva00579160TheCurrent->startGame(0);
    InitGameLogicRandom(Rva00579160TheCurrent->getSeed());

    bool isSkirmish = true;
    const MapMetaData *md = TheMapCache->findMap(Rva00579160TheCurrent->getMap());
    if (md)
        isSkirmish = md->byte_24;

    if (isSkirmish) {
        GameMessage *msg = TheMessageStream->appendMessage(0x1e);
        msg->appendIntegerArgument(2);
        msg->appendIntegerArgument(1);
        msg->appendIntegerArgument(0);
    } else {
        GameMessage *msg = TheMessageStream->appendMessage(0x1e);
        msg->appendIntegerArgument(0);
        msg->appendIntegerArgument(1);
        msg->appendIntegerArgument(0);
    }
}
