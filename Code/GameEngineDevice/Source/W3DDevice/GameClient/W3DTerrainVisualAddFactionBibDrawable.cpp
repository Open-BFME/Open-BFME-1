// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// BFME's addFactionBibDrawable uses the four-corner path from the Zero Hour
// twin, but its Drawable/ThingTemplate/GeometryInfo layouts are different.
// Keep those layout witnesses local to this body.

typedef bool Bool;
typedef float Real;
enum DrawableID { DRAWABLE_ID_ZERO = 0 };

extern void j_000309f4(void);
#include "vector3.h"
#include "vector4.h"

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void set(Real nx, Real ny, Real nz)
	{
		x = nx;
		y = ny;
		z = nz;
	}
};

class Matrix3D
{
public:
	Vector4 Row[3];

	Vector4 &operator[](int row)
	{
		return Row[row];
	}

	const Vector4 &operator[](int row) const
	{
		return Row[row];
	}

	static __forceinline void Transform_Vector(const Matrix3D &matrix,
		const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		Vector3 *v;

		if (out == &in) {
			tmp = in;
			v = &tmp;
		} else {
			v = (Vector3 *)&in;
		}

		out->X = (matrix[0][0] * v->X + matrix[0][1] * v->Y +
			matrix[0][2] * v->Z + matrix[0][3]);
		out->Y = (matrix[1][0] * v->X + matrix[1][1] * v->Y +
			matrix[1][2] * v->Z + matrix[1][3]);
		out->Z = (matrix[2][1] * v->Y + matrix[2][0] * v->X +
			matrix[2][2] * v->Z + matrix[2][3]);
	}
};

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &other);
	// ??1Rva000FFCA0@@QAE@XZ
	~GeometryInfo()
	{
		typedef void (__fastcall *DestroyCall)(GeometryInfo *);
		((DestroyCall)j_000309f4)(this);
	}

private:
	void *m_vtable;
	unsigned char m_unmodelled[0x58];
};

class BfmeGeometryInfo
{
public:
	Real boxMajorRadius() const;
	Real boxMinorRadius() const;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
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

	const GeometryInfo &getTemplateGeometryInfo() const
	{
		return *(const GeometryInfo *)((const unsigned char *)this + 0x60);
	}
};

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
	DrawableID getID() const;

	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = (const ThingTemplate *)
				thingTemplate->m_nextOverride->getFinalOverride();
		return thingTemplate;
	}

private:
	void *m_vtable;
	ThingTemplate *m_template;
};

class W3DTerrainVisualBase
{
public:
	virtual void baseAnchor() {}

private:
	unsigned char m_base[0x0C];
};

class W3DTerrainVisual : public W3DTerrainVisualBase
{
public:
	// BFME layout witness: m_logicHeightMap +0x18, render object +0x10.
	virtual void addFactionBibDrawable(Drawable *factionBuilding, Bool highlight, Real extra);

private:
	void *m_terrainRenderObject;
	void *m_waterRenderObject;
	void *m_logicHeightMap;
	Bool m_isWaterGridRenderingEnabled;
};

extern void j_00029fa0(void);

// ?invoke@Rva006C8D50@@QAEXXZ
struct Rva006C8D50Call
{
	void invoke(Vector3 *, DrawableID, Bool);
};

typedef void (Rva006C8D50Call::*AddTerrainBibDrawableCall)(
	Vector3 *, DrawableID, Bool);

// ?addFactionBibDrawable@W3DTerrainVisual@@UAEXPAVDrawable@@_NM@Z
void W3DTerrainVisual::addFactionBibDrawable(Drawable *factionBuilding,
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
		const GeometryInfo info = factionBuilding->getTemplate()->getTemplateGeometryInfo();
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
		Vector3 &corner0 = corners[0];
		Vector3 &corner1 = corners[1];
		Vector3 &corner2 = corners[2];
		Vector3 &corner3 = corners[3];
		mtx->Transform_Vector(*mtx, corner0, &corner0);
		mtx->Transform_Vector(*mtx, corner1, &corner1);
		mtx->Transform_Vector(*mtx, corner2, &corner2);
		mtx->Transform_Vector(*mtx, corner3, &corner3);
		union
		{
			void (*asFunction)(void);
			AddTerrainBibDrawableCall asMember;
		} addBib;
		addBib.asFunction = j_00029fa0;
		(reinterpret_cast<Rva006C8D50Call *>(m_terrainRenderObject)->*
			addBib.asMember)(corners, factionBuilding->getID(), highlight);
	}
}
