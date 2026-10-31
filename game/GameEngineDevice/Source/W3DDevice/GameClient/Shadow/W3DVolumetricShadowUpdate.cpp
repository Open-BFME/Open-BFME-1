// cl: /DNDEBUG /MD /EHsc
// W3DVolumetricShadow::Update(Bool) (retail 0x007BF7D0, 758 bytes, ret 4).
//
// Identity: tools/ilt_oracle.py CONFIRMS ?Update@W3DVolumetricShadow@@IAEX_N@Z
// at this body; the ZH no-argument spelling the MASM lift carried is
// CONTRADICTED (retail pops one stack word and ORs it into the +0x4900 byte).
//
// Body: Zero Hour's W3DVolumetricShadow::Update with the BFME deltas the
// Open BFME 2 donor Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/
// W3DVolumetricShadowUpdate.cpp (open-bfme-2 b5a7b8290) reads from its own
// retail: a forceUpdate argument parked in the +0x4900 byte while the shadow
// vertex/index buffers (0x01306F1C/0x01306F20) are missing, the X bound test
// only for geometry with more than one mesh (+0x2094), and, after a forced
// update, every XYZ vertex buffer's render-task list cleared. BFME 1 offsets:
// TheTerrainRenderObject slot +0x248 getHeightMapHeight and min height at
// +0x300C; TheW3DBufferManager's first XYZ buffer at +0x9000, next through
// getNextVertexBuffer 0x007B7CF0. The bounding centre/extent words
// 0x01306F00..0x01306F14 are the ZH file statics bcX..beZ of the shadow
// manager's unit, read here through their addresses.

typedef float Real;
typedef int Int;
typedef bool Bool;

#define AIRBORNE_UNIT_GROUND_DELTA	2.0f
#define MAX_SHADOW_LENGTH_EXTRA_AIRBORNE_SCALE_FACTOR	1.5f
#define SHADOW_EXTRUSION_BUFFER	0.1f

#include <math.h>

class Vector3
{
public:
	Vector3(void) {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	__forceinline Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Real X, Y, Z;
};

static __forceinline float shadowFabs(float val)
{
	int value = *(int *)&val;
	value &= 0x7fffffff;
	return *(float *)&value;
}

struct Coord3D;

class RenderObjClass
{
public:
	Vector3 Get_Position(void) const;
};

class TerrainLogic
{
public:
	virtual void vslot000(void);
	virtual void vslot001(void);
	virtual void vslot002(void);
	virtual void vslot003(void);
	virtual void vslot004(void);
	virtual void vslot005(void);
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
};
extern TerrainLogic *TheTerrainLogic;

class BaseHeightMapRenderObjClass
{
public:
#define HM_SLOT(n) virtual void hmSlot##n(void);
	HM_SLOT(000) HM_SLOT(001) HM_SLOT(002) HM_SLOT(003) HM_SLOT(004) HM_SLOT(005) HM_SLOT(006) HM_SLOT(007)
	HM_SLOT(008) HM_SLOT(009) HM_SLOT(010) HM_SLOT(011) HM_SLOT(012) HM_SLOT(013) HM_SLOT(014) HM_SLOT(015)
	HM_SLOT(016) HM_SLOT(017) HM_SLOT(018) HM_SLOT(019) HM_SLOT(020) HM_SLOT(021) HM_SLOT(022) HM_SLOT(023)
	HM_SLOT(024) HM_SLOT(025) HM_SLOT(026) HM_SLOT(027) HM_SLOT(028) HM_SLOT(029) HM_SLOT(030) HM_SLOT(031)
	HM_SLOT(032) HM_SLOT(033) HM_SLOT(034) HM_SLOT(035) HM_SLOT(036) HM_SLOT(037) HM_SLOT(038) HM_SLOT(039)
	HM_SLOT(040) HM_SLOT(041) HM_SLOT(042) HM_SLOT(043) HM_SLOT(044) HM_SLOT(045) HM_SLOT(046) HM_SLOT(047)
	HM_SLOT(048) HM_SLOT(049) HM_SLOT(050) HM_SLOT(051) HM_SLOT(052) HM_SLOT(053) HM_SLOT(054) HM_SLOT(055)
	HM_SLOT(056) HM_SLOT(057) HM_SLOT(058) HM_SLOT(059) HM_SLOT(060) HM_SLOT(061) HM_SLOT(062) HM_SLOT(063)
	HM_SLOT(064) HM_SLOT(065) HM_SLOT(066) HM_SLOT(067) HM_SLOT(068) HM_SLOT(069) HM_SLOT(070) HM_SLOT(071)
	HM_SLOT(072) HM_SLOT(073) HM_SLOT(074) HM_SLOT(075) HM_SLOT(076) HM_SLOT(077) HM_SLOT(078) HM_SLOT(079)
	HM_SLOT(080) HM_SLOT(081) HM_SLOT(082) HM_SLOT(083) HM_SLOT(084) HM_SLOT(085) HM_SLOT(086) HM_SLOT(087)
	HM_SLOT(088) HM_SLOT(089) HM_SLOT(090) HM_SLOT(091) HM_SLOT(092) HM_SLOT(093) HM_SLOT(094) HM_SLOT(095)
	HM_SLOT(096) HM_SLOT(097) HM_SLOT(098) HM_SLOT(099) HM_SLOT(100) HM_SLOT(101) HM_SLOT(102) HM_SLOT(103)
	HM_SLOT(104) HM_SLOT(105) HM_SLOT(106) HM_SLOT(107) HM_SLOT(108) HM_SLOT(109) HM_SLOT(110) HM_SLOT(111)
	HM_SLOT(112) HM_SLOT(113) HM_SLOT(114) HM_SLOT(115) HM_SLOT(116) HM_SLOT(117) HM_SLOT(118) HM_SLOT(119)
	HM_SLOT(120) HM_SLOT(121) HM_SLOT(122) HM_SLOT(123) HM_SLOT(124) HM_SLOT(125) HM_SLOT(126) HM_SLOT(127)
	HM_SLOT(128) HM_SLOT(129) HM_SLOT(130) HM_SLOT(131) HM_SLOT(132) HM_SLOT(133) HM_SLOT(134) HM_SLOT(135)
	HM_SLOT(136) HM_SLOT(137) HM_SLOT(138) HM_SLOT(139) HM_SLOT(140) HM_SLOT(141) HM_SLOT(142) HM_SLOT(143)
	HM_SLOT(144) HM_SLOT(145)
#undef HM_SLOT
	virtual Real getHeightMapHeight(Real x, Real y, Coord3D *normal) const;

	char m_pad[0x3008];
	Real m_minHeight;
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

// BaseHeightMapRenderObjClass::getMinHeight, inlined; a file-static accessor
// so this unit emits no COMDAT for the header's own copy.
static __forceinline Real getMinHeight(const BaseHeightMapRenderObjClass *map)
{
	return map->m_minHeight;
}

class W3DBufferManager
{
public:
	enum VBM_FVF_TYPES { VBM_FVF_XYZ, MAX_FVF = 9 };
	struct W3DRenderTask;
	struct W3DVertexBuffer
	{
		char m_pad[0x10];
		W3DVertexBuffer *m_NextVB;
		char m_pad14[4];
		W3DRenderTask *m_renderTaskList;
	};
	// Matched out of line at 0x007B7CF0 (W3DBufferManagerVertexBuffer.cpp);
	// retail inlines only the first, null-buffer lookup here.
	W3DVertexBuffer *getNextVertexBuffer(W3DVertexBuffer *pVb, VBM_FVF_TYPES type);

	char m_pad[0x9000];
	W3DVertexBuffer *m_W3DVertexBuffers[MAX_FVF];
};
extern W3DBufferManager *TheW3DBufferManager;

static __forceinline W3DBufferManager::W3DVertexBuffer *firstVertexBuffer(
	W3DBufferManager *manager, W3DBufferManager::VBM_FVF_TYPES type)
{
	return manager->m_W3DVertexBuffers[type];
}

class W3DShadowGeometry
{
public:
	char m_pad[0x2094];
	Int m_meshCount;
};

static __forceinline Int getMeshCount(const W3DShadowGeometry *geometry)
{
	return geometry->m_meshCount;
}

class W3DVolumetricShadow
{
protected:
	void Update(Bool forceUpdate);
	void updateOptimalExtrusionPadding(void);

	void *m_vtable;
	char m_pad4[0x68];
	W3DShadowGeometry *m_geometry;		// +0x6C
	RenderObjClass *m_robj;				// +0x70
	Real m_shadowLengthScale;			// +0x74
	Real m_robjExtent;					// +0x78
	Real m_extraExtrusionPadding;		// +0x7C
	char m_pad80[0x4880];
	Bool m_pendingUpdate;				// +0x4900
};

// 0x007BF3C0 (still a dump): the per-light volume rebuild taking the
// extrusion length; reached through ILT 0x00039B35 with this in ECX.
class Rva007BF3C0Volumes
{
public:
	void rva007BF3C0(Real zoffset);
};

struct IDirect3DVertexBuffer8;
struct IDirect3DIndexBuffer8;
extern IDirect3DVertexBuffer8 *shadowVertexBufferD3D;
extern IDirect3DIndexBuffer8 *shadowIndexBufferD3D;

extern Real g_Va01306F14;	// bcX
extern Real g_Va01306F10;	// bcY
extern Real g_Va01306F0C;	// bcZ
extern Real g_Va01306F08;	// beX
extern Real g_Va01306F04;	// beY
extern Real g_Va01306F00;	// beZ
#define bcX g_Va01306F14
#define bcY g_Va01306F10
#define bcZ g_Va01306F0C
#define beX g_Va01306F08
#define beY g_Va01306F04
#define beZ g_Va01306F00

void W3DVolumetricShadow::Update(Bool forceUpdate)
{
	static Int currentTime, lastTime;
	static Vector3 originCompareVector(0,0,0);
	Vector3 pos;

	if( m_geometry == 0)
		return;

	if (shadowVertexBufferD3D == 0 || shadowIndexBufferD3D == 0)
	{
		m_pendingUpdate |= forceUpdate;
		return;
	}

	forceUpdate = forceUpdate | m_pendingUpdate;
	m_pendingUpdate = false;

	{
		pos=m_robj->Get_Position();
		if (pos.X == originCompareVector.X &&
		    pos.Y == originCompareVector.Y &&
		    pos.Z == originCompareVector.Z)
		{
			return;
		}
		Real groundHeight;
		if (TheTerrainLogic)
			groundHeight=TheTerrainLogic->getGroundHeight(pos.X,pos.Y);
		else
			groundHeight=TheTerrainRenderObject->getHeightMapHeight(pos.X,pos.Y, 0);
		if (fabs(pos.Z - groundHeight) >= AIRBORNE_UNIT_GROUND_DELTA)
		{
			Real extent = MAX_SHADOW_LENGTH_EXTRA_AIRBORNE_SCALE_FACTOR * m_robjExtent;
			if (shadowFabs(pos.X - bcX) > (beX + extent) ||
				shadowFabs(pos.Y - bcY) > (beY + extent) ||
				shadowFabs(pos.Z - bcZ) > (beZ + extent))
				return;

			((Rva007BF3C0Volumes *)this)->rva007BF3C0(fabs(pos.Z - getMinHeight(TheTerrainRenderObject)) + SHADOW_EXTRUSION_BUFFER);
		}
		else
		{
			if ((getMeshCount(m_geometry) > 1 && shadowFabs(pos.X - bcX) > (beX + m_robjExtent)) ||
				shadowFabs(pos.Y - bcY) > (beY + m_robjExtent) ||
				shadowFabs(pos.Z - bcZ) > (beZ + m_robjExtent))
				return;

			if (!m_extraExtrusionPadding)
				updateOptimalExtrusionPadding();

			((Rva007BF3C0Volumes *)this)->rva007BF3C0(m_extraExtrusionPadding);
		}

		if (forceUpdate)
		{
			for (W3DBufferManager::W3DVertexBuffer *vb = firstVertexBuffer(TheW3DBufferManager, W3DBufferManager::VBM_FVF_XYZ);
				vb; vb = TheW3DBufferManager->getNextVertexBuffer(vb, W3DBufferManager::VBM_FVF_XYZ))
				vb->m_renderTaskList = 0;
		}

		lastTime = currentTime;
	}
}
