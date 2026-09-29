// ?startNewGame@Rva00367810Entries@@QAEXXZ
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// stlport
// Retail 0x00367470 through RET at 0x00367701: 658 bytes, not ledger 644.
// Identity retained from stash: GameLogic::startNewGame invokes this store.
#include <bitset>
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
template<> inline bool StringBase<char>::isEmpty() const {
    return (m_data ? m_data->length : 0)==0;
}
typedef unsigned char ByteBool;
class GameLogic {
    public: bool _bfme_isInLivingWorldCampaign();
    char m_lead[0x90];
    ByteBool m_byte90;
};
extern GameLogic *TheGameLogic;
struct Rva002EE330PlayerList {
    char m_unmodelled[0xc];
    void *m_campaign;
};
extern Rva002EE330PlayerList *ThePlayerList;
extern void j_0001e056();
extern void j_0001df16();
extern void j_0003fe09();
// Typed calls through existing ILT symbols retain their address identity.
// 1E056 -> D42A0 takes a three-word campaign value by pointer.
// 1DF16 -> 10B500 selects the next upgrade from a 192-bit mask.
// 3FE09 -> 367010 takes a coordinate pair and a one-byte flag.
struct Call367470 {
};
template<class R, class A> __forceinline R call1(void (*raw)(), void *self, A a) {
    typedef R(Call367470::*F)(A);
    union {
        void(*raw)();
        F member;
    }
    f;
    f.raw=raw;
    return (((Call367470*)self)->*f.member)(a);
}
template<class R, class A, class B> __forceinline R call2(void (*raw)(), void *self, A a, B b) {
    typedef R(Call367470::*F)(A,B);
    union {
        void(*raw)();
        F member;
    }
    f;
    f.raw=raw;
    return (((Call367470*)self)->*f.member)(a,b);
}
class BfmeSharedString : public AsciiString {
};
__forceinline bool equal367470(const BfmeSharedString &a,const AsciiString &b) {
    return a.StringBase<char>::compare(b)==0;
}
class Rva00361960 {
    public: BfmeSharedString copyString();
};
struct Entry367470 {
    char field00[8];
    ByteBool field08;
    char field09[15];
    int field18;
    int field1c;
    int m_state;
    char field24[0x34];
    void resetState(int state) {
        if(m_state!=1)m_state=state;
    }
    int delay();
    void activate() {
        field08=1;
    }
};
struct Campaign367470 {
    char field00[0x74];
    int field74;
    char field78[0x1c];
    int field94[3];
    int fielda0;
    int fielda4;
    _STL::bitset<192> fielda8;
};
extern Campaign367470 *Campaign;
class UpgradeCenter;
extern UpgradeCenter *TheUpgradeCenter;
class Rva000C9870DwordSlot {
    public: void set(int);
};
class Rva000C97B0DwordSlot {
    public: void set(int);
};
class Upgrade;
class UpgradeTemplate;
enum UpgradeStatusType {
    UPGRADE_STATUS_INVALID,UPGRADE_STATUS_IN_PRODUCTION,UPGRADE_STATUS_COMPLETE
};
struct Player {
    bool addSkillPoints(float,bool);
    Upgrade *addUpgrade(const UpgradeTemplate*,UpgradeStatusType);
    char field00[0x258];
    int m_rankLevel;
    int field25c;
    int field260;
    int m_sciencePurchasePoints;
};
struct Upgrade367470 {
    char field00[0x20];
    unsigned field20;
};
struct GlobalData367470 {
    char field00[0x218];
    int field218;
};
extern GlobalData367470 *TheWritableGlobalData;
inline int Entry367470::delay() {
    return TheWritableGlobalData->field218==4?field1c:field18;
}
class Rva00367810Entries {
    public:
    void startNewGame();
    char m_lead[4];
    AsciiString field04;
    int field08[2];
    ByteBool m_busy;
    char m_pad[3];
    int field14;
    Entry367470 *m_first,*m_last;
};
void Rva00367810Entries::startNewGame() {
    if (!TheGameLogic->_bfme_isInLivingWorldCampaign()) return;
    m_busy=1;
    Player *campaign=(Player*)ThePlayerList->m_campaign;
    if(campaign) {
        ByteBool saved=TheGameLogic->m_byte90;
        TheGameLogic->m_byte90=0;
        campaign->addSkillPoints((float)Campaign->field74,false);
        ((Rva000C9870DwordSlot*)campaign)->set(campaign->m_rankLevel);
        TheGameLogic->m_byte90=saved;
        campaign->m_sciencePurchasePoints=Campaign->fielda0;
        ((Rva000C97B0DwordSlot*)campaign)->set(Campaign->fielda4);
        call1<void>(j_0001e056,campaign,&Campaign->field94);
        _STL::bitset<192> bits=Campaign->fielda8;
        while((int)bits.count()>0) {
            Upgrade367470 *upgrade=call1<Upgrade367470*>(j_0001df16,TheUpgradeCenter,&bits);
            if(!upgrade) break;
            campaign->addUpgrade((const UpgradeTemplate*)upgrade,UPGRADE_STATUS_COMPLETE);
            bits._Unchecked_reset(upgrade->field20);
        }
    }
    if(field04.isEmpty()) {
        for(unsigned i=0;i<(unsigned)(m_last-m_first);++i) m_first[i].resetState(0);
        return;
    }
    {
        for(unsigned i=0;i<(unsigned)(m_last-m_first);++i) {
            bool equal;
            equal=equal367470(((Rva00361960*)(m_first+i))->copyString(),field04);
            if(equal) {
                field14=m_first[i].delay();
                m_first[i].activate();
                call2<void>(j_0003fe09,m_first+i,&field08,true);
            }
            else m_first[i].resetState(0);
        }
        m_busy=0;
        field14=(int)0xff000000;
    }
}
