// ?update@AttributeModifierPoolUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.884 date=2026-09-28
// UpdateSleepTime return type follows UpdateModuleInterface::update in the ZH header
// and landed BFME update methods; vtable 010E9208 slot 0 identifies this override.
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <bitset>
#include <deque>
#include <vector>
#include <new>
#include "ascii_string.h"
template<int N> class BitFlags;
#define OBJECT_TU_MEMBERS void clearAndSetModelConditionFlags(const BitFlags<320>&,const BitFlags<320>&);
#include "GameEngine/Source/GameLogic/Object/object.h"
template<int N> class BitFlags {
    public: _STL::bitset<N> m_bits;
};
struct AttributeModifierEntry {
    int m_index;
    AsciiString m_name;
    unsigned m_expirationFrame;
    unsigned m_upgradeFrame;
    const unsigned& expiration()const {
        return m_expirationFrame;
    }
    const unsigned& upgrade()const {
        return m_upgradeFrame;
    }
    void setUpgrade(unsigned value) {
        m_upgradeFrame=value;
    }
    unsigned nextFrame()const {
        return m_upgradeFrame>0 ? (m_expirationFrame<m_upgradeFrame?m_expirationFrame:m_upgradeFrame):m_expirationFrame;
    }
};
struct Call36A140 {
};
template<class R> __forceinline R call0(void(*raw)(),void*self) {
    typedef R(Call36A140::*F)();
    union {
        void(*raw)();
        F member;
    }
    f;
    f.raw=raw;
    return (((Call36A140*)self)->*f.member)();
}
template<class R,class A> __forceinline R call1(void(*raw)(),void*self,A a) {
    typedef R(Call36A140::*F)(A);
    union {
        void(*raw)();
        F member;
    }
    f;
    f.raw=raw;
    return (((Call36A140*)self)->*f.member)(a);
}
template<class R,class A,class B> __forceinline R call2(void(*raw)(),void*self,A a,B b) {
    typedef R(Call36A140::*F)(A,B);
    union {
        void(*raw)();
        F member;
    }
    f;
    f.raw=raw;
    return (((Call36A140*)self)->*f.member)(a,b);
}
extern void j_0001fae6();
extern void j_0002694a();
extern void j_000343ba();
extern void j_00036c82();
extern void j_00002955();
extern void j_000095ed();
extern void j_0001dbba();
extern void j_0002b1a2();
extern void j_0001a97e();
struct ModifierKey0036A140 {
    int value;
};
struct DefinitionFlags36A140 {
    unsigned m_bits;
    int getSingleBit()const {
        for(int i=0;i<7;++i)if(m_bits&(1<<(i&31)))return i;
        return -1;
    }
};
struct Definition36A140 {
    char field00[12];
    DefinitionFlags36A140 m_flags;
};
struct Upgrade36A140 {
    const void *value;
    unsigned delay;
};
class FXList {
    public:bool bfmeIsBlocked();
    void doFXObj(const Object*,const Object*)const;
};
class AttributeModifierDefinitionStore {
    public:BitFlags<320> rva0036B250ConditionsAt(int)const;
    int secondaryValueAt(int,const Object*)const;
};
extern AttributeModifierDefinitionStore *TheAttributeModifierDefinitionStore;
struct GameLogic36A140 {
    char field00[0x3c];
    unsigned m_frame;
};
extern GameLogic36A140 *TheGameLogic;
class PB_DeepBase {
    public:virtual ~PB_DeepBase();
    void *m_f04;
    Object *m_object;
};
class PB_BehaviorModuleInterface {
    public:virtual void behaviorModuleInterfaceAnchor()=0;
};
enum UpdateSleepTime {
    UPDATE_SLEEP_FOREVER=0x3fffffff
};
class PB_UpdateModuleInterface {
    public:virtual UpdateSleepTime update()=0;
};
class UpdateModule:public PB_DeepBase,public PB_BehaviorModuleInterface,public PB_UpdateModuleInterface {
    public: unsigned field14;
    int field18,field1c;
};
class AttributeModifierPoolUpdate:public UpdateModule {
    public:
    virtual UpdateSleepTime update();
    Object *getObject()const {
        return m_object;
    }
    _STL::vector<AttributeModifierEntry> m_modifiers;
    unsigned m_nextExpiration;
    char field30[0x1c];
    int m_counts[7];
};
UpdateSleepTime AttributeModifierPoolUpdate::update() {
    unsigned frame=TheGameLogic->m_frame;
    unsigned next=0x3fffffff;
    _STL::deque<ModifierKey0036A140> pending;
    for(AttributeModifierEntry *it=m_modifiers.begin();it!=m_modifiers.end();) {
        if(it->m_upgradeFrame>0 && frame>=it->m_upgradeFrame) {
            pending.push_back(*(const ModifierKey0036A140*)&it->m_index);
            it->m_upgradeFrame=0;
        }
        if(frame>=it->m_expirationFrame) {
            unsigned clear[10];
            call2<void>(j_0001fae6,TheAttributeModifierDefinitionStore,clear,it->m_index);
            BitFlags<320> set;
            call2<void>(j_000095ed,getObject(),clear,&set);
            if(it->m_upgradeFrame<=frame) {
                FXList *fx=(FXList*)TheAttributeModifierDefinitionStore->secondaryValueAt(it->m_index,getObject());
                if(fx) {
                    Object *object=getObject();
                    if(!fx->bfmeIsBlocked())fx->doFXObj(object,0);
                }
                Definition36A140 *definition=call1<Definition36A140*>(j_0001dbba,TheAttributeModifierDefinitionStore,it->m_index);
                if(definition)--m_counts[definition->m_flags.getSingleBit()];
                it=m_modifiers.erase(it);
            }
            else {
                unsigned due=it->m_upgradeFrame;
                ++it;
                next=next<due?next:due;
            }
        }
        else {
            // Retail evaluates the value-returning minimum twice; keep both evaluations.
            next=next<it->nextFrame()?next:it->nextFrame();
            ++it;
        }
    }
    m_nextExpiration=next<0x3fffffff?next:0x3fffffff;
    while(!pending.empty()) {
        Upgrade36A140 *upgrade=call1<Upgrade36A140*>(j_0002b1a2,TheAttributeModifierDefinitionStore,*(int*)&pending.front());
        if(upgrade && upgrade->value)call1<void>(j_0001a97e,getObject(),upgrade->value);
        pending.pop_front();
    }
    if(m_nextExpiration<0x3fffffff)return (UpdateSleepTime)(m_nextExpiration-frame);
    m_nextExpiration=0x3fffffff;
    return UPDATE_SLEEP_FOREVER;
}
