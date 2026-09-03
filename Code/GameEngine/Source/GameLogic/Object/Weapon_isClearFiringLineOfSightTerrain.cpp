// cl: /DNDEBUG /MD /EHs-c-
//
// Weapon::isClearFiringLineOfSightTerrain(source, victimPos). ZH adds
// getMaxHeightAbovePosition onto the source position then asks
// PartitionManager for terrain LOS; BFME asks TerrainLogic::isClearLineOfSight
// at vtable +0x3C instead. this is unused, matching the simplified ZH body.

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

private:
	unsigned char m_unreconstructed_00[0x38];
	Coord3D m_position;
	unsigned char m_unreconstructed_44[0xAC - 0x44];
	GeometryInfo m_geometry;
};

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
	bool isClearFiringLineOfSightTerrain(const Object *source, const Coord3D &victimPos) const;
	bool isClearGoalFiringLineOfSightTerrain(const Object *source, const Coord3D &goalPos, const Coord3D &victimPos) const;
};

bool Weapon::isClearFiringLineOfSightTerrain(const Object *source, const Coord3D &victimPos) const
{
	Coord3D origin = *source->getPosition();
	origin.z += source->getGeometryInfo().getMaxHeightAbovePosition();
	return TheTerrainLogic->isClearLineOfSight(origin, victimPos);
}

bool Weapon::isClearGoalFiringLineOfSightTerrain(const Object *source, const Coord3D &goalPos, const Coord3D &victimPos) const
{
	Coord3D origin = goalPos;
	origin.z += source->getGeometryInfo().getMaxHeightAbovePosition();
	return TheTerrainLogic->isClearLineOfSight(origin, victimPos);
}
