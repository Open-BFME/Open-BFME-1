// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Natural reconstruction from ZH PlayerList.cpp and retail RVA 0x000E0060.
// Identity: installed vtable VA 0x01084180 slot 8 -> ILT 0x00029276.
// Extent: complete Capstone CFG, 386 instructions, 1203 bytes, RET at 0xE0512.
// Standalone TU: the Zero Hour PlayerList.cpp owns unrelated matched EH funclets.
#include "ascii_string.h"

template<> inline bool StringBase<char>::isEmpty() const
{ return m_data == 0 || m_data->length == 0; }
template<> inline const char *StringBase<char>::str() const
{ return m_data ? m_data->data : ""; }

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum Relationship { ENEMIES, NEUTRAL, ALLIES };
enum PlayerType { PLAYER_HUMAN = 0 };
class StaticNameKey { public: NameKeyType key() const; };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
extern StaticNameKey TheKey_playerName, TheKey_multiplayerIsLocal,
    TheKey_playerIsHuman, TheKey_playerEnemies, TheKey_playerAllies;

class Dict
{
    unsigned char m_unreconstructed[0x14];
public:
    AsciiString getAsciiString(NameKeyType, bool * = 0) const;
    bool getBool(NameKeyType, bool * = 0) const;
};
class BuildListInfo;
// SidesList::findSideInfo (0x19C670 family) and the target's loop both
// witness +0x28 count, +0x2C array, 0x18 stride, +4 dictionary.
class SidesInfo
{
    BuildListInfo *m_buildList;
    Dict m_dict;
public:
    Dict *getDict() { return &m_dict; }
    BuildListInfo *getBuildList() { return m_buildList; }
    void releaseBuildList() { m_buildList = 0; }
};
class SidesList
{
    char m_unreconstructed[0x28];
    int m_numSides;
    SidesInfo m_sides[32];
public:
    int getNumSides() { return m_numSides; }
    SidesInfo *getSideInfo(int side)
    { return side >= 0 && side < m_numSides ? &m_sides[side] : 0; }
};
extern SidesList *TheSidesList;
class TeamFactory
{
public:
    void clear();
    void initFromSides(SidesList *);
};
extern TeamFactory *TheTeamFactory;
class Network;
extern Network *TheNetwork;

class VRelease;
class Rva000C91C0ReleaseSet { public: void set(VRelease*); };
class Player
{
    char m_unreconstructed[0x20];
    NameKeyType m_playerNameKey;
public:
    int m_playerIndex;
    int getPlayerIndex() const { return m_playerIndex; }
    NameKeyType getPlayerNameKey() const { return m_playerNameKey; }
    // 0x000DB020 through ILT 0x0000E5E8; identity_evidence/0x000db020.md.
    void initFromDict(const Dict *);
    void setBuildList(BuildListInfo *list)
    { ((Rva000C91C0ReleaseSet*)this)->set((VRelease*)list); }
    void setPlayerType(PlayerType, bool);
    void becomingLocalPlayer(bool);
    void setPlayerRelationship(const Player *, Relationship);
    void setDefaultTeam();
};
void d_001072a0(int,int,int);
void d_001072f0();
class ShroudManager { public: __declspec(noinline) void m_008F7380(int,void (*)(int,int,int)); };
class Gen_012ED5C0 { public: void m_00880E10(void (*)()); };
extern ShroudManager *TheShroudManager;
extern Gen_012ED5C0 *g_012ED5C0;
struct T_008f8c30 { void m(int,void (*)(int,int,int)); };
__declspec(noinline) void ShroudManager::m_008F7380(int tag,void (*refresh)(int,int,int))
{ ((T_008f8c30*)*(void**)((char*)this+12))->m(tag,refresh); }

class PlayerList
{
public:
    virtual ~PlayerList();
    virtual void init();
    virtual void newGame();
    Player *getNeutralPlayer() { return m_players[0]; }
    Player *getNthPlayer(int i)
    { return i < 0 || i >= 32 ? 0 : m_players[i]; }
    Player *findPlayerWithNameKey(NameKeyType key)
    {
        for (int i=0; i<m_playerCount; ++i)
            if (m_players[i]->getPlayerNameKey() == key) return m_players[i];
        return 0;
    }
    void setLocalPlayer(Player *player);
private:
    char m_baseFields[8]; // primary vptr + name + Snapshot vptr = 12 bytes
    Player *m_local;
    int m_playerCount;
    Player *m_players[32];
};

// BFME extension independently witnessed by PlayerListSetLocalPlayer.cpp and
// retail 0xDF3C0; the compiler inlines only the fallback selection call.
void PlayerList::setLocalPlayer(Player *player)
{
    if (player == 0) player = getNeutralPlayer();
    if (player != m_local)
    {
        if (m_local) m_local->becomingLocalPlayer(false);
        m_local = player;
        player->becomingLocalPlayer(true);
    }
    if (TheShroudManager)
        TheShroudManager->m_008F7380(player->getPlayerIndex(), d_001072a0);
    if (g_012ED5C0) g_012ED5C0->m_00880E10(d_001072f0);
}

// ?newGame@PlayerList@@UAEXXZ
void PlayerList::newGame()
{
    int i;
    TheTeamFactory->clear();
    init();
    bool setLocal = false;
    for (i=0; i<TheSidesList->getNumSides(); ++i)
    {
        Dict *d = TheSidesList->getSideInfo(i)->getDict();
        AsciiString pname = d->getAsciiString(TheKey_playerName.key());
        if (pname.isEmpty()) continue;
        Player *p = m_players[m_playerCount++];
        p->initFromDict(d);
        bool exists;
        if (d->getBool(TheKey_multiplayerIsLocal.key(), &exists))
        {
            setLocalPlayer(p);
            setLocal = true;
        }
        if (!setLocal && !TheNetwork && d->getBool(TheKey_playerIsHuman.key()))
        {
            setLocalPlayer(p);
            setLocal = true;
        }
        p->setBuildList(TheSidesList->getSideInfo(i)->getBuildList());
        TheSidesList->getSideInfo(i)->releaseBuildList();
    }
    if (!setLocal)
    {
        for (i=0; i<TheSidesList->getNumSides(); ++i)
        {
            Player *p = getNthPlayer(i);
            if (p != getNeutralPlayer())
            {
                p->setPlayerType(PLAYER_HUMAN, false);
                setLocalPlayer(p);
                setLocal = true;
                break;
            }
        }
    }
    TheTeamFactory->initFromSides(TheSidesList);
    for (i=0; i<TheSidesList->getNumSides(); ++i)
    {
        Dict *d = TheSidesList->getSideInfo(i)->getDict();
        Player *p = findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(d->getAsciiString(TheKey_playerName.key()).str()));
        AsciiString tok;
        AsciiString enemies = d->getAsciiString(TheKey_playerEnemies.key());
        while (enemies.nextToken(&tok))
        {
            Player *p2 = findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(tok.str()));
            if (p2) p->setPlayerRelationship(p2, ENEMIES);
        }
        AsciiString allies = d->getAsciiString(TheKey_playerAllies.key());
        while (allies.nextToken(&tok))
        {
            Player *p2 = findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(tok.str()));
            if (p2) p->setPlayerRelationship(p2, ALLIES);
        }
        p->setPlayerRelationship(p, ALLIES);
        if (p != getNeutralPlayer())
            p->setPlayerRelationship(getNeutralPlayer(), NEUTRAL);
        p->setDefaultTeam();
    }
}
