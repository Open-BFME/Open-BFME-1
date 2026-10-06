// cl: /DNDEBUG /MD /EHsc
// findPositionAround, retail RVA 0x001AF610 (1139 bytes), free cdecl.
// Identity: the ILT 0x00026C4C pin (?findPositionAround@@YA_NPBUCoord3D@@
// PBUFindPositionOptions@@PAU1@@Z) jumps here, and the matched callers
// (WorkerAIUpdate::findGoodBuildOrRepairPosition, DockUpdate,
// CreateCrateDie, GarrisonContain) call it with that signature.  The body is
// Zero Hour's PartitionManager::findPositionAround moved into BFME's
// TerrainLogic.cpp (the GetGameLogicRandomValueReal file literal, line 0x1065),
// plus BFME's docking-trace diagnostics whose format strings name
// "TerrainLogic::FindPositionAround()".  The sanity NULL check is gone.
// ringSpacing is ZH's file-static Real (5.0f), here the .data word at
// RVA 0x00EACC34, pinned under an address-keeping name.  The sample count is
// fast_float2long_round((Real)ceil(x)), the CRT ceil import plus fistp.
// Note the second success trace prints startAngle + angleSpacing * i, as
// retail does.
#include <math.h>

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#define TRUE true
#define FALSE false
#define TWO_PI 6.28318530718f
#define RANDOM_START_ANGLE -99999.9f

struct Coord3D
{
	Real x, y, z;
};

struct Region3D
{
	Coord3D lo, hi;

	Bool isInRegionNoZ( const Coord3D *query ) const
	{
		return (lo.x < query->x) && (query->x < hi.x) &&
			(lo.y < query->y) && (query->y < hi.y);
	}
};

struct FindPositionOptions
{
	UnsignedInt flags;
	Real minRadius;
	Real maxRadius;
	Real startAngle;
	Real maxZDelta;
	void *ignoreObject;
	const void *sourceToPathToDest;
	void *relationshipObject;
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void getMaximumPathfindExtent( Region3D *extent );
};
extern TerrainLogic *TheTerrainLogic;

class GameLogic
{
public:
	Int getFrame() const { return m_frame; }
	char prefix[0x1a0];
	Int m_frame;
};
extern GameLogic *TheGameLogic;

class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
extern bool g_bfmeDockingTraceActive;
extern "C" void bfmeRetailCritterDesyncLog( CRCParameterCheck *, const char *, ... );

Real g_rva001AF610RingSpacing = 5.0f;

Real GetGameLogicRandomValueReal( Real lo, Real hi, char *file, Int line );
Bool Rva001AEA80TryPosition( const Coord3D *center, Real dist, Real angle,
	const FindPositionOptions *options, Coord3D *result );

__forceinline long fast_float2long_round( float f )
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define DOCKING_TRACE (g_bfmeDockingTraceActive && TheGameLogic->getFrame() > 0 && TheCRCParameterCheck)

Bool findPositionAround( const Coord3D *center,
	const FindPositionOptions *options,
	Coord3D *result )
{
	Region3D extent;
	TheTerrainLogic->getMaximumPathfindExtent( &extent );

	if (DOCKING_TRACE)
		bfmeRetailCritterDesyncLog( TheCRCParameterCheck,
			"    TerrainLogic::FindPositionAround() center=%g,%g,%g, extent=lo:%g,%g,%g hi:%g,%g,%g",
			center->x, center->y, center->z,
			extent.lo.x, extent.lo.y, extent.lo.z,
			extent.hi.x, extent.hi.y, extent.hi.z );

	if (!extent.isInRegionNoZ( center ))
	{
		if (DOCKING_TRACE)
			bfmeRetailCritterDesyncLog( TheCRCParameterCheck,
				"    !extent.isInRegionNoZ, result = center, return true" );
		*result = *center;
		return true;
	}

	Real startAngle;
	if (options->startAngle == RANDOM_START_ANGLE)
		startAngle = GetGameLogicRandomValueReal( 0.0f, TWO_PI,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Map\\TerrainLogic.cpp", 0x1065 );
	else
		startAngle = options->startAngle;

	if (DOCKING_TRACE)
		bfmeRetailCritterDesyncLog( TheCRCParameterCheck, "    startAngle=%g", startAngle );

	for (Real dist = options->minRadius; dist <= options->maxRadius; dist += g_rva001AF610RingSpacing)
	{
		Real angleSpacing;
		if (dist == options->minRadius)
			angleSpacing = TWO_PI;
		else
			angleSpacing = (g_rva001AF610RingSpacing / (dist + 1.0f)) * (TWO_PI / 6.0f);

		if (DOCKING_TRACE)
			bfmeRetailCritterDesyncLog( TheCRCParameterCheck, "    angleSpacing=%g", angleSpacing );

		Int samples = fast_float2long_round( (Real)ceil( (TWO_PI / angleSpacing) / 2.0f ) );
		for (Int i = 0; i < samples; ++i)
		{
			if (Rva001AEA80TryPosition( center, dist, startAngle + angleSpacing * i, options, result ) == TRUE)
			{
				if (DOCKING_TRACE)
					bfmeRetailCritterDesyncLog( TheCRCParameterCheck,
						"    TryPosition1 succeeds - i=%d, center=%g,%g,%g, dist=%g, angle=%g, result=%g,%g,%g",
						i, center->x, center->y, center->z, dist, startAngle + angleSpacing * i,
						result->x, result->y, result->z );
				return TRUE;
			}

			if (i != 0)
			{
				if (Rva001AEA80TryPosition( center, dist, startAngle - angleSpacing * i, options, result ))
				{
					if (DOCKING_TRACE)
						bfmeRetailCritterDesyncLog( TheCRCParameterCheck,
							"    TryPosition2 succeeds - i=%d, center=%g,%g,%g, dist=%g, angle=%g, result=%g,%g,%g",
							i, center->x, center->y, center->z, dist, startAngle + angleSpacing * i,
							result->x, result->y, result->z );
					return TRUE;
				}
			}

			if (DOCKING_TRACE)
				bfmeRetailCritterDesyncLog( TheCRCParameterCheck,
					"    TryPosition1&2 both failed - i=%d, center=%g,%g,%g, dist=%g, angle=%g",
					i, center->x, center->y, center->z, dist, startAngle + angleSpacing * i );
		}
	}

	if (DOCKING_TRACE)
		bfmeRetailCritterDesyncLog( TheCRCParameterCheck,
			"    TerrainLogic::FindPositionAround() total failure, return FALSE" );

	return FALSE;
}
