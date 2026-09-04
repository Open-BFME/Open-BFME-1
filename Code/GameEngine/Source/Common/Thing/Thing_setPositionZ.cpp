// ?setPositionZ@Thing@@QAEXM@Z
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Byte-exact C++ reconstruction of Thing::setPositionZ at retail RVA 0x00132B60.

#include "PreRTS.h"
#include "Common/PerfTimer.h"
#include "Common/Thing.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/GlobalData.h"
#include "Common/NameKeyGenerator.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Team.h"
#include "Lib/Trig.h"
#include "GameLogic/TerrainLogic.h"

class BFMERetailThingVTable
{
public:
	virtual Real calculateHeightAboveTerrain() const = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, Real oldAngle) = 0;
};

class BFMERetailTerrainLogicVTable
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = NULL) const = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual PathfindLayerEnum alignOnTerrain(Real angle, const Coord3D& pos, Bool stickToGround, Matrix3D& mtx) = 0;
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ) = 0;
};

class BfmeSubC1054;

class BfmeD1054
{
public:
	void bfmeAdd1054(BfmeSubC1054 *item);
};

void Thing::setPositionZ(Real z)
{
	if (!(reinterpret_cast<const unsigned char *>(m_template.operator->())[0xc8] & 0x10))
	{
		Real oldAngle;
		Coord3D oldPos;
		const Coord3D *cachedPos = &m_cachedPos;
		oldAngle = m_cachedAngle;
		oldPos.x = cachedPos->x;
		oldPos.y = m_cachedPos.y;
		oldPos.z = m_cachedPos.z;
		Matrix3D oldMtx = m_transform;

		m_transform.Set_Z_Translation(z);
		m_cachedPos.z = z;

		if (m_cacheFlags & VALID_ALTITUDE_TERRAIN)
		{
			m_cachedAltitudeAboveTerrain += (z - oldPos.z);
		}
		if (m_cacheFlags & VALID_ALTITUDE_SEALEVEL)
		{
			m_cachedAltitudeAboveTerrainOrWater += (z - oldPos.z);
		}

		reinterpret_cast<BFMERetailThingVTable *>(this)->reactToTransformChange(&oldMtx, &oldPos, oldAngle);
	}
	else
	{
		Matrix3D mtx;
		const Bool stickToGround = true;
		Coord3D pos;
		pos.x = m_cachedPos.x;
		pos.y = m_cachedPos.y;
		pos.z = z;
		reinterpret_cast<BFMERetailTerrainLogicVTable *>(TheTerrainLogic)->alignOnTerrain(getOrientation(), pos, stickToGround, mtx);
		reinterpret_cast<BfmeD1054 *>(this)->bfmeAdd1054(reinterpret_cast<BfmeSubC1054 *>(&mtx));
	}
	DEBUG_ASSERTCRASH(!(_isnan(getPosition()->x) || _isnan(getPosition()->y) || _isnan(getPosition()->z)), ("Drawable/Object position NAN! '%s'\n", m_template->getName().str()));
}
