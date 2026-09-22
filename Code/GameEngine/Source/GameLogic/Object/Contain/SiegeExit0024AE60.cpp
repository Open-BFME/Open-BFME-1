// RVA 0x0024AE60, 1070 bytes, thiscall with two stack arguments (ret 8).
// HordeSiegeEngineContain ownership: caller 0x0024B3A0 is secondary-vtable
// 0x010AFFB8 slot 2, installed at +0x30 by exact ctor 0x0024A560. It passes
// this-0x30 to this helper. The original method name remains unknown.
// Module data +0x224/+0x228 is also witnessed by the matched
// HordeSiegeEngineContainIsValidContainerFor.cpp. Owner Object is this+8.
// Pathfinding contracts and +0x01D1 call: docs/analysis/0x003e9720.md.
// Kind/status ordinals below preserve retail values without inventing names.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /O2 /Ob2 /Ireference/shims/stlp_nodealloc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include "vector3.h"
#include "matrix3d.h"
#include "Lib/BaseType.h"
#include <vector>
namespace _STL {
template <> __declspec(noinline) void vector<Coord3D>::push_back(const Coord3D &);
template <> __declspec(noinline) vector<Coord3D>::~vector();
}
class Player;
class Module;
class Object;
class LocomotorSet;
enum NameKeyType { Key0024AE60Invalid=0 };
enum PathfindLayerEnum { Layer0024AE60_11=17 };
enum KindOfType { Kind0024AE60_5C=92, Kind0024AE60_6C=108 };
enum ObjectStatusTypes { Status0024AE60_3B=59 };
enum CommandSourceType { CMD_FROM_AI=2 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva2225E0Filter { public: bool accepts(Object *,Player *); };
struct ModuleData0024AE60 {
    char pad000[0x224];
    Rva2225E0Filter field224;
    char pad225[3];
    int field228;
};
class AIUpdateInterface { public:
    void ignoreObstacle(Object *);
    const LocomotorSet &getLocomotorSet() const {return *(const LocomotorSet *)((char *)this+0x1A8);}
    void ignoreUntil0024AE60(unsigned int frame) {*(unsigned int *)((char *)this+0x178)=frame;}
};
class AICommandInterface { public:
    void aiBfmeCommand9FollowPath(const std::vector<Coord3D> *,Object *,CommandSourceType);
    void aiHunt(CommandSourceType);
};
class BfmeGeometryInfo {public: float boxMajorRadius() const;};
class Thing { public:
    void setPosition(const Coord3D *);
    void setOrientation(float);
    void setTransformMatrix(const Matrix3D *);
    bool isKindOf(KindOfType) const;
    const Coord3D *getUnitDirectionVector2D() const;
};
class Object : public Thing { public:
    Module *findModule(NameKeyType) const;
    Player *getControllingPlayer() const;
    bool getSingleLogicalBonePosition(const char *,Coord3D *,Matrix3D *) const;
    void setLayer(PathfindLayerEnum);
    void clearStatus(ObjectStatusTypes);
    const Coord3D *position() const {return (const Coord3D *)((char *)this+0x38);}
    float orientation() const {return *(const float *)((char *)this+0x44);}
    AIUpdateInterface *ai() const {return *(AIUpdateInterface **)((char *)this+0x204);}
    const BfmeGeometryInfo &geometry() const {return *(BfmeGeometryInfo *)((char *)this+0xAC);}
};
void j_00011252();
class Pathfinder { public:
    void addObjectToPathfindMap(Object *);
    void updateGoal(Object *,const Coord3D *,PathfindLayerEnum,const char *,int);
    float getLayerHeight(PathfindLayerEnum,const Coord3D *,Coord3D *);
    bool adjustToPossibleDestination(Object *object,const LocomotorSet &set,Coord3D *destination) {
        union {void (*route)(); bool (Pathfinder::*method)(Object *,const LocomotorSet &,Coord3D *);} call;
        call.route=j_00011252;
        return (this->*call.method)(object,set,destination);
    }
};
class TerrainLogic {public: PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *);};
class AI {public: char pad[0xC]; Pathfinder *m_pathfinder; Pathfinder *pathfinder() const {return m_pathfinder;}};
struct GameLogic0024AE60 {char pad[0x3C]; unsigned int frame;};
extern AI *TheAI;
#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)
#define TheGameLogic0024AE60 (*(GameLogic0024AE60 **)0x012F0898)
class Rva00266340 {public: bool is() const;};
class Rva00227B60ContainDispatch {public: void dispatch(Object *,bool);};
class Rva0024C2A0Owner {public: void processNested(Object *,void *);};
template <int N> class Slots0024AE60 : public Slots0024AE60<N-1> { public: virtual void unused(char (*)[N])=0;};
template <> class Slots0024AE60<0> {};
class ContainView0024AE60 : public Slots0024AE60<36> {public: virtual void remove(Object *,bool)=0;};
void j_0002bd82();
class CoordCall0024AE60 {public:
    void normalize() {
        union {void (*route)(); void (CoordCall0024AE60::*method)();} call;
        call.route=j_0002bd82; (this->*call.method)();
    }
};
class SiegeExit0024AE60 {public:
    void release(Object *rider,void *argument);
    char pad000[4]; ModuleData0024AE60 *data; Object *owner;
};
void SiegeExit0024AE60::release(Object *rider,void *argument)
{
    static NameKeyType key=TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
    Module *deployment=owner->findModule(key);
    Object *me=owner;
    ModuleData0024AE60 *md=data;
    if (md->field224.accepts(rider,me->getControllingPlayer()) && md->field228>0) {
        ((Rva00227B60ContainDispatch *)((char *)this+0x20))->dispatch(rider,false);
        float originalZ=rider->position()->z;
        Coord3D destination; destination.x=rider->position()->x; destination.y=rider->position()->y;
        {
            Coord3D delta;
            delta.x=destination.x-me->position()->x;
            delta.y=destination.y-me->position()->y;
            delta.z=originalZ-me->position()->z;
            ((CoordCall0024AE60 *)&delta)->normalize();
            float dx=delta.x*50.0f; float dy=delta.y*50.0f;
            destination.x += dx; destination.y += dy;
            destination.z=0;
        }
        AIUpdateInterface *ai=rider->ai();
        TheAI->pathfinder()->addObjectToPathfindMap(rider);
        if (ai) {
            ai->ignoreObstacle(0);
            ai->ignoreUntil0024AE60(TheGameLogic0024AE60->frame+5);
            TheAI->pathfinder()->adjustToPossibleDestination(rider,ai->getLocomotorSet(),&destination);
            std::vector<Coord3D> path;
            path.push_back(destination);
            path.push_back(destination);
            ((AICommandInterface *)((char *)ai+0x20))->aiBfmeCommand9FollowPath(&path,me,CMD_FROM_AI);
            TheAI->pathfinder()->updateGoal(rider,&destination,
                TheTerrainLogic->getLayerForDestination(rider,&destination),
                "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeSiegeEngineContain.cpp",0xBE);
        }
    } else if (deployment && ((Rva00266340 *)deployment)->is()) {
        ((ContainView0024AE60 *)((char *)this+0x20))->remove(rider,false);
        float angle=me->orientation();
        Coord3D position;
        if (me->isKindOf(Kind0024AE60_5C)) {
            Matrix3D transform;
            me->getSingleLogicalBonePosition("Ladder04",&position,&transform);
            rider->setTransformMatrix(&transform);
            rider->setLayer(Layer0024AE60_11);
            AIUpdateInterface *ai=rider->ai();
            TheAI->pathfinder()->addObjectToPathfindMap(rider);
            if (ai) {
                ai->ignoreObstacle(0);
                ai->ignoreUntil0024AE60(TheGameLogic0024AE60->frame+5);
                ((AICommandInterface *)((char *)ai+0x20))->aiHunt(CMD_FROM_AI);
            }
        } else {
            position=*me->position();
            Coord3D direction; const Coord3D *dir=me->getUnitDirectionVector2D(); direction.x=dir->x; direction.y=dir->y;
            // Preserve the x87 radius until both component updates complete.
            double radius=me->geometry().boxMajorRadius();
            position.x += direction.x*radius;
            position.y += direction.y*radius;
            position.z=TheAI->pathfinder()->getLayerHeight(Layer0024AE60_11,&position,0);
            Coord3D start=position;
            position.x += direction.x*20.0f;
            position.y += direction.y*20.0f;
            start.x += direction.x*40.0f;
            start.y += direction.y*40.0f;
            // Retail makes both calls with the same coordinate pointer.
            rider->setPosition(&start);
            rider->setPosition(&start);
            rider->setOrientation(angle);
            rider->setLayer(Layer0024AE60_11);
            TheAI->pathfinder()->addObjectToPathfindMap(rider);
            AIUpdateInterface *ai=rider->ai();
            if (ai) {
                ai->ignoreUntil0024AE60(TheGameLogic0024AE60->frame+15);
                ai->ignoreObstacle(0);
                ((AICommandInterface *)((char *)ai+0x20))->aiHunt(CMD_FROM_AI);
            }
        }
        if (rider->isKindOf(Kind0024AE60_6C)) rider->clearStatus(Status0024AE60_3B);
    } else {
        ((Rva0024C2A0Owner *)((char *)this+0x30))->processNested(rider,argument);
    }
}
