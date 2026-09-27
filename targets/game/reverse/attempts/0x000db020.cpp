// ?initFromDict@Player@@QAEXPBVDict@@@Z
// partial score=0.35537190082644626 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1 /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// stlport
// Native reconstruction of Player::initFromDict, BFME 0x000DB020/3751.
// Identity: native PlayerList::newGame calls ILT 0000E5E8 with const Dict*;
// upstream Player.h agrees on thiscall, public void, RET4. The existing
// updateLoadProgress lift name is false; this bank does not alter that row.
//
// Retail and a fresh read-only Ghidra export prove the BFME human/skirmish
// branches, indexed TeamRec containers and embedded 24-byte SideInfo arrays.
// SidesList +28/+32C counts, +2C/+330 arrays, +630/+64C team owners; each
// owner has its 16-byte node vector at +C, with Dict at node+C.
//
// Independent allocation witnesses: Squad vtable VA01083E78 slot3 reaches
// native Squad::xfer 0018BF80, which proves the two vector triples; native
// PlayerSetCurrentlySelectedAIGroup 000D2C60 independently constructs the
// same 28 bytes. ResourceGatheringManager table VA01084C40 is shared by
// 000E6090/113 constructor and native 000E6140/175 destructor; retain its
// existing address-derived constructor spelling. TunnelTracker 000F8980/140
// independently proves the 32-byte allocation and table VA01085FD8.
//
// Opaque helpers: D1C30 is bool thiscall(int*)/RET4; D1E30 consumes a const
// AsciiString&/RET4. Script copying uses existing ILT 00031F57 -> 0035E450.
// No new dependency pin is required. StringBase compare(const char*) below
// independently matches all 90 bytes at 000A2BB0; it adds no headline bytes.
// CharStringView exposes the witnessed StringBase comparison algorithm to
// this caller while preserving the two actual out-of-line compare calls.
//
// Measured 3751/3751 bytes, 2418 masked differences, 177 relocations,
// correct 0x30 frame; normalized shape 0.953, separately from byte score.
// Blocker: register/stack lifetimes, loop cursors and EH-temporary scheduling.
// This is evidence only; no game-source or coverage row is changed.
#define __PLACEMENT_VEC_NEW_INLINE
#include "ascii_string.h"
#include "unicode_string.h"
#define ASCIISTRING_H
#define UNICODESTRING_H
#include <stddef.h>
#include <string.h>
#include "Lib/BaseType.h"
#include "Common/Debug.h"
#include "Common/Dict.h"

template <> __declspec(noinline) int StringBase<char>::compare(const char *str) const
{
    const int strLen = str ? (int)strlen(str) : 0;
    const int len = m_data ? m_data->length : 0;
    const char *data = m_data ? m_data->data : "";
    int result = memcmp(data, str, len < strLen ? len : strLen);
    if (result == 0)
        result = len - strLen;
    return result;
}
template <class T> inline const T *StringBase<T>::str() const
{
    return m_data ? m_data->data : (const T *)"";
}
inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->~StringBase<unsigned short>();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &r)
{
    ((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&r);
    return *this;
}
class CharStringView
{
    struct Header
    {
        int refs;
        unsigned short length, capacity;
        char data[1];
    };
    Header *m_data;

  public:
    __forceinline int compare(const char *str, int len) const
    {
        const int myLen = m_data ? m_data->length : 0;
        const char *data = m_data ? m_data->data : "";
        int result = memcmp(data, str, myLen < len ? myLen : len);
        if (result == 0)
            result = myLen - len;
        return result;
    }
    __forceinline int compare(const CharStringView &str) const
    {
        const int len = str.m_data ? str.m_data->length : 0;
        const char *data = str.m_data ? str.m_data->data : "";
        return compare(data, len);
    }
};
static __forceinline int compareNames(const AsciiString &a, const AsciiString &b)
{
    return ((const CharStringView &)a).compare((const CharStringView &)b);
}
template <class T, int O, class C> inline T &field(C *p)
{
    return *(T *)((char *)p + O);
}
#define STATIC_KEY(va) (((StaticNameKey *)(va))->key())
#define GLOBAL(T, va) (*(T **)(va))
#define PLAYER_KEY(name) STATIC_KEY(key_##name)
enum
{
    key_playerFaction = 0x12a7938,
    key_playerDisplayName = 0x12a7930,
    key_playerName = 0x12a7918,
    key_playerIsSkirmish = 0x12a7928,
    key_multiplayerStartIndex = 0x12a7968,
    key_playerIsHuman = 0x12a7920,
    key_playerIsPreorder = 0x12a7980,
    key_playerAIType = 0x12a7988,
    key_skirmishDifficulty = 0x12a7970,
    key_playerStartMoney = 0x12a7950,
    key_playerFactionIcon = 0x12a7990,
    key_teamOwner = 0x12a75c0,
    key_teamName = 0x12a75b8
};
class PlayerTemplate;
class PlayerTemplateStore
{
  public:
    const PlayerTemplate *findPlayerTemplate(NameKeyType) const;
};
class Rva00027D6DMoney
{
  public:
    void unidentified_00027d6d(unsigned int, bool);
};
class Handicap
{
  public:
    void readFromDict(const Dict *);
};
class Rva000C9330Player
{
  public:
    void readColorsFromDict(const Dict *);
};
class Deletable
{
  public:
    virtual ~Deletable();
};
class ScriptList : public Deletable
{
  public:
    ScriptList *rva0035E450();
};
extern void j_00031f57();
inline ScriptList *ScriptList::rva0035E450()
{
    typedef ScriptList *(ScriptList::*M)();
    union {
        void (*f)();
        M m;
    } u;
    u.f = j_00031f57;
    return (this->*u.m)();
}
struct SideInfo
{
    int field_0;
    Dict dict;
    ScriptList *scripts;
    char field_c[12];
};
struct TeamNode
{
    short next, previous, reserved, free;
    int generation;
    Dict dict;
};
class Rva0019BE80TeamRec
{
  public:
    int append(const Dict *);
};
class BfmeIndexedNodesFM
{
  public:
    void bfmeRelease(int);
};
struct TeamList
{
    char prefix[12];
    TeamNode *nodes;
    TeamNode *end;
    TeamNode *capacity;
    short numActive, freeHead;
    int append(const Dict *d)
    {
        return ((Rva0019BE80TeamRec *)this)->append(d);
    }
    void remove(int i)
    {
        ((BfmeIndexedNodesFM *)this)->bfmeRelease(i);
    }
};
struct SidesList
{
    char prefix[0x28];
    int numSides;
    SideInfo sides[32];
    int numSkirmishSides;
    SideInfo skirmishSides[32];
    TeamList teams;
    TeamList skirmishTeams;
    SideInfo *getSide(int i)
    {
        return i < 0 || i >= numSides ? 0 : &sides[i];
    }
    SideInfo *getSkirmishSide(int i)
    {
        return i < 0 || i >= numSkirmishSides ? 0 : &skirmishSides[i];
    }
};
extern SidesList *TheSidesList;
#define SIDES TheSidesList
class GameInfo
{
  public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual bool predicate34();
};
class Rva000E6090 : public Deletable
{
  public:
    Rva000E6090();

  private:
    int head1, head2;
};
class TunnelTracker : public Deletable
{
  public:
    TunnelTracker();

  private:
    int words[7];
};
extern int Gen01083E78;
class Squad
{
  public:
    Squad()
        : table(&Gen01083E78), idsBegin(0), idsEnd(0), idsCapacity(0), objectsBegin(0),
          objectsEnd(0), objectsCapacity(0)
    {
    }

  private:
    int *table;
    int idsBegin, idsEnd, idsCapacity, objectsBegin, objectsEnd, objectsCapacity;
};
extern void j_00005b73(), j_000188ea(), j_00006be5(), j_00032952();
class TableClearView
{
  public:
    void clearA()
    {
        typedef void (TableClearView::*M)();
        union {
            void (*f)();
            M m;
        } u;
        u.f = j_000188ea;
        (this->*u.m)();
    }
    void clearB()
    {
        typedef void (TableClearView::*M)();
        union {
            void (*f)();
            M m;
        } u;
        u.f = j_00005b73;
        (this->*u.m)();
    }
};

class Player
{
  public:
    char m_00[8];
    UnicodeString m_08;
    char m_0c[0x10];
    AsciiString m_1c;
    NameKeyType m_20;
    int m_24;
    AsciiString m_28;
    PlayerType m_2c;
    char m_30[0x1f0];
    Deletable *m_220;
    int m_224;
    Rva000E6090 *m_228;
    TunnelTracker *m_22c;
    char m_230[0x5c];
    char *m_28c;
    char *m_290;
    char m_294[3];
    bool m_297;
    char m_298[7];
    bool m_29f[32];
    char m_2bf[5];
    int m_2c4[32];
    unsigned short m_344;
    char m_346[0x30e];
    Squad *m_654[10];
    Squad *m_67c;
    char m_680[0x18];
    AsciiString m_698;
    void initFromDict(const Dict *);
    void init(const PlayerTemplate *);
    void setPlayerType(PlayerType, bool);
    bool findSkirmishSide(int *);
    void readColors(const Dict *d)
    {
        ((Rva000C9330Player *)this)->readColorsFromDict(d);
    }
    bool rva000D1C30(int *p)
    {
        typedef bool (Player::*M)(int *);
        union {
            void (*f)();
            M m;
        } u;
        u.f = j_00032952;
        return (this->*u.m)(p);
    }
    void rva000D1E30(const AsciiString &s)
    {
        typedef void (Player::*M)(const AsciiString &);
        union {
            void (*f)();
            M m;
        } u;
        u.f = j_00006be5;
        (this->*u.m)(s);
    }
};
void Player::initFromDict(const Dict *d)
{
    AsciiString tmplname = d->getAsciiString(PLAYER_KEY(playerFaction));
    const PlayerTemplate *pt =
        GLOBAL(PlayerTemplateStore, 0x12ed750)
            ->findPlayerTemplate(GLOBAL(NameKeyGenerator, 0x12ed600)->nameToKey(tmplname.str()));
    init(pt);
    m_08 = d->getUnicodeString(PLAYER_KEY(playerDisplayName));
    AsciiString pname = d->getAsciiString(PLAYER_KEY(playerName));
    m_1c = pname;
    m_20 = GLOBAL(NameKeyGenerator, 0x12ed600)->nameToKey(pname.str());
    bool exists, skirmish = false, forceHuman = false;
    if (!field<const bool, 0xbc>(pt) && d->getBool(PLAYER_KEY(playerIsSkirmish), &exists))
    {
        for (int i = 0; i < SIDES->numSkirmishSides; ++i)
        {
            AsciiString side =
                SIDES->getSkirmishSide(i)->dict.getAsciiString(PLAYER_KEY(playerFaction));
            const PlayerTemplate *st =
                GLOBAL(PlayerTemplateStore, 0x12ed750)
                    ->findPlayerTemplate(
                        GLOBAL(NameKeyGenerator, 0x12ed600)->nameToKey(side.str()));
            if (st && field<const StringBase<char>, 8>(st).compare(m_28) == 0)
            {
                skirmish = true;
                break;
            }
        }
        if (!skirmish)
            forceHuman = true;
    }
    m_224 = d->getInt(PLAYER_KEY(multiplayerStartIndex), &exists);
    readColors(d);
    if (d->getBool(PLAYER_KEY(playerIsHuman)) || forceHuman)
    {
        m_2c = PLAYER_HUMAN;
        delete m_220;
        m_220 = 0;
        if (d->getBool(PLAYER_KEY(playerIsPreorder), &exists))
            m_297 = true;
        if (SIDES->numSkirmishSides > 0 &&
            d->getAsciiString(PLAYER_KEY(playerName)).compare("ReplayObserver") != 0 &&
            tmplname.compare("FactionObserver") != 0)
        {
            if (GLOBAL(GameInfo, 0x12f708c)->predicate34())
            {
                AsciiString wanted = "PlayerHuman";
                for (int i = 0; i < SIDES->numSkirmishSides; ++i)
                {
                    SideInfo *side = SIDES->getSkirmishSide(i);
                    if (side && &side->dict)
                    {
                        AsciiString sideName = side->dict.getAsciiString(PLAYER_KEY(playerName));
                        if (((const StringBase<char> &)sideName).compare(wanted) == 0)
                        {
                            readColors(&side->dict);
                            break;
                        }
                    }
                }
            }
            if (d->getType(PLAYER_KEY(playerAIType)) != Dict::DICT_ASCIISTRING)
            {
                AsciiString wanted = "SkirmishHuman";
                for (int i = 0; i < SIDES->numSkirmishSides; ++i)
                {
                    if (compareNames(
                            SIDES->getSkirmishSide(i)->dict.getAsciiString(PLAYER_KEY(playerName)),
                            wanted) == 0)
                    {
                        if (SIDES->getSkirmishSide(i)->scripts)
                        {
                            SIDES->getSide(m_24)->scripts =
                                SIDES->getSkirmishSide(i)->scripts->rva0035E450();
                            AsciiString originalName =
                                SIDES->getSkirmishSide(i)->dict.getAsciiString(
                                    PLAYER_KEY(playerName));
                            for (int j = SIDES->skirmishTeams.nodes[0].next; j;
                                 j = SIDES->skirmishTeams.nodes[j].next)
                            {
                                const Dict *ownerDict = &SIDES->skirmishTeams.nodes[j].dict;
                                if (compareNames(ownerDict->getAsciiString(PLAYER_KEY(teamOwner)),
                                                 originalName) == 0)
                                {
                                    Dict td(SIDES->skirmishTeams.nodes[j].dict);
                                    AsciiString teamName = td.getAsciiString(PLAYER_KEY(teamName));
                                    if (compareNames(teamName,
                                                     AsciiString("team") + originalName) == 0)
                                        td.setAsciiString(PLAYER_KEY(teamName),
                                                          AsciiString("team") + pname);
                                    td.setAsciiString(PLAYER_KEY(teamOwner), pname);
                                    SIDES->teams.append(&td);
                                }
                            }
                        }
                        break;
                    }
                }
            }
            if (field<int, 0x10c>(GLOBAL(char, 0x12f0898)) != 6)
                rva000D1E30(pname);
            goto allocation;
        }
    }
    else
        setPlayerType(PLAYER_COMPUTER, skirmish);
    if (skirmish)
    {
        int sideIndex;
        if (!(GLOBAL(GameInfo, 0x12f708c)->predicate34() ? findSkirmishSide(&sideIndex)
                                                         : rva000D1C30(&sideIndex)))
            return;
        int diffInt = d->getInt(PLAYER_KEY(skirmishDifficulty), &exists);
        int difficulty = field<int, 0x17620>(GLOBAL(char, 0x12f076c));
        if (exists)
            difficulty = diffInt;
        if (m_220)
            field<int, 0x2c>(m_220) = difficulty;
        if (GLOBAL(GameInfo, 0x12f708c)->predicate34())
        {
            SideInfo *side = SIDES->getSkirmishSide(sideIndex);
            if (side)
                readColors(&side->dict);
        }
        if (GLOBAL(GameInfo, 0x12f708c)->predicate34() ||
            d->getType(PLAYER_KEY(playerAIType)) != Dict::DICT_ASCIISTRING)
        {
            ScriptList *scripts = SIDES->getSkirmishSide(sideIndex)->scripts->rva0035E450();
            delete SIDES->getSide(m_24)->scripts;
            SIDES->getSide(m_24)->scripts = scripts;
            for (int j = SIDES->teams.nodes[0].next; j;)
            {
                int next = SIDES->teams.nodes[j].next;
                const Dict *ownerDict = &SIDES->teams.nodes[j].dict;
                if (compareNames(ownerDict->getAsciiString(PLAYER_KEY(teamOwner)), pname) == 0)
                    SIDES->teams.remove(j);
                j = next;
            }
            AsciiString originalName =
                SIDES->getSkirmishSide(sideIndex)->dict.getAsciiString(PLAYER_KEY(playerName));
            for (int j = SIDES->skirmishTeams.nodes[0].next; j;
                 j = SIDES->skirmishTeams.nodes[j].next)
            {
                const Dict *ownerDict = &SIDES->skirmishTeams.nodes[j].dict;
                if (compareNames(ownerDict->getAsciiString(PLAYER_KEY(teamOwner)), originalName) ==
                    0)
                {
                    Dict td(SIDES->skirmishTeams.nodes[j].dict);
                    AsciiString teamName = td.getAsciiString(PLAYER_KEY(teamName));
                    if (compareNames(teamName, AsciiString("team") + originalName) == 0)
                        td.setAsciiString(PLAYER_KEY(teamName), AsciiString("team") + pname);
                    td.setAsciiString(PLAYER_KEY(teamOwner), pname);
                    SIDES->teams.append(&td);
                }
            }
        }
        if (!GLOBAL(GameInfo, 0x12f708c)->predicate34())
            rva000D1E30(pname);
    }
allocation:
    delete m_228;
    m_228 = 0;
    m_228 = new Rva000E6090;
    delete m_22c;
    m_22c = 0;
    m_22c = new TunnelTracker;
    field<Handicap, 0xc>(this).readFromDict(d);
    field<TableClearView, 4>(m_28c).clearA();
    field<TableClearView, 4>(m_290).clearB();
    for (int i = 0; i < 32; ++i)
    {
        m_29f[i] = false;
        m_2c4[i] = 0;
    }
    m_344 = 0;
    unsigned int money = d->getInt(PLAYER_KEY(playerStartMoney), &exists);
    if (exists)
        field<Rva00027D6DMoney, 0x48>(this).unidentified_00027d6d(money, false);
    for (int i = 0; i < 10; ++i)
    {
        Squad *&s = m_654[i];
        delete (Deletable *)s;
        s = 0;
        s = new Squad;
    }
    Squad *&selected = m_67c;
    delete (Deletable *)selected;
    selected = 0;
    selected = new Squad;
    m_698 = d->getAsciiString(PLAYER_KEY(playerFactionIcon), &exists);
}
