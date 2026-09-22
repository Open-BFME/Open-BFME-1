// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Retail001C6F10/346, Object vtable0109EE58 slot20 via ILT0002B74C.
// Matched Object constructor001D29A0 independently names setTeam.
// BFME extends the released body with a two-part team name, three partition
// notifications, two Lua notifications, contained-object propagation, radar,
// upgrade updates and the final Drawable callback. The team guard includes
// the radar and upgrade calls; the final Drawable callback is unconditional.
// Calls have been decoded from retail. The contained-interface local follows
// the independently matched Object_containPairDispatch.cpp access pattern.

typedef bool Bool;
typedef int Int;

#include "ascii_string.h"
template <typename T> inline void StringBase<T>::concat(T c)
{
    concat(&c, 1);
}
template <> inline void StringBase<char>::concat(const StringBase<char> &s)
{
    const int len = s.m_data ? s.m_data->length : 0;
    const char *data = s.m_data ? &s.m_data->data[0] : "";
    concat(data, len);
}
template <typename T> inline void StringBase<T>::clear()
{
    releaseBuffer();
}
extern const AsciiString Rva01336E50EmptyString;
class Team;
class Player
{
  public:
    unsigned char m_pad[0x230];
    Team *m_defaultTeam;
    Bool isPlayerActive() const; // pinned retail 0x000C9D10
};

class Rva001C6F10TeamPrototype
{
  public:
    unsigned char pad[0x10];
    AsciiString m_name, m_rva14;
};
class Team
{
  public:
    unsigned char pad[4];
    Rva001C6F10TeamPrototype *m_prototype;
    const AsciiString &getName() const
    {
        if (!m_prototype)
            return Rva01336E50EmptyString;
        return m_prototype->m_name;
    }
    const AsciiString &rva14Name() const
    {
        if (!m_prototype)
            return Rva01336E50EmptyString;
        return m_prototype->m_rva14;
    }
    Player *getControllingPlayer() const; // pinned retail 0x000EC8F0
};

class ThePlayerListType
{
  public:
    unsigned char m_pad[0x14];
    Player *m_field14;
};
extern ThePlayerListType *ThePlayerList; // VA 0x012ED748

class PartitionData
{
  public:
    void makeDirty(); // retail 0x008F7B30
};

class Rva009F2BA0
{
  public:
    void init(); // retail 0x009F2BA0
};

class Rva009A2350
{
  public:
    void init(); // retail 0x009A2350
};

class Object;
class Radar
{
  public:
    void rva00107A50(Object *);
};
extern Radar *TheRadar; // VA 0x012EF0E4

class Rva0012F060COwner
{
  public:
    void rva002E4180(Object *);
    void rva002E4030(Object *);
};
extern Rva0012F060COwner *g_bfmeOwnerBR; // VA 0x012F060C

// Address-qualified view returned by containment slot26.
class Rva0140Interface
{
  public:
    virtual void pad0();
    virtual void pad4();
    virtual void pad8();
    virtual void padC();
    virtual void pad10();
    virtual void pad14();
    virtual void pad18();
    virtual void pad1C();
    virtual void pad20();
    virtual void pad24();
    virtual void pad28();
    virtual void pad2C();
    virtual void pad30();
    virtual void pad34();
    virtual void pad38();
    virtual void pad3C();
    virtual void pad40();
    virtual void pad44();
    virtual void pad48();
    virtual void pad4C();
    virtual void pad50();
    virtual void pad54();
    virtual void pad58();
    virtual void pad5C();
    virtual void pad60();
    virtual void pad64();
    virtual void pad68();
    virtual void pad6C();
    virtual void pad70();
    virtual void pad74();
    virtual void pad78();
    virtual void pad7C();
    virtual void pad80();
    virtual void pad84();
    virtual void pad88();
    virtual void pad8C();
    virtual void pad90();
    virtual void pad94();
    virtual void pad98();
    virtual void pad9C();
    virtual void padA0();
    virtual void padA4();
    virtual void padA8();
    virtual void padAC();
    virtual void padB0();
    virtual void padB4();
    virtual void padB8();
    virtual void padBC();
    virtual void padC0();
    virtual void padC4();
    virtual void padC8();
    virtual void padCC();
    virtual void padD0();
    virtual void padD4();
    virtual void padD8();
    virtual void padDC();
    virtual void padE0();
    virtual void padE4();
    virtual void padE8();
    virtual void padEC();
    virtual void padF0();
    virtual void padF4();
    virtual void padF8();
    virtual void padFC();
    virtual void pad100();
    virtual void pad104();
    virtual void pad108();
    virtual void pad10C();
    virtual void pad110();
    virtual void pad114();
    virtual void pad118();
    virtual void pad11C();
    virtual void pad120();
    virtual void pad124();
    virtual void pad128();
    virtual void pad12C();
    virtual void pad130();
    virtual void pad134();
    virtual void pad138();
    virtual void pad13C();
    virtual void slot140(Team *team);
};

class ContainInterface
{
  public:
    virtual void pad0();
    virtual void pad4();
    virtual void pad8();
    virtual void padC();
    virtual void pad10();
    virtual void pad14();
    virtual void pad18();
    virtual void pad1C();
    virtual void pad20();
    virtual void pad24();
    virtual void pad28();
    virtual void pad2C();
    virtual void pad30();
    virtual void pad34();
    virtual void pad38();
    virtual void pad3C();
    virtual void pad40();
    virtual void pad44();
    virtual void pad48();
    virtual void pad4C();
    virtual void pad50();
    virtual void pad54();
    virtual void pad58();
    virtual void pad5C();
    virtual void pad60();
    virtual void pad64();
    virtual Rva0140Interface *slot68();
};

// Drawable view returned by Object slot10.
class Rva34Interface
{
  public:
    virtual void pad00();
    virtual void pad04();
    virtual void pad08();
    virtual void pad0C();
    virtual void pad10();
    virtual void pad14();
    virtual void pad18();
    virtual void pad1C();
    virtual void pad20();
    virtual void pad24();
    virtual void pad28();
    virtual void pad2C();
    virtual void pad30();
    virtual void slot34();
};

class Object
{
  public:
    virtual void pad0();
    virtual void pad4();
    virtual void pad8();
    virtual void padC();
    virtual void pad10();
    virtual void pad14();
    virtual void pad18();
    virtual void pad1C();
    virtual void pad20();
    virtual void pad24();
    virtual Rva34Interface *pad28();
    virtual void pad2C();
    virtual void pad30();
    virtual void pad34();
    virtual void pad38();
    virtual void pad3C();
    virtual void pad40();
    virtual void pad44();
    virtual void pad48();
    virtual void pad4C();
    virtual void setTeam(Team *team);
    virtual void pad54(Team *team);
    void updateUpgradeModules(); // ILT00027FCF ->001C5800

  private:
    unsigned char m_pad004[0x1fc - 4];
    ContainInterface *m_contain; // +0x1fc
    unsigned char m_pad200[0x23c - 0x200];
    Team *m_team;                   // +0x23c
    AsciiString m_originalTeamName; // +0x240
    unsigned char m_pad244[0x3b0 - 0x244];
    PartitionData *m_partitionData; // +0x3b0
    Rva009F2BA0 *m_field3b4;
    Rva009A2350 *m_field3b8;
};

void Object::setTeam(Team *team)
{
    if (team && !team->getControllingPlayer()->isPlayerActive())
        team = ThePlayerList->m_field14->m_defaultTeam;

    pad54(team);

    if (m_team)
    {
        m_originalTeamName = m_team->getName();
        m_originalTeamName.concat('/');
        m_originalTeamName.concat(m_team->rva14Name());
    }
    else
        m_originalTeamName.clear();

    if (m_partitionData)
        m_partitionData->makeDirty();
    if (m_field3b4)
        m_field3b4->init();
    if (m_field3b8)
        m_field3b8->init();

    if (g_bfmeOwnerBR)
    {
        g_bfmeOwnerBR->rva002E4180(this);
        g_bfmeOwnerBR->rva002E4030(this);
    }

    if (team)
    {
        ContainInterface *contain = m_contain;
        if (contain)
        {
            Rva0140Interface *interfacePtr = contain->slot68();
            if (interfacePtr)
                interfacePtr->slot140(team);
        }

        TheRadar->rva00107A50(this);
        updateUpgradeModules();
    }

    Rva34Interface *result = pad28();
    if (result)
        result->slot34();
}
