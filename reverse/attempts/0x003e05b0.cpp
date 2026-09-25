// ?bfmeStepE05B0@Pathfinder@@QAE_NPAVObject@@PAUICoord2D@@@Z
// partial score=0.123077 date=2026-09-25
// ?bfmeStepE05B0@Pathfinder@@QAE_NPAVObject@@PAUICoord2D@@@Z
// Retail 0x003E05B0, 715 bytes. Incoming ABI: Pathfinder* in ECX, Object*
// then a callback-state view beginning with ICoord2D on the stack; ret 8.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/pathfind /ICode/GameEngine/Source/GameLogic/Object /ICode/GameEngine/Source/Common/Thing /ICode/GameEngine/Include /ICode/Libraries/Source/WWVegas/WWLib
// stlport

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum KindOfType { KINDOF_INVALID = 0 };
enum Relationship { RELATIONSHIP_INVALID = 0 };
enum CrushSquishTestType { CRUSH_SQUISH_INVALID = 0 };

#define THING_TU_MEMBERS \
	Bool isKindOf(KindOfType kind) const;
#include "../Code/GameEngine/Source/Common/Thing/thing.h"

#define OBJECT_TU_MEMBERS \
	Bool bfmeIsComputerControlled() const; \
	Bool canCrushOrSquish(Object *other, CrushSquishTestType test) const; \
	Relationship getRelationship(const Object *other) const;
#include "../Code/GameEngine/Source/GameLogic/Object/object.h"

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

Bool Pathfinder::bfmeStepE05B0(Object *object, ICoord2D *stateView)
{
	// its five output/accumulator slots before entering either loop.
	Int span = *(Int *)((char *)stateView + 0x0c);
	Int adjustedSpan = span;
	if (*(unsigned char *)((char *)stateView + 0x10) != 0)
		++adjustedSpan;

	// These are callback-owned output/working bytes. Keep them offset-based:
	// preserved without speculative semantic field names.
	*(Int *)((char *)stateView + 0x28) = 0;
	*(unsigned char *)((char *)stateView + 0x2d) = 0;
	*(unsigned char *)((char *)stateView + 0x2e) = 0;
	*(unsigned char *)((char *)stateView + 0x2c) = 0;
	*(Int *)((char *)stateView + 0x30) = 0;

	Int lastID = 0;
	Int x = stateView->x - span;
	if (x >= stateView->x + adjustedSpan)
		return true;

	for (; x < stateView->x + adjustedSpan; ++x)
	{
		Int y = stateView->y - *(Int *)((char *)stateView + 0x0c);
		for (; y < stateView->y + adjustedSpan; ++y)
		{
			// the Pathfinder extent; a failed signed bound returns false.
			if (x < extentLoX || x > extentHiX ||
				y < extentLoY || y > extentHiY)
				return false;

			// otherwise index the ground-map row. Null is a false return.
			const Int layer = *(Int *)((char *)stateView + 8);
			PathfindCell *cell = 0;
			if (layer > 1 && layer <= 15)
				cell = layers[layer].getCell(x, y);
			if (cell == 0)
				cell = map[x] + y;
			if (cell == 0)
				return false;

						if ((cell->bits & 7) == 5)
				++*(Int *)((char *)stateView + 0x30);

			if (((cell->bits >> 21) & 1) != 0 && object->bfmeIsComputerControlled())
				++*(Int *)((char *)stateView + 0x30);

			// per-cell movement validation each independently increment counter.
			const UnsignedInt stateFlags = *(UnsignedInt *)((char *)stateView + 0x14);
			if ((stateFlags & 8) != 0)
			{
				const Int cellLayer = (cell->bits >> 6) & 0x3f;
				const Int requestedLayer = *(Int *)((char *)stateView + 8);
				if (requestedLayer != cellLayer && cellLayer != 16 &&
					(requestedLayer == 1 || (requestedLayer >= 17 && requestedLayer <= 64)))
					++*(Int *)((char *)stateView + 0x30);
			}

			if ((stateFlags & 4) != 0 && !bfmeStepD4F90((char *)stateView + 0x1c, cell))
				++*(Int *)((char *)stateView + 0x30);

			const Int cellSubType = (cell->bits >> 3) & 7;
			if (cellSubType == 0)
				continue;
			if (cellSubType == 1 || cellSubType == 4)
				*(unsigned char *)((char *)stateView + 0x2e) = 1;

			CellInfoView *cellInfo = (CellInfoView *)cell->info;
			const Int id = cellInfo ? cellInfo->objectID : 0;
			if (id == object->m_id || id == *(Int *)((char *)stateView + 0x18) || id == lastID)
				continue;

			lastID = id;
			Object *found = globalGameLogic()->findObjectByID(id);
			if (found == 0)
				continue;

			Bool relIsTwo = false;
			Bool specialKind = false;
			if (cellSubType == 2 || cellSubType == 4)
			{
				relIsTwo = object->getRelationship(found) == (Relationship)2;
				if (relIsTwo)
					*(unsigned char *)((char *)stateView + 0x2d) = 1;
				if (*((unsigned char *)stateView + 0x11) != 0)
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
				if (*(Int *)((char *)found + 0x204) == 0 || (*(UnsignedInt *)((char *)stateView + 0x14) & 2) != 0)
					return false;
				*(Int *)((char *)stateView + 0x28) = 1;
				continue;
			}

			if (object->canCrushOrSquish(found, (CrushSquishTestType)2))
				continue;
			if ((*(UnsignedInt *)((char *)stateView + 0x14) & 1) != 0)
				return false;
			*(unsigned char *)((char *)stateView + 0x2c) = 1;
			// increment y and its 16-byte cell offset before testing inner bound.
		}
	}
	return true;
}
