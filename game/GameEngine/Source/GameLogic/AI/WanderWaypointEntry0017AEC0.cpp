// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc
// Retail 0017AEC0..0017B003, source twin AIWanderState::onEnter (ZH AIStates.cpp).
// Keep the address: the earlier AIFollowWaypointPathExactState attribution is wrong.
// Shared hub ABI and extra-distance setter: docs/analysis/0x00172600.md.
extern void j_000022bb(); extern void j_00012ebd(); extern void j_00019dc1();
extern void j_000428e8(); extern void j_0000ebab();
extern int GetGameLogicRandomValue(int,int,char*,int);
extern "C" __declspec(dllimport) double __cdecl floor(double);

// Native BaseType.h fast_float2long_round, also used by the landed
// AIWanderState_update_Bfme.cpp. C++ casts call __ftol2 instead of the
// witnessed rounded FISTP; this is the existing x87 codegen helper only.
__forceinline long roundFloat0017AEC0(float value)
{
    long result;
    __asm { fld value }
    __asm { fistp result }
    return result;
}
struct Template0017AEC0 {
    void* vptr;
    Template0017AEC0* nextOverride;
    unsigned char pad008[0xe4]; float widthFactor;
    Template0017AEC0* finalOverride() {
        typedef Template0017AEC0* (Template0017AEC0::*Call)();
        union { void* raw; Call method; } u; u.raw=(void*)j_000022bb;
        return (this->*u.method)();
    }
};
struct Locomotor0017AEC0 {
    void* vptr;
    Template0017AEC0* template004;
    float width() {
        typedef float (Locomotor0017AEC0::*Call)();
        union { void* raw; Call method; } u; u.raw=(void*)j_00012ebd;
        return (this->*u.method)();
    }
};
struct Update0017AEC0 {
    unsigned char pad000[0x1cc]; Locomotor0017AEC0* locomotor;

};
struct Owner0017AEC0 {
    unsigned char pad000[0x74]; unsigned int id;
    unsigned char pad078[0x18c]; Update0017AEC0* ai;
};
struct Waypoint0017AEC0;
struct Machine0017AEC0 {
    unsigned char pad000[0x10]; Owner0017AEC0* owner;
    unsigned char pad014[0x3c]; const Waypoint0017AEC0* waypoint;
};
enum StateReturnType { STATE_CONTINUE=0, STATE_SUCCESS=-1, STATE_FAILURE=-2 };
class AIInternalMoveToState { public: virtual StateReturnType onEnter(); };
class WanderWaypointEntry0017AEC0 {
public:
    unsigned char pad000[0x1c]; Machine0017AEC0* machine;
    unsigned char pad020[0x30]; float offsetX,offsetY;
    unsigned char pad058[8]; const Waypoint0017AEC0* currentWaypoint;
    const Waypoint0017AEC0* priorWaypoint;
    unsigned char pad068[4]; int waitFrames,timer;
    void computeGoal(bool useOffsets) {
        typedef void (WanderWaypointEntry0017AEC0::*Call)(bool);
        union { void* raw; Call method; } u; u.raw=(void*)j_00019dc1;
        (this->*u.method)(useOffsets);
    }
    float extraDistance() {
        typedef float (WanderWaypointEntry0017AEC0::*Call)();
        union { void* raw; Call method; } u; u.raw=(void*)j_000428e8;
        return (this->*u.method)();
    }
    int enter();
};
#define Zero0017AEC0 (*(const float*)0x01075350)
#define Half0017AEC0 (*(const float*)0x0107533C)

int WanderWaypointEntry0017AEC0::enter()
{
    currentWaypoint = machine->waypoint;
    Update0017AEC0* ai = machine->owner->ai;
    priorWaypoint = 0;
    if (currentWaypoint && ai) {
        offsetX = offsetY = 0;
        Locomotor0017AEC0* loco = ai->locomotor;
        if (loco) {
            Template0017AEC0* data = loco->template004;
            if (!data) data = 0;
            else if (data->nextOverride) data = data->nextOverride->finalOverride();
            if (data->widthFactor > Zero0017AEC0) {
                int delta = roundFloat0017AEC0((float)floor(loco->width() + Half0017AEC0));
                if (delta < 1) delta = 1;
                int negativeDelta = -delta;
                offsetX = (float)(GetGameLogicRandomValue(negativeDelta,delta,
                    "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp",0x2578)*10);
                offsetY = (float)(GetGameLogicRandomValue(negativeDelta,delta,
                    "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp",0x2579)*10);
            }
        }
        timer = 0;
        waitFrames = 10 + (machine->owner->id & 7);
        computeGoal(false);
        int result = ((AIInternalMoveToState*)this)->AIInternalMoveToState::onEnter();
        typedef void (Update0017AEC0::*SetExtra)(float);
        union { void* raw; SetExtra method; } setter;
        setter.raw = (void*)j_0000ebab;
        (ai->*setter.method)(extraDistance());
        return result;
    }
    return -2;
}
