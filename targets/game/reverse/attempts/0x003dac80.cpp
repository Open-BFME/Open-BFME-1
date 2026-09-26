// ?adjust003DAC80@Rva003DAC80@@QAE_NPAUCoord3D@@@Z
// partial score=0.85 date=2026-09-16
// Scratch-only complete reconstruction probe for retail 0x003DAC80 (170 bytes).
// The owner and method remain address-derived.  Retail's entry is thiscall with
// one stack argument: a Coord3D pointer updated in place.
//
// The 0x003D9F00 helper is deliberately declared with the ABI witnessed at
// this callsite.  Its direct retail route here is ILT 0x000135E3; the similarly
// named route at 0x0004ACBE reaches a different body and is not used.

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

	// Four stack arguments, as seen at 0x003DAC80:
	//   const ICoord2D &, Int scanLimit, ICoord2D *result,
	//   Pathfinder *const *context
	Bool walk003D9F00( const ICoord2D &cell, Int scanLimit,
		ICoord2D *result, Pathfinder *const *context );
};

// The address-derived declaration above is typed; this local alternate name
// records the already-proven callsite route without adding a symbols.csv pin.
#pragma comment(linker, "/alternatename:?walk003D9F00@Pathfinder@@QAE_NABUICoord2D@@HPAUICoord2D@@PAPAV1@@Z=?j_000135e3@@YAXXZ")

class Rva003DAC80 : public Pathfinder
{
public:
	Bool adjust003DAC80( Coord3D *posInOut );
};

Bool Rva003DAC80::adjust003DAC80( Coord3D *posInOut )
{
	ICoord2D localCell;
	ICoord2D selectedCell;
	Pathfinder *context;
	if (worldToCell( posInOut, &localCell ))
		return false;
	context = this;
	if (!walk003D9F00( localCell, 0x190, &selectedCell, &context ))
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
