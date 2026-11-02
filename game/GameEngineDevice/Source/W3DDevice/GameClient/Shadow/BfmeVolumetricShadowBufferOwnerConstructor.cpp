// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug
// stlport
//
// BfmeVolumetricShadowBufferOwner's constructor at retail 0x007C2F20 (662
// bytes, ret 8).
//
// IDENTITY.  The matched factory BfmeShadowBufferManager007C3260::createShadow
// (0x007C3260) calls this body through ILT 0x0003BD9F with the manager's list
// head and the shadow resource; the body installs vtable 0x01128738
// (??_7BfmeVolumetricShadowBufferOwner@@6B@, dir32_addresses.csv), whose
// destructor 0x007C1660 undoes exactly what is built here: the intrusive
// prev-link list, the resource reference and the 0x18-byte entry array with
// its three new[] blocks per mesh.  The base initialization is the same
// Rva007B12F0Base call (ILT 0x0000AF38) and 0x58..0x64 field defaults as the
// matched W3DVolumetricShadow constructor 0x007BA950.
//
// Unwind map (tools/eh_info.py): state 0 destroys the base through ILT
// 0x0003F562, state 1 the local mesh vector through ILT 0x00025C25.
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include "vector2.h"
#include "vector3.h"
#include <string.h>
#include <vector>

extern "C" const void *__identifier("??_7BfmeVolumetricShadowBufferOwner@@6B@")[];

class Object;

class MeshModelClass
{
public:
	virtual void Delete_This(void);
	int m_refCount;					// 0x04
	unsigned char m_unreconstructed_08[0x10];
	unsigned int m_flags;				// 0x18
	unsigned char m_unreconstructed_1c[8];
	int m_polygonCount;				// 0x24
	int m_vertexCount;				// 0x28

	void Release_Ref(void)
	{
		if (--m_refCount == 0)
			Delete_This();
	}
};

class MeshClass
{
public:
	virtual void v00(void);
	virtual void v04(void);
	virtual void v08(void);
	virtual void v0c(void);
	virtual void v10(void);
	virtual void v14(void);
	virtual const char *Get_Name(void) const;

	MeshModelClass *Get_Model(void);

	int m_refCount;					// 0x04
	unsigned char m_unreconstructed_08[0xc0];
	MeshModelClass *m_model;			// 0xc8
};

struct BfmeShadowBox
{
	Vector3 Center;
	Vector3 Extent;
};

#define BFME_SHADOW_SLOT(N) virtual void s##N(void);
class BfmeShadowResource
{
public:
	BFME_SHADOW_SLOT(00) BFME_SHADOW_SLOT(01) BFME_SHADOW_SLOT(02) BFME_SHADOW_SLOT(03)
	BFME_SHADOW_SLOT(04) BFME_SHADOW_SLOT(05) BFME_SHADOW_SLOT(06) BFME_SHADOW_SLOT(07)
	BFME_SHADOW_SLOT(08) BFME_SHADOW_SLOT(09) BFME_SHADOW_SLOT(10) BFME_SHADOW_SLOT(11)
	BFME_SHADOW_SLOT(12) BFME_SHADOW_SLOT(13) BFME_SHADOW_SLOT(14) BFME_SHADOW_SLOT(15)
	BFME_SHADOW_SLOT(16) BFME_SHADOW_SLOT(17) BFME_SHADOW_SLOT(18) BFME_SHADOW_SLOT(19)
	BFME_SHADOW_SLOT(20) BFME_SHADOW_SLOT(21) BFME_SHADOW_SLOT(22) BFME_SHADOW_SLOT(23)
	BFME_SHADOW_SLOT(24) BFME_SHADOW_SLOT(25) BFME_SHADOW_SLOT(26) BFME_SHADOW_SLOT(27)
	BFME_SHADOW_SLOT(28) BFME_SHADOW_SLOT(29) BFME_SHADOW_SLOT(30) BFME_SHADOW_SLOT(31)
	BFME_SHADOW_SLOT(32) BFME_SHADOW_SLOT(33) BFME_SHADOW_SLOT(34) BFME_SHADOW_SLOT(35)
	BFME_SHADOW_SLOT(36) BFME_SHADOW_SLOT(37) BFME_SHADOW_SLOT(38) BFME_SHADOW_SLOT(39)
	BFME_SHADOW_SLOT(40) BFME_SHADOW_SLOT(41) BFME_SHADOW_SLOT(42) BFME_SHADOW_SLOT(43)
	BFME_SHADOW_SLOT(44) BFME_SHADOW_SLOT(45) BFME_SHADOW_SLOT(46) BFME_SHADOW_SLOT(47)
	BFME_SHADOW_SLOT(48) BFME_SHADOW_SLOT(49) BFME_SHADOW_SLOT(50) BFME_SHADOW_SLOT(51)
	BFME_SHADOW_SLOT(52) BFME_SHADOW_SLOT(53) BFME_SHADOW_SLOT(54) BFME_SHADOW_SLOT(55)
	BFME_SHADOW_SLOT(56) BFME_SHADOW_SLOT(57) BFME_SHADOW_SLOT(58) BFME_SHADOW_SLOT(59)
	BFME_SHADOW_SLOT(60) BFME_SHADOW_SLOT(61) BFME_SHADOW_SLOT(62) BFME_SHADOW_SLOT(63)
	BFME_SHADOW_SLOT(64) BFME_SHADOW_SLOT(65) BFME_SHADOW_SLOT(66)
	virtual void Get_Obj_Space_Bounding_Box(BfmeShadowBox &box) const;	// +0x10c

	int m_refCount;					// 0x04
};
#undef BFME_SHADOW_SLOT

// The recursive mesh collector at retail 0x007C2E50 (ILT 0x0002A2F2).
class Rva007C2E50Node;
class Rva007C2E50Collector
{
public:
	void collect(_STL::vector<Object *> *out, Rva007C2E50Node *node);
};

class Rva007B12F0Base
{
public:
	Rva007B12F0Base();
	~Rva007B12F0Base();

	void *m_vtable;
	char m_padding[0x54];
};

struct BfmeShadowBufferEntry
{
	MeshClass *mesh;
	Vector3 *vertices;
	unsigned char *polygonFlags;
	Vector3 *polygonNormals;
	int count;
	bool isShadowMesh;
};

// The 0x58..0x64 defaults shared with W3DVolumetricShadow (0x007BA950).
class BfmeShadowVolumeBase : public Rva007B12F0Base
{
public:
	BfmeShadowVolumeBase()
	{
		m_field58 = 0;
		m_field5c = 0;
		m_field60 = 20.0f;
		m_field64 = 0;
	}

	int m_field58;
	int m_field5c;
	float m_field60;
	unsigned char m_field64;
};

class BfmeVolumetricShadowBufferOwner : public BfmeShadowVolumeBase
{
public:
	BfmeVolumetricShadowBufferOwner(
		BfmeVolumetricShadowBufferOwner **prevLink,
		BfmeShadowResource *resource);

private:
	BfmeVolumetricShadowBufferOwner **m_prevLink;	// 0x68
	BfmeVolumetricShadowBufferOwner *m_next;	// 0x6c
	unsigned int m_unreconstructed_070;
	BfmeShadowResource *m_resource;			// 0x74
	int m_entryCount;				// 0x78
	BfmeShadowBufferEntry *m_entries;		// 0x7c
	float m_radius;					// 0x80
	float m_height;					// 0x84
	float m_shadowLengthScale;			// 0x88
	float m_extraExtrusionPadding;			// 0x8c
};

BfmeVolumetricShadowBufferOwner::BfmeVolumetricShadowBufferOwner(
	BfmeVolumetricShadowBufferOwner **prevLink, BfmeShadowResource *resource)
{
	*(unsigned int *)this = (unsigned int)__identifier("??_7BfmeVolumetricShadowBufferOwner@@6B@");
	m_prevLink = prevLink;
	m_next = *prevLink;
	m_resource = resource;
	m_shadowLengthScale = 0.0f;
	m_extraExtrusionPadding = 0.0f;
	if (m_next != 0)
		m_next->m_prevLink = &m_next;
	*prevLink = this;
	++m_resource->m_refCount;

	_STL::vector<Object *> meshes;
	((Rva007C2E50Collector *)this)->collect(&meshes, (Rva007C2E50Node *)m_resource);

	for (unsigned int i = 0; i < meshes.size(); )
	{
		if (((MeshClass *)meshes[i])->m_model->m_flags & 0x1000)
		{
			++i;
		}
		else
		{
			meshes[i] = meshes.back();
			meshes.pop_back();
		}
	}

	m_entryCount = meshes.size();
	m_entries = new BfmeShadowBufferEntry[m_entryCount];

	for (int j = 0; j < m_entryCount; ++j)
	{
		m_entries[j].mesh = (MeshClass *)meshes[j];
		++m_entries[j].mesh->m_refCount;
		MeshModelClass *model = m_entries[j].mesh->Get_Model();
		m_entries[j].vertices = new Vector3[model->m_vertexCount];
		m_entries[j].polygonFlags = new unsigned char[model->m_polygonCount];
		m_entries[j].polygonNormals = new Vector3[model->m_polygonCount];
		m_entries[j].count = 0;
		m_entries[j].isShadowMesh = ((MeshClass *)meshes[j])->Get_Name()
			&& strstr(((MeshClass *)meshes[j])->Get_Name(), "SHADOW");
		model->Release_Ref();
	}

	BfmeShadowBox box;
	m_resource->Get_Obj_Space_Bounding_Box(box);
	Vector2 corner;
	corner.X = fabs(box.Center.X) + box.Extent.X;
	corner.Y = fabs(box.Center.Y) + box.Extent.Y;
	m_radius = corner.Length();
	m_height = box.Center.Z + box.Extent.Z + 20.0f;
}
