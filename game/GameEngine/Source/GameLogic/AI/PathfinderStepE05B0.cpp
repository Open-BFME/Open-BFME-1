// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/pathfind /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/Thing /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Evidence: targets/game/reverse/identity_evidence/0x003e05b0-register-residue.md
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum KindOfType { KINDOF_INVALID = 0 };
enum Relationship { RELATIONSHIP_INVALID = 0 };
#include "../../../Include/Common/Enums/CrushSquishTestType.h"

#define THING_TU_MEMBERS \
	Bool isKindOf(KindOfType kind) const;
#include "thing.h"

#define OBJECT_TU_MEMBERS \
	Bool bfmeIsComputerControlled() const; \
	Bool canCrushOrSquish(Object *other, CrushSquishTestType test) const; \
	Relationship getRelationship(const Object *other) const;
#include "object.h"

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

class PathfindCell
{
public:
	void *info;
	Int opaque04[2];
	UnsignedInt bits;
	Int type() const { return bits & 7; }
	Int layer() const { return (bits >> 6) & 0x3f; }
};

class PathfindLayer
{
public:
	PathfindLayer() { }
	PathfindCell *getCell(Int x, Int y);
private:
	unsigned char opaque[0x44];
};

class Pathfinder
{
public:
	Bool bfmeStepE05B0_003E05B0(Object *object, ICoord2D *stateView);
	__forceinline PathfindCell *getCell(Int layer, Int x, Int y);
	Bool bfmeStepD4F90(void *state, PathfindCell *cell);
private:
	unsigned char prefix[0x10];
	PathfindCell **map;
	Int extentLoX, extentLoY, extentHiX, extentHiY;
	unsigned char opaque[0x85c - 0x24];
	PathfindLayer layers[16];
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

extern GameLogic *TheGameLogic;

static GameLogic *&globalGameLogic()
{
	return TheGameLogic;
}

struct CellInfoView
{
	unsigned char opaque[0x18];
	Int objectID;
};

// ?getCell@Pathfinder@@QAEPAVPathfindCell@@HHH@Z absent-from-retail
__forceinline PathfindCell *Pathfinder::getCell(Int layer, Int x, Int y)
{
    if (x >= extentLoX && x <= extentHiX && y >= extentLoY && y <= extentHiY) {
        if (layer > 1 && layer <= 15) {
            PathfindCell *cell = layers[layer].getCell(x, y);
            if (cell) return cell;
        }
        return &map[x][y];
    }
    return 0;
}

// The callback record keeps the witnessed BFME input and output offsets.
struct Rva003E05B0State {
    // Input
    ICoord2D cell;
    Int layer;
    Int radius;
    Bool centerInCell;
    Bool considerTransient;
    unsigned char opaque12[2];
    UnsignedInt field14;
    Int field18;
    unsigned char field1c[12];
    // Output 
    Int allyFixedCount;
    Bool enemyFixed;
    Bool allyMoving;
    Bool allyGoal;
    unsigned char opaque2f;
    Int field30;
};

/**
 * Checks to see if obj can move through the pathfind cell at x,y.
 * Returns false if there are other units already there.
 * Assumes your locomotor already said you can go there.
 */
// ?bfmeStepE05B0_003E05B0@Pathfinder@@QAE_NPAVObject@@PAUICoord2D@@@Z
Bool Pathfinder::bfmeStepE05B0_003E05B0(Object *object, ICoord2D *stateView)
{
	Rva003E05B0State *state = (Rva003E05B0State *)stateView;
	state->allyFixedCount = 0;
	state->allyMoving = 0;
	state->allyGoal = 0;
	state->enemyFixed = 0;
	state->field30 = 0;

	Int adjustedSpan = state->radius;
	if (state->centerInCell != 0)
		++adjustedSpan;

	Int lastID = 0;
	Int x = state->cell.x - state->radius;

//	Bool isInfantry = obj->isKindOf(KINDOF_INFANTRY);
	for (; x < state->cell.x + adjustedSpan; ++x)
	{
		Int y = state->cell.y - state->radius;
		for (; y < state->cell.y + adjustedSpan; ++y)
		{
			PathfindCell *cell = getCell(state->layer, x, y);
			if (cell == 0)
				return false; // off the map, so can't place here.

			if ((cell->bits & 7) == 5)
				++state->field30;

			if (((unsigned char)(cell->bits >> 21) & 1) != 0 && object->bfmeIsComputerControlled())
				++state->field30;

			const UnsignedInt stateFlags = state->field14;
			if ((stateFlags & 8) != 0)
			{
				const Int cellLayer = (cell->bits >> 6) & 0x3f;
				const Int requestedLayer = state->layer;
				if (requestedLayer != cellLayer &&
					((requestedLayer == 1 && cellLayer != 16) || (requestedLayer >= 17 && requestedLayer <= 64 && cellLayer != 16)))
					++state->field30;
			}

			if ((stateFlags & 4) != 0 && !bfmeStepD4F90(state->field1c, cell))
				++state->field30;

			const Int cellSubType = (cell->bits >> 3) & 7;
			if (cellSubType == 0)
				continue;  // Nobody is here, so it's ok.
			if (cellSubType == 1)
				state->allyGoal = 1;
			else if (cellSubType == 4)
				state->allyGoal = 1;

			CellInfoView *cellInfo = (CellInfoView *)cell->info;
			const Int id = cellInfo ? cellInfo->objectID : 0;
			if (id == object->m_id || // we got it.
				id == state->field18 || // we are ignoring this one.
				id == lastID)
				continue;

			lastID = id;
			Object *found = globalGameLogic()->findObjectByID(id);
			if (found == 0)
				continue;

			Bool specialKind = false;
			Bool relIsTwo;
			if (cellSubType == 2 || cellSubType == 4)
			{
				// order matters: we want to know if I consider it to be an ally, not vice versa
				relIsTwo = object->getRelationship(found) == (Relationship)2;
				if (relIsTwo)
					state->allyMoving = 1;
				if (state->considerTransient != 0)
					specialKind = true;
			}
			if (cellSubType == 3)
				relIsTwo = object->getRelationship(found) == (Relationship)2;
			else if (!specialKind)
				continue;

			if (relIsTwo && object->isKindOf((KindOfType)0x73) &&
				found->isKindOf((KindOfType)0x73))
				continue;
			// Infantry can run through infantry.
			if (object->isKindOf((KindOfType)0x7c) &&
				found->isKindOf((KindOfType)0x08))
				continue;

			// See if it is an ally.
			// order matters: we want to know if I consider it to be an ally, not vice versa
			if (relIsTwo)
			{
				if (*(Int *)((char *)found + 0x204) == 0 || (state->field14 & 2) != 0)
					return false; // can't path through not-idle units.
#if 0
				if (!unit->getAIUpdateInterface()->isIdle()) {
					return false; // can't path through not-idle units.
				}
#endif
				state->allyFixedCount = 1;
				continue;
			}

			if (object->canCrushOrSquish(found, (CrushSquishTestType)2))
				continue;
			if ((state->field14 & 1) != 0)
				return false;
			state->enemyFixed = 1;
		}
	}
	return true;
}
