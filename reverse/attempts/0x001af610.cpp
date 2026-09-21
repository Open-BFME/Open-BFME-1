// ?d_001af610@@YAXXZ
// partial score=0.8 date=2026-09-18
// cl: /DNDEBUG /MD /EHsc
// Retail 0x001AF610.  The ILT at 0x00026C4C names this free cdecl helper
// findPositionAround; the retail trace strings identify its TerrainLogic map
// implementation.  Keep the BFME globals as address views so this TU does not
// manufacture alternate class declarations for the shared singletons.

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Region3D
{
	float x_min;
	float y_min;
	float z_min;
	float x_max;
	float y_max;
	float z_max;

	bool isInRegionNoZ( const Coord3D *point ) const
	{
		return x_min < point->x && point->x < x_max &&
			y_min < point->y && point->y < y_max;
	}
};

struct FindPositionOptions
{
	unsigned int flags;
	float minRadius;
	float maxRadius;
	float startAngle;
	float maxZDelta;
	void *ignoreObject;
	const void *sourceToPathToDest;
	void *relationshipObject;
};

class TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void getMaximumPathfindExtent( Region3D *extent ) const = 0;
};

struct BfmeGameLogic
{
	char prefix[0x1a0];
	int frame;
};

extern void j_0000fa6f( void );
extern float GetGameLogicRandomValueReal( float low, float high, char *file, int line );
extern "C" double __cdecl ceil( double value );
extern "C" void __cdecl bfmeRetailCritterDesyncLog( void *, const char *, ... );

typedef bool (__cdecl *TryPositionCall)( const Coord3D *, float, float,
	const FindPositionOptions *, Coord3D * );

#define BFME_TERRAIN_LOGIC (*(TerrainLogic **)0x012EF4CC)
#define BFME_DOCKING_TRACE (*(bool *)0x012F0478)
#define BFME_GAME_LOGIC (*(BfmeGameLogic **)0x012F0898)
#define TheCRCParameterCheck (*(void **)0x012ED4FC)
#define BFME_ONE (*(const float *)0x01075334)
#define BFME_RING_SPACING (*(const float *)0x012ACC34)
#define BFME_TWO_PI_MEMORY (*(const float *)0x01087B10)
#define BFME_HALF (*(const float *)0x0107533C)

bool findPositionAround( const Coord3D *center,
	const FindPositionOptions *options,
	Coord3D *result )
{
	Region3D extent;
	TerrainLogic *terrainLogic = *(TerrainLogic **)0x012EF4CC;
	terrainLogic->getMaximumPathfindExtent( &extent );

	{
		register void *crcParameterCheck;
		if (BFME_DOCKING_TRACE && BFME_GAME_LOGIC->frame > 0 &&
			(crcParameterCheck = TheCRCParameterCheck) != 0)
	{
		bfmeRetailCritterDesyncLog(crcParameterCheck,
			"    TerrainLogic::FindPositionAround() center=%g,%g,%g, extent=lo:%g,%g,%g hi:%g,%g,%g",
			center->x, center->y, center->z,
			extent.x_min, extent.y_min, extent.z_min,
			extent.x_max, extent.y_max, extent.z_max);
	}
	}

	if (!extent.isInRegionNoZ( center ))
	{
		if (BFME_DOCKING_TRACE && BFME_GAME_LOGIC->frame > 0 &&
			TheCRCParameterCheck != 0)
		{
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
				"    !extent.isInRegionNoZ, result = center, return true");
		}

		*result = *center;
		return true;
	}

	float startAngle;
	if (options->startAngle == -99999.9f)
	{
		startAngle = GetGameLogicRandomValueReal(
			0.0f, 6.28318530717958647692f,
			(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Map\\TerrainLogic.cpp",
			0x1065);
	}
	else
	{
		startAngle = options->startAngle;
	}

	if (BFME_DOCKING_TRACE && BFME_GAME_LOGIC->frame > 0 && TheCRCParameterCheck)
	{
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
			"    startAngle=%g", startAngle);
	}

	for (float dist = options->minRadius;
		dist <= options->maxRadius;
		dist += BFME_RING_SPACING)
	{
		float angleSpacing;
		if (dist == options->minRadius)
			angleSpacing = 6.28318530717958647692f;
		else
			angleSpacing = (BFME_RING_SPACING / (dist + BFME_ONE)) * 1.0471976f;

		if (BFME_DOCKING_TRACE && BFME_GAME_LOGIC->frame > 0 && TheCRCParameterCheck)
		{
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
				"    angleSpacing=%g", angleSpacing);
		}

		int samples = (int)ceil( (double)((BFME_TWO_PI_MEMORY / angleSpacing) * BFME_HALF) );
		for (int i = 0; i < samples; ++i)
		{
			if (((TryPositionCall)j_0000fa6f)(center, dist,
				startAngle + angleSpacing * i, options, result))
			{
				if (BFME_DOCKING_TRACE && BFME_GAME_LOGIC->frame > 0 && TheCRCParameterCheck)
				{
					bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
						"    TryPosition1 succeeds - i=%d, center=%g,%g,%g, dist=%g, angle=%g, result=%g,%g,%g",
						i, center->x, center->y, center->z, dist,
						startAngle + angleSpacing * i,
						result->x, result->y, result->z);
				}
				return true;
			}

			if (i != 0 && ((TryPositionCall)j_0000fa6f)(center, dist,
				startAngle - angleSpacing * i, options, result))
			{
				if (BFME_DOCKING_TRACE && BFME_GAME_LOGIC->frame > 0 && TheCRCParameterCheck)
				{
					bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
						"    TryPosition1 succeeds - i=%d, center=%g,%g,%g, dist=%g, angle=%g, result=%g,%g,%g",
						i, center->x, center->y, center->z, dist,
						startAngle - angleSpacing * i,
						result->x, result->y, result->z);
				}
				return true;
			}

			if (BFME_DOCKING_TRACE && BFME_GAME_LOGIC->frame > 0 && TheCRCParameterCheck)
			{
				bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
					"    TryPosition1&2 both failed - i=%d, center=%g,%g,%g, dist=%g, angle=%g",
					i, center->x, center->y, center->z, dist,
					startAngle - angleSpacing * i);
				}
		}
	}

	if (BFME_DOCKING_TRACE && BFME_GAME_LOGIC->frame > 0 && TheCRCParameterCheck)
	{
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
			"    TerrainLogic::FindPositionAround() total failure, return FALSE");
	}

	return false;
}
