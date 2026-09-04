// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: Weapon::isClearFiringLineOfSightTerrain(source, victim),
// retail 0x001E8B70 size 122. Twin of the landed Coord3D overload at
// 0x001E1A60. Origin is source position plus getMaxHeightAbovePosition;
// victim aim comes from a Weapon helper (ILT 0x0003ABE3 -> 0x001E7480)
// instead of GeometryInfo::getCenterPosition. TerrainLogic vtable+0x3C
// isClearLineOfSight, same as the Coord3D overloads. Focused TU -- do
// not fold into Weapon.cpp.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Geometry.h
class GeometryInfo
{
public:
	float getMaxHeightAbovePosition(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	bool isClearFiringLineOfSightTerrain(const Object *source, const Object *victim) const;
	Coord3D bfmeGetLOSVictimPos(const Object *source, const Object *victim, int flag) const;
};

// ?isClearFiringLineOfSightTerrain@Weapon@@QBE_NPBVObject@@0@Z
bool Weapon::isClearFiringLineOfSightTerrain(const Object *source, const Object *victim) const
{
	Coord3D origin = *source->getPosition();
	origin.z += source->getGeometryInfo().getMaxHeightAbovePosition();
	Coord3D victimPos;
	victimPos = bfmeGetLOSVictimPos(source, victim, 0);
	return TheTerrainLogic->isClearLineOfSight(origin, victimPos);
}
