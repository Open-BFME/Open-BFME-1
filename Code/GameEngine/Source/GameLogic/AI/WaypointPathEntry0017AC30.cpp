// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc
// 0017AC30..0017AD6F. Full retail order and layouts witnessed in the body;
// hub and setter ABIs: docs/analysis/0x00172600.md, Callee contracts/Neighbour notes.
// ZH AIFollowWaypointPathExactState::onEnter is the source twin; no class identity claim.
extern void j_0000314d(); extern void j_00012f17(); extern void j_000300bc();
extern void j_00009c2d(); extern void j_0003a17a(); extern void j_000494db();
extern void j_00048ca7();
struct Position0017AC30 { float x,y,z; };
struct Offset0017AC30 { float x,y; };
struct Waypoint0017AC30 { unsigned char pad000[12]; Position0017AC30 position; };
struct Group0017AC30 {
    float speed() {
        typedef float (Group0017AC30::*Call)();
        union { void* raw; Call method; } u; u.raw=(void*)j_000300bc;
        return (this->*u.method)();
    }
    bool center(Position0017AC30* p) {
        typedef bool (Group0017AC30::*Call)(Position0017AC30*);
        union { void* raw; Call method; } u; u.raw=(void*)j_00009c2d;
        return (this->*u.method)(p);
    }
};
struct Path0017AC30 { unsigned char pad000[8]; Waypoint0017AC30* node; };
struct Locomotor0017AC30 { unsigned char pad000[0x40]; unsigned int flags040; };
struct Update0017AC30 {
    unsigned char pad000[0x140]; Path0017AC30* path;
    unsigned char pad144[0x88]; Locomotor0017AC30* locomotor;
    unsigned char pad1d0[0x156]; bool field326;
    unsigned char pad327; bool field328;
    Group0017AC30* group() {
        typedef Group0017AC30* (Update0017AC30::*Call)();
        union { void* raw; Call method; } u; u.raw=(void*)j_00012f17;
        return (this->*u.method)();
    }
    void setPath(const Waypoint0017AC30* w,const Offset0017AC30* offset) {
        typedef void (Update0017AC30::*Call)(const Waypoint0017AC30*,const Offset0017AC30*);
        union { void* raw; Call method; } u; u.raw=(void*)j_000494db;
        (this->*u.method)(w,offset);
    }
    void setSpeed(float speed) {
        typedef void (Update0017AC30::*Call)(float);
        union { void* raw; Call method; } u; u.raw=(void*)j_00048ca7;
        (this->*u.method)(speed);
    }
};
struct Owner0017AC30 {
    unsigned char pad000[0x38]; Position0017AC30 position;
    unsigned char pad044[0x1c0]; Update0017AC30* ai;
};
struct Machine0017AC30 {
    unsigned char pad000[0x10]; Owner0017AC30* owner;
    unsigned char pad014[0x3c]; const Waypoint0017AC30* waypoint;
    void setPosition(const Position0017AC30* p) {
        typedef void (Machine0017AC30::*Call)(const Position0017AC30*);
        union { void* raw; Call method; } u; u.raw=(void*)j_0000314d;
        (this->*u.method)(p);
    }
};
enum StateReturnType { STATE_CONTINUE=0, STATE_SUCCESS=-1, STATE_FAILURE=-2 };
class AIInternalMoveToState { public: virtual StateReturnType onEnter(); };
class WaypointPathEntry0017AC30 {
public:
    unsigned char pad000[0x1c]; Machine0017AC30* machine;
    unsigned char pad020[4]; Position0017AC30 goal;
    unsigned char pad030[0x1c]; bool adjustsDestination;
    unsigned char pad04d[3]; const Waypoint0017AC30* lastWaypoint;
    bool moveAsGroup;
    int enter();
};
extern bool Glo012F0239;
class CRCParameterCheck;
extern CRCParameterCheck* TheCRCParameterCheck;
typedef void (__cdecl *Log0017AC30)(CRCParameterCheck*,const char*,...);

int WaypointPathEntry0017AC30::enter()
{
    const Waypoint0017AC30* waypoint = machine->waypoint;
    Update0017AC30* ai = machine->owner->ai;
    if (!waypoint) return -2;
    machine->setPosition(&waypoint->position);
    Offset0017AC30 offset;
    offset.x = offset.y = 0;
    Owner0017AC30* owner = machine->owner;
    float speed = 999999.0f;
    if (moveAsGroup) {
        Group0017AC30* group = ai->group();
        if (group) {
            speed = group->speed();
            Position0017AC30 center;
            group->center(&center);
            offset.x = owner->position.x - center.x;
            offset.y = owner->position.y - center.y;
        }
    }
    ai->field328 = true;
    ai->field326 = false;
    if (Glo012F0239 && TheCRCParameterCheck)
        ((Log0017AC30)j_0003a17a)(TheCRCParameterCheck,"CritterDesync: setAdjustDestination(FALSE) 56");
    adjustsDestination = false;
    goal = waypoint->position;
    int result = ((AIInternalMoveToState*)this)->AIInternalMoveToState::onEnter();
    ai->setPath(waypoint,&offset);
    if (ai->path && ai->path->node) goal = ai->path->node->position;
    lastWaypoint = waypoint;
    ai->locomotor->flags040 |= 2;
    ai->setSpeed(speed);
    return result;
}
