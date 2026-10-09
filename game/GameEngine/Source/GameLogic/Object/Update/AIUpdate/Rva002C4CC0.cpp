// cl: /DNDEBUG /MD /I.
// stlport
#define OBJECT_TU_MEMBERS void *unidentified_001BFE20() const;
#include "game/GameEngine/Source/GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS
#include "game/GameEngine/Source/Common/Thing/GameLogicObjectLookup.h"
#include "game/GameEngine/Source/GameLogic/command_source_type.h"
extern GameLogic *TheGameLogic;
class BfmeC979 { public: void bfmeGo979C(); };
class Rva002C4910 { public: void method(Object *, CommandSourceType); };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };
class HordeAIUpdate { public: virtual UpdateSleepTime update(); };
class AICommandInterface { public: void aiIdle(CommandSourceType); };
template <class T> inline T &field(void *p, unsigned int offset) {
    return *reinterpret_cast<T *>(static_cast<char *>(p) + offset);
}
template <int N> class Slots : public Slots<N-1> { public: virtual void slot(char (*)[N]); };
template <> class Slots<0> {};
class AIUpdateInterface : public Slots<96> { public: virtual bool isIdle() const; };
class Bool90 : public Slots<36> { public: virtual bool value(); };
class Float14 : public Slots<5> { public: virtual float value(); };
class Int10 : public Slots<4> { public: virtual void value(bool); };
class RepairA0 : public Slots<40> { public: virtual void value(Object *, CommandSourceType); };
class Rva002C4CC0 {
public:
    int update();
};
// ?update@Rva002C4CC0@@QAEHXZ
// Open BFME 2 donor Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/HordeAIUpdatePrivateCommands.cpp.
int Rva002C4CC0::update() {
    Object *obj = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 8);
    if (!obj) return 0x3FFFFFFF;
    void *horde = obj->unidentified_001BFE20();
    if (!horde) return 0x3FFFFFFF;
    void *primary = reinterpret_cast<char *>(this) - 0x10;
    reinterpret_cast<BfmeC979 *>(primary)->bfmeGo979C();
    if (field<unsigned int>(this, 0x334)) {
        Object *target = TheGameLogic->findObjectByID(field<unsigned int>(this, 0x338));
        if (!target || (target->m_privateStatus & 1)) {
            reinterpret_cast<AICommandInterface *>(static_cast<char *>(field<void *>(obj, 0x204)) + 0x20)->aiIdle(CMD_FROM_AI);
            field<unsigned int>(this, 0x334) = 0;
            return 1;
        }
        if (obj->m_ai->isIdle() && !reinterpret_cast<Bool90 *>(horde)->value()) {
            Object *repairTarget = TheGameLogic->findObjectByID(field<unsigned int>(this, 0x338));
            if (repairTarget) reinterpret_cast<RepairA0 *>(primary)->value(repairTarget, CMD_FROM_AI);
            field<unsigned int>(this, 0x334) = 0;
            return 1;
        }
        return reinterpret_cast<HordeAIUpdate *>(this)->HordeAIUpdate::update();
    }
    if (field<unsigned int>(this, 0x338)) {
        Object *target = TheGameLogic->findObjectByID(field<unsigned int>(this, 0x338));
        if (!target || (target->m_privateStatus & 1) || reinterpret_cast<Float14 *>(target->m_body)->value() == 1.0f) {
            reinterpret_cast<Int10 *>(horde)->value(true);
            field<unsigned int>(this, 0x338) = 0;
        }
        return 1;
    }
    if (field<unsigned int>(this, 0x33C)) {
        Object *target = TheGameLogic->findObjectByID(field<unsigned int>(this, 0x33C));
        if (target) reinterpret_cast<Rva002C4910 *>(primary)->method(target, CMD_FROM_AI);
        field<unsigned int>(this, 0x33C) = 0;
        return 1;
    }
    return reinterpret_cast<HordeAIUpdate *>(this)->HordeAIUpdate::update();
}
