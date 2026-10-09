// ?update@WoundArrowUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.8645 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <math.h>

#include "Libraries/Include/Lib/Coord3D.h"
#define BFME_HAVE_COORD3D
class WoundArrowConditionBits0026E1F0
{
public:
    bool test(int bit) const { return m_bits.test(bit); }
    void set(int bit) { m_bits.set(bit); }
    void reset(int bit) { m_bits.reset(bit); }
private:
    _STL::bitset<320> m_bits;
};
typedef WoundArrowConditionBits0026E1F0 ModelConditionFlags;
#define BFME_HAVE_MODELCONDITIONFLAGS
#define OBJECT_TU_MEMBERS void notifyModelConditionChanged();
#include "GameEngine/Source/GameLogic/Object/object.h"
#include "GameEngine/Source/GameLogic/command_source_type.h"

enum LocomotorSetType { LOCOMOTORSET_0026E1F0 = 4 };
#define AI_SLOT(n) virtual void slot##n();
class AIUpdateInterface
{
public:
    AI_SLOT(0) AI_SLOT(1) AI_SLOT(2) AI_SLOT(3) AI_SLOT(4) AI_SLOT(5) AI_SLOT(6) AI_SLOT(7)
    AI_SLOT(8) AI_SLOT(9) AI_SLOT(10) AI_SLOT(11) AI_SLOT(12) AI_SLOT(13) AI_SLOT(14) AI_SLOT(15)
    AI_SLOT(16) AI_SLOT(17) AI_SLOT(18) AI_SLOT(19) AI_SLOT(20) AI_SLOT(21) AI_SLOT(22) AI_SLOT(23)
    AI_SLOT(24) AI_SLOT(25) AI_SLOT(26) AI_SLOT(27) AI_SLOT(28) AI_SLOT(29) AI_SLOT(30) AI_SLOT(31)
    AI_SLOT(32) AI_SLOT(33) AI_SLOT(34) AI_SLOT(35) AI_SLOT(36) AI_SLOT(37) AI_SLOT(38) AI_SLOT(39)
    AI_SLOT(40) AI_SLOT(41) AI_SLOT(42) AI_SLOT(43) AI_SLOT(44) AI_SLOT(45) AI_SLOT(46) AI_SLOT(47)
    AI_SLOT(48) AI_SLOT(49) AI_SLOT(50) AI_SLOT(51) AI_SLOT(52) AI_SLOT(53) AI_SLOT(54) AI_SLOT(55)
    AI_SLOT(56) AI_SLOT(57) AI_SLOT(58) AI_SLOT(59) AI_SLOT(60) AI_SLOT(61) AI_SLOT(62) AI_SLOT(63)
    AI_SLOT(64) AI_SLOT(65) AI_SLOT(66) AI_SLOT(67) AI_SLOT(68) AI_SLOT(69) AI_SLOT(70) AI_SLOT(71)
    AI_SLOT(72) AI_SLOT(73) AI_SLOT(74) AI_SLOT(75) AI_SLOT(76) AI_SLOT(77) AI_SLOT(78) AI_SLOT(79)
    AI_SLOT(80) AI_SLOT(81) AI_SLOT(82) AI_SLOT(83) AI_SLOT(84) AI_SLOT(85) AI_SLOT(86) AI_SLOT(87)
    AI_SLOT(88) AI_SLOT(89) AI_SLOT(90) AI_SLOT(91) AI_SLOT(92) AI_SLOT(93) AI_SLOT(94) AI_SLOT(95)
    virtual bool isIdle() const;
    AI_SLOT(97) AI_SLOT(98) AI_SLOT(99) AI_SLOT(100) AI_SLOT(101) AI_SLOT(102) AI_SLOT(103) AI_SLOT(104)
    AI_SLOT(105) AI_SLOT(106) AI_SLOT(107) AI_SLOT(108) AI_SLOT(109) AI_SLOT(110) AI_SLOT(111) AI_SLOT(112)
    AI_SLOT(113) AI_SLOT(114) AI_SLOT(115) AI_SLOT(116) AI_SLOT(117) AI_SLOT(118) AI_SLOT(119) AI_SLOT(120)
    AI_SLOT(121) AI_SLOT(122) AI_SLOT(123) AI_SLOT(124) AI_SLOT(125) AI_SLOT(126)
    virtual bool chooseLocomotorSet(LocomotorSetType);
};
#undef AI_SLOT

struct AIChooseTable0026E1F0
{
    void *m_slots[127];
    bool (AIUpdateInterface::*chooseLocomotorSet)(LocomotorSetType);
};
class AICommandInterface
{
public:
    void aiMoveToPosition(const Coord3D *, CommandSourceType);
};
#include "GameEngine/Source/Common/Thing/GameLogicObjectLookup.h"
extern GameLogic *TheGameLogic;
class BfmeThing916D { public: void bfmeGo916D(void *); };
class WoundArrowUpdate;
class SpecialAbilityUpdate
{
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
    virtual void slot8(); virtual void slot9(); virtual void slot10();
private:
    void onExit(bool, bool);
public:
    virtual void slot11();
public:
    virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void triggerAbilityEffect();
    friend class WoundArrowUpdate;
};
class WoundArrowUpdateModuleData
{
public:
    unsigned char m_pad000[0x254];
    float m_field254;
};
enum UpdateSleepTime { UPDATE_SLEEP_1 = 1, UPDATE_SLEEP_FOREVER = 0x3fffffff };
class WoundArrowUpdate
{
public:
    virtual UpdateSleepTime update();
    Object *getObject() const { return *(Object **)((const char *)this - 8); }
    const WoundArrowUpdateModuleData *getWoundArrowUpdateModuleData() const
    { return *(const WoundArrowUpdateModuleData **)((const char *)this - 0xc); }
private:
    unsigned char m_pad004[0x9c - 4];
    int m_targetID;
    unsigned char m_pad0a0[0xd8 - 0xa0];
    bool m_hasAppliedWound;
};
static __forceinline void setCondition0026E1F0(Object *object, int bit)
{
    if (!object->m_modelConditionFlags.test(bit)) {
        object->m_modelConditionFlags.set(bit);
        object->notifyModelConditionChanged();
    }
}
static __forceinline void clearCondition0026E1F0(Object *object, int bit)
{
    if (object->m_modelConditionFlags.test(bit)) {
        object->m_modelConditionFlags.reset(bit);
        object->notifyModelConditionChanged();
    }
}

// ?update@WoundArrowUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime WoundArrowUpdate::update()
{
    if (!m_hasAppliedWound) {
        ((SpecialAbilityUpdate *)((char *)this - 0x10))->triggerAbilityEffect();
        return UPDATE_SLEEP_1;
    }
    if (!getObject()->m_ai->isIdle())
        return UPDATE_SLEEP_1;
    Object *owner = getObject();
    m_hasAppliedWound = false;
    Object *target = TheGameLogic->findObjectByID(m_targetID);
    if (target) {
        AIUpdateInterface *ai = target->m_ai;
        if (!ai)
            return UPDATE_SLEEP_FOREVER;
        const WoundArrowUpdateModuleData *data = getWoundArrowUpdateModuleData();
        AIChooseTable0026E1F0 *table = *(AIChooseTable0026E1F0 **)ai;
        float dx = target->m_cachedPos.x - owner->m_cachedPos.x;
        float dy = target->m_cachedPos.y - owner->m_cachedPos.y;
        float inverse = 1.0f / (float)sqrt(dx * dx + dy * dy);
        Coord3D position;
        position.x = dx * inverse * data->m_field254;
        position.y = dy * inverse * data->m_field254;
        position.x += target->m_cachedPos.x;
        position.y += target->m_cachedPos.y;
        (ai->*table->chooseLocomotorSet)(LOCOMOTORSET_0026E1F0);
        ((AICommandInterface *)((char *)ai + 0x20))->aiMoveToPosition(&position, CMD_FROM_AI);
        setCondition0026E1F0(target, 76);
    }
    ((BfmeThing916D *)owner)->bfmeGo916D((void *)2);
    clearCondition0026E1F0(owner, 196);
    ((SpecialAbilityUpdate *)((char *)this - 0x10))->SpecialAbilityUpdate::onExit(false, false);
    return UPDATE_SLEEP_FOREVER;
}
