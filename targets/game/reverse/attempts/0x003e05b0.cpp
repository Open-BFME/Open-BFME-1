// ?bfmeStepE05B0@Pathfinder@@QAE_NPAVObject@@PAUICoord2D@@@Z
// partial score=0.8282122905027933 date=2026-09-28
// ?bfmeStepE05B0@Pathfinder@@QAE_NPAVObject@@PAUICoord2D@@@Z
// Retail 0x003E05B0, 715 bytes. Incoming ABI: Pathfinder* in ECX, Object*
// then a callback-state view beginning with ICoord2D on the stack; ret 8.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/pathfind /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/Thing /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// stlport

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum KindOfType { KINDOF_INVALID = 0 };
enum Relationship { RELATIONSHIP_INVALID = 0 };
enum CrushSquishTestType { CRUSH_SQUISH_INVALID = 0 };

#define THING_TU_MEMBERS \
	Bool isKindOf(KindOfType kind) const;
#include "thing.h"

#define OBJECT_TU_MEMBERS \
	Bool bfmeIsComputerControlled() const; \
	Bool canCrushOrSquish(Object *other, CrushSquishTestType test) const; \
	Relationship getRelationship(const Object *other) const;
#include "object.h"

struct ICoord2D { Int x, y; };

struct PathfindCell
{
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
	Bool bfmeStepE05B0(Object *object, ICoord2D *stateView);
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

static GameLogic *&globalGameLogic()
{
	return *(GameLogic **)0x012F0898;
}

struct CellInfoView
{
	unsigned char opaque[0x18];
	Int objectID;
};

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

// Input and output order follows the ZH TCheckMovementInfo twin; the extra
// BFME slots keep their offsets. Calls at 0x003E5820 use this 0x34-byte record.
struct Rva003E05B0State {
    ICoord2D cell;
    Int layer;
    Int radius;
    Bool centerInCell;
    Bool considerTransient;
    unsigned char opaque12[2];
    UnsignedInt field14;
    Int field18;
    unsigned char field1c[12];
    Int allyFixedCount;
    Bool enemyFixed;
    Bool allyMoving;
    Bool allyGoal;
    unsigned char opaque2f;
    Int field30;
};

Bool Pathfinder::bfmeStepE05B0(Object *object, ICoord2D *stateView)
{
	Rva003E05B0State *state = (Rva003E05B0State *)stateView;
	// its five output/accumulator slots before entering either loop.

	// These are callback-owned output/working bytes. Keep them offset-based:
	// preserved without speculative semantic field names.
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

	for (; x < state->cell.x + adjustedSpan; ++x)
	{
		Int y = state->cell.y - state->radius;
		for (; y < state->cell.y + adjustedSpan; ++y)
		{
			PathfindCell *cell = getCell(state->layer, x, y);
			if (cell == 0)
				return false;

						if ((cell->bits & 7) == 5)
				++state->field30;

			if (((unsigned char)(cell->bits >> 21) & 1) != 0 && object->bfmeIsComputerControlled())
				++state->field30;

			// per-cell movement validation each independently increment counter.
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
				continue;
			if (cellSubType == 1 || cellSubType == 4)
				state->allyGoal = 1;

			CellInfoView *cellInfo = (CellInfoView *)cell->info;
			const Int id = cellInfo ? cellInfo->objectID : 0;
			if (id == object->m_id || id == state->field18 || id == lastID)
				continue;

			lastID = id;
			Object *found = globalGameLogic()->findObjectByID(id);
			if (found == 0)
				continue;

			Bool specialKind = false;
			Bool relIsTwo;
			if (cellSubType == 2 || cellSubType == 4)
			{
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

			// this candidate early and return to the inner-loop advance.
			if (relIsTwo && object->isKindOf((KindOfType)0x73) &&
				found->isKindOf((KindOfType)0x73))
				continue;
			if (object->isKindOf((KindOfType)0x7c) &&
				found->isKindOf((KindOfType)0x08))
				continue;

			if (relIsTwo)
			{
				if (*(Int *)((char *)found + 0x204) == 0 || (state->field14 & 2) != 0)
					return false;
				state->allyFixedCount = 1;
				continue;
			}

			if (object->canCrushOrSquish(found, (CrushSquishTestType)2))
				continue;
			if ((state->field14 & 1) != 0)
				return false;
			state->enemyFixed = 1;
			// increment y and its 16-byte cell offset before testing inner bound.
		}
	}
	return true;
}
