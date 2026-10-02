// cl: /DNDEBUG /MD /EHsc /O2 /D_STLP_USE_STATIC_LIB
// stlport
#include <list>
#include <vector>
#include <map>
#include <hash_map>

template<class T> class StringBase
{
public:
    ~StringBase() { releaseBuffer(); }
private:
    void releaseBuffer();
    T *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    ~AsciiString() {}
};

class Rva000D0430IntFourByteTree { public: ~Rva000D0430IntFourByteTree(); char bytes[12]; };
class Rva000D0310IntFourByteTree { public: ~Rva000D0310IntFourByteTree(); char bytes[12]; };
class Rva000D8250AsciiStringFourByteHash { public: ~Rva000D8250AsciiStringFourByteHash(); char bytes[20]; };
class Rva000D8330AsciiStringFourByteHash { public: ~Rva000D8330AsciiStringFourByteHash(); char bytes[20]; };

struct TeamPrototype000DD440
{
    char pad[8];
    void *owner;
    void friend_setOwningPlayer(void *player) { owner = player; }
};

struct Timer000DD440 { unsigned int id, frame; };

class Deletable000DD440
{
public:
    virtual ~Deletable000DD440();
};

class BfmeBaseVUQ
{
public:
    virtual ~BfmeBaseVUQ() {}
};

void __cdecl bfmeFreeScalar(void *block);
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);

class BfmeVecMemberY
{
public:
    ~BfmeVecMemberY()
    {
        int *start = m_start;
        if (start) {
            unsigned int bytes = sizeof(int) * (m_end - start);
            if (bytes > 0x80) bfmeFreeScalar(start);
            else bfmeDeallocate(start, bytes);
        }
    }
private:
    int *m_start;
    int *m_finish;
    int *m_end;
};

namespace {
class Gen_000D1730 : public BfmeBaseVUQ
{
public:
    virtual ~Gen_000D1730() {}
    virtual void bfmePure000D1730() {}
private:
    int m_field;
    BfmeVecMemberY m_vector;
};
}

class Gen_uwm_0002cd7c
{
public:
    ~Gen_uwm_0002cd7c();
    char bytes[0x2ec];
};

class Gen_uw_0002a081
{
public:
    ~Gen_uw_0002a081();
    char bytes[12];
};

class Rva000DD430RecordWrapper
{
public:
    ~Rva000DD430RecordWrapper() {}
private:
    unsigned int m_reserved;
    Gen_uw_0002a081 m_records;
};

class Player : public BfmeBaseVUQ
{
protected:
    virtual ~Player();
public:
    virtual void bfmeVirtual000DD440() = 0;
private:
    void *m_playerTemplate;                   // +0x004
    StringBase<unsigned short> m_displayName;// +0x008
    char pad00c[0x10];                       // +0x00c
    AsciiString m_playerName;                // +0x01c
    char pad020[8];                          // +0x020
    AsciiString m_side;                      // +0x028
    char pad02c[4];                          // +0x02c
    BfmeBaseVUQ m_member30;                  // +0x030
    char pad034[0x14];                       // +0x034
    BfmeBaseVUQ m_member48;                  // +0x048
    char pad04c[0x24];                       // +0x04c
    void *m_battlePlanBonuses;               // +0x070
    char pad074[0x30];                       // +0x074
    BfmeBaseVUQ m_memberA4;                  // +0x0a4
    char pad0a8[0xc];                        // +0x0a8
    BfmeBaseVUQ m_memberB4;                  // +0x0b4
    char pad0b8[0x114];                      // +0x0b8
    Rva000D0310IntFourByteTree m_tree1;    // +0x1cc
    Rva000D8250AsciiStringFourByteHash m_hash1; // +0x1d8
    Rva000D8250AsciiStringFourByteHash m_hash2; // +0x1ec
    Rva000D8330AsciiStringFourByteHash m_hash3; // +0x200
    Rva000D0430IntFourByteTree m_tree2;    // +0x214
    char pad220[0x10];                       // +0x220
    void *m_defaultTeam;                    // +0x230
    std::vector<int> m_sciences;             // +0x234
    std::vector<int> m_sciencesDisabled;     // +0x240
    std::vector<int> m_sciencesHidden;       // +0x24c
    char pad258[0x18];                       // +0x258
    StringBase<unsigned short> m_generalName;// +0x270
    Gen_000D1730 m_member274;               // +0x274
    std::list<TeamPrototype000DD440 *> m_playerTeamPrototypes; // +0x288
    Deletable000DD440 *m_playerRelations;   // +0x28c
    Deletable000DD440 *m_teamRelations;     // +0x290
    char pad294[0xb4];                       // +0x294
    Gen_uwm_0002cd7c m_scoreKeeper;         // +0x348
    char pad634[0xc];                        // +0x634
    std::list<void *> m_kindChanges;        // +0x640
    char pad644[8];                          // +0x644
    std::list<void *> m_otherList;          // +0x64c
    std::list<Timer000DD440> m_timers;       // +0x650
    Deletable000DD440 *m_squads[10];        // +0x654
    Deletable000DD440 *m_currentSelection;  // +0x67c
    char pad680[4];                          // +0x680
    Rva000DD430RecordWrapper m_records;     // +0x684
    char pad694[4];                          // +0x694
    AsciiString m_tail;                      // +0x698
};

Player::~Player()
{
    m_defaultTeam = 0;
    m_playerTemplate = 0;
    for (std::list<TeamPrototype000DD440 *>::iterator it = m_playerTeamPrototypes.begin(); it != m_playerTeamPrototypes.end(); ++it)
        (*it)->friend_setOwningPlayer(0);
    m_playerTeamPrototypes.clear();
    if (m_teamRelations)
        delete m_teamRelations;
    Deletable000DD440 *otherRelation = m_playerRelations;
    if (otherRelation) {
        m_teamRelations = 0;
        delete otherRelation;
    } else {
        m_teamRelations = 0;
    }
    m_playerRelations = 0;
    for (int i=0; i<10; ++i) {
        if (m_squads[i]) {
            delete m_squads[i];
            m_squads[i] = 0;
        }
    }
    if (m_currentSelection) {
        delete m_currentSelection;
        m_currentSelection = 0;
    }
    if (m_battlePlanBonuses) {
        delete (char *)m_battlePlanBonuses;
        m_battlePlanBonuses = 0;
    }
}
