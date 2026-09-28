// ?Rva003DF250@Pathfinder@@QAE_NPAVObject@@PAUCoord3D@@@Z
// partial score=0.1443768997 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/Thing /Igame/GameEngine/Source/Common /Igame/GameEngine/Source/GameLogic /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#include <bitset>
#define ASCIISTRING_H
#include "ascii_string.h"
#define __THING_H_
#define __KINDOF_H_
#include "PreRTS.h"
#include "Common/GameType.h"
class Module;
typedef int Int;
typedef bool Bool;
typedef float Real;
extern "C" __declspec(dllimport) double __cdecl floor(double);
#undef REAL_TO_INT_FLOOR
#define REAL_TO_INT_FLOOR(x) fast_float2long_round((Real)floor((double)(x)))
extern const Real g_pathfindCellSize;
extern const Real g_pathfindDoubleCellSize;
extern const Real g_pathfindLevelLimit;
extern const Real g_pathfindCellCenterBias;

class BfmeOverridable {
public:
    BfmeOverridable *friend_getFinalOverride(void);
    BfmeOverridable *getFinalOverride(void) {
        if (!m_override) return this;
        return m_override->friend_getFinalOverride();
    }
    Int m_unknown00;
    BfmeOverridable *m_override;
    unsigned char m_pad08[0xc8 - 0x08];
    Int m_flagsC8;
    unsigned char m_padCC[0xd4 - 0xcc];
    Int m_flagsD4;
    unsigned char m_padD8[0x408 - 0xd8];
    Real m_level;
};
enum KindOfType { KINDOF_INVALID_003DF250 = 0 };
#define THING_TU_MEMBERS Bool isKindOf(KindOfType) const;
#define OBJECT_TU_MEMBERS \
    BfmeOverridable *bfmeTemplateView() const { return (BfmeOverridable *)m_template; } \
    Bool bfmeIsComputerControlled() const; \
    Real bfmeBoundingCircleRadius() const { return *(const Real *)((const char *)this + 0xbc); }
#include "Object/object.h"

struct PathfindCellInfo {
    unsigned char m_prefix[0x14];
    ObjectID m_goalUnitID;
    ObjectID m_posUnitID;
};
struct PathfindCell {
    PathfindCellInfo *m_info;
    Int m_unknown04;
    Int m_unknown08;
    unsigned int m_packed;
    Int getRawType() const { return m_packed & 7; }
    Int getFlags() const { return m_packed & 0x38; }
    unsigned char getGoalAircraftByte() const { return (unsigned char)(m_packed >> 21); }
    ObjectID getGoalUnit() const { return m_info ? m_info->m_goalUnitID : INVALID_ID; }
    ObjectID getPosUnit() const { return m_info ? m_info->m_posUnitID : INVALID_ID; }
};
class PathfindLayer {
public:
    PathfindCell *getCell(Int, Int);
private:
    unsigned char m_body[0x44];
};

class TerrainLogic { public: PathfindLayerEnum getLayerForDestination(Object *, const Coord3D *); };
class GameLogic { public: Object *findObjectByID(int); };
#define s_logic (*(GameLogic **)0x012F0898)
#define s_terrain (*(TerrainLogic **)0x012EF4CC)

class Pathfinder {
public:
    protected:
    void getRadiusAndCenter(const Object *, Int &, Bool &);
public:
    Bool worldToCell(const Coord3D *, ICoord2D *);
    void adjustCoordToCell(Int, Int, Bool, Coord3D &, PathfindLayerEnum);
    Bool Rva003DF250(Object *, Coord3D *);
    PathfindCell *getCell(Int, Int, Int);
private:
    unsigned char m_prefix[0x10];
    PathfindCell **m_map;
    IRegion2D m_extent;
    unsigned char m_mid[0x85c - 0x24];
    PathfindLayer m_layers[16];
};

__forceinline PathfindCell *Pathfinder::getCell(Int layer, Int x, Int y)
{
    if (x >= m_extent.lo.x && x <= m_extent.hi.x && y >= m_extent.lo.y && y <= m_extent.hi.y) {
        if (layer > 1 && layer <= 15) {
            PathfindCell *cell = m_layers[layer].getCell(x, y);
            if (cell) return cell;
        }
        return &m_map[x][y];
    }
    return 0;
}

__declspec(noinline) void Pathfinder::getRadiusAndCenter( const Object *object, Int &radius, Bool &centerInCell )
{
	Real diameter;
	Int maxRadius = 2;
	BfmeOverridable *t1 = object->bfmeTemplateView();
	if ((t1 == 0 ? t1 : t1->getFinalOverride())->m_flagsC8 & 0x400) {
		maxRadius = 4;
	} else {
		BfmeOverridable *t2 = object->bfmeTemplateView();
		if ((t2 == 0 ? t2 : t2->getFinalOverride())->m_flagsD4 & 0x1000) {
			maxRadius = 4;
		}
	}

	diameter = object->bfmeBoundingCircleRadius() * 2.0f;
	if (diameter > g_pathfindCellSize && diameter < g_pathfindDoubleCellSize) {
		diameter = 20.0f;
	}

	if ((object->bfmeTemplateView() == 0 ? object->bfmeTemplateView() :
		object->bfmeTemplateView()->getFinalOverride())->m_level > g_pathfindLevelLimit) {
		diameter = (object->bfmeTemplateView() == 0 ? object->bfmeTemplateView() :
		object->bfmeTemplateView()->getFinalOverride())->m_level;
	}

	radius = REAL_TO_INT_FLOOR( diameter / 10.0f + g_pathfindCellCenterBias );
	centerInCell = false;
	if (radius == 0) radius++;
	if (radius & 1) {
		centerInCell = true;
	}
	radius /= 2;
	if (radius > maxRadius) {
		radius = maxRadius;
		centerInCell = true;
	}
}

bool Pathfinder::Rva003DF250(Object *object, Coord3D *position)
{
    Int radius;
    Bool centered;
    getRadiusAndCenter(object, radius, centered);

    Coord3D local = *position;
    if (!centered) {
        local.x += *(const float *)0x01075344;
        local.y += *(const float *)0x01075344;
    }
    PathfindLayerEnum selectedLayer = s_terrain->getLayerForDestination(object, position);
    ICoord2D cellIndex;
    worldToCell(&local, &cellIndex);
    int cellX = cellIndex.x, cellY = cellIndex.y;
    adjustCoordToCell(cellX, cellY, centered, *position, selectedLayer);

    Int endDelta = radius;
    if (centered) endDelta++;
    ObjectID selfID = (ObjectID)object->m_id;
    for (int x = cellX - radius; x < cellX + endDelta; ++x) {
        for (int y = cellY - radius; y < cellY + endDelta; ++y) {
            if (x < m_extent.lo.x || x > m_extent.hi.x || y < m_extent.lo.y || y > m_extent.hi.y)
                return false;
            PathfindCell *cell = getCell(selectedLayer, x, y);
            if (!cell)
                return false;

            unsigned int flags = cell->m_packed;
            if ((flags & 7) == 5)
                return false;
            if ((cell->getGoalAircraftByte() & 1) && object->bfmeIsComputerControlled())
                return false;
            flags = cell->m_packed;
            unsigned int type = flags & 7;
            if (type == 4 || type == 5 || type == 6)
                return false;
            if (flags & 0x38) {
                PathfindCellInfo *info = cell->m_info;
                ObjectID relatedID = info ? info->m_posUnitID : INVALID_ID;
                if (relatedID != selfID && relatedID != 0) {
                    if (!object->isKindOf((KindOfType)0x7c))
                        return false;
                    Object *related = s_logic->findObjectByID(relatedID);
                    if (related && !related->isKindOf((KindOfType)8))
                        return false;
                }
                relatedID = info ? info->m_goalUnitID : INVALID_ID;
                if (relatedID != selfID && relatedID != 0) {
                    Object *related = s_logic->findObjectByID(relatedID);
                    if (related) {
                        if (related->isKindOf((KindOfType)0x6c)) {
                            if (!object->isKindOf((KindOfType)0x6c))
                                continue;
                        }
                        if (!related->isKindOf((KindOfType)8) || !object->isKindOf((KindOfType)0x7c)) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}
