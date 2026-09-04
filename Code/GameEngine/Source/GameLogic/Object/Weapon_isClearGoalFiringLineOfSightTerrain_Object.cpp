// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: Weapon::isClearGoalFiringLineOfSightTerrain(source, goalPos, victim),
// retail 0x001E8C10 size 199. Twin of the landed Object-victim LOS at
// 0x001E8B70. Origin is goalPos plus source getMaxHeightAbovePosition;
// victim aim is the same Weapon helper. BFME then walks Object+4 through
// Overridable::getFinalOverride and, when template+0xCC bit 3 is set,
// asks TheAI->pathfinder() to adjust the two points. TerrainLogic
// vtable+0x3C isClearLineOfSight. Focused TU.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition(void) const;
};

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
	unsigned char m_pad_000[4];
	Overridable *m_nextOverride;
	unsigned char m_pad_008[0xCC - 0x08];
	unsigned int m_flagsCC;
};

class Object
{
public:
	const Coord3D *getPosition(void) const
	{
		return &m_position;
	}

	const GeometryInfo &getGeometryInfo(void) const
	{
		return m_geometry;
	}

	unsigned char m_pad_000[4];
	Overridable *m_template;
	unsigned char m_pad_008[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_pad_044[0xAC - 0x44];
	GeometryInfo m_geometry;
};

class Pathfinder
{
public:
	void bfmeAdjustLOSPoints(Coord3D *victimPos, Coord3D *origin);
};

class AI
{
public:
	unsigned char m_pad_000[0x0C];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

class TerrainLogic
{
public:
#define BFME_VIRTUAL_SLOT(n) virtual void _v##n(void) = 0
	BFME_VIRTUAL_SLOT(00); BFME_VIRTUAL_SLOT(01); BFME_VIRTUAL_SLOT(02); BFME_VIRTUAL_SLOT(03);
	BFME_VIRTUAL_SLOT(04); BFME_VIRTUAL_SLOT(05); BFME_VIRTUAL_SLOT(06); BFME_VIRTUAL_SLOT(07);
	BFME_VIRTUAL_SLOT(08); BFME_VIRTUAL_SLOT(09); BFME_VIRTUAL_SLOT(10); BFME_VIRTUAL_SLOT(11);
	BFME_VIRTUAL_SLOT(12); BFME_VIRTUAL_SLOT(13); BFME_VIRTUAL_SLOT(14);
#undef BFME_VIRTUAL_SLOT
	virtual bool isClearLineOfSight(const Coord3D &pos, const Coord3D &posOther) const = 0;
};

extern TerrainLogic *TheTerrainLogic;

class Weapon
{
public:
	bool isClearGoalFiringLineOfSightTerrain(const Object *source, const Coord3D &goalPos, const Object *victim) const;
	Coord3D bfmeGetLOSVictimPos(const Object *source, const Object *victim, int flag) const;
};

// ?isClearGoalFiringLineOfSightTerrain@Weapon@@QBE_NPBVObject@@ABUCoord3D@@0@Z
bool Weapon::isClearGoalFiringLineOfSightTerrain(const Object *source, const Coord3D &goalPos, const Object *victim) const
{
	const Coord3D *goal = &goalPos;
	float gy = goal->y;
	const Object *src = source;
	Coord3D origin;
	origin.x = goal->x;
	origin.y = gy;
	origin.z = goal->z;
	origin.z += src->getGeometryInfo().getMaxHeightAbovePosition();
	Coord3D victimPos;
	victimPos = bfmeGetLOSVictimPos(src, victim, 0);
	if (victim)
	{
		Overridable *tmpl = victim->m_template;
		const Overridable *resolved;
		if (!tmpl)
			resolved = 0;
		else if (tmpl->m_nextOverride)
			resolved = tmpl->m_nextOverride->getFinalOverride();
		else
			resolved = tmpl;
		if (resolved->m_flagsCC & 0x08000000)
		{
			AI *ai = TheAI;
			if (ai != 0 && ai->m_pathfinder != 0)
				ai->m_pathfinder->bfmeAdjustLOSPoints(&victimPos, &origin);
		}
	}
	return TheTerrainLogic->isClearLineOfSight(origin, victimPos);
}
