// ?addFactionBib@W3DTerrainVisual@@UAEXPAVObject@@_NM@Z
// partial score=0.48 date=2026-09-16
// Scratch reconstruction for retail 0x00732130..0x007323CF (672 bytes).
// The retail owner is W3DTerrainVisual::addFactionBib, vtable slot 23.
// BFME's Object and GeometryInfo layouts differ from the old ZH headers, so
// those two views are local; the coordinate and matrix types are native.
//
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "Common/GameType.h"
#include "matrix3d.h"

class Xfer;

// Native STL vector storage is three pointers on this target.  The element
// types are owned by GeometryInfo's other translation unit; this view keeps
// their ABI-sized members without forcing a second STLport include here.
struct BfmeVector
{
	void *begin;
	void *end;
	void *capacity;
};

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);
};

// BFME GeometryInfo is 0x5C bytes: the two native STL vectors begin at
// +0x2C and +0x38, followed by cached extent words through +0x58.
class GeometryInfo : public Snapshot
{
public:
	GeometryInfo(const GeometryInfo &other);
	virtual ~GeometryInfo();

private:
	Bool m_isSmall;
	int m_scalar08;
	int m_scalar0c;
	int m_scalar10;
	int m_scalar14;
	int m_scalar18;
	int m_scalar1c;
	int m_scalar20;
	int m_scalar24;
	int m_scalar28;
	BfmeVector m_shapes;
	BfmeVector m_records;
	int m_cached44;
	int m_cached48;
	int m_cached4c;
	int m_cached50;
	int m_cached54;
	int m_cached58;
};

// BFME's accessors are on this overlay, not on the old ZH GeometryInfo.
class BfmeGeometryInfo
{
public:
	Real boxMajorRadius() const;
	Real boxMinorRadius() const;
};

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

class ThingTemplate : public Overridable
{
public:
	Real getFactoryExitWidth() const
	{
		return *(const Real *)((const unsigned char *)this + 0x3B4);
	}

	Real getFactoryExtraBibWidth() const
	{
		return *(const Real *)((const unsigned char *)this + 0x3B8);
	}
};

class Object
{
public:
	const Matrix3D *getTransformMatrix() const
	{
		return &m_transform;
	}

	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = (const ThingTemplate *)
				thingTemplate->m_nextOverride->getFinalOverride();
		return thingTemplate;
	}

	ObjectID getID() const
	{
		return m_id;
	}

	const GeometryInfo &getGeometryInfo() const
	{
		return m_geometryInfo;
	}

private:
	void *m_vtable;
	ThingTemplate *m_template;
	Matrix3D m_transform;
	unsigned char m_unmodelled38[0x3C];
	ObjectID m_id;
	unsigned char m_unmodelled78[0x34];
	GeometryInfo m_geometryInfo;
};

class Rva006C8D40
{
public:
	// The retail tail thunk forwards these three arguments unchanged.
	void invoke(Vector3 *corners, ObjectID id, Bool highlight);
};

class W3DTerrainVisualSnapshot
{
public:
	virtual void crc();
	virtual void xfer();
};

class W3DTerrainVisualSubsystem
{
public:
	virtual void init();
	virtual void reset();
};

class W3DTerrainVisualBase : public W3DTerrainVisualSnapshot,
	public W3DTerrainVisualSubsystem
{
private:
	char m_baseFields[8];
};

class W3DTerrainVisual : public W3DTerrainVisualBase
{
public:
	virtual void addFactionBib(Object *factionBuilding, Bool highlight,
		Real extra);

private:
	Rva006C8D40 *m_terrainRenderObject;
	void *m_waterRenderObject;
	void *m_logicHeightMap;
	Bool m_isWaterGridRenderingEnabled;
};

// ?addFactionBib@W3DTerrainVisual@@UAEXPAVObject@@_NM@Z
void W3DTerrainVisual::addFactionBib(Object *factionBuilding,
	Bool highlight, Real extra)
{
	if (m_logicHeightMap)
	{
		const Matrix3D *mtx = factionBuilding->getTransformMatrix();
		Vector3 corners[4];
		Coord3D pos;
		pos.set(0, 0, 0);
		Real exitWidth = factionBuilding->getTemplate()->getFactoryExitWidth();
		Real extraWidth = factionBuilding->getTemplate()->getFactoryExtraBibWidth() + extra;
		const GeometryInfo info = factionBuilding->getGeometryInfo();
		const BfmeGeometryInfo &bfmeInfo = (const BfmeGeometryInfo &)info;
		Real sizeX = bfmeInfo.boxMajorRadius();
		Real sizeY = bfmeInfo.boxMinorRadius();

		corners[0].Set(pos.x, pos.y, pos.z);
		corners[0].X -= sizeX + extraWidth;
		corners[0].Y -= sizeY + extraWidth;
		corners[1].Set(pos.x, pos.y, pos.z);
		corners[1].X += sizeX + exitWidth + extraWidth;
		corners[1].Y -= sizeY + extraWidth;
		corners[2].Set(pos.x, pos.y, pos.z);
		corners[2].X += sizeX + exitWidth + extraWidth;
		corners[2].Y += sizeY + extraWidth;
		corners[3].Set(pos.x, pos.y, pos.z);
		corners[3].X -= sizeX + extraWidth;
		corners[3].Y += sizeY + extraWidth;

		mtx->Transform_Vector(*mtx, corners[0], &corners[0]);
		mtx->Transform_Vector(*mtx, corners[1], &corners[1]);
		mtx->Transform_Vector(*mtx, corners[2], &corners[2]);
		mtx->Transform_Vector(*mtx, corners[3], &corners[3]);
		m_terrainRenderObject->invoke(corners, factionBuilding->getID(), highlight);
	}
}
