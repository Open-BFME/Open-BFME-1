// cl: /DNDEBUG /MD
//
// Open-BFME: the Pathfinder queries that answer a question about a straight
// segment of the world.
//
//   ?snapLine@              0x003E6AF0, 110 bytes
//   ?isGroundPathPassable@  0x003EAC00,  91 bytes
//   ?isLinePassable@        0x003EE7A0, 131 bytes  (eight arguments)
//   ?lineBlocked@           0x003EE850, 100 bytes
//   ?isLinePassable@        0x003EE8D0, 119 bytes  (six arguments)
//   ?lineClear@             0x003EE970, 102 bytes
//
// One body six times: build a payload object on the stack, convert both world
// endpoints to cell coordinates with worldToCell, walk the cells between them,
// and turn the walk's verdict into the answer. snapLine is the only one that
// does anything else -- when the walk reports a hit it copies the payload's
// working position back over the caller's destination.
//
// The payload type is not decoration: it IS the dispatch. Retail has a dozen
// cell-space line walks, each taking a different user-data struct, and picking
// the struct picks the walker. These four reach three of them, and one file each
// could only ever declare "the" iterateCellsAlongLine, so nothing said that
// different bodies are being called:
//
//   Rva003DE480Struct      ILT 0x00005713 -> 0x003DE480   snapLine
//   GroundPathPassableInfo ILT 0x00013DC2 -> 0x003E33F0   isGroundPathPassable
//   BfmeCheckMovementInfo  ILT 0x00029DF7 -> 0x003E7F80   both isLinePassable
//   Rva003DB640Info        ILT 0x00023DDF -> 0x003E81E0   lineBlocked
//   Rva003E5A50Info        ILT 0x0001DAA2 -> 0x003E8440   lineClear
//
// isGroundPathPassable reaches its walker through a PRIVATE overload, which is
// why it sits in its own section below: access is part of the mangled name, so
// `?iterateCellsAlongLine@Pathfinder@@AAEH...PAUGroundPathPassableInfo@@@Z` and
// the public ones are different symbols. The ledger pins that private symbol and
// a public `...PAURva003E33F0Struct@@...` to the SAME ILT 0x00013DC2, so
// GroundPathPassableInfo and Rva003E33F0Struct are one struct under two names --
// the meaningful one is kept here.
//
// isGroundPathPassable also takes its arguments in a different order from the
// other four: the layer sits between the two endpoints rather than before them,
// and it names the layer of the START point specifically.
//
// lineBlocked's file used to reconstruct Rva003DB640Info's CONSTRUCTOR as well
// as the query, a 60-line body the ledger declares no row for. It did not need
// to: symbols.csv already pins ??0Rva003DB640Info@@QAE@PAVPathfinder@@
// PAVObject@@H@Z to ILT 0x00042262 -> 0x003DB640, and that body is already
// carried as a matched gen-dump row. Declared and not defined, the call leaves
// the TU and reaches the same address, lineBlocked still matches to the byte,
// and the source no longer holds a second copy of a function it does not own.
//
// The overload set below is the point of the file. It also lines the four
// predicates up against each other: lineBlocked answers true when the walk DID
// hit something and the other three answer true when it did not, and the two
// isLinePassable overloads differ only in what they put in the payload -- the
// eight-argument one takes the caller's crusher and restrict-surfaces flags and
// forces allowPinched off, the six-argument one hard-codes crusher off with
// restrict-surfaces and allowPinched on.
//
// The Bool spellings differed across the four files and two of them mattered:
// the predicates return H (int), and worldToCell returns _N (bool). They are
// written out below rather than hidden behind a typedef that meant two things.

typedef int Int;
typedef int Bool;								// the predicates mangle as H
typedef unsigned int size_t;

inline void *operator new(size_t, void *p)
{
	return p;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x, y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Pathfinder;

// ---------------------------------------------------------------- snapLine
// The payload Rva003D61C0::set() fills; only its working Coord3D is read back.
struct Rva003D61C0Vec
{
	Int a, b, c;
};

class Rva003D61C0
{
public:
	Rva003D61C0 &set(Int a, Int b, const Rva003D61C0Vec *p);

	Int m_00;
	Int m_04;
	Coord3D m_pos;
};

struct Rva003DE480Struct;

// -------------------------------------------------------- both isLinePassable
class Object;

class BfmeCheckMovementInfo
{
public:
	BfmeCheckMovementInfo(Pathfinder *pathfinder, Object *obj, Int zone,
		Bool considerTransient, Bool isCrusher, Bool restrictSurfaces,
		Bool allowPinched);

	unsigned char m_body[0x58];
};

// ------------------------------------------------------------- lineBlocked
// Declared, never defined: the body is pinned at ILT 0x00042262 -> 0x003DB640.
class Rva003DB640Info
{
public:
	Rva003DB640Info(Pathfinder *pathfinder, Object *obj, Int value);

	unsigned char m_body[0x50];
};

// ------------------------------------------------------ isGroundPathPassable
struct GroundPathPassableInfo
{
	Pathfinder *pathfinder;
	int pathDiameter;
};

// --------------------------------------------------------------- lineClear
class Rva003E5A50Info
{
public:
	Rva003E5A50Info(Pathfinder *pathfinder, Object *obj, Int value);

	unsigned char m_body[0x54];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	bool worldToCell(const Coord3D *pos, ICoord2D *cell);

	// One name, four callees -- the user-data type is what selects the walker.
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003DE480Struct *userData);		///< ILT 0x00005713 -> 0x003DE480
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, BfmeCheckMovementInfo *info);		///< ILT 0x00029DF7 -> 0x003E7F80
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003DB640Info *info);			///< ILT 0x00023DDF -> 0x003E81E0
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003E5A50Info *info);			///< ILT 0x0001DAA2 -> 0x003E8440

	void snapLine(const Coord3D *from, Coord3D *to);
	bool isGroundPathPassable(const Coord3D &startWorld,
		PathfindLayerEnum startLayer, const Coord3D &endWorld,
		int pathDiameter);
	Bool isLinePassable(Object *obj, Int zone, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end, Bool considerTransient,
		Bool isCrusher, Bool restrictSurfaces);
	Bool lineBlocked(Object *obj, Int value, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end);
	Bool isLinePassable(Object *obj, Int zone, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end, Bool considerTransient);
	Bool lineClear(Object *obj, Int value, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end);

private:
	// Same ILT as the public ...PAURva003E33F0Struct@@... spelling, but the
	// access specifier is part of the mangled name, so this one has to be here.
	Int iterateCellsAlongLine(const ICoord2D &startCell, const ICoord2D &endCell,
		PathfindLayerEnum layer, GroundPathPassableInfo *info);		///< ILT 0x00013DC2 -> 0x003E33F0
};

// ?snapLine@Pathfinder@@QAEXPBUCoord3D@@PAU2@@Z
// Walk the segment on LAYER_GROUND and, if the cell iterator reports a hit,
// write the payload's working Coord3D back onto the destination.
void Pathfinder::snapLine(const Coord3D *from, Coord3D *to)
{
	Rva003D61C0 info;
	info.set((Int)this, 4, (const Rva003D61C0Vec *)from);
	ICoord2D start;
	worldToCell(from, &start);
	ICoord2D end;
	worldToCell(to, &end);
	if (iterateCellsAlongLine(start, end, LAYER_GROUND, (Rva003DE480Struct *)&info)) {
		to->x = info.m_pos.x;
		to->y = info.m_pos.y;
		to->z = info.m_pos.z;
	}
}

// ?isGroundPathPassable@Pathfinder@@QAE_NABUCoord3D@@W4PathfindLayerEnum@@0H@Z
// Endpoints by reference, layer in the middle, and the payload is two words
// built in place rather than a constructed object.
bool Pathfinder::isGroundPathPassable(const Coord3D &startWorld,
	PathfindLayerEnum startLayer, const Coord3D &endWorld,
	int pathDiameter)
{
	GroundPathPassableInfo info;
	ICoord2D endCell;
	ICoord2D startCell;

	info.pathfinder = this;
	info.pathDiameter = pathDiameter;
	worldToCell(&startWorld, &startCell);
	worldToCell(&endWorld, &endCell);

	return iterateCellsAlongLine(startCell, endCell, startLayer, &info) == 0;
}

// ?isLinePassable@Pathfinder@@QAEHPAVObject@@HW4PathfindLayerEnum@@PBUCoord3D@@2HHH@Z
// The caller's crusher and restrict-surfaces flags, allowPinched forced off.
Bool Pathfinder::isLinePassable(Object *obj, Int zone, PathfindLayerEnum layer,
	const Coord3D *startWorld, const Coord3D *endWorld, Bool considerTransient,
	Bool isCrusher, Bool restrictSurfaces)
{
	ICoord2D end;
	ICoord2D start;
	unsigned char storage[0x58];
	BfmeCheckMovementInfo *payload = new (storage) BfmeCheckMovementInfo(
		this, obj, zone, considerTransient, isCrusher, restrictSurfaces, 0);
	worldToCell(startWorld, &start);
	worldToCell(endWorld, &end);
	return iterateCellsAlongLine(start, end, layer, payload) == 0;
}

// ?lineBlocked@Pathfinder@@QAEHPAVObject@@HW4PathfindLayerEnum@@PBUCoord3D@@2@Z
// The only one of the six that answers true when the walk DID hit something.
Bool Pathfinder::lineBlocked(Object *obj, Int value, PathfindLayerEnum layer,
	const Coord3D *startWorld, const Coord3D *endWorld)
{
	ICoord2D end;
	ICoord2D start;
	unsigned char storage[0x50];
	Rva003DB640Info *payload = new (storage) Rva003DB640Info(this, obj, value);
	worldToCell(startWorld, &start);
	worldToCell(endWorld, &end);
	return iterateCellsAlongLine(start, end, layer, payload) != 0;
}

// ?isLinePassable@Pathfinder@@QAEHPAVObject@@HW4PathfindLayerEnum@@PBUCoord3D@@2H@Z
// crusher off, restrict-surfaces and allowPinched on.
Bool Pathfinder::isLinePassable(Object *obj, Int zone, PathfindLayerEnum layer,
	const Coord3D *startWorld, const Coord3D *endWorld, Bool considerTransient)
{
	ICoord2D end;
	ICoord2D start;
	unsigned char storage[0x58];
	BfmeCheckMovementInfo *payload = new (storage) BfmeCheckMovementInfo(
		this, obj, zone, considerTransient, 0, 1, 1);
	worldToCell(startWorld, &start);
	worldToCell(endWorld, &end);
	return iterateCellsAlongLine(start, end, layer, payload) == 0;
}

// ?lineClear@Pathfinder@@QAEHPAVObject@@HW4PathfindLayerEnum@@PBUCoord3D@@2@Z
Bool Pathfinder::lineClear(Object *obj, Int value, PathfindLayerEnum layer,
	const Coord3D *startWorld, const Coord3D *endWorld)
{
	ICoord2D end;
	ICoord2D start;
	unsigned char storage[0x54];
	Rva003E5A50Info *payload = new (storage) Rva003E5A50Info(this, obj, value);
	worldToCell(startWorld, &start);
	worldToCell(endWorld, &end);
	return iterateCellsAlongLine(start, end, layer, payload) == 0;
}
