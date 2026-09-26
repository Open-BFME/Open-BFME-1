// ??0Bridge@@QAE@AAVBridgeInfo@@PAVDict@@VAsciiString@@H@Z
// Source conversion of retail RVA 0x001A98A0 (861 bytes).
// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2 /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// The coord.h aggregate gives the witnessed POD corners and center; use the
// native Coord2D declaration separately for the out-of-line toAngle call.
// Retail 0x001A98A0: the matched TerrainLogic::addBridgeToLogic caller
// passes BridgeInfo, Dict, AsciiString and a fourth word, and allocates 0x90.
#include "ascii_string.h"
#define Coord2D ZeroHourCoord2D
#include "coord.h"
#undef Coord2D
#include "coord2d.h"
#include <bitset>

inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->~StringBase<char>(); }
inline Coord2D::Coord2D() {}
inline Coord2D::~Coord2D() {}

class BridgeInfo;
class Dict;
class Team;
class ThingTemplate;
class TerrainRoadType;

// The matched copy constructor at 0x001A1F30 copies BridgeInfo's 0x6c bytes.
// Retain its existing address-derived identity until that callee is renamed.
class Gen_001A1F30 {
public:
    Gen_001A1F30(const Gen_001A1F30 &);
    Coord3D from, to;
    float bridgeWidth;
    Coord3D fromLeft, fromRight, toLeft, toRight;
    int bridgeIndex, curDamageState, bridgeObjectID;
    int towerObjectID[4];
    bool damageStateChanged;
};

struct BfmeVec4CMB { int words[4]; };
class BfmeThingCMB { public: void bfmeGoCMB(BfmeVec4CMB *); };

class Thing {
public:
    void setPosition(const Coord3D *);
    void setOrientation(float);
};
class Object : public Thing {
public:
    void updateObjValuesFromMapProperties(Dict *);
    char m_00[0x74];
    int m_id;
};
template<int N> class BitFlags {
public:
    std::bitset<N> m_bits;
};
class ThingFactory {
public:
    Object *newObject(const ThingTemplate *, Team *, const BitFlags<86> &, unsigned);
};
class BfmeThingFactory {
public:
    const ThingTemplate *findTemplate(const AsciiString &);
};
class TerrainRoadCollection {
public:
    TerrainRoadType *findBridge(AsciiString);
};
extern ThingFactory *TheThingFactory;
extern TerrainRoadCollection *TheTerrainRoads;

class Bridge {
public:
    Bridge(BridgeInfo &, Dict *, AsciiString, int);
    virtual ~Bridge();
private:
    Bridge *m_next;
    AsciiString m_templateName;
    Gen_001A1F30 m_bridgeInfo;
    Region2D m_bounds;
    int m_layer;
    BfmeThingCMB *m_8c;
};

template<class T> static inline const T &bridgeMin(const T &a, const T &b) { return a < b ? a : b; }
template<class T> static inline const T &bridgeMax(const T &a, const T &b) { return a > b ? a : b; }

Bridge::Bridge(BridgeInfo &info, Dict *props, AsciiString name, int extra) :
    m_next(0), m_bridgeInfo((const Gen_001A1F30 &)info), m_layer(0), m_8c((BfmeThingCMB *)extra)
{
    // The integer bounds and floating center have disjoint lifetimes.
    union { BfmeVec4CMB bounds; Coord3D center; };
    m_templateName = name;
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
    if (m_8c) {
        ((BfmeThingCMB *)extra)->bfmeGoCMB(&bounds);
        m_bounds.lo.x = bridgeMin(m_bounds.lo.x, (float)bounds.words[0]);
        m_bounds.lo.y = bridgeMin(m_bounds.lo.y, (float)bounds.words[1]);
        m_bounds.hi.x = bridgeMax(m_bounds.hi.x, (float)bounds.words[2]);
        m_bounds.hi.y = bridgeMax(m_bounds.hi.y, (float)bounds.words[3]);
    }
    m_bridgeInfo.curDamageState = 0;
    m_bridgeInfo.bridgeObjectID = 0;
    if (!props) return;
    static const ThingTemplate *genericBridgeTemplate = ((BfmeThingFactory *)TheThingFactory)->findTemplate("GenericBridge");
    if (!genericBridgeTemplate) return;
    BitFlags<86> status;
    Object *bridge = TheThingFactory->newObject(genericBridgeTemplate, 0, status, 0);
    center.x = (m_bridgeInfo.fromLeft.x + m_bridgeInfo.toRight.x) * 0.5f;
    center.y = (m_bridgeInfo.fromLeft.y + m_bridgeInfo.toRight.y) * 0.5f;
    center.z = (m_bridgeInfo.fromLeft.z + m_bridgeInfo.toRight.z) * 0.5f;
    bridge->setPosition(&center);
    m_bridgeInfo.bridgeObjectID = bridge->m_id;
    bridge->updateObjValuesFromMapProperties(props);
    {
        Coord2D direction;
        direction.x = m_bridgeInfo.toLeft.x - m_bridgeInfo.fromLeft.x;
        direction.y = m_bridgeInfo.toLeft.y - m_bridgeInfo.fromLeft.y;
        bridge->setOrientation(direction.toAngle());
    }
    TheTerrainRoads->findBridge(name);
}
