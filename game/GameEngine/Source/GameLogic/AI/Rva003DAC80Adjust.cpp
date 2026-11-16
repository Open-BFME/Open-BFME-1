// ?adjust003DAC80@Rva003DAC80@@QAE_NPAUCoord3D@@@Z [retail body 0x003DAC80]
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include
// Twin of the matched 0x003DAD60 wrapper; this one walks the ground-layer
// circular iterator 0x003D9F00 (ILT 0x000135E3) instead of 0x003DA3C0.
// Retail wrapper keeps its unknown method identity address-derived.
typedef int Int;
typedef bool Bool;

#include "Lib/Coord3D.h"

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 1
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

class Pathfinder
{
public:
	Bool worldToCell( const Coord3D *pos, ICoord2D *cell );

	Bool iterateCircular1Ground003D9F00(const ICoord2D *cell, Int scanLimit,
		ICoord2D *result, void *context);

	// ?walk003D9F00@Pathfinder@@QAE_NABUICoord2D@@HPAU2@PBQAV1@@Z absent-from-retail
	__forceinline Bool walk003D9F00(const ICoord2D &cell, Int scanLimit,
		ICoord2D *result, Pathfinder *const *context)
	{
		return iterateCircular1Ground003D9F00(&cell, scanLimit, result, (void *)context);
	}
};

class Rva003DAC80 : public Pathfinder
{
public:
	Bool adjust003DAC80( Coord3D *posInOut );
};

Bool Rva003DAC80::adjust003DAC80( Coord3D *posInOut )
{
	ICoord2D selectedCell;
	{
		ICoord2D localCell;
		Pathfinder *context;
		if (worldToCell( posInOut, &localCell ))
			return false;
		context = this;
		if (!walk003D9F00( localCell, 0x190, &selectedCell, &context ))
			return false;
	}
	Int x = selectedCell.x * 10;
	float worldX = (float)x + 1.0f;
	posInOut->x = worldX;

	Int y = selectedCell.y * 10;
	float worldY = (float)y + 1.0f;
	posInOut->y = worldY;
	posInOut->z = TheTerrainLogic->getLayerHeight( worldX, worldY,
		PATHFIND_LAYER_GROUND, 0, true );
	return true;
}
