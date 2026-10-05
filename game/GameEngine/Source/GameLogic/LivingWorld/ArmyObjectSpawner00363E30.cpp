// RVA 0x00363E30: creates retail Objects from a LivingWorldArmy record.
// Called by 0x00367010. Owner identity is unproved, so its RVA remains in the name.
// Object restore fields +0x374..+0x38C and army fields are witnessed by this body.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <list>
#include <bitset>
#include "ascii_string.h"
#include "unicode_string.h"
template<> inline bool StringBase<char>::isEmpty() const {
    return !m_data || !m_data->length;
}
template<int N> class BitFlags {
    public: _STL::bitset<N> m_bits;
};
template<class T> __forceinline T& at363E30(void *p,unsigned offset) {
    return *(T*)((char*)p+offset);
}
struct ObjectRestoreState363E30 {
    int field374,field378,field37c,field380;
    bool field384;
};
#define OBJECT_TU_MEMBERS void setRestoreState363E30(int value) { ObjectRestoreState363E30 &state=at363E30<ObjectRestoreState363E30>(this,0x374); state.field380=value; state.field378=0; state.field384=false; } ContainModuleInterface *getContain() const {return m_contain;} void updateUpgradeModules(); void clearAndSetModelConditionFlags(const BitFlags<320>&,const BitFlags<320>&);
#include "../Object/object.h"
class GameLogic {
    public: char field00[0x90];
    bool field90;
};
extern GameLogic *TheGameLogic;
struct Player363E30 {
    char field00[0x230];
    Team *field230;
    Team *getTeam() {
        return field230;
    }
};
struct PlayerList363E30 {
    char field00[0xc];
    Player363E30 *field0c;
};
class PlayerList;
extern PlayerList *ThePlayerList;
class ThingFactory {
    public: Object *newObject(const ThingTemplate*,Team*,const BitFlags<86>&,unsigned);
};
class BfmeThingFactory {
    public: const ThingTemplate *findTemplate(const AsciiString&);
};
extern ThingFactory *TheThingFactory;
struct ExperienceTracker {
    char field00[0xc];
    float field0c;
    char field10[0x14];
    bool field24;
};
class CreateInterface363E30 {
    public: virtual void slot00();
    virtual void onCreate();
};
class BehaviorInterface363E30 {
    public: virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual CreateInterface363E30 *getCreate();
};
class BehaviorBase363E30 {
    public: virtual void slot00();
    int field04,field08;
};
class BehaviorModule : public BehaviorBase363E30,public BehaviorInterface363E30 {
};
class UpgradeInterface363E30 {
    public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9C();
    virtual void slotA0();
    virtual void slotA4();
    virtual void slotA8();
    virtual void slotAC();
    virtual void apply(const _STL::bitset<192>*,bool);
};
class ContainModuleInterface {
    public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual UpgradeInterface363E30 *getInterface();
};
class LivingWorldArmy {
    public:
    AsciiString getName() const;
    const AsciiString& getLabel()const {
        return field4c;
    }
    BitFlags<320> getFlags()const {
        return field50;
    }
    char field00[8];
    float field08;
    int field0c;
    _STL::bitset<192> field10;
    char field28[0x14];
    int field3c;
    int field40,field44,field48;
    AsciiString field4c;
    BitFlags<320> field50;
    UnicodeString field78;
};
extern void j_0003a279();
extern void j_000326f5();
extern void j_0000faa6();
// ABI read from the calls and their retail targets:
// 3A279 takes Object* and the owner index; 326F5 takes float and bool;
// 0FAA6 takes one bool and returns the linked Object*.
struct Call363E30 {
};
template<class R,class A> __forceinline R call1(void (*raw)(),void*self,A a) {
    typedef R(Call363E30::*F)(A);
    union {
        void(*raw)();
        F member;
    }
    f;
    f.raw=raw;
    return (((Call363E30*)self)->*f.member)(a);
}
template<class R,class A,class B> __forceinline R call2(void (*raw)(),void*self,A a,B b) {
    typedef R(Call363E30::*F)(A,B);
    union {
        void(*raw)();
        F member;
    }
    f;
    f.raw=raw;
    return (((Call363E30*)self)->*f.member)(a,b);
}
class ArmyObjectSpawner00363E30 {
    public:
    void spawn(const LivingWorldArmy *army,int count,_STL::list<Object*> *output);
    int field00,field04;
};
void ArmyObjectSpawner00363E30::spawn(const LivingWorldArmy *army,int count,_STL::list<Object*> *output) {
    Player363E30 *player=reinterpret_cast<PlayerList363E30 *>(ThePlayerList)->field0c;
    if(!player)return;
    const ThingTemplate *thing=((BfmeThingFactory*)TheThingFactory)->findTemplate(army->getName());
    if(!thing)return;
    bool saved=TheGameLogic->field90;
    TheGameLogic->field90=false;
    for(int i=0;i<count;++i) {
        BitFlags<86> status;
        Object *object=TheThingFactory->newObject(thing,player->getTeam(),status,0);
        if(!object) {
            TheGameLogic->field90=saved;
            return;
        }
        for(BehaviorModule **module=object->m_behaviors;*module;++module) {
            CreateInterface363E30 *create=(*module)->getCreate();
            if(create)create->onCreate();
        }
        call2<void>(j_0003a279,TheGameLogic,object,field04);
        float experience=army->field08;
        if(object->m_experienceTracker->field0c < experience) {
            call2<void>(j_000326f5,object->m_experienceTracker,experience,true);
            object->m_experienceTracker->field24=false;
        }
        *(_STL::bitset<192>*)object->m_objectUpgradesCompleted |= army->field10;
        object->updateUpgradeModules();
        at363E30<int>(object,0x374)=army->field3c;
        at363E30<StringBase<unsigned short> >(object,0x388).set(*(const StringBase<unsigned short>*)&army->field78);
        at363E30<int>(object,0x37c)=army->field44;
        object->setRestoreState363E30(army->field48);
        if(!army->getLabel().isEmpty()) at363E30<AsciiString>(object,0x38c)=army->getLabel();
        object->clearAndSetModelConditionFlags(BitFlags<320>(),army->getFlags());
        Object *other=call1<Object*>(j_0000faa6,object,false);
        if(other && other->getContain() && other->getContain()->getInterface())other->getContain()->getInterface()->apply(&army->field10,false);
        output->push_back(object);
    }
    TheGameLogic->field90=saved;
}
