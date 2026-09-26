// ?xfer@W3DShrubBuffer@@MAEXPAVXfer@@@Z
// partial score=0.99743 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Probe: 1557/1557 bytes, four differing load-order bytes.
// Retail loads treeType into EDI at 0x0072178E before this into EBX at 0x00721792.
// The append callee 0x00720D10 and the 0x0071CD80 record copy are already typed.

#include <string.h>

#include "vector3.h"
#include "matrix3d.h"
#include "sphere.h"

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *buf1, const void *buf2, unsigned int count);

#include "ascii_string.h"

template<> inline int StringBase<char>::getLength() const { return m_data ? m_data->length : 0; }
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

inline Int compareNamesNoCase(const AsciiString &self, const AsciiString &other)
{
 Int lenOther = other.getLength();
 const char *pOther = other.str();
 Int lenThis = self.getLength();
 const char *pThis = self.str();
 Int shorter = lenThis < lenOther ? lenThis : lenOther;
 Int diff = _memicmp(pThis,pOther,shorter);
 if (diff != 0) return diff;
 return lenThis-lenOther;
}

struct Coord2D
{
	Real x, y;
};

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}

	Real x, y, z;
};

struct Region2D
{
	Coord2D lo, hi;
};

struct XferVersion
{
	XferVersion(unsigned char version, unsigned char currentVersion) :
		m_version(version), m_currentVersion(currentVersion)
	{
	}

	unsigned char m_version;
	unsigned char m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool IsLoading() const;
	virtual Bool IsStoring() const;
	virtual Bool IsCRC() const;
	virtual Bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void xferRegion2D(Region2D *value);
	virtual void slot19();
	virtual void xferCoord2D(Coord2D *value);
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void xferCoord3D(Coord3D *value);
	virtual void slot25();
	virtual void xferAsciiString(AsciiString *value);
	virtual void xferReal(Real *value);
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
	virtual void xferUser(const char *typeName, void *data, Int dataSize);
};

// Landed cdecl helpers that transfer three floats, a drawable ID and a matrix.
class BfmeSeedTarget;
void bfmeHandOver_00001A50(BfmeSeedTarget *target, void *item);
void BfmeParticleSystemXferHandle(Xfer &xfer, void *value);
void BfmeParticleSystemXferMatrix(Xfer &xfer, void *value);

struct Rva00720D10Data;

class ModuleData
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	// Returns the tree type's draw data; the original name is unknown.
	virtual const Rva00720D10Data *slot09() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleInfo
{
public:
	const ModuleData *getNthData(Int i) const
	{
		if (i >= 0 && i < size())
			return m_info[i].second;
		return 0;
	}

private:
	struct Nugget
	{
		AsciiString first;
		AsciiString m_moduleTag;
		const ModuleData *second;
		Int interfaceMask;
		Bool copiedFromDefault;
		Bool inheritable;
		Bool overrideableByLikeKind;
	};

	UnsignedInt size(void) const { return m_infoEnd - m_info; }

	Nugget *m_info;
	Nugget *m_infoEnd;
};

class ThingTemplate
{
public:
	const ModuleInfo &getModuleInfo2A0(void) const { return m_moduleInfo2A0; }

private:
	unsigned char m_pad000[0x2a0];
	ModuleInfo m_moduleInfo2A0;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

class MeshClass;

class RenderObjClass
{
public:
	virtual void Delete_This(void);
	virtual void renderObjSlot04(void);
	virtual void renderObjSlot08(void);
	virtual Int Class_ID(void) const;
	virtual void renderObjSlot10(void);
	// Retail slot +0x14 returns the mesh view; its original name is unknown.
	virtual MeshClass *renderObjSlot14(void) const;

	void Release_Ref(void)
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

	Int m_refCount;
};

class MeshClass : public RenderObjClass
{
};

RenderObjClass *Create_Render_Obj(const char *name);

struct BfmeFormattedText
{
	void *text;
	Int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *result, Int tag, const char *format, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);
extern int g_rva005c5100ThrowInfo;

struct Rva00720D10Data
{
	unsigned char m_pad00[8];
	AsciiString m_modelName;
	AsciiString m_textureName;
};

// The 0xA4-byte shrub record; 0x0071CD80 is its matched copy constructor.
class Gen_0071CD80
{
public:
	Gen_0071CD80() {}
	Gen_0071CD80(const Gen_0071CD80 &other);
	void copyFrom(const Gen_0071CD80 &other) { this->Gen_0071CD80::Gen_0071CD80(other); }

	Vector3 location;
	Real scale;
	Matrix3D transform;
	Int treeType;
	unsigned char m_pad44[0x5c - 0x44];
	UnsignedInt drawableID;
	unsigned char m_pad60[0xa4 - 0x60];
};

struct Rva00721380ShrubType
{
	MeshClass *m_mesh;
	Vector3 m_offset;
	SphereClass m_bounds;
	const Rva00720D10Data *m_data;
	Coord2D m_coord24;
	Coord2D m_coord2C;
	Coord2D m_coord34;
	Coord2D m_coord3C;
	Bool m_doShadow;
	AsciiString m_textureName;
	AsciiString m_modelName;
	AsciiString m_nameC;
	AsciiString m_templateName;
	Int m_field58;
};

class W3DShrubBuffer
{
public:
	void rva00720D10(UnsignedInt id, Coord3D location, Real scale, const Matrix3D *transform, Real randomScaleAmount,
		const Rva00720D10Data *data, Int shadowKind, const AsciiString &textureName, const AsciiString &nameD);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad004[0xb8 - 4];
	short m_areaPartition[2500];
	Region2D m_bounds;
	unsigned char m_pad1450[0x1548 - 0x1450];
	Gen_0071CD80 m_trees[12000];
	Int m_numTrees;
	unsigned char m_pad1e1ccc[0x1e1cd4 - 0x1e1ccc];
	Rva00721380ShrubType m_treeTypes[64];
	Int m_numTreeTypes;
	Vector3 m_cameraLookAtVector;
};

// ?xfer@W3DShrubBuffer@@MAEXPAVXfer@@@Z
void W3DShrubBuffer::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	if (xfer->IsCRC())
		return;

	// version
	XferVersion version(1, 2);
	xfer->xferVersion(&version);

	Int i;
	Int numTrees = m_numTrees;
	xfer->xferInt(&numTrees);

	if (version.m_currentVersion >= 2) {
		xfer->xferInt(&m_numTreeTypes);
		for (i = 0; i < m_numTreeTypes; i++) {
			bfmeHandOver_00001A50((BfmeSeedTarget *)xfer, &m_treeTypes[i].m_offset);
			bfmeHandOver_00001A50((BfmeSeedTarget *)xfer, &m_treeTypes[i].m_bounds.Center);
			xfer->xferReal(&m_treeTypes[i].m_bounds.Radius);
			xfer->xferCoord2D(&m_treeTypes[i].m_coord24);
			xfer->xferCoord2D(&m_treeTypes[i].m_coord2C);
			xfer->xferCoord2D(&m_treeTypes[i].m_coord34);
			xfer->xferCoord2D(&m_treeTypes[i].m_coord3C);
			xfer->xferBool(&m_treeTypes[i].m_doShadow);
			xfer->xferAsciiString(&m_treeTypes[i].m_textureName);
			xfer->xferAsciiString(&m_treeTypes[i].m_modelName);
			xfer->xferAsciiString(&m_treeTypes[i].m_nameC);
			xfer->xferInt(&m_treeTypes[i].m_field58);
			xfer->xferAsciiString(&m_treeTypes[i].m_templateName);
			if (xfer->IsLoading()) {
				// Rebuild the type's draw data and mesh from the loaded names; a type without data is corrupt.
				m_treeTypes[i].m_data = 0;
				const ThingTemplate *tmpl = TheThingFactory->findTemplate(m_treeTypes[i].m_templateName);
				if (tmpl) {
					const ModuleData *moduleData = tmpl->getModuleInfo2A0().getNthData(0);
					if (moduleData)
						m_treeTypes[i].m_data = moduleData->slot09();
				}
				if (!m_treeTypes[i].m_data) {
					BfmeFormattedText error;
					bfmeFormatText(&error, 4, 0);
					_CxxThrowException(&error, &g_rva005c5100ThrowInfo);
				}
				if (m_treeTypes[i].m_mesh) {
					m_treeTypes[i].m_mesh->Release_Ref();
					m_treeTypes[i].m_mesh = 0;
				}
				RenderObjClass *robj = Create_Render_Obj(m_treeTypes[i].m_modelName.str());
				if (robj) {
					if (robj->Class_ID() == 0)
						m_treeTypes[i].m_mesh = robj->renderObjSlot14();
					else
						robj->Release_Ref();
				}
			}
		}
	}

	if (xfer->IsLoading()) {
		m_numTrees = 0;
		for (i = 0; i < 2500; i++)
			m_areaPartition[i] = -1;
	}

	for (i = 0; i < numTrees; i++) {
		Gen_0071CD80 tree;
		memset(&tree, 0, sizeof(tree));
		AsciiString modelName;
		AsciiString modelTexture;
		Int treeType = -2;
		if (xfer->IsStoring()) {
			tree.copyFrom(m_trees[i]);
			treeType = m_trees[i].treeType;
			if (treeType != -2) {
				modelName = m_treeTypes[treeType].m_data->m_modelName;
				modelTexture = m_treeTypes[treeType].m_data->m_textureName;
			}
		}
		xfer->xferAsciiString(&modelName);
		xfer->xferAsciiString(&modelTexture);
		if (xfer->IsLoading()) {
			Int j;
			for (j = 0; j < m_numTreeTypes; j++) {
				if (compareNamesNoCase(m_treeTypes[j].m_data->m_modelName,modelName) == 0 &&
						compareNamesNoCase(m_treeTypes[j].m_data->m_textureName,modelTexture) == 0) {
					treeType = j;
					break;
				}
			}
		}

		xfer->xferReal(&tree.location.X);
		xfer->xferReal(&tree.location.Y);
		xfer->xferReal(&tree.location.Z);
		xfer->xferReal(&tree.scale);
		BfmeParticleSystemXferMatrix(*xfer, &tree.transform);
		BfmeParticleSystemXferHandle(*xfer, &tree.drawableID);

		Bool doShadow = false;
		AsciiString textureName;
		if (!xfer->IsLoading() && treeType >= 0 && treeType < m_numTreeTypes) {
			doShadow = m_treeTypes[treeType].m_doShadow;
			textureName = m_treeTypes[treeType].m_textureName;
		}
		xfer->xferBool(&doShadow);
		xfer->xferAsciiString(&textureName);
		bfmeHandOver_00001A50((BfmeSeedTarget *)xfer, &m_cameraLookAtVector);
		xfer->xferRegion2D(&m_bounds);

		if (xfer->IsLoading() && treeType >= 0 && treeType < m_numTreeTypes) {
			Coord3D pos;
			pos.x = tree.location.X;
			pos.y = tree.location.Y;
			pos.z = tree.location.Z;
			rva00720D10(tree.drawableID, pos, tree.scale, &tree.transform, 0, m_treeTypes[treeType].m_data,
				doShadow ? 1 : 0, textureName, "");
		}
	}
}
