// ?ParseGameOptionsString@@YA_NPAVLANGameInfo@@VAsciiString@@PADI@Z
// partial score=0.993 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"
#include <map>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
enum { MAX_SLOTS = 8 };

class UnicodeString : public StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
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
static __forceinline UnicodeStringMap::iterator findNoThrow(
    UnicodeStringMap &values, const UnicodeString &key) throw()
{
    return values.find(key);
}

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
    AsciiString getMap() const { return m_mapName; }
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
    UnicodeString getLogin() { return m_login; }
    UnicodeString getHost() { return m_host; }
    void setLogin(const UnicodeString &name) { m_login.set(name); }
    void setHost(const UnicodeString &name) { m_host.set(name); }
    UnicodeString m_name;
    UnicodeString m_login;
    UnicodeString m_host;
    unsigned char m_rest[0x1c - 0x0c];
};

class GameSlot
{
public:
    Bool isHuman() const;
    UnicodeString getName() const;

private:
    unsigned char m_data[0x44];
};

class LANGameSlot : public GameSlot
{
public:
    LANPlayer *getUser();
    void setLastHeard(UnsignedInt now) { m_lastHeard = now; }
    void setLogin(const UnicodeString &name) { m_user.setLogin(name); }
    void setHost(const UnicodeString &name) { m_user.setHost(name); }
    LANPlayer m_user;
    AsciiString m_serial;
    UnsignedInt m_lastHeard;
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
extern Bool ParseAsciiStringToGameInfo(GameInfo *, char *, UnsignedInt);
extern Bool ParseAsciiStringToGameInfo(GameInfo *, AsciiString, Bool);
extern void processInactiveLanMessages();
extern void resetLanGameState();
extern Int (*g_bfmeNowVNH)(void);

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
            oldLogins[slot->getName()] = *(UnicodeString *)((char *)slot->getUser() + 4);
            oldMachines[slot->getName()] = *(UnicodeString *)((char *)slot->getUser() + 8);
        }
    }

    Bool parsed;
    if (buffer && length)
        parsed = ParseAsciiStringToGameInfo(game, buffer, length);
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

        UnsignedInt now = g_bfmeNowVNH();
        for (i = 0; i < MAX_SLOTS; ++i)
        {
            LANGameSlot *slot = game->getLANSlot(i);
            if (slot->isHuman())
            {
                slot->setLastHeard(now);
                mapIt = findNoThrow(oldLogins, slot->getName());
                if (mapIt != oldLogins.end())
                {
                    UnicodeString *loginValue = &mapIt->second;
                    UnicodeString login = *loginValue;
                    StringBase<unsigned short> *loginDestination = &slot->m_user.m_login;
                    loginDestination->set(login);
                }
                mapIt = findNoThrow(oldMachines, slot->getName());
                if (mapIt != oldMachines.end())
                {
                    UnicodeString *hostValue = &mapIt->second;
                    UnicodeString host = *hostValue;
                    StringBase<unsigned short> *hostDestination = &slot->m_user.m_host;
                    hostDestination->set(host);
                }
            }
        }

        return true;
    }

    return false;
}
