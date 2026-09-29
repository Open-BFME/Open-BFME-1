// ?applyAttributeModifier@AttributeModifierPoolUpdate@@QAE_NABVAsciiString@@H@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame
// stlport
//
// AttributeModifierPoolUpdate::applyAttributeModifier, retail RVA 0x0036A570,
// 1037 bytes.  Identity: the image's own ILT entry 0x00049585 carries this
// decorated name (targets/game/reverse/symbols.csv) and the matched caller
// Object::applyAttributeModifier (0x001C1DA0,
// game/GameEngine/Source/GameLogic/Object/ObjectContainQueries.cpp) forwards
// the modifier name and duration straight into it; the sibling bodies
// AttributeModifierPoolUpdate::{isModifierActive,getAttributeModifierBonus,
// getAttributeModifierMultiplier,getCountForCategoryMask} all reach this pool's
// definition store at TheAttributeModifierDefinitionStore 0x012F07E4, which is
// the same global this body reads.  EA's own label for the same symbol is
// AttributeModifierPoolUpdate::addModifierToPool
// (targets/game/reverse/ea_evidence.csv 0x0036A570); EA renames are applied by
// tools/ea_queue.py, not by this row.
//
// The pool stores 16-byte entries, and its definition store supplies the two
// ten-word model-condition masks used by Object::clearAndSetModelConditionFlags:
// 0x0036B250 (definition +0x1C) is set, 0x0036B330 (definition +0x44) is cleared.
//
// The existing-modifier FX block is written once per arm of the
// isModifierActive test, and it must be: written once after the test it compiles
// with the receiver copy sunk under the argument pushes (`push 0; push ebx; mov
// ecx,esi; call`), which is three bytes off retail at +0x25C.  Duplicated, the
// two `push 0` nodes stay in the arms and the shared tail is retail's
// `mov ecx,esi; push ebx; call`.  The same effect is visible in the matched
// NAT::doThisConnectionRound (0x006726B0): its two `setConnectionState` arms
// push their state constants and merge on `mov ecx,esi; push edi; call` at +0xBD,
// while the single call at +0x10 sinks.  Full lever list and the
// counter-witnesses: targets/game/reverse/analysis/0x0036a570-fx-call-order.md.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string.h>
#include <bitset>
#include "Libraries/Source/WWVegas/WWLib/ascii_string.h"
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
enum NameKeyType {
};
template <int NUMBITS> class BitFlags {
    public: BitFlags() {
    }
    _STL::bitset<NUMBITS> m_bits;
};
typedef BitFlags<320> ModelConditionFlags;
template<> inline const char *StringBase<char>::str()const {
    return m_data?m_data->data:"";
}
class NameKeyGenerator {
    public:
    NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define OBJECT_TU_MEMBERS void clearAndSetModelConditionFlags(const BitFlags<320>&,const BitFlags<320>&); void giveUpgrade(const UpgradeTemplate*);
class UpgradeTemplate;
#include "GameEngine/Source/GameLogic/Object/object.h"
class PB_DeepBase {
    public:virtual ~PB_DeepBase();
    void *m_f04;
    Object *m_object;
};
class PB_BehaviorModuleInterface {
    public:virtual void behaviorModuleInterfaceAnchor()=0;
};
class PB_UpdateModuleInterface {
    public:virtual unsigned update()=0;
};
class UpdateModule:public PB_DeepBase,public PB_BehaviorModuleInterface,public PB_UpdateModuleInterface {
    public:Object *getObject()const {
        return m_object;
    }
    void setWakeFrame(Object*,unsigned);
    unsigned field14;
    int field18,field1c;
};
struct AttributeModifierEntry {
    Int getIndex()const {
        return m_index;
    }
    Int m_index;
    AsciiString m_unused04;
    // Proven owning string: copy at 0x36A6D6 and destructor at 0x36A961.
    UnsignedInt m_expirationFrame;
    UnsignedInt m_unused0c;
    AttributeModifierEntry(Int index,AsciiString name):m_index(index),m_unused04(name),m_expirationFrame(0),m_unused0c(0) {
    }
    UnsignedInt nextFrame()const {
        return m_unused0c>0?(m_expirationFrame<m_unused0c?m_expirationFrame:m_unused0c):m_expirationFrame;
    }
};
struct DefinitionFlags36A570 {
    unsigned m_bits;
    int getSingleBit()const {
        for(int i=0;i<7;++i)if(m_bits&(1<<(i&31)))return i;
        return -1;
    }
};
struct AttributeModifierDefinition {
    char field00[12];
    DefinitionFlags36A570 m_flags;
};
struct Upgrade36A570 {
    const UpgradeTemplate *value;
    unsigned delay;
};
class FXList {
    public:bool bfmeIsBlocked();
    void doFXObj(const Object*,const Object*)const;
};
class BodyModuleInterface {
    public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    // Slot 0x18 consumes no argument; the pushed 1 belongs to slot 0x58.
    virtual float getValue();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    // Matched ActiveBody evidence identifies slot 0x58 as setMaxHealth.
    virtual void setValue(float,int);
};
class Rva0036B410Subobject;
class Rva0036B410Collection {
    public:
    Rva0036B410Subobject *subobjectAt(int index) const;
};
class AttributeModifierDefinitionStore {
    public:
    Int indexOf(Int key) const;
    Int valueAt(Int index) const;
    ModelConditionFlags rva0036B250ConditionsAt(Int modifierIndex) const;
    ModelConditionFlags copyClearMask(Int modifierIndex) const;
    Int primaryValueAt(Int,const Object*)const;
    Int secondaryValueAt(Int,const Object*)const;
    Bool getValue(Int,Int,float*)const;
    AttributeModifierDefinition *findDefinition(UnsignedInt modifierIndex);
};
// 0x0036B330 twins the pinned 0x0036B250 getter (thiscall, hidden return, ret 8).
#pragma comment(linker, "/alternatename:?copyClearMask@AttributeModifierDefinitionStore@@QBE?AV?$BitFlags@$0BEA@@@H@Z=?j_00018e3f@@YAXXZ")
extern AttributeModifierDefinitionStore *TheAttributeModifierDefinitionStore;
class Rva00367E30Logic {
    private:
    unsigned char m_unreconstructed[0x3c];
    public:
    UnsignedInt m_frame;
    UnsignedInt getFrame()const {
        return m_frame;
    }
};
extern Rva00367E30Logic *TheBfmeGameLogic;
class AttributeModifierPoolUpdate : public UpdateModule {
    public:
    Bool applyAttributeModifier(const AsciiString &name, Int duration);
    private:
    std::vector<AttributeModifierEntry> m_modifiers;
    UnsignedInt m_nextExpiration;
    UnsignedInt m_activationFrames[7];
    Int m_counts[7];
    Bool isModifierActive(UnsignedInt,const AttributeModifierEntry*)const;
};
// Taking the object as a parameter evaluates getObject() before the empty mask.
static inline void setConditions36A570(Object *object,const ModelConditionFlags &set) {
    object->clearAndSetModelConditionFlags(ModelConditionFlags(),set);
}
static inline void clearConditions36A570(Object *object,const ModelConditionFlags &clr) {
    object->clearAndSetModelConditionFlags(clr,ModelConditionFlags());
}
Bool AttributeModifierPoolUpdate::applyAttributeModifier(const AsciiString&name,Int duration) {
    const char *text=name.str();
    NameKeyType key=TheNameKeyGenerator->nameToKey(text);
    Int index=TheAttributeModifierDefinitionStore->indexOf((Int)key);
    if(index<0)return false;
    UnsignedInt frame=TheBfmeGameLogic->m_frame;
    std::vector<AttributeModifierEntry>::iterator it=m_modifiers.begin();
    for(;it!=m_modifiers.end();++it) {
        if(it->m_index==index) {
            Int length=duration;
            if(length<0)length=TheAttributeModifierDefinitionStore->valueAt(index);
            if(length)it->m_expirationFrame=frame+length;
            else it->m_expirationFrame=0x3fffffff;
            if(it->m_expirationFrame<m_nextExpiration) {
                m_nextExpiration=it->m_expirationFrame;
                setWakeFrame(m_object,length);
            }
            if(isModifierActive(frame,it)) {
                FXList *fx=(FXList*)TheAttributeModifierDefinitionStore->primaryValueAt(it->m_index,getObject());
                if(fx) {
                    Object *object=m_object;
                    if(!fx->bfmeIsBlocked())fx->doFXObj(object,0);
                }
            } else {
                FXList *fx=(FXList*)TheAttributeModifierDefinitionStore->secondaryValueAt(it->m_index,getObject());
                if(fx) {
                    Object *object=m_object;
                    if(!fx->bfmeIsBlocked())fx->doFXObj(object,0);
                }
            }
            return true;
        }
    }
    {
        ModelConditionFlags flags=TheAttributeModifierDefinitionStore->rva0036B250ConditionsAt(index);
        setConditions36A570(getObject(),flags);
        flags=TheAttributeModifierDefinitionStore->copyClearMask(index);
        clearConditions36A570(getObject(),flags);
        AttributeModifierEntry entry(index,name);
        Int length=duration;
        if(length<0)length=TheAttributeModifierDefinitionStore->valueAt(index);
        UnsignedInt expiration=length>0?length:0;
        entry.m_expirationFrame=expiration?frame+expiration:0x3fffffff;
        Upgrade36A570 *upgrade=(Upgrade36A570*)((const Rva0036B410Collection*)TheAttributeModifierDefinitionStore)->subobjectAt(index);
        if(upgrade->value) {
            if(!upgrade->delay)getObject()->giveUpgrade(upgrade->value);
            else entry.m_unused0c=frame+upgrade->delay;
        }
        UnsignedInt next=entry.nextFrame();
        if(next<m_nextExpiration) {
            m_nextExpiration=next;
            setWakeFrame(getObject(),expiration);
        }
        if(isModifierActive(TheBfmeGameLogic->getFrame(),&entry)) {
            Drawable *draw=m_object->getDrawable();
            if(draw) {
                FXList *fx=(FXList*)TheAttributeModifierDefinitionStore->primaryValueAt(entry.m_index,getObject());
                if(fx) {
                    Object *object=m_object;
                    if(!fx->bfmeIsBlocked())fx->doFXObj(object,0);
                }
            }
        }
        float amount=0;
        TheAttributeModifierDefinitionStore->getValue(entry.m_index,13,&amount);
        if(amount>0.0f) {
            BodyModuleInterface *body=m_object->m_body;
            if(body)body->setValue(body->getValue()+amount,1);
        }
        m_modifiers.push_back(entry);
        AttributeModifierDefinition *definition=TheAttributeModifierDefinitionStore->findDefinition(index);
        if(definition)++m_counts[definition->m_flags.getSingleBit()];
    }
    return true;
}
