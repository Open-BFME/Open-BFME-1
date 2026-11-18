// cl: /DNDEBUG /MD /EHsc
// ?Rva001752A0@@YA_NPAUCoord3D@@PAVObject@@1@Z
// Evidence: targets/game/reverse/identity_evidence/001752a0-path-location.md
#include <math.h>

#include "../../../Include/Common/ScalarTypes.h"

enum KindOfType { KINDOF_5C = 0x5c };
#include "../ScriptEngine/game_logic_dispatch.h"
enum WeaponSlotType { WEAPONSLOT_DUMMY = 0 };
#include "../../../Include/Common/ObjectID.h"
#include "../../../Include/Common/Enums/PathfindLayerEnum.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"
extern void b_000fb930();
class Rva001752A0CoordCalls
{
public:
    // ?normalize@Rva001752A0CoordCalls@@QAEXXZ absent-from-retail
    __forceinline void normalize()
    {
        typedef void (Rva001752A0CoordCalls::*Call)();
        union { void (*raw)(); Call call; } target;
        target.raw = b_000fb930;
        (this->*target.call)();
    }
};

class Module;
class Weapon;
class LocomotorSet {};
class Rva00266340 { public: Bool is() const; };

class AIUpdateInterface
{
    char m_pad000[0x1a8];
public:
    LocomotorSet m_locomotorSet;
};

#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS Bool isKindOf(KindOfType kind) const;
#define OBJECT_TU_MEMBERS \
    Weapon *getCurrentWeapon(WeaponSlotType *slot); \
    friend bool Rva001752A0(Coord3D *, Object *, Object *); \
protected: \
    Module *findModule(NameKeyType key) const;
#include "../Object/object.h"
#undef OBJECT_TU_MEMBERS
#undef THING_TU_MEMBERS
#undef BFME_HAVE_COORD3D

struct Rva001752A0RadiusView
{
    char m_pad000[0xbc];
    Real m_bfmeBC;
};

extern void b_003edf90();
extern void b_003eac80();

class Pathfinder
{
public:
    // ?slowDoesPathExist003EDF90@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@1PBVLocomotorSet@@@Z absent-from-retail
    __forceinline Bool slowDoesPathExist003EDF90(Object *obj, const Coord3D *from, const Coord3D *to, const LocomotorSet *locomotor)
    {
        typedef Bool (Pathfinder::*Call)(Object *, const Coord3D *, const Coord3D *, const LocomotorSet *);
        union { void (*raw)(); Call call; } target;
        target.raw = b_003edf90;
        return (this->*target.call)(obj, from, to, locomotor);
    }
    int bfmeCellTypeFourWithFlag(const Coord3D *pos, PathfindLayerEnum layer);
    // ?adjustToPossibleDestination003EAC80@Pathfinder@@QAE_NPAVObject@@ABVLocomotorSet@@PAUCoord3D@@@Z absent-from-retail
    __forceinline Bool adjustToPossibleDestination003EAC80(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest)
    {
        typedef Bool (Pathfinder::*Call)(Object *, const LocomotorSet &, Coord3D *);
        union { void (*raw)(); Call call; } target;
        target.raw = b_003eac80;
        return (this->*target.call)(obj, locomotorSet, dest);
    }
};

class BfmePathfinderMethods {};

class AIData
{
    char m_pad000[0xd0];
public:
    Real m_meleeOffset;
};

class AI
{
    char m_pad000[0x0c];
public:
    Pathfinder *m_pathfinder;
    // ?pathfinder@AI@@QAEPAVPathfinder@@XZ absent-from-retail
    Pathfinder *pathfinder() { return m_pathfinder; }
    char m_pad010[4];
    AIData *m_data14;
};



class TerrainLogic;

class Rva001A7C20TerrainLogic
{
public:
    PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern void b_003f5e20();
extern AI *TheAI;
extern NameKeyGenerator *TheNameKeyGenerator;
extern TerrainLogic *TheTerrainLogic;

// ?Rva001752A0@@YA_NPAUCoord3D@@PAVObject@@1@Z
bool Rva001752A0(Coord3D *destination, Object *source, Object *victim)
{
    AIUpdateInterface *ai = source->m_ai;
    if (ai == 0)
        return false;

    Coord3D victimPos;
    Coord3D candidate;
    Real initialDistance;
    Bool pathCheck;
    Bool adjusted;
    Coord3D delta;
    AI *theAI;
    {
        Real destinationX = destination->x;
        Real destinationY = destination->y;
        const Coord3D *position = &source->m_cachedPos;
        delta.x = destinationX - position->x;
        Real dy = destinationY - position->y;
        victimPos.x = destination->x;
        victimPos.y = destination->y;
        victimPos.z = destination->z;
        initialDistance = (Real)sqrt(delta.x * delta.x + dy * dy);

        if (victim)
        {
            victimPos = victim->m_cachedPos;
            if (victim->isKindOf(KINDOF_5C))
            {
                static NameKeyType key = TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
                Module *module = victim->findModule(key);
                if (module && ((Rva00266340 *)module)->is())
                    return true;
            }
        }

        Pathfinder *pathfinder = TheAI->pathfinder();
        typedef Bool (BfmePathfinderMethods::*Check)(const Object *, const Coord3D *, const Weapon *, int);
        union { void (*raw)(); Check check; } checkTarget;
        checkTarget.raw = b_003f5e20;
        pathCheck = (((BfmePathfinderMethods *)pathfinder)->*checkTarget.check)(source, &victimPos, source->getCurrentWeapon(0), 0);
        if (pathCheck && TheAI->pathfinder()->slowDoesPathExist003EDF90(source, position, destination, 0))
            return true;

        delta = *destination;
        candidate.x = destination->x;
        candidate.y = destination->y;
        candidate.z = destination->z;
        delta.x -= position->x;
        delta.y -= position->y;
        delta.z = 0.0f;
        int limit = -1 - (int)((Real)sqrt(delta.y * delta.y + delta.x * delta.x) * -0.05f);
        Real length = (Real)sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
        Real scale = 1.0f / length;
        delta.x *= scale;
        delta.y = (double)delta.y * scale;
        delta.z *= scale;
        delta.x *= 20.0f;
        delta.y *= 20.0f;
        delta.z *= 20.0f;

        Bool specialCell = false;
        for (int index = 0; index < limit; ++index)
        {
            candidate.x -= delta.x;
            candidate.y -= delta.y;
            candidate.z -= delta.z;
            if (TheAI->pathfinder()->slowDoesPathExist003EDF90(source, position, &candidate, 0))
                goto found;
            if (((Rva001A7C20TerrainLogic *)TheTerrainLogic)->getLayerForDestination(source, &candidate) > LAYER_GROUND ||
                (unsigned char)TheAI->pathfinder()->bfmeCellTypeFourWithFlag(&candidate, LAYER_GROUND))
                specialCell = true;
        }
        return false;

found:
        theAI = TheAI;
        adjusted = false;
        if (specialCell && !pathCheck)
        {
            Real offset = theAI->m_data14->m_meleeOffset + ((const Rva001752A0RadiusView *)source)->m_bfmeBC;
            ((Rva001752A0CoordCalls *)&delta)->normalize();
            adjusted = true;
            // Read each component before the shared offset operand.
            delta.x = *(const volatile Real *)&delta.x * offset;
            delta.y = *(const volatile Real *)&delta.y * offset;
            delta.z *= offset;
            candidate.x -= delta.x;
            candidate.y -= delta.y;
            candidate.z -= delta.z;
        }
    }

    delta = *destination;
    Real dx = delta.x - candidate.x;
    Real dy = delta.y - candidate.y;
    if (!adjusted)
    {
        if ((Real)sqrt(dx * dx + dy * dy) + 20.0f > initialDistance)
            return false;
    }

    theAI->pathfinder()->adjustToPossibleDestination003EAC80(source, ai->m_locomotorSet, &candidate);
    *destination = candidate;
    return true;
}
