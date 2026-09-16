// ?adjust003DAD60@Rva003DAD60@@QAE_NPAUCoord3D@@@Z
// partial score=0.85 date=2026-09-16
// Scratch-only complete reconstruction probe for retail 0x003DAD60 (170 bytes).
// The owner and method remain address-derived.  Retail's entry is thiscall with
// one stack argument: a Coord3D pointer updated in place.
//
// The caller-side four-argument ABI is decoded independently here.  ILT
// 0x00003C24 reaches the distinct helper body at 0x003DA3C0; this is not the
// 0x000135E3 route to 0x003D9F00 used by the adjacent twin.

typedef int Int;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};

class TerrainLogic
{
public:
	virtual void _pad00( void );
	virtual void _pad04( void );
	virtual void _pad08( void );
	virtual void _pad0C( void );
	virtual void _pad10( void );
	virtual void _pad14( void );
	virtual void _pad18( void );
	virtual float getLayerHeight( float x, float y, PathfindLayerEnum layer,
		Coord3D *normal, bool clip ) const;
};

extern TerrainLogic *TheTerrainLogic;
extern float Rva00C75334One;

class Pathfinder
{
public:
	Bool worldToCell( const Coord3D *pos, ICoord2D *cell );

	// Retail pushes four stack arguments in this order at the callsite:
	//   const ICoord2D &, Int scanLimit, ICoord2D *result,
	//   Pathfinder *const *context
	Bool walk003DA3C0( const ICoord2D &cell, Int scanLimit,
		ICoord2D *result, Pathfinder *const *context );
};

// This typed, address-derived declaration records the proven ILT route locally;
// it does not add a symbols.csv pin.  The spelling uses ICoord2D (not Coord2).
#pragma comment(linker, "/alternatename:?walk003DA3C0@Pathfinder@@QAE_NABUICoord2D@@HPAUICoord2D@@PAPAV1@@Z=?j_00003c24@@YAXXZ")

class Rva003DAD60 : public Pathfinder
{
public:
	Bool adjust003DAD60( Coord3D *posInOut );
};

Bool Rva003DAD60::adjust003DAD60( Coord3D *posInOut )
{
	ICoord2D localCell;
	ICoord2D selectedCell;
	Pathfinder *context;
	if (worldToCell( posInOut, &localCell ))
		return false;
	context = this;
	if (!walk003DA3C0( localCell, 0x190, &selectedCell, &context ))
		return false;

	Int x = selectedCell.x * 10;
	float worldX = (float)x + Rva00C75334One;
	posInOut->x = worldX;

	Int y = selectedCell.y * 10;
	float worldY = (float)y + Rva00C75334One;
	posInOut->y = worldY;
	posInOut->z = TheTerrainLogic->getLayerHeight( worldX, worldY,
		(PathfindLayerEnum)1, 0, true );
	return true;
}
