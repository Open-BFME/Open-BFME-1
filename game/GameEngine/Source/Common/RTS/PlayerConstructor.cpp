// cl: /DNDEBUG /MD /EHsc /O2 /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Player::Player(int), retail 0x000DD980, 898 bytes.
// Identity: Player vtable 0x010840CC (PlayerDeletingDestructor.cpp),
// matched PlayerList ctor passes index through ILT 0x00041943;
// layout agrees with PlayerDestructor.cpp and PlayerInit.cpp.
#include <list>
#include <vector>
#include <map>
#include <bitset>
#include <hash_map>
#include "string_base.h"

template<class T> inline StringBase<T>::StringBase() : m_data(0) {}
template<class T> inline StringBase<T>::~StringBase() { releaseBuffer(); }
class AsciiString : private StringBase<char> {
public:
    AsciiString() {}
    AsciiString(const char *text) : StringBase<char>(text) {}
    ~AsciiString() {}
};
class UnicodeString : private StringBase<unsigned short> {
public:
    UnicodeString() {}
    ~UnicodeString() {}
};
class BfmeBaseVUQ { public: virtual ~BfmeBaseVUQ() {} };
class Handicap { public: Handicap(); float m_handicaps[2][2]; };
class Rva000CBAF0 : public BfmeBaseVUQ {
public:
    Rva000CBAF0() : m_04(100),m_08(0),m_0c(0),m_10(0),m_14(0) {}
    virtual ~Rva000CBAF0();
    int m_04,m_08,m_0c,m_10,m_14;
};
class Money : public BfmeBaseVUQ {
public:
    Money() : m_money(0), m_playerIndex(0) {}
    virtual ~Money();
    unsigned int m_money; int m_playerIndex;
};
struct Rva000DD980SixWords {
    Rva000DD980SixWords() {}
    _STL::bitset<192> m_words;
};
class Rva000CBA50 : public BfmeBaseVUQ {
public:
    Rva000CBA50() : m_04(0),m_08(0),m_0c(0) {}
    virtual ~Rva000CBA50();
    int m_04,m_08,m_0c;
};
class Rva000C8480Owner {
public:
    Rva000C8480Owner();
    virtual ~Rva000C8480Owner();
    int m_a[32],m_aCount,m_b[32],m_bCount;
};
enum NameKeyType { NAMEKEY_INVALID=0 };
enum VeterancyLevel { LEVEL_REGULAR=0 };
struct Rva000D63C0Mapped { float m_value; };
// Same AsciiString-keyed tables as matched PlayerInit.cpp.
namespace rts { template<class T> struct hash { unsigned int operator()(T value) const; }; }
struct Rva000D6770Value { AsciiString m_key; int m_mapped; };
struct Rva000D6770ExtractKey {
    const AsciiString &operator()(const Rva000D6770Value &x) const { return x.m_key; }
};
enum Rva000D6C60Mapped { Rva000D6C60MappedZero=0 };
typedef _STL::hashtable<Rva000D6770Value,AsciiString,rts::hash<AsciiString>,
    Rva000D6770ExtractKey,_STL::equal_to<AsciiString>,_STL::allocator<Rva000D6770Value> > HashA;
typedef _STL::pair<const AsciiString,Rva000D6C60Mapped> HashBValue;
typedef _STL::hashtable<HashBValue,AsciiString,rts::hash<AsciiString>,
    _STL::_Select1st<HashBValue>,_STL::equal_to<AsciiString>,_STL::allocator<HashBValue> > HashBTable;
typedef _STL::hash_map<AsciiString,Rva000D6C60Mapped,rts::hash<AsciiString> > HashB;
template<> void HashA::_M_initialize_buckets(unsigned int);
template<> void HashBTable::_M_initialize_buckets(unsigned int);
class Gen_000D1730 : public BfmeBaseVUQ {
public:
    Gen_000D1730() : m_field(0) {}
    virtual ~Gen_000D1730() {}
    virtual void bfmePure000D1730() {}
    int m_field;
    _STL::vector<int> m_vector;
};
class ScoreKeeper { public: ScoreKeeper(); virtual ~ScoreKeeper(); char bytes[0x2e8]; };
// PlayerDestructor.cpp establishes the twelve-byte cleanup member at +4.
class Gen_uw_0002a081 { public: ~Gen_uw_0002a081(); char bytes[12]; };
class BfmeOwnCC {
public:
    BfmeOwnCC(void *);
    virtual void bfmePureCC();
    Gen_uw_0002a081 m_bfmeSubCC;
    void *m_bfmeValueCC;
};
class PlayerTemplate;
struct BfmeVec;
class ExperienceLevelSystem { public: BfmeVec *findExperienceScalarTable(const AsciiString &); };
extern ExperienceLevelSystem *TheExperienceLevelSystem;
struct Timer000DD440 { unsigned int id,frame; };
class Player : public BfmeBaseVUQ {
public:
    Player(int playerIndex);
protected:
    virtual ~Player();
public:
    void init(const PlayerTemplate *);
    void *m_playerTemplate;
    UnicodeString m_playerDisplayName;
    Handicap m_handicap;
    AsciiString m_playerName;
    int m_playerNameKey;
    int m_playerIndex;
    AsciiString m_side;
    int m_playerType;
    Rva000CBAF0 m_member30;
    Money m_money;
    void *m_upgradeList;
    int m_radarCount,m_disableProofRadarCount,m_radarDisabled;
    int m_bombardBattlePlans,m_holdTheLineBattlePlans,m_searchAndDestroyBattlePlans;
    void *m_battlePlanBonuses;
    Rva000DD980SixWords m_flags74,m_flags8c;
    Rva000CBA50 m_energy;
    Rva000C8480Owner m_stats;
    void *m_1c0;
    int m_color,m_nightColor;
    _STL::map<NameKeyType,Rva000D63C0Mapped> m_productionCostChanges;
    HashA m_hash1,m_hash2;
    HashB m_hash3;
    _STL::map<NameKeyType,VeterancyLevel> m_productionVeterancyLevels;
    void *m_ai;
    int m_224;
    void *m_228,*m_22c,*m_defaultTeam;
    _STL::vector<int> m_sciences,m_sciencesDisabled,m_sciencesHidden;
    int m_rankLevel,m_skillPoints,m_260,m_sciencePurchasePoints,m_268,m_levelDown;
    UnicodeString m_generalName;
    Gen_000D1730 m_member274;
    _STL::list<void *> m_playerTeamPrototypes;
    void *m_playerRelations,*m_teamRelations;
    char m_294[0xb4];
    ScoreKeeper m_scoreKeeper;
    char m_634[0xc];
    _STL::list<void *> m_kindChanges;
    int m_644,m_648;
    _STL::list<void *> m_otherList;
    _STL::list<Timer000DD440> m_timers;
    void *m_squads[10],*m_currentSelection;
    int m_isPlayerDead;
    BfmeOwnCC m_records;
    AsciiString m_tail;
    BfmeVec *m_skillPointsScalarTable;
};
#include <stddef.h>
typedef char check_1cc[offsetof(Player,m_productionCostChanges)==0x1cc?1:-1];
typedef char check_348[offsetof(Player,m_scoreKeeper)==0x348?1:-1];
typedef char check_698[offsetof(Player,m_tail)==0x698?1:-1];
Player::Player(int playerIndex)
    : m_hash1(100,rts::hash<AsciiString>(),_STL::equal_to<AsciiString>()),
      m_hash2(100,rts::hash<AsciiString>(),_STL::equal_to<AsciiString>()),
      m_records(this)
{
    m_playerIndex=playerIndex;
    m_battlePlanBonuses=0;
    m_upgradeList=0;
    m_1c0=0;
    m_ai=0;
    m_228=0;
    m_22c=0;
    m_currentSelection=0;
    m_playerRelations=0;
    m_teamRelations=0;
    for(int i=0;i<10;++i) m_squads[i]=0;
    m_skillPointsScalarTable=TheExperienceLevelSystem->findExperienceScalarTable(AsciiString("PlayerSkillPointsScalarTable"));
    init(0);
}


