// ?next@FootprintIterator001A1460@@QAE_NPAUCoord2D@@@Z
// partial score=0.2756 date=2026-10-04
// cl: /DNDEBUG /MD /EHsc
// FootprintIterator001A1460 constructor, retail 0x001A1460 (1071 bytes).
//
// BFME moved the footprint walk of Zero Hour's TerrainLogic::flattenTerrain
// (GeneralsMD TerrainLogic.cpp) into a 0xB4-byte iterator object. The matched
// TerrainLogic::flattenTerrain (TerrainLogicFlattenTerrain.cpp) builds one on
// its object's GeometryInfo, orientation and position (ILT 0x00042CCB),
// then steps it with 0x001A12D0. The class keeps the caller's address-derived
// name.
//
// Read from the retail body: the geometry is copied (0x000FFD10); a single-box
// geometry (GeometryInfo 0x0087E8D0) gets Zero Hour's four rotated corners and
// their min/max, anything else the square around the bounding circle; each
// bound becomes a cell index with floor(v * 0.1f) (MAP_XY_FACTOR 10) rounded by
// fast_float2long_round, and the cursor starts one row before the first cell.

typedef float Real;
typedef int Int;
typedef bool Bool;

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
__forceinline long fast_float2long_round(float f)
{
	long i;

	__asm {
		fld [f]
		fistp [i]
	}

	return i;
}

extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" float __cdecl cosf(float);
extern "C" float __cdecl sinf(float);

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor(x)))

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &v) { x = v.x; y = v.y; z = v.z; }

	Real x, y, z;
};

struct ICoord2D
{
	Int x, y;
};

struct Coord2D
{
	Real x, y;
};

class Vector3
{
public:
	void Set(Real x, Real y, Real z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	Real X, Y, Z;
};

// BFME's 0x5C-byte GeometryInfo (GeometryInfoCopyConstructor.cpp); only the
// bounding-circle radius at +0x10 is read directly.
class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &that);				///< 0x000FFD10
	virtual ~GeometryInfo();								///< 0x000FFCA0

	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }

private:
	Bool m_isSmall;
	Int m_word08;
	Int m_word0c;
	Real m_boundingCircleRadius;						///< +0x10
	Real m_boundingSphereRadius;						///< +0x14
	unsigned char m_unmodelled18[0x44];
};

class BfmeThingTemplateShadowSelector
{
public:
	Bool usePluralShadowName() const;
};

extern Bool __cdecl Point_In_Triangle_2D(const Vector3 &, const Vector3 &,
	const Vector3 &, const Vector3 &, Int, Int, Bool &);
extern Real g_bfmeDirectionWeight1285;

// The single-box radii accessors (BfmeGeometryInfo_boxRadii.cpp), reached
// through the same view the matched bib-drawable and bridge callers use.
class BfmeGeometryInfo
{
public:
	Real boxMajorRadius() const;							///< 0x0087DC20
	Real boxMinorRadius() const;							///< 0x0087DC30
};

class FootprintIterator001A1460
{
public:
	FootprintIterator001A1460(const GeometryInfo &geom, Real angle, const Coord3D *pos);
	Bool next(Coord2D *out);

private:
	GeometryInfo m_geom;									///< +0x00
	Real m_angle;											///< +0x5C
	Coord3D m_pos;											///< +0x60
	ICoord2D m_iMin;										///< +0x6C
	ICoord2D m_iMax;										///< +0x74
	Vector3 m_topLeft;										///< +0x7C
	Vector3 m_topRight;										///< +0x88
	Vector3 m_bottomRight;									///< +0x94
	Vector3 m_bottomLeft;									///< +0xA0
	Int m_curX;												///< +0xAC
	Int m_curY;												///< +0xB0
};

// ??0FootprintIterator001A1460@@QAE@ABVGeometryInfo@@MPBUCoord3D@@@Z
FootprintIterator001A1460::FootprintIterator001A1460(const GeometryInfo &geom,
	Real angle, const Coord3D *pos)
	: m_geom(geom), m_angle(angle), m_pos(*pos)
{
	if (((const BfmeThingTemplateShadowSelector &)geom).usePluralShadowName())
	{
		const BfmeGeometryInfo &box = (const BfmeGeometryInfo &)geom;
		Real halfsizeX = box.boxMajorRadius();
		Real halfsizeY = box.boxMinorRadius();

		Real c = cosf(angle);
		Real s = sinf(angle);

		m_topLeft.Set(pos->x - halfsizeX*c - halfsizeY*s, pos->y + halfsizeY*c - halfsizeX*s, 0);
		m_topRight.Set(pos->x + halfsizeX*c - halfsizeY*s, pos->y + halfsizeY*c + halfsizeX*s, 0);
		m_bottomRight.Set(pos->x + halfsizeX*c + halfsizeY*s, pos->y - halfsizeY*c + halfsizeX*s, 0);
		m_bottomLeft.Set(pos->x - halfsizeX*c + halfsizeY*s, pos->y - halfsizeY*c - halfsizeX*s, 0);

		Real minX = m_topLeft.X;
		if (minX > m_topRight.X) minX = m_topRight.X;
		if (minX > m_bottomRight.X) minX = m_bottomRight.X;
		if (minX > m_bottomLeft.X) minX = m_bottomLeft.X;
		Real maxX = m_topLeft.X;
		if (maxX < m_topRight.X) maxX = m_topRight.X;
		if (maxX < m_bottomRight.X) maxX = m_bottomRight.X;
		if (maxX < m_bottomLeft.X) maxX = m_bottomLeft.X;

		Real minY = m_topLeft.Y;
		if (minY > m_topRight.Y) minY = m_topRight.Y;
		if (minY > m_bottomRight.Y) minY = m_bottomRight.Y;
		if (minY > m_bottomLeft.Y) minY = m_bottomLeft.Y;
		Real maxY = m_topLeft.Y;
		if (maxY < m_topRight.Y) maxY = m_topRight.Y;
		if (maxY < m_bottomRight.Y) maxY = m_bottomRight.Y;
		if (maxY < m_bottomLeft.Y) maxY = m_bottomLeft.Y;

		m_iMin.x = REAL_TO_INT_FLOOR(minX * 0.1f);
		m_iMin.y = REAL_TO_INT_FLOOR(minY * 0.1f);
		m_iMax.x = REAL_TO_INT_FLOOR(maxX * 0.1f);
		m_iMax.y = REAL_TO_INT_FLOOR(maxY * 0.1f);
	}
	else
	{
		Real radius = geom.getBoundingCircleRadius();
		m_iMin.x = REAL_TO_INT_FLOOR((pos->x - radius) * 0.1f);
		m_iMin.y = REAL_TO_INT_FLOOR((pos->y - radius) * 0.1f);
		m_iMax.x = REAL_TO_INT_FLOOR((pos->x + radius) * 0.1f);
		m_iMax.y = REAL_TO_INT_FLOOR((pos->y + radius) * 0.1f);
	}

	m_curX = m_iMin.x;
	m_curY = m_iMin.y - 1;
}

Bool FootprintIterator001A1460::next(Coord2D *out)
{
	Bool edge;
	Vector3 pt;
	for (;;)
	{
		if (++m_curY > m_iMax.y)
		{
			Int maxX = m_iMax.x;
			for (;;)
			{
				if (++m_curX > maxX)
					return false;

				m_curY = m_iMin.y;
				if (m_iMin.y <= m_iMax.y)
					break;
			}
		}

		pt.Z = 0.0f;
		pt.X = (Real)m_curX * g_bfmeDirectionWeight1285;
		pt.Y = (Real)m_curY * g_bfmeDirectionWeight1285;

		if (((BfmeThingTemplateShadowSelector &)m_geom).usePluralShadowName())
		{
			if (Point_In_Triangle_2D(m_topLeft, m_topRight, m_bottomLeft,
				pt, 0, 1, edge) ||
				Point_In_Triangle_2D(m_topRight, m_bottomRight, m_bottomLeft,
					pt, 0, 1, edge))
			{
				goto success;
			}
		}
		else
		{
			Real dx = pt.X - m_pos.x;
			Real dy = pt.Y - m_pos.y;
			Real radius = m_geom.getBoundingCircleRadius();
			if (dx * dx + dy * dy < radius * radius)
			{
				goto success;
			}
		}
	}

success:
	out->x = pt.X;
	out->y = pt.Y;
	return true;
}
