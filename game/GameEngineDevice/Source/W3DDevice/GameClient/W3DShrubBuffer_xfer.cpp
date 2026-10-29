// ?xfer00721380@W3DShrubBuffer@@MAEXPAVXfer@@@Z
// stlport
// cl: /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WW3D2 /Igame /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/shims/sweep /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#define __PLACEMENT_VEC_NEW_INLINE
#include <string.h>

#include "vector3.h"
#include "matrix3d.h"
#include "sphere.h"

#include "basetype.h"
extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *buf1, const void *buf2, unsigned int count);

#include "ascii_string.h"


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

#include "GameEngine/Source/Common/System/xfer.h"
struct Rva00721380Version : Xfer::Version
{
 Rva00721380Version(unsigned char v, unsigned char c)
 {
  data[0] = v;
  data[1] = c;
 }
};

// Cdecl helpers transfer three floats, a drawable ID and a matrix.
class BfmeSeedTarget;
void bfmeHandOver_00001A50(BfmeSeedTarget *target, void *item);
class MidVirtualSlot90Receiver;
void Rva0010C3E0(MidVirtualSlot90Receiver *, void *);
void BfmeParticleSystemXferMatrix(Xfer &xfer, void *value);

struct Rva00720D10Data;

#define ASCIISTRING_H
#include "GameEngine/Include/Common/Module.h"

// Retail dispatch at +0x24 differs from native ModuleData (+0x18).
// This address-derived view describes only that independently decoded vtable ABI.
class Rva00721380ModuleDataView
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Rva00721380ModuleInfoView
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

class ThingTemplate;
inline const Rva00721380ModuleInfoView &rva00721380Modules(const ThingTemplate *value)
{
 return *reinterpret_cast<const Rva00721380ModuleInfoView *>(reinterpret_cast<const unsigned char *>(value) + 0x2a0);
}

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class ThingFactory;
extern ThingFactory *TheThingFactory;
#define TheThingFactory ((BfmeThingFactory *)TheThingFactory)

#include "rendobj.h"

RenderObjClass *Create_Render_Obj(const char *name);

struct BfmeFormattedText
{
	char *text;
	Int tag;
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};

struct Rva00720D10Data
{
	unsigned char m_pad00[8];
	AsciiString m_modelName;
	AsciiString m_textureName;
};

// Shrub record copied by the existing address-derived constructor.
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
	RenderObjClass *m_mesh;
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

// Retail copies three floats into the outgoing argument and saves its address.
// The view retains that copy lifetime without a coordinate destructor.
struct Rva00721380CoordView
{
 Rva00721380CoordView() {}
 Rva00721380CoordView(const Rva00721380CoordView &other) : x(other.x), y(other.y), z(other.z) {}
 Real x, y, z;
};

class W3DShrubBuffer
{
public:
	void rva00720D10(UnsignedInt id, Coord3D location, Real scale, const Matrix3D *transform, Real randomScaleAmount,
		const Rva00720D10Data *data, Int shadowKind, const AsciiString &textureName, const AsciiString &nameD);

protected:
	virtual void xfer00721380(Xfer *xfer);

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

// ------------------------------------------------------------------------------------------------
/** Xfer
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer00721380@W3DShrubBuffer@@MAEXPAVXfer@@@Z
void W3DShrubBuffer::xfer00721380(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	if (xfer->IsCRC())
		return;

	// version
	Rva00721380Version version(1,2);
	*xfer == version;

	Int i;
	Int numTrees = m_numTrees;
	xfer->xferInt(&numTrees);

	if (version.data[1] >= 2) {
		xfer->xferInt(&m_numTreeTypes);
		for (i = 0; i < m_numTreeTypes; i++) {
			bfmeHandOver_00001A50((BfmeSeedTarget *)xfer, &m_treeTypes[i].m_offset);
			bfmeHandOver_00001A50((BfmeSeedTarget *)xfer, &m_treeTypes[i].m_bounds.Center);
			xfer->xferReal(&m_treeTypes[i].m_bounds.Radius);
			*xfer == m_treeTypes[i].m_coord24;
			*xfer == m_treeTypes[i].m_coord2C;
			*xfer == m_treeTypes[i].m_coord34;
			*xfer == m_treeTypes[i].m_coord3C;
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
					const ModuleData *moduleData = rva00721380Modules(tmpl).getNthData(0);
					if (moduleData)
						m_treeTypes[i].m_data = reinterpret_cast<const Rva00721380ModuleDataView *>(moduleData)->slot09();
				}
				if (!m_treeTypes[i].m_data) {
					throw XferException(4, 0);
				}
				if (m_treeTypes[i].m_mesh) {
					m_treeTypes[i].m_mesh->Release_Ref();
					m_treeTypes[i].m_mesh = 0;
				}
				RenderObjClass *robj = Create_Render_Obj(m_treeTypes[i].m_modelName.str());
				if (robj) {
					if (robj->Class_ID() == 0)
						m_treeTypes[i].m_mesh = reinterpret_cast<RenderObjClass *>(robj->_bfme_ro_v3());
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

	// Save trees. [8/11/2003]
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
		xfer->xferReal(&tree.scale);	///< Scale at location.
		BfmeParticleSystemXferMatrix(*xfer, &tree.transform);
		Rva0010C3E0(reinterpret_cast<MidVirtualSlot90Receiver *>(xfer), &tree.drawableID);	///< Drawable this tree corresponds to.

		Bool doShadow = false;
		AsciiString textureName;
		if (!xfer->IsLoading() && treeType >= 0 && treeType < m_numTreeTypes) {
			doShadow = m_treeTypes[treeType].m_doShadow;
			textureName = m_treeTypes[treeType].m_textureName;
		}
		xfer->xferBool(&doShadow);
		xfer->xferAsciiString(&textureName);
		bfmeHandOver_00001A50((BfmeSeedTarget *)xfer, &m_cameraLookAtVector);
		*xfer == m_bounds;

		if (xfer->IsLoading() && treeType >= 0 && treeType < m_numTreeTypes) {
			Coord3D pos;
			pos.x = tree.location.X;
			pos.y = tree.location.Y;
			pos.z = tree.location.Z;
			typedef void (W3DShrubBuffer::*AppendView)(UnsignedInt, Rva00721380CoordView, Real, const Matrix3D *, Real, const Rva00720D10Data *, Int, const AsciiString &, const AsciiString &);
			AppendView append = reinterpret_cast<AppendView>(&W3DShrubBuffer::rva00720D10);
			(this->*append)(tree.drawableID, reinterpret_cast<const Rva00721380CoordView &>(pos), tree.scale, &tree.transform, 0, m_treeTypes[treeType].m_data,
				doShadow ? 1 : 0, textureName, "");
		}
	}
}  // end xfer
