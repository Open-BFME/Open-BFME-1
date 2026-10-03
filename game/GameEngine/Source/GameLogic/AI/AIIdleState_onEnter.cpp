// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?onEnter@AIIdleState@@UAE?AW4StateReturnType@@XZ: game/GameEngine/Source/GameLogic/AI/AIStates.cpp
// AIIdleState vtable 0x010985B0 slot 4 -> ILT 0x0002CC23 -> retail 0x00170020.
// Native OVERRIDE accessor preserves the base template when no override exists.
#include "ascii_string.h"

typedef bool Bool;
typedef unsigned short UnsignedShort;
enum StateReturnType { STATE_CONTINUE = 0 };

class AIUpdateInterface
{
public:
    void resetNextMoodCheckTime();
};

// upstream: GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
    virtual void overrideAnchor();
    Overridable *m_nextOverride;
    const Overridable *getFinalOverride() const;
};

struct Rva00170020Template : Overridable
{
    char m_pad008[0x20 - 8];
    AsciiString m_nameString;
    char m_pad024[0x4CD - 0x24];
    unsigned char m_bfmeIdleFlag;
};

struct BfmeAIIdleOnEnterFiringTracker
{
    char m_pad000[0x20];
    unsigned int m_field020;
};

struct Rva00170020Object
{
    char m_pad000[4];
    Rva00170020Template *m_template;
    char m_pad008[0x38 - 8];
    float m_positionX, m_positionY, m_positionZ;
    char m_pad044[0x74 - 0x44];
    unsigned int m_id;
    char m_pad078[0x1EC - 0x78];
    BfmeAIIdleOnEnterFiringTracker *m_tracker;
    char m_pad1F0[0x204 - 0x1F0];
    AIUpdateInterface *m_ai;

    const Rva00170020Template *getTemplate() const
    {
        const Rva00170020Template *result = m_template;
        if (result && result->m_nextOverride)
            result = static_cast<const Rva00170020Template *>(result->m_nextOverride->getFinalOverride());
        return result;
    }
};

struct BfmeAIIdleOnEnterMachine
{
    char m_pad000[0x10];
    Rva00170020Object *m_owner;
};

class State
{
public:
    virtual StateReturnType onEnter();
    char m_pad004[0x18];
    BfmeAIIdleOnEnterMachine *m_machine;
};

class AIIdleState : public State
{
public:
    virtual StateReturnType onEnter();
    char m_pad020[4];
    UnsignedShort m_initialSleepOffset;
    Bool m_shouldLookForTargets;
    Bool m_inited;
};

class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(CRCParameterCheck *, const char *, ...);
extern int __cdecl GetGameLogicRandomValue(int, int, char *, int);

StateReturnType AIIdleState::onEnter()
{
    Rva00170020Object *obj = m_machine->m_owner;
    AIUpdateInterface *ai = obj->m_ai;
    if (ai)
        ai->resetNextMoodCheckTime();
    m_inited = true;

    if (obj->getTemplate()->m_bfmeIdleFlag)
    {
        BfmeAIIdleOnEnterFiringTracker *tracker = obj->m_tracker;
        if (tracker)
            tracker->m_field020 = 0;
    }

    CRCParameterCheck *crc = TheCRCParameterCheck;
    if (crc)
    {
        unsigned int id = obj->m_id;
        const char *name = obj->getTemplate()->m_nameString.str();
        bfmeRetailCritterDesyncLog(crc,
            "AIIdleState::onEnter() called for object %s(%d) at location %g,%g,%g.",
            name, id,
            (double)obj->m_positionX, (double)obj->m_positionY, (double)obj->m_positionZ);
    }

    m_initialSleepOffset = (UnsignedShort)GetGameLogicRandomValue(0, 10,
        "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp", 0x7A2);
    return STATE_CONTINUE;
}
