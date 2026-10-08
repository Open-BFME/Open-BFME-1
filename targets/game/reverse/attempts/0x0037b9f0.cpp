// ?update0037B9F0@Rva0037C310Owner@@QAE_NXZ
// partial score=0.9618 date=2026-10-08
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/Thing /Igame/GameEngine/Source/GameClient
// stlport
#include "ascii_string.h"
template <> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length==0; }
template <> inline bool StringBase<char>::isNotEmpty() const { return !isEmpty(); }
class Rva001CF980Result;
#define OBJECT_TU_MEMBERS bool applyAttributeModifier(const AsciiString &,int); Rva001CF980Result *queryAt001CF980();
#include "object.h"
#include "GameLogicObjectLookup.h"
#include "FXListRetail.h"
extern GameLogic *TheBfmeGameLogic;
struct Frame0037B9F0 { char pad00[0x3c]; unsigned frame3c; unsigned getFrame() const { return frame3c; } };
class Rva001CF980Result { public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
    virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual Object *object4c();
};
struct BfmeThingFCD { void checkAndNotify(); };
struct Config0037B9F0 {
    char pad00[4]; int kind04; char pad08[0x2c]; FXList *fx34;
    char pad38[4]; AsciiString text3c; unsigned delay40; bool flag44; char pad45[3]; int count48;
    int state4c; unsigned delay50;
    unsigned getDelay40() const { return delay40; }
    AsciiString copyString0037B0D0();
};
class Rva0037C310Owner { public:
    bool update0037B9F0();
    Object *object00; Config0037B9F0 *data04; int id08; char pad0c[0x20]; unsigned frame2c,frame30;
};
// ?update0037B9F0@Rva0037C310Owner@@QAE_NXZ
bool Rva0037C310Owner::update0037B9F0()
{
    bool expired=false;
    if(frame2c && ((Frame0037B9F0 *)TheBfmeGameLogic)->frame3c >= frame2c) expired=true;
    bool apply=data04->copyString0037B0D0().isNotEmpty() && ((Frame0037B9F0 *)TheBfmeGameLogic)->getFrame() == frame30+data04->getDelay40();
    if(apply) {
        int count=data04->flag44 ? 0 : data04->count48;
        object00->applyAttributeModifier(data04->copyString0037B0D0(),count);
    }
    if(data04->delay50 && ((Frame0037B9F0 *)TheBfmeGameLogic)->frame3c >= frame30+data04->delay50) {
        AIUpdateInterface *ai=object00->m_ai;
        if(ai) ((BfmeThingFCD *)ai)->checkAndNotify();
    }
    if(data04->fx34) {
        Object *object=object00;
        Rva001CF980Result *query=object->queryAt001CF980();
        if(query) object=query->object4c();
        int id=id08;
        Object *target=TheBfmeGameLogic->findObjectByID(id);
        if(target || !id) {
            if(!object) object=object00;
            FXList *fx=data04->fx34;
            if(fx && !fx->bfmeIsBlocked()) fx->doFXObj(object,target);
        }
    }
    if(data04->kind04==3) {
        Object *target=TheBfmeGameLogic->findObjectByID(id08);
        if(!target || (target->m_privateStatus&1)) expired=true;
    }
    return !expired;
}
