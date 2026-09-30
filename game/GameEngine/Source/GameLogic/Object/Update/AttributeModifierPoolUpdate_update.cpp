// ?update@AttributeModifierPoolUpdate@@UAE?AW4UpdateSleepTime@@XZ
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// AttributeModifierPoolUpdate::update, retail RVA 0x0036A140 (vtable 010E9208 slot 0, the
// secondary update interface at this+8). Expires pool entries, queues delayed upgrades and
// returns the sleep time; the field references outlive ++it, as retail's split addresses show.
#include <bitset>
#include <deque>
#include <vector>
#include <new>
#include "ascii_string.h"
template<int N> class BitFlags;
class UpgradeTemplate;
#define OBJECT_TU_MEMBERS void clearAndSetModelConditionFlags(const BitFlags<320>&,const BitFlags<320>&); void giveUpgrade(const UpgradeTemplate*);
#include "GameEngine/Source/GameLogic/Object/object.h"
template<int N> class BitFlags {
    public: BitFlags() {
    }
    _STL::bitset<N> m_bits;
};
struct AttributeModifierEntry {
    int m_index;
    AsciiString m_name;
    unsigned m_expirationFrame;
    unsigned m_upgradeFrame;
};
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
// Spelling pinned in symbols.csv for ILT 0x0001DBBA (findDefinition's return type).
struct AttributeModifierDefinition {
    char field00[12];
    DefinitionFlags36A140 m_flags;
};
struct Upgrade36A140 {
    const UpgradeTemplate *value;
    unsigned delay;
};
class FXList {
    public:bool bfmeIsBlocked();
    void doFXObj(const Object*,const Object*)const;
};
class AttributeModifierDefinitionStore {
    public:BitFlags<320> rva0036B250ConditionsAt(int)const;
    int secondaryValueAt(int,const Object*)const;
    AttributeModifierDefinition *findDefinition(unsigned);
};
extern AttributeModifierDefinitionStore *TheAttributeModifierDefinitionStore;
class Rva0036B410Subobject;
class Rva0036B410Collection {
    public:Rva0036B410Subobject *subobjectAt(int index)const;
};
class GameLogic {
    public:char field00[0x3c];
    unsigned m_frame;
};
extern GameLogic *TheGameLogic;
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
        unsigned &upgrade=it->m_upgradeFrame;
        if(upgrade>0 && frame>=upgrade) {
            pending.push_back(*(const ModifierKey0036A140*)&it->m_index);
            upgrade=0;
        }
        const unsigned &expiration=it->m_expirationFrame;
        if(frame>=expiration) {
            BitFlags<320> clear=TheAttributeModifierDefinitionStore->rva0036B250ConditionsAt(it->m_index);
            getObject()->clearAndSetModelConditionFlags(clear,BitFlags<320>());
            if(upgrade<=frame) {
                FXList *fx=(FXList*)TheAttributeModifierDefinitionStore->secondaryValueAt(it->m_index,getObject());
                if(fx) {
                    Object *object=getObject();
                    if(!fx->bfmeIsBlocked())fx->doFXObj(object,0);
                }
                AttributeModifierDefinition *definition=TheAttributeModifierDefinitionStore->findDefinition(it->m_index);
                if(definition)--m_counts[definition->m_flags.getSingleBit()];
                it=m_modifiers.erase(it);
            }
            else {
                ++it;
                next=next<upgrade?next:upgrade;
            }
        }
        else {
            ++it;
            unsigned soonest=next<(upgrade>0?(expiration<upgrade?expiration:upgrade):expiration)?next:(upgrade>0?(expiration<upgrade?expiration:upgrade):expiration);
            next=soonest;
        }
    }
    m_nextExpiration=next<0x3fffffff?next:0x3fffffff;
    while(!pending.empty()) {
        Upgrade36A140 *upgrade=(Upgrade36A140*)((const Rva0036B410Collection*)TheAttributeModifierDefinitionStore)->subobjectAt(pending.front().value);
        if(upgrade && upgrade->value)getObject()->giveUpgrade(upgrade->value);
        pending.pop_front();
    }
    if(m_nextExpiration<0x3fffffff)return (UpdateSleepTime)(m_nextExpiration-frame);
    m_nextExpiration=0x3fffffff;
    return UPDATE_SLEEP_FOREVER;
}
