// Retail 0x0037C030..0x0037C24F (543 bytes).
// The owner layout is shared with the established Rva0037C310Owner predicate:
// object +0; data +4; last target ID +8; template ID +0xC; frame +0x30.
// This method records the target, applies the configured FX and model states,
// then resolves and dispatches a named Lua event with a DelayedLuaEventList.
// The original method/owner names remain unproved, so addresses are retained.
// Template override accessor follows the matched Thing_isKindOf.cpp helper;
// getID/getTemplateID use the native ZH accessor shapes with retail offsets.
// The explicit early null return is significant to MSVC 7.1 code generation.
// String view mirrors ascii_string.h's four-byte handle and 8-byte header.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object
#include "ascii_string.h"
class Rva001CF980Result;
class ThingTemplate;
class Overridable { public: const Overridable *getFinalOverride() const; void *vtable; Overridable *next04; };
class ThingTemplate : public Overridable { public: char pad08[0x470]; unsigned short at478; unsigned short getTemplateID() const { return at478; } };
#define THING_TU_MEMBERS const ThingTemplate *getTemplate() const { if(!m_template) return 0; if(m_template->next04) return (const ThingTemplate *)m_template->next04->getFinalOverride(); return m_template; } bool isSignificantlyAboveTerrain() const;
#define OBJECT_TU_MEMBERS int getID() const { return m_id; } Rva001CF980Result *queryAt001CF980(); void rva001CD300(int,int); void notifyModelConditionChanged(); void clearAndSetModelConditionFlags(const ModelConditionFlags &,const ModelConditionFlags &);
class ModelConditionFlags { public: unsigned bits[10]; void set(int i) { bits[i>>5] |= 1u << (i&31); } unsigned test(int i) const { return bits[i>>5] & (1u << (i&31)); } };
#define BFME_HAVE_MODELCONDITIONFLAGS
#include "object.h"
class Rva001CF980Result { public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
    virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual Object *object4c();
};
class FXList { public: bool bfmeIsBlocked(); void doFXObj(const Object *,const Object *) const; };
class Rva0026FBE0Owner { public: void selectState(int,int); };
class DelayedLuaEventList { public: DelayedLuaEventList(); virtual ~DelayedLuaEventList(); char events04[0x48]; };
class BfmeOwnerBR { public: void bfmeTail939B(struct BfmeElem939B *,Object *,DelayedLuaEventList *); };
// VA 0x012F060C is TheLuaScriptEngine (data_rows.csv, defined in
// Team_updateState.cpp); BfmeOwnerBR is the address-derived view.
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
class Rva002E4CA0 { public: void *rva002E4CA0(int) const; };
enum NameKeyType { InvalidKey=-1 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
struct GameLogic0037C030 { char pad00[0x3c]; unsigned frame3c; };
extern GameLogic0037C030 *TheGameLogic0037C030;
struct NarrowHeader0037C030 { int refs; unsigned short len,cap; char text[1]; };
inline const NarrowHeader0037C030 *header0037C030(const AsciiString &s) { return *(const NarrowHeader0037C030 *const *)&s; }
inline bool empty0037C030(const AsciiString &s) { const NarrowHeader0037C030 *p=header0037C030(s); return !p || !p->len; }
inline const char *text0037C030(const AsciiString &s) { const NarrowHeader0037C030 *p=header0037C030(s); return p?p->text:""; }
struct Config0037C030 {
    char pad00[0xc]; unsigned delay0c; char pad10[0x20]; FXList *fx30; char pad34[0x18]; int state4c;
    char pad50[4]; ModelConditionFlags flags54; char pad7c[0x28]; ModelConditionFlags flagsa4;
    AsciiString copyString0037B100();
};
class Rva0037C310Owner { public:
    void apply0037C030(Object *target);
    Object *object00; Config0037C030 *data04; int id08; unsigned short type0c; char pad0e[0x1e]; unsigned frame2c,frame30;
};
void Rva0037C310Owner::apply0037C030(Object *target)
{
    unsigned frame=TheGameLogic0037C030->frame3c;
    frame30=frame;
    if(target) { id08=target->getID(); type0c=target->getTemplate()->getTemplateID(); }
    else { id08=0; type0c=0; }
    frame2c=data04->delay0c ? frame+data04->delay0c : 0;
    if(data04->fx30) {
        Object *object=object00;
        Rva001CF980Result *query=object->queryAt001CF980();
        if(query) object=query->object4c();
        if(!object) object=object00;
        FXList *fx=data04->fx30;
        if(fx && !fx->bfmeIsBlocked()) fx->doFXObj(object,target);
    }
    AIUpdateInterface *ai=object00->m_ai;
    if(ai) {
        int state=data04->state4c;
        if(state==0 || (state>1 && state<=5)) ((Rva0026FBE0Owner *)ai)->selectState(state,(int)target);
        if(object00->queryAt001CF980()) object00->rva001CD300((int)&data04->flagsa4,(int)&data04->flags54);
        else object00->clearAndSetModelConditionFlags(data04->flagsa4,data04->flags54);
        if(target && target->isSignificantlyAboveTerrain()) {
            Object *object=object00;
            if(!(object->m_modelConditionFlags.bits[5]&0x40000000)) { object->m_modelConditionFlags.bits[5]|=0x40000000; object->notifyModelConditionChanged(); }
        }
        if(!empty0037C030(data04->copyString0037B100())) {
            BfmeElem939B *event=(BfmeElem939B *)((Rva002E4CA0 *)TheLuaScriptEngine)->rva002E4CA0(TheNameKeyGenerator->nameToKey(text0037C030(data04->copyString0037B100())));
            if(event) { DelayedLuaEventList list; ((BfmeOwnerBR *)TheLuaScriptEngine)->bfmeTail939B(event,object00,&list); }
        }
    }
}
