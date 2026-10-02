// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// WaterRenderObjClass::generateVertexBuffer, retail 0x0079EAB0, 797 bytes.
// Donor: EA Generals Zero Hour W3DWater.cpp generateVertexBuffer (GPLv3), the
// class's Zero Hour home; the body shape (pool/usage/fvf defaults, the
// doStatic override, the conditional create, the deferred fill and the
// x/z grid loop) is the twin's.
//
// Identity is proved by the matched retail caller
// WaterRenderObjReAcquireResources.cpp (retail 0x007A0500), which calls this
// body by name as generateVertexBuffer(PATCH_SIZE, PATCH_SIZE,
// SEA_PATCH_VERTEX_SIZE, true) and
// generateVertexBuffer(m_gridCellsX+1, m_gridCellsY+1, MATER_MESH_VERTEX_SIZE,
// false): four stack arguments (ret 0x10), the bool last, and the 0x18 the
// static path locks -- exactly the mangled
// ?generateVertexBuffer@WaterRenderObjClass@@IAEJHHH_N@Z, which the Zero Hour
// header declares inside the class body (a base virtual override; MSVC
// mangling does not encode virtualness).
//
// BFME differences from the twin, each witnessed by the retail bytes:
//  - the buffer is created through a GLOBAL device at 0x01340534 rather than
//    the m_pDev member, and its CreateVertexBuffer takes SIX arguments (the
//    twin's five plus a trailing null);
//  - the witnessed usage immediates are 0x208 (dynamic) and 8 (static), not
//    the twin's D3DUSAGE_WRITEONLY combinations; the pool immediates are
//    D3DPOOL_DEFAULT and D3DPOOL_MANAGED as in the twin;
//  - the vertex buffer pointer is at this+0x124, the write offset at this+0x12c
//    and the vertex count at this+0x13c, so the layout view below stands in
//    for the twin's class members (the twin's layout is not BFME's);
//  - retail holds the row's z coordinate and its scaled copy in two x87
//    registers across the inner loop; spelling the scale as the literal below
//    is what makes MSVC 7.1 hoist it that way (see the constant's comment).

#define Matrix4x4 Matrix4
#include "dx8wrapper.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

/// The retail scale both texture coordinates are multiplied by.  Retail reads
/// the float ?g_bfmeK1266A@@3MB at 0x01075338, whose image value is 3.0f -- the
/// twin's PATCH_UV_TILES/PATCH_WIDTH, 42/14.  The literal is deliberate: with
/// the constant behind an extern the product is rematerialised inside the
/// vertex loop instead of being hoisted into an x87 register, which is the
/// shape docs/shape_levers.md records as "an x87 product loads its operands in
/// the wrong order: make the constant a literal".
#define WATER_UV_SCALE 3.0f

/// Retail dispatches the vertex-buffer factory on vtable slot 0x68 with the
/// six arguments listed above; the leading slots are unnamed because nothing
/// in this body proves what they are.
struct BfmeRetailWaterDevice
{
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual HRESULT __stdcall CreateVertexBuffer(unsigned int, unsigned int, unsigned int,
		unsigned int, struct BfmeRetailVertexBuffer **, void *) = 0;
};

/// Retail locks on vtable slot 0x2c and unlocks on 0x30.
struct BfmeRetailVertexBuffer
{
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0;
	virtual HRESULT __stdcall Lock(unsigned int, unsigned int, void **, unsigned int) = 0;
	virtual HRESULT __stdcall Unlock() = 0;
};

/// The twin's Setting in the retail offset view: 0x30 bytes, with the vertex
/// alpha the body fills at +0x24.
struct BfmeWaterSetting
{
	unsigned char gap0[0x24];
	DWORD transparentWaterDiffuse;
	Real uScrollPerMs;
	Real vScrollPerMs;
};

/// The twin's SEA_PATCH_VERTEX: 0x18 bytes, the size retail locks.
struct BfmeSeaPatchVertex
{
	Real x, y, z;
	DWORD c;
	Real tu, tv;
};

/// Retail offsets of the members this body touches.  The twin's class layout
/// does not match BFME's, so the body reads and writes through this view.
struct BfmeWaterVertexLayout
{
	unsigned char gap0[0x100];
	Real m_level;											///< retail this+0x100
	unsigned char gap1[0x124 - 0x104];
	BfmeRetailVertexBuffer *m_vertexBufferD3D;					///< retail this+0x124
	unsigned char gap2[0x12c - 0x128];
	Int m_vertexBufferD3DOffset;								///< retail this+0x12c
	unsigned char gap3[0x13c - 0x130];
	Int m_numVertices;										///< retail this+0x13c
	unsigned char gap4[0x2e0 - 0x140];
	BfmeWaterSetting m_settings[4];							///< retail this+0x2e0
	unsigned char gap5[0x400 - 0x2e0 - 4 * 0x30];
	Int m_tod;												///< retail this+0x400
};

class WaterRenderObjClass
{
protected:
	HRESULT generateVertexBuffer(Int sizeX, Int sizeY, Int vertexSize, Bool doFill);
};

HRESULT WaterRenderObjClass::generateVertexBuffer(Int sizeX, Int sizeY, Int vertexSize, Bool doStatic)
{
	BfmeWaterVertexLayout *self = (BfmeWaterVertexLayout *)this;
	HRESULT hr;

	self->m_numVertices = sizeX * sizeY;
	BfmeWaterSetting *setting = &self->m_settings[self->m_tod];

	// default setting for a dynamic vertex buffer.  The pool immediates are
	// D3DPOOL_DEFAULT and D3DPOOL_MANAGED, as in the twin.
	int pool = 0;
	DWORD usage = 0x208;
	DWORD fvf = 0x242;

	if (doStatic)
	{	// change settings for a static vertex buffer
		pool = 1;		// D3DPOOL_MANAGED
		usage = 8;
		fvf = 0;		// no FVF, the water is drawn with a vertex shader
		self->m_numVertices = sizeX * sizeY;
	}

	if (self->m_vertexBufferD3D == NULL)
	{	// Create vertex buffer.  Retail reads the global device once and keeps
		// it in a register across the whole argument sequence, so the local
		// copy is the witnessed shape, not a convenience.
		BfmeRetailWaterDevice *device = reinterpret_cast<BfmeRetailWaterDevice *>(DX8Wrapper::_Get_D3D_Device8());
		if (FAILED(hr = device->CreateVertexBuffer(self->m_numVertices * vertexSize,
			usage, fvf, pool, &self->m_vertexBufferD3D, 0)))
			return hr;
	}

	self->m_vertexBufferD3DOffset = 0;

	if (!doStatic)
		return S_OK;	// only create the buffer, other code will fill it.

	// load results into buffer
	BfmeSeaPatchVertex *pVertices;
	if (FAILED(hr = self->m_vertexBufferD3D->Lock(0, self->m_numVertices * sizeof(BfmeSeaPatchVertex),
		(void **)&pVertices, 0)))
		return hr;

	Int x, z;
	for (z = 0; z < sizeY; z++)
	{
		for (x = 0; x < sizeX; x++)
		{
			pVertices->x = (Real)x;
			pVertices->y = self->m_level;
			pVertices->z = (Real)z;
			pVertices->tu = (Real)x * WATER_UV_SCALE;
			pVertices->tv = (Real)z * WATER_UV_SCALE;
			pVertices->c = setting->transparentWaterDiffuse;	// vertex alpha/color
			pVertices++;
		}
	}

	if (FAILED(hr = self->m_vertexBufferD3D->Unlock()))
		return hr;

	return S_OK;
}
