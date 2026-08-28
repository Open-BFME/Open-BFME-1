// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?iterateCellsAlongLine@Pathfinder@@: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// The world-space half of Pathfinder::iterateCellsAlongLine, thirteen times.
//
// Zero Hour declares one pair of overloads: a world-space one that converts
// both Coord3D endpoints to cell coordinates and forwards, and the cell-space
// Bresenham walk it forwards to.  Both take a CellAlongLineProc callback and a
// void* user data.  Retail drops the callback parameter -- the already-landed
// Pathfinder::moveAlliesAwayFromDestination conversion and the two pins in
// reverse/symbols.csv both show the cell-space walk taking four arguments with
// no callback among them -- so each call site gets its own overload, discriminated
// by the type of the user-data pointer.  Thirteen world-space forwarders survive
// in retail, byte-identical apart from the cell-space callee each one calls.
//
// Two of the callees were already pinned by earlier work and keep their spelling
// here: the MADStruct one at 0x003ED9F0, whose other caller IS
// moveAlliesAwayFromDestination, and the void* one at 0x003F1F00, whose other
// caller is Pathfinder::tightenPath.  A third is named by its only caller:
// Pathfinder::isAttackViewBlockedByObstacle at 0x003EA980 reaches 0x003E7E60,
// and Zero Hour's body of that function fills a ViewAttackBlockedStruct.
//
// The remaining ten user-data types are not recoverable from these bodies -- a
// forwarder reads nothing through the pointer -- so each is named for the
// cell-space walk it belongs to and left incomplete.  Nothing in the emitted
// bytes depends on the type; it exists to give each address one name.
//
// Frame: two ICoord2D locals in declaration order, start at esp+0xc and end at
// esp+4 after the saved esi, matching retail.

typedef int Int;
typedef bool Bool;

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

enum PathfindLayerEnum { LAYER_GROUND = 1 };

struct Rva003D7440Struct;
struct Rva003D7680Struct;
struct Rva003D79C0Struct;
struct Rva003DE480Struct;
struct ViewAttackBlockedStruct;
struct Rva003E33F0Struct;
struct Rva003E3650Struct;
struct Rva003E7F80Struct;
struct Rva003E81E0Struct;
struct Rva003E8440Struct;
struct MADStruct;
struct Rva003F1CA0Struct;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *world, ICoord2D *cell);		///< ILT thunk at 0x000171E8

	Int iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
			PathfindLayerEnum layer, Rva003D7440Struct *userData);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
			PathfindLayerEnum layer, Rva003D7440Struct *userData);	///< ILT thunk at 0x0004ACBE

	Int iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
			PathfindLayerEnum layer, Rva003D7680Struct *userData);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
			PathfindLayerEnum layer, Rva003D7680Struct *userData);	///< ILT thunk at 0x00048419

	Int iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
			PathfindLayerEnum layer, Rva003D79C0Struct *userData);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
			PathfindLayerEnum layer, Rva003D79C0Struct *userData);	///< ILT thunk at 0x00016103

	Int iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
			PathfindLayerEnum layer, Rva003DE480Struct *userData);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
			PathfindLayerEnum layer, Rva003DE480Struct *userData);	///< ILT thunk at 0x00005713

	Int iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
			PathfindLayerEnum layer, ViewAttackBlockedStruct *userData);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
			PathfindLayerEnum layer, ViewAttackBlockedStruct *userData);	///< ILT thunk at 0x0000CC1B

	Int iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
			PathfindLayerEnum layer, Rva003E33F0Struct *userData);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
			PathfindLayerEnum layer, Rva003E33F0Struct *userData);	///< ILT thunk at 0x00013DC2

	Int iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
			PathfindLayerEnum layer, Rva003E3650Struct *userData);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
			PathfindLayerEnum layer, Rva003E3650Struct *userData);	///< ILT thunk at 0x0004940E

	Int iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
			PathfindLayerEnum layer, Rva003E7F80Struct *userData);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
			PathfindLayerEnum layer, Rva003E7F80Struct *userData);	///< ILT thunk at 0x00029DF7

	Int iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
			PathfindLayerEnum layer, Rva003E81E0Struct *userData);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
			PathfindLayerEnum layer, Rva003E81E0Struct *userData);	///< ILT thunk at 0x00023DDF

	Int iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
			PathfindLayerEnum layer, Rva003E8440Struct *userData);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
			PathfindLayerEnum layer, Rva003E8440Struct *userData);	///< ILT thunk at 0x0001DAA2

	void iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
			PathfindLayerEnum layer, MADStruct *userData);

	Int iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
			PathfindLayerEnum layer, Rva003F1CA0Struct *userData);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
			PathfindLayerEnum layer, Rva003F1CA0Struct *userData);	///< ILT thunk at 0x0003EBC1

	Int iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
			PathfindLayerEnum layer, void *userData);

protected:
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
			PathfindLayerEnum layer, void *userData);		///< ILT thunk at 0x000190B0

private:
	void iterateCellsAlongLine(const ICoord2D *start, const ICoord2D *end,
			PathfindLayerEnum layer, MADStruct *userData);	///< ILT thunk at 0x00014092
};

// retail 0x003D9EA0 -- forwards to the cell-space walk at 0x003D7440
Int Pathfinder::iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
																PathfindLayerEnum layer, Rva003D7440Struct *userData)
{
	ICoord2D start, end;
	worldToCell( &startWorld, &start );
	worldToCell( &endWorld, &end );
	return iterateCellsAlongLine(start, end, layer, userData);
}

// retail 0x003DA9A0 -- forwards to the cell-space walk at 0x003D7680
Int Pathfinder::iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
																PathfindLayerEnum layer, Rva003D7680Struct *userData)
{
	ICoord2D start, end;
	worldToCell( &startWorld, &start );
	worldToCell( &endWorld, &end );
	return iterateCellsAlongLine(start, end, layer, userData);
}

// retail 0x003DAA00 -- forwards to the cell-space walk at 0x003D79C0
Int Pathfinder::iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
																PathfindLayerEnum layer, Rva003D79C0Struct *userData)
{
	ICoord2D start, end;
	worldToCell( &startWorld, &start );
	worldToCell( &endWorld, &end );
	return iterateCellsAlongLine(start, end, layer, userData);
}

// retail 0x003E2ED0 -- forwards to the cell-space walk at 0x003DE480
Int Pathfinder::iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
																PathfindLayerEnum layer, Rva003DE480Struct *userData)
{
	ICoord2D start, end;
	worldToCell( &startWorld, &start );
	worldToCell( &endWorld, &end );
	return iterateCellsAlongLine(start, end, layer, userData);
}

// retail 0x003E7E60 -- forwards to the cell-space walk at 0x003E3190
Int Pathfinder::iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
																PathfindLayerEnum layer, ViewAttackBlockedStruct *userData)
{
	ICoord2D start, end;
	worldToCell( &startWorld, &start );
	worldToCell( &endWorld, &end );
	return iterateCellsAlongLine(start, end, layer, userData);
}

// retail 0x003E7EC0 -- forwards to the cell-space walk at 0x003E33F0
Int Pathfinder::iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
																PathfindLayerEnum layer, Rva003E33F0Struct *userData)
{
	ICoord2D start, end;
	worldToCell( &startWorld, &start );
	worldToCell( &endWorld, &end );
	return iterateCellsAlongLine(start, end, layer, userData);
}

// retail 0x003E7F20 -- forwards to the cell-space walk at 0x003E3650
Int Pathfinder::iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
																PathfindLayerEnum layer, Rva003E3650Struct *userData)
{
	ICoord2D start, end;
	worldToCell( &startWorld, &start );
	worldToCell( &endWorld, &end );
	return iterateCellsAlongLine(start, end, layer, userData);
}

// retail 0x003ED8D0 -- forwards to the cell-space walk at 0x003E7F80
Int Pathfinder::iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
																PathfindLayerEnum layer, Rva003E7F80Struct *userData)
{
	ICoord2D start, end;
	worldToCell( &startWorld, &start );
	worldToCell( &endWorld, &end );
	return iterateCellsAlongLine(start, end, layer, userData);
}

// retail 0x003ED930 -- forwards to the cell-space walk at 0x003E81E0
Int Pathfinder::iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
																PathfindLayerEnum layer, Rva003E81E0Struct *userData)
{
	ICoord2D start, end;
	worldToCell( &startWorld, &start );
	worldToCell( &endWorld, &end );
	return iterateCellsAlongLine(start, end, layer, userData);
}

// retail 0x003ED990 -- forwards to the cell-space walk at 0x003E8440
Int Pathfinder::iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
																PathfindLayerEnum layer, Rva003E8440Struct *userData)
{
	ICoord2D start, end;
	worldToCell( &startWorld, &start );
	worldToCell( &endWorld, &end );
	return iterateCellsAlongLine(start, end, layer, userData);
}

// retail 0x003F1C40 -- forwards to the cell-space walk at 0x003ED9F0
void Pathfinder::iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
																PathfindLayerEnum layer, MADStruct *userData)
{
	ICoord2D start, end;
	worldToCell( &startWorld, &start );
	worldToCell( &endWorld, &end );
	iterateCellsAlongLine(&start, &end, layer, userData);
}

// retail 0x003F5BB0 -- forwards to the cell-space walk at 0x003F1CA0
Int Pathfinder::iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
																PathfindLayerEnum layer, Rva003F1CA0Struct *userData)
{
	ICoord2D start, end;
	worldToCell( &startWorld, &start );
	worldToCell( &endWorld, &end );
	return iterateCellsAlongLine(start, end, layer, userData);
}

// retail 0x003F5C10 -- forwards to the cell-space walk at 0x003F1F00
Int Pathfinder::iterateCellsAlongLine(const Coord3D &startWorld, const Coord3D &endWorld,
																PathfindLayerEnum layer, void *userData)
{
	ICoord2D start, end;
	worldToCell( &startWorld, &start );
	worldToCell( &endWorld, &end );
	return iterateCellsAlongLine(start, end, layer, userData);
}

