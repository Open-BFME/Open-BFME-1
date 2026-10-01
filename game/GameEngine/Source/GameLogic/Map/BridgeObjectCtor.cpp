// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/stringinline /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// Bridge::Bridge(Object*) at 0x001A9CE0. The matched
// TerrainLogic::addLandmarkBridgeToLogic caller reaches it through 0x00047C0D.
// The body ends with ret 4 at +0x581; the following 16-byte switch table was
// compared separately. All 1428 bytes match retail, while the row claims the
// 1412 executable bytes. Three ABI pins document independently decoded callees.
//
// Start: the banked 1408-byte Zero Hour reconstruction. BFME initializes the
// BridgeInfo member, uses the owning StringBase string model, and constructs
// a real Coord3D array. Its visible empty destructor still participates in the
// compiler's vector helpers; a scalar Coord3D copy gives the retail cursor.
#include "StringInline.h"
// 0x00887C90 is StringBase<char>::set(const StringBase<char>&), called here
// on Bridge+8. The existing StringInline header has the correct ownership
// model but no assignment operation; this view supplies that proven ABI.
class Rva00887C90String { public: void set(const AsciiString &); };
#define Coord3D BridgePoint
#define Coord2D BridgeDirection
#include "coord.h"
#undef Coord3D
#undef Coord2D
#include "coord3d.h"
inline Coord3D::Coord3D(const Coord3D &that) { x = that.x; y = that.y; z = that.z; }
inline Coord3D::~Coord3D() {}
extern float __cdecl Cos(float);
extern float __cdecl Sin(float);
enum BridgeTowerType { BRIDGE_TOWER_FROM_LEFT, BRIDGE_TOWER_FROM_RIGHT, BRIDGE_TOWER_TO_LEFT, BRIDGE_TOWER_TO_RIGHT, BRIDGE_MAX_TOWERS };
enum BodyDamageType { BODY_PRISTINE };
enum PathfindLayerEnum { LAYER_GROUND };
enum ObjectID { INVALID_ID = 0 };
const float PATHFIND_CELL_SIZE_F = 10.0f;
class Overridable {
public:
    const Overridable *getFinalOverride() const;
    void *m_vptr;
    Overridable *m_nextOverride;
};
class BfmeGeometryInfo {
public:
    float boxMajorRadius() const;
    float boxMinorRadius() const;
    char m_prefix[0x24];
    float m_majorRadius, m_minorRadius;
};
class ThingTemplate : public Overridable {
public:
    char m_08[0x18];
    AsciiString m_name;
    char m_24[0x4c];
    float m_70;
    const AsciiString &getName() const { return m_name; }
};
class Object {
public:
    void *m_vptr;
    ThingTemplate *m_template;
    char m_08[0x30];
    BridgePoint m_cachedPos;
    float m_orientation;
    char m_48[0x2c];
    ObjectID m_id;
    char m_78[0x34];
    BfmeGeometryInfo m_ac;
    const ThingTemplate *getTemplate() const {
        const ThingTemplate *t = m_template;
        if (!t) return 0;
        return t->m_nextOverride ? (const ThingTemplate *)t->m_nextOverride->getFinalOverride() : t;
    }
    const BridgePoint *getPosition() const { return &m_cachedPos; }
    float getOrientation() const { return m_orientation; }
    const BfmeGeometryInfo &getGeometryInfo() const { return m_ac; }
    ObjectID getID() const { return m_id; }
};
// ILT 0x00035D82 -> 0x001A87C0 copy-constructs an AsciiString in the
// hidden result from this+0x54+4*index and returns that result (ret 8).
// The Zero Hour getter and this constructor's findTemplate call independently
// identify it. The existing address-derived callee body is also retained as evidence.
class TerrainRoadType {
public:
    AsciiString getTowerObjectName(BridgeTowerType);
};
class TerrainRoadCollection { public: TerrainRoadType *findBridge(AsciiString); };
class BfmeThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
class ThingFactory;
extern TerrainRoadCollection *TheTerrainRoads;
extern ThingFactory *TheThingFactory;
static inline BfmeThingFactory *localThingFactory() { return (BfmeThingFactory *)TheThingFactory; }
struct BridgeInfo {
    BridgePoint from, to;
    float bridgeWidth;
    BridgePoint fromLeft, fromRight, toLeft, toRight;
    int bridgeIndex;
    BodyDamageType curDamageState;
    ObjectID bridgeObjectID;
    ObjectID towerObjectID[BRIDGE_MAX_TOWERS];
    bool damageStateChanged;
    __forceinline BridgeInfo() {
        from.zero(); to.zero(); bridgeWidth = 0;
        fromLeft.zero(); fromRight.zero(); toLeft.zero(); toRight.zero();
        bridgeIndex = 0; curDamageState = BODY_PRISTINE; damageStateChanged = false;
        bridgeObjectID = INVALID_ID;
        for (int i=0; i<BRIDGE_MAX_TOWERS; ++i) towerObjectID[i]=INVALID_ID;
    }
};
class Bridge {
public:
    Bridge(Object *);
    virtual ~Bridge();
    // Native coord3d.h spells Coord3D as class; the pre-existing caller pin
    // spells the same witnessed 12-byte coordinate parameter as struct.
    Object *createTower(Coord3D *, BridgeTowerType, const ThingTemplate *, Object *);
private:
    Bridge *m_next;
    AsciiString m_templateName;
    BridgeInfo m_bridgeInfo;
    Region2D m_bounds;
    PathfindLayerEnum m_layer;
    void *m_extra;
};

Bridge::Bridge(Object *bridgeObj) : m_next(0), m_layer(LAYER_GROUND), m_extra(0)
{
	((Rva00887C90String *)&m_templateName)->set(bridgeObj->getTemplate()->getName());


	const BridgePoint *pos = bridgeObj->getPosition();
	Real angle = bridgeObj->getOrientation();

	Real halfsizeX = bridgeObj->getGeometryInfo().boxMajorRadius();
	Real halfsizeY = bridgeObj->getGeometryInfo().boxMinorRadius();
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

	BridgeDirection v;
	v.x = m_bridgeInfo.toLeft.x - m_bridgeInfo.toRight.x;
	v.y = m_bridgeInfo.toLeft.y - m_bridgeInfo.toRight.y;
	v.normalize();

	Coord3D towerPos[BRIDGE_MAX_TOWERS];
	*(BridgePoint *)&towerPos[BRIDGE_TOWER_FROM_LEFT] = m_bridgeInfo.fromLeft;
	*(BridgePoint *)&towerPos[BRIDGE_TOWER_FROM_RIGHT] = m_bridgeInfo.fromRight;
	*(BridgePoint *)&towerPos[BRIDGE_TOWER_TO_LEFT] = m_bridgeInfo.toLeft;
	*(BridgePoint *)&towerPos[BRIDGE_TOWER_TO_RIGHT] = m_bridgeInfo.toRight;

	Real offset = PATHFIND_CELL_SIZE_F/2.0f;
	const ThingTemplate *towerTemplate;
	BridgeTowerType type;
	Object *tower;
	for( Int i = 0; i < BRIDGE_MAX_TOWERS; ++i )
	{
		type = (BridgeTowerType)i;
		towerTemplate = localThingFactory()->findTemplate( bridgeTemplate->getTowerObjectName( type ) );
		if (towerTemplate) {
			offset = towerTemplate->m_70;
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
		m_bridgeInfo.towerObjectID[i] = tower->getID();
	}

}
