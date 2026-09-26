// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath
// AISkirmishPlayer vtable 0x01096FB0 slot 13 points through ILT 0x0000F399
// to this body. Slot 14 dispatches repairStructure when a broken bridge is found.
#include "coord3d.h"

inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &source) { *(Coord3DBase *)this = *(const Coord3DBase *)&source; }
inline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &source)
{
    x = source.x;
    y = source.y;
    z = source.z;
    return *this;
}

class Object
{
public:
    const Coord3D *getPosition() const { return (const Coord3D *)((const char *)this + 0x38); }
    class AIUpdateInterface *getAI() const { return *(AIUpdateInterface **)((char *)this + 0x204); }
};

class AIUpdateInterface
{
public:
    const void *getLocomotorSet() const { return (const char *)this + 0x1a8; }
};

class Waypoint
{
public:
    const Coord3D *getLocation() const { return (const Coord3D *)((const char *)this + 0xc); }
    Waypoint *getNext() const { return *(Waypoint **)((const char *)this + 0x1c); }
};

class Pathfinder
{
public:
    bool clientSafeQuickDoesPathExist(Object *, const Coord3D *, const Coord3D *, int);
    int findBrokenBridge(const void *, const Coord3D *, const Coord3D *);
};

class AI
{
    char padding[0xc];
    Pathfinder *m_pathfinder;
public:
    Pathfinder *pathfinder() const { return m_pathfinder; }
};
extern AI *TheAI;

class AISkirmishPlayer
{
public:
#define SKIRMISH_SLOT(n) virtual void slot##n();
    SKIRMISH_SLOT(00) SKIRMISH_SLOT(01) SKIRMISH_SLOT(02) SKIRMISH_SLOT(03)
    SKIRMISH_SLOT(04) SKIRMISH_SLOT(05) SKIRMISH_SLOT(06) SKIRMISH_SLOT(07)
    SKIRMISH_SLOT(08) SKIRMISH_SLOT(09) SKIRMISH_SLOT(10) SKIRMISH_SLOT(11)
    SKIRMISH_SLOT(12)
#undef SKIRMISH_SLOT
    virtual bool checkBridges(Object *unit, Waypoint *way);
    virtual void repairStructure(int id);
};

bool AISkirmishPlayer::checkBridges(Object *unit, Waypoint *way)
{
    Coord3D unitPos = *unit->getPosition();
    AIUpdateInterface *ai = unit->getAI();
    if (!ai) return false;
    const void *locoSet = ai->getLocomotorSet();
    for (Waypoint *curWay = way; curWay; curWay = curWay->getNext()) {
        const Coord3D *location = curWay->getLocation();
        if (TheAI->pathfinder()->clientSafeQuickDoesPathExist(unit, &unitPos, location, 0))
            continue;
        int bridge = TheAI->pathfinder()->findBrokenBridge(locoSet, &unitPos, location);
        if (bridge) {
            repairStructure(bridge);
            return true;
        }
    }
    return false;
}
