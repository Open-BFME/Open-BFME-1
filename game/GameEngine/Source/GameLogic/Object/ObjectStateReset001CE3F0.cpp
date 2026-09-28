// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <bitset>
// RVA 0x001CE3F0: Object state reset reached by SellList and GameLogic.
// Address-qualified method retains the existing pin; Object layout from object.h.
// Body slots +0xA4 (no args; pointer result) and +0x24 (one zero arg)
// and condition bits 67/68 cleared then 73 set are decoded from retail.
// Native bitset accessor layers reproduce retail mask loads and stores.
class ModelConditionFlags { public:
    bool test(int bit) const { return bits.test(bit); }
    void set(int bit) { bits.set(bit); }
    void reset(int bit) { bits.reset(bit); }
private: _STL::bitset<320> bits;
};
enum ObjectStatusTypes { Status3=3, Status19=19 };
#define BFME_HAVE_MODELCONDITIONFLAGS
#define OBJECT_TU_MEMBERS void clearStatus(ObjectStatusTypes status);
#include "object.h"
class BfmeThingBUD { public: void bfmeGoBUD(); };
class BodyState001CE3F0 {
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
    virtual void slot24(int);
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
    virtual BfmeThingBUD *slotA4();
};
class Drawable {
public: void replaceModelConditionState(const ModelConditionFlags &, bool, unsigned int);
};
class AIUpdateInterface { public: virtual void friend_notifyStateMachineChanged(); };
class ObjectSMCHelper { public: void setModelConditionState(int, unsigned int); };
class Rva001CE3F0 : public Object { public: void apply(); };
static __forceinline void notify(Object *object) {
    if (object->m_drawable) object->m_drawable->replaceModelConditionState(object->m_modelConditionFlags, false, 0);
    if (object->m_ai) object->m_ai->AIUpdateInterface::friend_notifyStateMachineChanged();
}
static __forceinline void clearCondition(Object *object, int bit) {
    if (object->m_modelConditionFlags.test(bit)) {
        object->m_modelConditionFlags.reset(bit);
        notify(object);
    }
}
static __forceinline void setCondition(Object *object, int bit) {
    if (!object->m_modelConditionFlags.test(bit)) {
        object->m_modelConditionFlags.set(bit);
        notify(object);
    }
}
void Rva001CE3F0::apply()
{
    BodyState001CE3F0 *body = (BodyState001CE3F0 *)m_body;
    body->slotA4()->bfmeGoBUD();
    body->slot24(0);
    clearStatus(Status3);
    clearStatus(Status19);
    clearCondition(this,67);
    clearCondition(this,68);
    setCondition(this,73);
    (*(ObjectSMCHelper **)((char *)this+0x1dc))->setModelConditionState(0x67,15);
}
