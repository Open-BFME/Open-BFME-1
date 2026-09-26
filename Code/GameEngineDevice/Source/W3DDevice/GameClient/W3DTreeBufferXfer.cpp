// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// W3DTreeBuffer::xfer, retail 0x007371D0: slot 3 of the vtable 0x01121608 the constructor installs.
// Zero Hour's tree loop at version 3, preceded by BFME's type table and extended by per-tree fields.

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

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

	AsciiString &operator=(const AsciiString &other) { set(other); return *this; }
	void set(const AsciiString &other);

	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

	Int compareNoCase(const AsciiString &other) const
	{
		Int lenOther = other.getLength();
		const char *pOther = other.str();
		Int lenThis = getLength();
		const char *pThis = str();
		Int shorter = lenThis < lenOther ? lenThis : lenOther;

		Int diff = _memicmp(pThis, pOther, shorter);
		if (diff != 0)
			return diff;

		return lenThis - lenOther;
	}

private:
	BfmeAsciiStringData *m_data;
};

struct Coord2D
{
	Real x, y;
};

struct Coord3D
{
	Real x, y, z;

	void set(Real ax, Real ay, Real az) { x = ax; y = ay; z = az; }
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
	virtual void slot18();
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

struct Rva00736B60Data;

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
	virtual const Rva00736B60Data *slot09() const;
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

// The 0xE8-byte tree record; its copy is the landed member-wise body at 0x00733B70.
struct Rva00733B70Record
{
	Vector3 location;
	Real scale;
	Matrix3D transform;
	Int treeType;
	unsigned char m_pad44[0x58 - 0x44];
	UnsignedInt drawableID;
	unsigned char m_pad5c[0x6c - 0x5c];
	Real m_angularVelocity;
	Real m_angularAcceleration;
	Coord3D m_toppleDirection;
	Int m_toppleState;
	Real m_angularAccumulation;
	unsigned char m_pad88[4];
	UnsignedInt m_options;
	Matrix3D m_mtx;
	UnsignedInt m_sinkFramesLeft;
	Bool m_flagC4;
	unsigned char m_padC5[0xe0 - 0xc5];
	Int m_fieldE0;
	Int m_fieldE4;

	Rva00733B70Record &copyFrom(const Rva00733B70Record &source);
};

struct Rva007371D0TreeType
{
	MeshClass *m_mesh;
	Vector3 m_offset;
	SphereClass m_bounds;
	const Rva00736B60Data *m_data;
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

// addTree's position, taken by value; the copy constructor makes retail build it in the argument slot.
struct Rva00736B60Coord
{
	Rva00736B60Coord(const Coord3D &c) : x(c.x), y(c.y), z(c.z) {}
	Rva00736B60Coord(const Rva00736B60Coord &other) : x(other.x), y(other.y), z(other.z) {}

	Real x, y, z;
};

class W3DTreeBuffer
{
public:
	void rva00736b60(UnsignedInt id, Rva00736B60Coord location, Real scale, const Matrix3D *transform,
		Real randomScaleAmount, const Rva00736B60Data *data, Int shadowKind, const AsciiString &textureName,
		const AsciiString &templateName);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad004[0x1b0 - 4];
	Rva00733B70Record m_trees[12000];
	Int m_numTrees;
	unsigned char m_pad2a7cb4[0x2a7cbc - 0x2a7cb4];
	Rva007371D0TreeType m_treeTypes[64];
	Int m_numTreeTypes;
	Vector3 m_cameraLookAtVector;
	unsigned char m_pad2a93cc[0x2a990d - 0x2a93cc];
	Bool m_useSmallBuffers;
};

// ?xfer@W3DTreeBuffer@@MAEXPAVXfer@@@Z
void W3DTreeBuffer::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	// version
	XferVersion version(1, 3);
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
				// Rebuild the type's draw data and mesh from the loaded names.
				const ThingTemplate *tmpl = TheThingFactory->findTemplate(m_treeTypes[i].m_templateName);
				if (tmpl) {
					const ModuleData *moduleData = tmpl->getModuleInfo2A0().getNthData(0);
					if (moduleData)
						m_treeTypes[i].m_data = moduleData->slot09();
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

	if (xfer->IsLoading())
		m_numTrees = 0;

	for (i = 0; i < numTrees; i++) {
		Rva00733B70Record tree;
		memset(&tree, 0, sizeof(tree));
		AsciiString modelName;
		AsciiString modelTexture;
		Int treeType = -2;
		if (xfer->IsStoring()) {
			tree.copyFrom(m_trees[i]);
			treeType = m_trees[i].treeType;
			if (treeType != -2) {
				modelName = m_treeTypes[treeType].m_modelName;
				modelTexture = m_treeTypes[treeType].m_nameC;
			}
		}
		xfer->xferAsciiString(&modelName);
		xfer->xferAsciiString(&modelTexture);
		if (xfer->IsLoading()) {
			Int j;
			for (j = 0; j < m_numTreeTypes; j++) {
				if (m_treeTypes[j].m_modelName.compareNoCase(modelName) == 0 &&
						m_treeTypes[j].m_nameC.compareNoCase(modelTexture) == 0) {
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

		// Topple parameters; saves before version 3 carry no separate topple matrix.
		xfer->xferReal(&tree.m_angularVelocity);
		xfer->xferReal(&tree.m_angularAcceleration);
		xfer->xferCoord3D(&tree.m_toppleDirection);
		xfer->xferUser("W3DToppleState", &tree.m_toppleState, sizeof(tree.m_toppleState));
		xfer->xferReal(&tree.m_angularAccumulation);
		xfer->xferUnsignedInt(&tree.m_options);
		if (version.m_currentVersion >= 3)
			BfmeParticleSystemXferMatrix(*xfer, &tree.m_mtx);
		else
			BfmeParticleSystemXferMatrix(*xfer, &tree.transform);
		xfer->xferUnsignedInt(&tree.m_sinkFramesLeft);
		xfer->xferBool(&tree.m_flagC4);
		xfer->xferInt(&tree.m_fieldE0);
		xfer->xferInt(&tree.m_fieldE4);

		Bool doShadow = false;
		AsciiString textureName;
		if (!xfer->IsLoading() && treeType >= 0 && treeType < m_numTreeTypes) {
			doShadow = m_treeTypes[treeType].m_doShadow;
			textureName = m_treeTypes[treeType].m_textureName;
		}
		xfer->xferBool(&doShadow);
		xfer->xferAsciiString(&textureName);
		bfmeHandOver_00001A50((BfmeSeedTarget *)xfer, &m_cameraLookAtVector);
		xfer->xferBool(&m_useSmallBuffers);

		if (xfer->IsLoading() && treeType >= 0 && treeType < m_numTreeTypes) {
			Coord3D pos;
			pos.set(tree.location.X, tree.location.Y, tree.location.Z);
			rva00736b60(tree.drawableID, pos, tree.scale, &tree.transform, 0, m_treeTypes[treeType].m_data,
				doShadow ? 1 : 0, textureName, m_treeTypes[treeType].m_templateName);
			if (m_numTrees) {
				Rva00733B70Record *curTree = &m_trees[m_numTrees - 1];
				curTree->m_angularAcceleration = tree.m_angularAcceleration;
				curTree->m_angularVelocity = tree.m_angularVelocity;
				curTree->m_toppleDirection = tree.m_toppleDirection;
				curTree->m_toppleState = tree.m_toppleState;
				curTree->m_options = tree.m_options;
				curTree->m_mtx = tree.m_mtx;
				curTree->m_sinkFramesLeft = tree.m_sinkFramesLeft;
				curTree->m_flagC4 = tree.m_flagC4;
				curTree->m_fieldE0 = tree.m_fieldE0;
				curTree->m_fieldE4 = tree.m_fieldE4;
			}
		}
	}
}
