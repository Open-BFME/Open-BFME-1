#include <math.h>

// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003F1690 is a Pathfinder receiver: it calls the matched getCell
// method through ECX and reads the four bounds words at this+0x24..0x30. Its
// caller contract is eleven stack words and a callee-cleaned 0x2C-byte frame.
// The exact method name is not established, so the RVA token is retained.
//
// The 0x003F2D20 query caller supplies eleven words in this order: an Object
// word, one opaque integer, a byte flag, four integers, a Bool center flag, a
// position pointer, a float, and an integer output pointer.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UByte;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x, y, z;
};

struct ICoord2D
{
	Int x, y;
};

enum PathfindLayerEnum
{
	RVA003F1690_LAYER_INVALID = 0
};

enum KindOfType
{
	RVA003F1690_KIND_0C = 12
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
};

class PathfindCell
{
public:
	Int getType() const { return (Int)(m_flags & 7); }
	Int getLayer() const { return (Int)((m_flags >> 6) & 0x3F); }

private:
	char m_pad00[0x0C];
	UnsignedInt m_flags;
};

// Address-only view of the four Pathfinder words read at +0x24..+0x30.
// Their comparison order in retail is x-low, y-low, x-high, y-high.
struct Rva003F1690BoundsView
{
	char m_pad00[0x24];
	Int m_lowX;
	Int m_lowY;
	Int m_highX;
	Int m_highY;
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, Int cellX, Int cellY);

protected:
	void adjustCoordToCell(Int cellX, Int cellY, Bool centerInCell,
		Coord3D &worldPosition, PathfindLayerEnum layer);

public:
	Bool rva003f1690(
		Int objectWord,
		Int opaqueWord2,
		UByte notComputer,
		Int cellX,
		Int cellY,
		Int layerWord,
		Int radius,
		Bool centerInCell,
		void *positionWord,
		Real referenceHeight,
		Int *outMetric);
};

typedef Bool (Pathfinder::*Rva003F1690CallContract)(
	Int, Int, UByte, Int, Int, Int, Int, Bool, void *, Real, Int *);
typedef char Rva003F1690MemberPointerSize[
	(sizeof(Rva003F1690CallContract) == sizeof(void (*)())) ? 1 : -1];

// Direct call at 0x003F170B reaches this ILT, which routes to 0x003DFF70.
// The seven stack words and AL return are read from this call site; neither
// the helper's semantic identity nor its parameter names are asserted.
extern void j_000073b5();
typedef Bool (Pathfinder::*Rva000073B5Call)(
	Int, Int, Int, Int, Int, UByte, Int *);

// Calls at 0x003F1780, 0x003F178C, and 0x003F17A4 route through this ILT to
// 0x003EDF90. Its fourth slot is deliberately an opaque 32-bit word: these
// sites pass zero, and the old slowDoesPathExist spelling is under ABI audit.
extern void j_0004a327();
typedef Bool (Pathfinder::*Rva0004A327Call)(
	Object *, const Coord3D *, const Coord3D *, UnsignedInt);

// The following two data references retain their retail address tokens.
// Their semantic GlobalData field names and shipped values are not established
// by this candidate.
extern const Real BfmeZeroRange;
#define Rva003F1690HeightTolerance (*(const Real *)0x0107FAA8)

Bool Pathfinder::rva003f1690(
	Int objectWord,
	Int opaqueWord2,
	UByte notComputer,
	Int cellX,
	Int cellY,
	Int layerWord,
	Int radius,
	Bool centerInCell,
	void *positionWord,
	Real referenceHeight,
	Int *outMetric)
{
	(void)opaqueWord2;
	Object *object = (Object *)(UnsignedInt)objectWord;
	Coord3D *position = (Coord3D *)positionWord;
	PathfindLayerEnum layer = (PathfindLayerEnum)layerWord;

	PathfindCell *cell = getCell(layer, cellX, cellY);
	if (cell == 0)
		return false;
	if (cell->getType() == 2)
		return false;

	if (notComputer)
	{
		const Rva003F1690BoundsView *bounds =
			(const Rva003F1690BoundsView *)this;
		if (cellX < bounds->m_lowX || cellY < bounds->m_lowY ||
			cellX > bounds->m_highX || cellY > bounds->m_highY)
			return false;
	}

	union Rva000073B5Binding
	{
		void (*address)();
		Rva000073B5Call member;
	} destinationCheck;
	destinationCheck.address = &j_000073b5;
	if (!(this->*destinationCheck.member)(
		objectWord, cellX, cellY, layerWord, radius,
		centerInCell, outMetric))
		return false;

	Int actualLayer = cell->getLayer();
	Coord3D candidate;
	adjustCoordToCell(cellX, cellY, centerInCell, candidate,
		(PathfindLayerEnum)actualLayer);

	Bool bypassPathChecks = object->isKindOf(RVA003F1690_KIND_0C);
	if (!bypassPathChecks)
	{
		// Retail skips this height delta check when the first address-backed
		// value is at least referenceHeight. Otherwise the absolute difference
		// must be no greater than the second address-backed value.
		if (referenceHeight > BfmeZeroRange &&
			(Real)fabs(candidate.z - referenceHeight) >
			Rva003F1690HeightTolerance)
			return false;

		union Rva0004A327Binding
		{
			void (*address)();
			Rva0004A327Call member;
		} pathCheck;
		pathCheck.address = &j_0004a327;
		const Coord3D *objectPosition =
			(const Coord3D *)((const char *)object + 0x38);
		const UnsignedInt opaqueFourthWord = 0;

		// Retail saves this first path result in the dead incoming flag slot and
		// tests it after the second and optional third path checks.
		Bool initialPathExists = (this->*pathCheck.member)(
			object, objectPosition, &candidate, opaqueFourthWord);

		if ((this->*pathCheck.member)(
			object, objectPosition, position, opaqueFourthWord))
		{
			if (!initialPathExists)
				return false;
		}
		else if (!(this->*pathCheck.member)(
			object, position, &candidate, opaqueFourthWord) && !initialPathExists)
		{
			return false;
		}
	}

	*position = candidate;
	return true;
}
