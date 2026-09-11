// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// BFME's unitMoved body uses the 50 by 50 tree partition and the older
// +0x1548 tree-record table.  The mirror is local because the witnessed BFME
// offsets differ from the Zero Hour W3DTreeBuffer declaration.

#include "Lib/BaseType.h"
#include "Common/GameType.h"

extern "C" __declspec(dllimport) double BfmeFloorER(double);
extern "C" __declspec(dllimport) double bfmeMathVE(double);

#undef REAL_TO_INT_FLOOR
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)BfmeFloorER((double)(x))) )
#undef REAL_TO_INT_CEIL
#define REAL_TO_INT_CEIL(x) (fast_float2long_round((Real)bfmeMathVE((double)(x))) )

class GlobalData
{
};

extern GlobalData *TheWritableGlobalData;

#define BFME_WRITABLE_GLOBAL_DATA (*(GlobalData **)0x012ED5C8)

enum KindOfType
{
	KINDOF_IMMOBILE = 2
};

struct Rva00721B20Coord3D
{
	Real x;
	Real y;
	Real z;

	void set(Real newX, Real newY, Real newZ)
	{
		x = newX;
		y = newY;
		z = newZ;
	}

	void sub(const Rva00721B20Coord3D *other)
	{
		x -= other->x;
		y -= other->y;
		z -= other->z;
	}

	Real lengthSqr(void) const
	{
		return x*x + y*y + z*z;
	}
};

class Thing
{
private:
	char m_pad00[0x38];

public:
	Bool isKindOf(KindOfType kind) const;
	const Coord3D *getUnitDirectionVector2D(void) const;
};

class Rva00721B20GeometryInfo
{
public:
	Real getMajorRadius(void) const
	{
		return *(volatile const Real *)((const char *)this + 0x10);
	}
};

class Object : public Thing
{
public:
	Rva00721B20Coord3D m_position;

	const Rva00721B20GeometryInfo &getGeometryInfo(void) const
	{
		return *(const Rva00721B20GeometryInfo *)((const char *)this + 0xac);
	}

	ObjectID getID(void) const
	{
		return *(const ObjectID *)((const char *)this + 0x74);
	}
};

struct Rva00721B20TreeData
{
	char m_pad00[0x10];
	UnsignedInt m_framesToMoveOutward;
};

struct Rva00721B20TreeType
{
	Rva00721B20TreeData *m_data;
	char m_pad04[0x58];
};

struct Rva00721B20Tree
{
	char m_pad00[0x1548];
	Rva00721B20Coord3D m_location;
	char m_pad0c[0x34];
	Int m_treeType;
	char m_pad44[0x18];
	DrawableID m_drawableID;
	Real m_pushAside;
	Real m_pushAsideDelta;
	Real m_pushAsideSin;
	Real m_pushAsideCos;
	ObjectID m_pushAsideSource;
	UnsignedInt m_lastFrameUpdated;
	Int m_nextInPartition;
	char m_pad7c[0x28];
};

class W3DTreeBuffer
{
public:
	void pushAsideTree(DrawableID id, const Coord3D *pusherPos,
		const Coord3D *pusherDirection, ObjectID pusherID);
};

class Rva00721B20W3DTreeBuffer
{
public:
	void unitMoved(Object *unit);

	private:
	char m_pad00[0xb8];
	Short m_areaPartition[50 * 50];
	Region2D m_bounds;
	char m_pad1450[0x1e0878];
	Int m_numTrees;
	UnsignedByte m_anythingChanged;
	UnsignedByte m_anyPushChanged;
	UnsignedByte m_updateAllKeys;
	char m_pad1e1ccf[0x25];
	Rva00721B20TreeType m_treeTypes[64];
};

// ?unitMoved@W3DTreeBuffer@@QAEXPAVObject@@@Z
void Rva00721B20W3DTreeBuffer::unitMoved(Object *unit)
{
	GlobalData *global = BFME_WRITABLE_GLOBAL_DATA;
	if (*(const unsigned char *)((const char *)global + 0x18) == 0 ||
		*(const unsigned char *)((const char *)global + 0x19) == 0)
		return;

	if (unit->isKindOf(KINDOF_IMMOBILE))
		return;

	Real radius = unit->getGeometryInfo().getMajorRadius();
	Real posX = unit->m_position.x;
	radius += *(const Real *)0x0109C34C;
	Real posY = unit->m_position.y;
	Real posZ = unit->m_position.z;
	Rva00721B20Coord3D pos;
	pos.x = posX;
	pos.y = posY;
	pos.z = posZ;
	Real x = pos.x-radius;
	Real y = pos.y-radius;
	if (x<m_bounds.lo.x) x = m_bounds.lo.x;
	if (y<m_bounds.lo.y) y = m_bounds.lo.y;
	if (x>m_bounds.hi.x) x = m_bounds.hi.x;
	if (y>m_bounds.hi.y) y = m_bounds.hi.y;
	Real xRatio = x/(m_bounds.hi.x-m_bounds.lo.x);
	Int xIndex = REAL_TO_INT_FLOOR ( xRatio * *(const Real *)0x0109C348 );
	Real yRatio = y/(m_bounds.hi.y-m_bounds.lo.y);
	Int yIndex = REAL_TO_INT_FLOOR ( yRatio * *(const Real *)0x0109C348 );

	x = pos.x+radius;
	y = pos.y+radius;
	if (x<m_bounds.lo.x) x = m_bounds.lo.x;
	if (y<m_bounds.lo.y) y = m_bounds.lo.y;
	if (x>m_bounds.hi.x) x = m_bounds.hi.x;
	if (y>m_bounds.hi.y) y = m_bounds.hi.y;
	Real xMaxRatio = x/(m_bounds.hi.x-m_bounds.lo.x);
	Int xMax = REAL_TO_INT_CEIL ( xMaxRatio * *(const Real *)0x0109C348 );
	Real yMaxRatio = y/(m_bounds.hi.y-m_bounds.lo.y);
	Int yMax = REAL_TO_INT_CEIL ( yMaxRatio * *(const Real *)0x0109C348 );

	Int i, j;
	for (i=xIndex; i<xMax; i++) {
		for (j=yIndex; j<yMax; j++) {
			Int treeNdx = m_areaPartition[i + 50*j];
			while (treeNdx != -1) {
				if (treeNdx<0 || treeNdx>=m_numTrees)
					break;
				Rva00721B20Tree *tree =
					(Rva00721B20Tree *)(treeNdx * 0xa4 + (char *)this);
				if (tree->m_treeType < 0) {
					treeNdx = tree->m_nextInPartition;
					continue;
				}
					Rva00721B20Coord3D delta;
					delta.set(tree->m_location.x, tree->m_location.y, tree->m_location.z);
					delta.sub(&pos);
					if (radius*radius>delta.lengthSqr()) {
						Rva00721B20TreeData *data =
							m_treeTypes[tree->m_treeType].m_data;
						if (data != 0 && data->m_framesToMoveOutward > 0) {
							((W3DTreeBuffer *)this)->pushAsideTree(tree->m_drawableID,
								(const Coord3D *)&pos, unit->getUnitDirectionVector2D(), unit->getID());
						}
					}
				treeNdx = ((Rva00721B20Tree *)(treeNdx * 0xa4 + (char *)this))->m_nextInPartition;
			}
		}
	}
}
