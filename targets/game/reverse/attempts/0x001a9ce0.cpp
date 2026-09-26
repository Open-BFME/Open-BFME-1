// ??0Bridge@@QAE@PAVObject@@@Z
// partial score=0.25 date=2026-09-22
// cl: /ICode/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/GameEngine/Source/Common/System /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "GameClient/TerrainRoads.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/BodyModule.h"

struct BridgeInfo
{
	Coord3D from, to;
	Real bridgeWidth;
	Coord3D fromLeft, fromRight, toLeft, toRight;
	Int bridgeIndex;
	BodyDamageType curDamageState;
	ObjectID bridgeObjectID;
	ObjectID towerObjectID[BRIDGE_MAX_TOWERS];
	Bool damageStateChanged;
};

class Bridge
{
public:
	Bridge(Object *bridgeObj);
	Object *createTower(Coord3D *worldPos, BridgeTowerType towerPos,
		const ThingTemplate *towerTemplate, Object *bridge);

private:
	void *m_vptr;
	Bridge *m_next;
	AsciiString m_templateName;
	BridgeInfo m_bridgeInfo;
	Region2D m_bounds;
	PathfindLayerEnum m_layer;
	void *m_extra;
};

Bridge::Bridge(Object *bridgeObj) : m_vptr((void *)0x0109C354), m_next(NULL)
{
	m_templateName = bridgeObj->getTemplate()->getName();

	DEBUG_ASSERTLOG( bridgeObj->getGeometryInfo().getGeomType()==GEOMETRY_BOX, ("Bridges need to be rectangles.\n"));

	const Coord3D *pos = bridgeObj->getPosition();
	Real angle = bridgeObj->getOrientation();

	Real halfsizeX = bridgeObj->getGeometryInfo().getMajorRadius();
	Real halfsizeY = bridgeObj->getGeometryInfo().getMinorRadius();
	m_bridgeInfo.bridgeWidth = 2*halfsizeY;

	Real c = (Real)Cos(angle);
	Real s = (Real)Sin(angle);

	m_bridgeInfo.fromLeft.set(pos->x-halfsizeX*c-halfsizeY*s, pos->y + halfsizeY*c - halfsizeX*s, pos->z);
	m_bridgeInfo.toLeft.set(pos->x+halfsizeX*c-halfsizeY*s, pos->y + halfsizeY*c + halfsizeX*s, pos->z);
	m_bridgeInfo.fromRight.set(pos->x-halfsizeX*c+halfsizeY*s, pos->y - halfsizeY*c - halfsizeX*s, pos->z);
	m_bridgeInfo.toRight.set(pos->x+halfsizeX*c+halfsizeY*s, pos->y - halfsizeY*c + halfsizeX*s, pos->z);

	m_bridgeInfo.from.x = (m_bridgeInfo.fromLeft.x + m_bridgeInfo.fromRight.x)/2.0f;
	m_bridgeInfo.from.y = (m_bridgeInfo.fromLeft.y + m_bridgeInfo.fromRight.y)/2.0f;
	m_bridgeInfo.from.z = (m_bridgeInfo.fromLeft.z + m_bridgeInfo.fromRight.z)/2.0f;

	m_bridgeInfo.to.x = (m_bridgeInfo.toLeft.x + m_bridgeInfo.toRight.x)/2.0f;
	m_bridgeInfo.to.y = (m_bridgeInfo.toLeft.y + m_bridgeInfo.toRight.y)/2.0f;
	m_bridgeInfo.to.z = (m_bridgeInfo.toLeft.z + m_bridgeInfo.toRight.z)/2.0f;

	m_bounds.lo.x = m_bridgeInfo.fromLeft.x;
	m_bounds.lo.y = m_bridgeInfo.fromLeft.y;
	m_bounds.hi = m_bounds.lo;
	if (m_bounds.lo.x > m_bridgeInfo.fromRight.x) m_bounds.lo.x = m_bridgeInfo.fromRight.x;
	if (m_bounds.lo.y > m_bridgeInfo.fromRight.y) m_bounds.lo.y = m_bridgeInfo.fromRight.y;
	if (m_bounds.hi.x < m_bridgeInfo.fromRight.x) m_bounds.hi.x = m_bridgeInfo.fromRight.x;
	if (m_bounds.hi.y < m_bridgeInfo.fromRight.y) m_bounds.hi.y = m_bridgeInfo.fromRight.y;
	if (m_bounds.lo.x > m_bridgeInfo.toLeft.x) m_bounds.lo.x = m_bridgeInfo.toLeft.x;
	if (m_bounds.lo.y > m_bridgeInfo.toLeft.y) m_bounds.lo.y = m_bridgeInfo.toLeft.y;
	if (m_bounds.hi.x < m_bridgeInfo.toLeft.x) m_bounds.hi.x = m_bridgeInfo.toLeft.x;
	if (m_bounds.hi.y < m_bridgeInfo.toLeft.y) m_bounds.hi.y = m_bridgeInfo.toLeft.y;
	if (m_bounds.lo.x > m_bridgeInfo.toRight.x) m_bounds.lo.x = m_bridgeInfo.toRight.x;
	if (m_bounds.lo.y > m_bridgeInfo.toRight.y) m_bounds.lo.y = m_bridgeInfo.toRight.y;
	if (m_bounds.hi.x < m_bridgeInfo.toRight.x) m_bounds.hi.x = m_bridgeInfo.toRight.x;
	if (m_bounds.hi.y < m_bridgeInfo.toRight.y) m_bounds.hi.y = m_bridgeInfo.toRight.y;

	m_bridgeInfo.curDamageState = BODY_PRISTINE;
	m_bridgeInfo.bridgeObjectID = bridgeObj->getID();

	AsciiString bridgeTemplateName = bridgeObj->getTemplate()->getName();
	TerrainRoadType *bridgeTemplate = TheTerrainRoads->findBridge( bridgeTemplateName );
	if( bridgeTemplate == NULL ) {
		DEBUG_LOG(( "*** Bridge Template Not Found '%s'.", bridgeTemplateName ));
		return;
	}

	Coord2D v;
	v.x = m_bridgeInfo.toLeft.x - m_bridgeInfo.toRight.x;
	v.y = m_bridgeInfo.toLeft.y - m_bridgeInfo.toRight.y;
	v.normalize();

	Coord3D towerPos[BRIDGE_MAX_TOWERS];
	towerPos[BRIDGE_TOWER_FROM_LEFT] = m_bridgeInfo.fromLeft;
	towerPos[BRIDGE_TOWER_FROM_RIGHT] = m_bridgeInfo.fromRight;
	towerPos[BRIDGE_TOWER_TO_LEFT] = m_bridgeInfo.toLeft;
	towerPos[BRIDGE_TOWER_TO_RIGHT] = m_bridgeInfo.toRight;

	Real offset = PATHFIND_CELL_SIZE_F/2.0f;
	const ThingTemplate *towerTemplate;
	BridgeTowerType type;
	Object *tower;
	for( Int i = 0; i < BRIDGE_MAX_TOWERS; ++i )
	{
		type = (BridgeTowerType)i;
		towerTemplate = TheThingFactory->findTemplate( bridgeTemplate->getTowerObjectName( type ) );
		if (towerTemplate) {
			offset = towerTemplate->getTemplateGeometryInfo().getMajorRadius();
		}
		Coord3D pos = towerPos[type];
		switch( type )
		{
			case BRIDGE_TOWER_FROM_LEFT:
			case BRIDGE_TOWER_TO_LEFT:
				pos.x += v.x*offset;
				pos.y += v.y*offset;
				break;
			case BRIDGE_TOWER_FROM_RIGHT:
			case BRIDGE_TOWER_TO_RIGHT:
				pos.x -= v.x*offset;
				pos.y -= v.y*offset;
				break;
		}
		tower = createTower( &pos, type, towerTemplate, bridgeObj );
		if( tower )
			m_bridgeInfo.towerObjectID[i] = tower->getID();
	}

	m_next = NULL;
}
