// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// BFME's four-argument game-options parser:
//
//   ?ParseGameOptionsString@@YA_NPAVLANGameInfo@@VAsciiString@@PADI@Z
//     0x00690490  954 B  (Y _N PA LANGameInfo VAsciiString PADI @Z)
//
// The Zero Hour twin that sits in game/GameEngine/Source/GameNetwork/
// LANGameInfo.cpp is the two-argument overload with a different body, so BFME's
// extension (an optional serialized packet plus its length) gets its own
// translation unit with its own layout view of the LAN classes.
//
// Identity: targets/game/reverse/symbols.csv pins this name and address, and
// the only named caller is LANAPI::handleGameAnnounce
// (game/GameEngine/Source/GameNetwork/LANAPIhandlers_handleGameAnnounce_Thunk.cpp),
// which hands it the game, the AsciiString options from the announcement and
// the packet body. The body keeps Zero Hour's structure and adds the packet
// path: `buffer && length` selects the serialized decoder, otherwise the
// AsciiString one.
//
// Two source shapes here are not guesses but measured, and both are needed for
// the body's two restore sites (+0x28c and +0x2e0) to match at all
// (tools/probe.py: 954/954 exact, every other byte already matched):
//
//   * Restoring a login/host copies the mapped value into a BY-VALUE argument.
//     Naming that argument a local (`UnicodeString login = mapIt->second;`)
//     makes MSVC materialise `&mapIt->second` in a scratch register
//     (`lea eax, [edi + 0x14]`, 0x00690490+0x28c) instead of coalescing it
//     into the dead iterator register (`add edi, 0x14`), at +0x2e0 as well.
//   * The same by-value parameter, but written through a named destination
//     pointer, is what puts the `set` receiver (`lea ecx, [esi + 0x48]`)
//     ahead of the argument push. A direct `m_login.set(value)` member call
//     pushes the argument first and emits the two in the other order.
//
// The Zero Hour source in
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/
// GameNetwork/LANGameInfo.cpp:253 is the readable body of this one; the BFME
// departures from it are the two extra arguments, the packet branch with
// the packet decoder at 0x0068EF70 (identity unproven, named by address), BFME's names for lanUpdateSlotList and
// updateGameOptions, and the two restore helpers.

#include "ascii_string.h"
#include <map>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
enum { MAX_SLOTS = 8 };

// BFME's UnicodeString derives from StringBase<unsigned short> and adds no
// data: every copy, compare and set in this body lands in the base.
class UnicodeString : public StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
    // The two map assignments land on StringBase<unsigned short>::set
    // (0x00888530) and not on operator= (0x00888A90), so BFME's
    // UnicodeString::operator= forwards to set. ascii_string.h carries the same
    // forwarding for AsciiString.
    UnicodeString &operator=(const UnicodeString &other)
    {
        set(other);
        return *this;
    }
    ~UnicodeString() {}
};

namespace _STL
{
template <> struct less<UnicodeString>
{
    bool operator()(const UnicodeString &left, const UnicodeString &right) const
    {
        return left.compare(right) < 0;
    }
};
}

typedef std::map<UnicodeString, UnicodeString> UnicodeStringMap;

// The two finds are inside a state that retail never unwinds out of, so they
// carry no EH state store: declaring them throw() is what keeps the store
// count at retail's (state 6/7 for the restores, 3 for the temporaries).
static __forceinline UnicodeStringMap::iterator findNoThrow(
    UnicodeStringMap &values, const UnicodeString &key) throw()
{
    return values.find(key);
}

// The layout view this body needs. Offsets are the ones the surrounding
// LANGameInfo TU and LANGameInfoBodies.cpp already carry: GameSlot is 0x44
// bytes, LANGameSlot adds m_user at +0x44, m_serial at +0x60 and m_lastHeard
// at +0x64, and GameInfo carries the map name at +0x3c with its CRC at +0x44.
// GameInfo's virtuals are placeholders in retail's own order: the body reads
// isInGame's flag byte directly and calls getLocalSlotNum at vtable+0x14.
class GameInfo
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual Int getLocalSlotNum() const;

    Bool isInGame() const { return m_inGame; }
    AsciiString getMap() const;  // out of line: MpGameSetup.cpp, retail 0x00098E70
    UnsignedInt getMapCRC() const { return m_mapCRC; }

private:
    unsigned char m_beforeInGame[0x0c - 4];
    Bool m_inGame;
    unsigned char m_beforeMap[0x3c - 0x0d];
    AsciiString m_mapName;
    UnsignedInt m_mapCRC;
    unsigned char m_tail[0x58 - 0x44];
};

class LANPlayer
{
public:
    UnicodeString m_name;                // this+0x00
    UnicodeString m_login;               // this+0x04
    UnicodeString m_host;                // this+0x08
    unsigned char m_rest[0x1c - 0x0c];
};

class GameSlot
{
public:
    Bool isHuman() const;                // ILT thunk 0x000279CB
    UnicodeString getName() const;       // ILT thunk 0x0003A20B

private:
    unsigned char m_data[0x44];
};

class LANGameSlot : public GameSlot
{
public:
    LANPlayer *getUser();                // ILT thunk 0x00042505
    void setLastHeard(UnsignedInt now) { m_lastHeard = now; }

    LANPlayer m_user;                    // this+0x44
    AsciiString m_serial;                // this+0x60
    UnsignedInt m_lastHeard;             // this+0x64
};

class LANGameInfo : public GameInfo
{
public:
    LANGameSlot *getLANSlot(Int slot)
    {
        if (slot < 0 || slot >= MAX_SLOTS)
            return 0;
        return &m_LANSlot[slot];
    }

private:
    LANGameSlot m_LANSlot[MAX_SLOTS];
};

// Only the two entries this body calls are named; the rest keep the retail
// order so RequestHasMap stays at +0x3c and AmIHost at +0xb8.
class LANAPI
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void RequestHasMap();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual Bool AmIHost();
};

extern LANAPI *TheLAN;
extern Bool ParseAsciiStringToGameInfo(GameInfo *, AsciiString, Bool);
// The serialized packet decoder: the BFME-only body at 0x0068EF70 (1881 B,
// cdecl (game, buffer, length) -> bool). Its real name is unproven, so it is
// called by a descriptive name and pinned at its address; the Zero Hour source
// only has the AsciiString overload.
extern Bool Rva0068EF70ParseBuffer(GameInfo *game, char *buffer, UnsignedInt length);
extern void processInactiveLanMessages();
extern void resetLanGameState();
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// Restores. The by-value parameter and the named destination pointer are both
// load-bearing; see the note at the top of the file.
static __forceinline void setSlotLogin(LANGameSlot *slot, UnicodeString value)
{
    StringBase<unsigned short> *destination = &slot->m_user.m_login;
    destination->set(value);
}

static __forceinline void setSlotHost(LANGameSlot *slot, UnicodeString value)
{
    StringBase<unsigned short> *destination = &slot->m_user.m_host;
    destination->set(value);
}

Bool ParseGameOptionsString(LANGameInfo *game, AsciiString options,
    char *buffer, UnsignedInt length)
{
    if (!TheLAN || !game)
        return false;

    Int oldLocalSlotNum = (game->isInGame()) ? game->getLocalSlotNum() : -1;
    Bool wasInGame = oldLocalSlotNum >= 0;
    AsciiString oldMap = game->getMap();
    UnsignedInt oldMapCRC, newMapCRC;
    oldMapCRC = game->getMapCRC();

    UnicodeStringMap oldLogins, oldMachines;
    UnicodeStringMap::iterator mapIt;
    Int i;
    for (i = 0; i < MAX_SLOTS; ++i)
    {
        LANGameSlot *slot = game->getLANSlot(i);
        if (slot && slot->isHuman())
        {
            oldLogins[slot->getName()] = slot->getUser()->m_login;
            oldMachines[slot->getName()] = slot->getUser()->m_host;
        }
    }

    Bool parsed;
    if (buffer && length)
        parsed = Rva0068EF70ParseBuffer(game, buffer, length);
    else
        parsed = ParseAsciiStringToGameInfo(game, options, true);

    if (parsed)
    {
        Int newLocalSlotNum = (game->isInGame()) ? game->getLocalSlotNum() : -1;
        Bool isInGame = newLocalSlotNum >= 0;
        if (!TheLAN->AmIHost() && isInGame)
        {
            newMapCRC = game->getMapCRC();
            if ((oldMapCRC ^ newMapCRC) || (!wasInGame && isInGame))
            {
                TheLAN->RequestHasMap();
                processInactiveLanMessages();
                resetLanGameState();
            }
        }

        UnsignedInt now = timeGetTime();
        for (i = 0; i < MAX_SLOTS; ++i)
        {
            LANGameSlot *slot = game->getLANSlot(i);
            if (slot->isHuman())
            {
                slot->setLastHeard(now);
                mapIt = findNoThrow(oldLogins, slot->getName());
                if (mapIt != oldLogins.end())
                    setSlotLogin(slot, mapIt->second);
                mapIt = findNoThrow(oldMachines, slot->getName());
                if (mapIt != oldMachines.end())
                    setSlotHost(slot, mapIt->second);
            }
        }

        return true;
    }

    return false;
}
