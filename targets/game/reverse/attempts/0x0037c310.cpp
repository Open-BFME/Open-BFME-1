// ?d_0037c310@@YAXXZ
// partial score=0.4337606837606838 date=2026-09-27
// Retail 0x0037C310..0x0037C4E1. Established address-derived identity from
// matched TargetEligibility00290990::accepts and pinned ILT 0x000466B4.
// Two native maps at +0x14/+0x20 record object/template cooldown frames.
// The AI/contain virtual declarations are read-only vtable slot views, not
// complete class layouts; no instances or vtables are emitted here.
// Unresolved template helper identities remain to be reconciled if byte exact.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <map>
enum KindOfType { Kind108 = 108 };
enum AIStateType { State45 = 45 };
#define THING_TU_MEMBERS bool isKindOf(KindOfType) const; const ThingTemplate *getTemplate() const;
#define OBJECT_TU_MEMBERS bool bfmeIsComputerControlled() const; void *unidentified_001BFE20() const; bool getAttributeModifierBonus(int,float *) const; AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
#include "object.h"
class AIUpdateInterface { public:
    virtual void slot000();
    virtual void slot004();
    virtual void slot008();
    virtual void slot00C();
    virtual void slot010();
    virtual void slot014();
    virtual void slot018();
    virtual void slot01C();
    virtual void slot020();
    virtual void slot024();
    virtual void slot028();
    virtual void slot02C();
    virtual void slot030();
    virtual void slot034();
    virtual void slot038();
    virtual void slot03C();
    virtual void slot040();
    virtual void slot044();
    virtual void slot048();
    virtual void slot04C();
    virtual void slot050();
    virtual void slot054();
    virtual void slot058();
    virtual void slot05C();
    virtual void slot060();
    virtual void slot064();
    virtual void slot068();
    virtual void slot06C();
    virtual void slot070();
    virtual void slot074();
    virtual void slot078();
    virtual void slot07C();
    virtual void slot080();
    virtual void slot084();
    virtual void slot088();
    virtual void slot08C();
    virtual void slot090();
    virtual void slot094();
    virtual void slot098();
    virtual void slot09C();
    virtual void slot0A0();
    virtual void slot0A4();
    virtual void slot0A8();
    virtual void slot0AC();
    virtual void slot0B0();
    virtual void slot0B4();
    virtual void slot0B8();
    virtual void slot0BC();
    virtual void slot0C0();
    virtual void slot0C4();
    virtual void slot0C8();
    virtual void slot0CC();
    virtual void slot0D0();
    virtual void slot0D4();
    virtual void slot0D8();
    virtual void slot0DC();
    virtual void slot0E0();
    virtual void slot0E4();
    virtual void slot0E8();
    virtual void slot0EC();
    virtual void slot0F0();
    virtual void slot0F4();
    virtual void slot0F8();
    virtual void slot0FC();
    virtual void slot100();
    virtual void slot104();
    virtual void slot108();
    virtual void slot10C();
    virtual void slot110();
    virtual void slot114();
    virtual void slot118();
    virtual void slot11C();
    virtual void slot120();
    virtual void slot124();
    virtual void slot128();
    virtual void slot12C();
    virtual void slot130();
    virtual bool ask134();
    virtual void slot138();
    virtual void slot13C();
    virtual void slot140();
    virtual void slot144();
    virtual void slot148();
    virtual void slot14C();
    virtual void slot150();
    virtual void slot154();
    virtual void slot158();
    virtual void slot15C();
    virtual void slot160();
    virtual void slot164();
    virtual void slot168();
    virtual void slot16C();
    virtual void slot170();
    virtual void slot174();
    virtual void slot178();
    virtual void slot17C();
    virtual bool ask180();
    AIStateType getAIStateType() const;
};
struct ContainView0037C310 {
    virtual void slot000();
    virtual void slot004();
    virtual void slot008();
    virtual void slot00C();
    virtual void slot010();
    virtual void slot014();
    virtual void slot018();
    virtual void slot01C();
    virtual void slot020();
    virtual void slot024();
    virtual void slot028();
    virtual void slot02C();
    virtual void slot030();
    virtual void slot034();
    virtual void slot038();
    virtual void slot03C();
    virtual void slot040();
    virtual void slot044();
    virtual void slot048();
    virtual void slot04C();
    virtual void slot050();
    virtual void slot054();
    virtual void slot058();
    virtual void slot05C();
    virtual void slot060();
    virtual void slot064();
    virtual void slot068();
    virtual void slot06C();
    virtual void slot070();
    virtual void slot074();
    virtual void slot078();
    virtual void slot07C();
    virtual void slot080();
    virtual void slot084();
    virtual void slot088();
    virtual void slot08C();
    virtual void slot090();
    virtual void slot094();
    virtual void slot098();
    virtual void slot09C();
    virtual void slot0A0();
    virtual void slot0A4();
    virtual void slot0A8();
    virtual void slot0AC();
    virtual void slot0B0();
    virtual void slot0B4();
    virtual void slot0B8();
    virtual void slot0BC();
    virtual void slot0C0();
    virtual void slot0C4();
    virtual void slot0C8();
    virtual void slot0CC();
    virtual void slot0D0();
    virtual void slot0D4();
    virtual void slot0D8();
    virtual void slot0DC();
    virtual void slot0E0();
    virtual void slot0E4();
    virtual void slot0E8();
    virtual void slot0EC();
    virtual void slot0F0();
    virtual Object *getF4();
};
class ThingTemplate { public: char pad00[0x478]; unsigned short at478; };
struct GameLogic0037C310 { char pad00[0x3c]; unsigned frame3c; };
extern GameLogic0037C310 *TheGameLogic0037C310;
struct Config0037C310 {
    int at00,at04; bool at08,at09; char pad0a[0x12];
    int at1c,at20,at24,at28; bool at2c,at2d;
};
typedef _STL::map<int,unsigned> ObjectFrameMap0037C310;
typedef _STL::map<unsigned short,unsigned> TemplateFrameMap0037C310;
class Rva0037C310Owner {
public:
    bool Rva0037C310(int a,int b,Object *target);
    Object *object00; const Config0037C310 *data04; char pad08[8]; unsigned frame10;
    ObjectFrameMap0037C310 objects14;
    TemplateFrameMap0037C310 templates20;
};
bool Rva0037C310Owner::Rva0037C310(int a,int b,Object *target)
{
    const Config0037C310 *data=data04;
    if (data->at08 || data->at09) {
        AIUpdateInterface *ai=object00->m_ai;
        if (!ai) return false;
        if (ai->ask180() && !ai->ask134()) {
            if((data=data04)->at08) return false;
        } else if((data=data04)->at09) return false;
    }
    if (data->at2c || data->at2d) {
        bool computer=object00->bfmeIsComputerControlled();
        data=data04;
        if(computer) {
            if(data->at2d) return false;
        } else if(data->at2c) return false;
    }
    if(data->at1c*a+data->at20>=0) return false;
    if(data->at24*b+data->at28>=0) return false;
    unsigned frame=TheGameLogic0037C310->frame3c;
    if(frame<frame10) return false;
    if(target) {
        int id=target->m_id;
        ObjectFrameMap0037C310::iterator it=objects14.find(id);
        if(it!=objects14.end()) {
            if(frame<it->second) return false;
            objects14.erase(it);
        }
        unsigned short type=target->getTemplate()->at478;
        TemplateFrameMap0037C310::iterator ti=templates20.find(type);
        if(ti!=templates20.end()) {
            if(TheGameLogic0037C310->frame3c<ti->second) return false;
            templates20.erase(ti);
        }
    }
    int kind=data04->at04;
    if(kind>=4 && kind<=7) {
        Object *object=object00;
        bool allowed=true;
        float bonus=0;
        if(object) {
            if(object->isKindOf(Kind108))
                object=((ContainView0037C310 *)object->unidentified_001BFE20())->getF4();
            if(object) {
                if(object->getAttributeModifierBonus(4,&bonus)) allowed=bonus<0.5f;
                if(object->getAIUpdateInterface() && object->getAIUpdateInterface()->getAIStateType()==State45) return false;
                if(!allowed) return false;
            }
        }
    }
    return true;
}
