// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/volumetricshadow /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
// W3DVolumetricShadow::RenderVolume -- retail 0x007BD9C0, 206 bytes, thiscall, ret 8.
// Identity: the matched W3DVolumetricShadowManager::renderShadows(Bool) at 0x007BFB90
// calls it by name through ILT 0x0003FFFD. Zero Hour twin: W3DVolumetricShadow::RenderVolume
// in GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp. BFME adds
// the Drawable transform refresh ahead of the twin's mesh selection, drops the twin's null
// mesh test, and swaps in the 0x00ED6848 identity matrix for a flagged mesh record.

#include "GameClient/DrawableInfo.h"

class Matrix3D;

// Retail .data 0x00ED6848 holds a 3x4 identity (1,0,0,0, 0,1,0,0, 0,0,1,0); only this body
// and the 0x007BF3C0 dump reference it, so it is not Matrix3D::Identity.
extern Matrix3D Rva00ED6848IdentityMatrix;

class Drawable
{
public:
	// pinned ILT 0x00017512 -> 0x0041CEC0
	const Matrix3D *getTransformMatrix(void) const;
};

// Slot names come from the matched HLodClass vtable 0x0113EBE8: slot 3 Class_ID, slot 20
// RenderObjClass::Validate_Transform, slot 21 Set_Transform, slot 85 Set_User_Data (86 is
// its Get_User_Data partner), slot 139 HLodClass::Peek_Lod_Model.
#define RENDOBJ_SLOT(n) virtual void slot##n(void);
class RenderObjClass
{
public:
	enum { CLASSID_MESH = 0 };	// ZH rendobj.h; HLodClass::Class_ID returns 0x19 = CLASSID_HLOD
	RENDOBJ_SLOT(0) RENDOBJ_SLOT(1) RENDOBJ_SLOT(2)
	virtual int Class_ID(void) const;
	RENDOBJ_SLOT(4) RENDOBJ_SLOT(5) RENDOBJ_SLOT(6) RENDOBJ_SLOT(7) RENDOBJ_SLOT(8)
	RENDOBJ_SLOT(9) RENDOBJ_SLOT(10) RENDOBJ_SLOT(11) RENDOBJ_SLOT(12) RENDOBJ_SLOT(13)
	RENDOBJ_SLOT(14) RENDOBJ_SLOT(15) RENDOBJ_SLOT(16) RENDOBJ_SLOT(17) RENDOBJ_SLOT(18)
	RENDOBJ_SLOT(19)
	virtual void Validate_Transform(void) const;
	virtual void Set_Transform(const Matrix3D &m);
	RENDOBJ_SLOT(22) RENDOBJ_SLOT(23) RENDOBJ_SLOT(24) RENDOBJ_SLOT(25) RENDOBJ_SLOT(26)
	RENDOBJ_SLOT(27) RENDOBJ_SLOT(28) RENDOBJ_SLOT(29) RENDOBJ_SLOT(30) RENDOBJ_SLOT(31)
	RENDOBJ_SLOT(32) RENDOBJ_SLOT(33) RENDOBJ_SLOT(34) RENDOBJ_SLOT(35) RENDOBJ_SLOT(36)
	RENDOBJ_SLOT(37) RENDOBJ_SLOT(38) RENDOBJ_SLOT(39) RENDOBJ_SLOT(40) RENDOBJ_SLOT(41)
	RENDOBJ_SLOT(42) RENDOBJ_SLOT(43) RENDOBJ_SLOT(44) RENDOBJ_SLOT(45) RENDOBJ_SLOT(46)
	RENDOBJ_SLOT(47) RENDOBJ_SLOT(48) RENDOBJ_SLOT(49) RENDOBJ_SLOT(50) RENDOBJ_SLOT(51)
	RENDOBJ_SLOT(52) RENDOBJ_SLOT(53) RENDOBJ_SLOT(54) RENDOBJ_SLOT(55) RENDOBJ_SLOT(56)
	RENDOBJ_SLOT(57) RENDOBJ_SLOT(58) RENDOBJ_SLOT(59) RENDOBJ_SLOT(60) RENDOBJ_SLOT(61)
	RENDOBJ_SLOT(62) RENDOBJ_SLOT(63) RENDOBJ_SLOT(64) RENDOBJ_SLOT(65) RENDOBJ_SLOT(66)
	RENDOBJ_SLOT(67) RENDOBJ_SLOT(68) RENDOBJ_SLOT(69) RENDOBJ_SLOT(70) RENDOBJ_SLOT(71)
	RENDOBJ_SLOT(72) RENDOBJ_SLOT(73) RENDOBJ_SLOT(74) RENDOBJ_SLOT(75) RENDOBJ_SLOT(76)
	RENDOBJ_SLOT(77) RENDOBJ_SLOT(78) RENDOBJ_SLOT(79) RENDOBJ_SLOT(80) RENDOBJ_SLOT(81)
	RENDOBJ_SLOT(82) RENDOBJ_SLOT(83) RENDOBJ_SLOT(84) RENDOBJ_SLOT(85)
	virtual void *Get_User_Data(void);

	// ZH RenderObjClass::Get_Transform: Validate_Transform, then the Transform member,
	// which retail reads at +0x18 (ZH layout hint).
	__forceinline const Matrix3D &Get_Transform(void) const
	{
		Validate_Transform();
		return *(const Matrix3D *)((const char *)this + 0x18);
	}
};

class HLodClass : public RenderObjClass
{
public:
	RENDOBJ_SLOT(87) RENDOBJ_SLOT(88) RENDOBJ_SLOT(89) RENDOBJ_SLOT(90) RENDOBJ_SLOT(91)
	RENDOBJ_SLOT(92) RENDOBJ_SLOT(93) RENDOBJ_SLOT(94) RENDOBJ_SLOT(95) RENDOBJ_SLOT(96)
	RENDOBJ_SLOT(97) RENDOBJ_SLOT(98) RENDOBJ_SLOT(99) RENDOBJ_SLOT(100) RENDOBJ_SLOT(101)
	RENDOBJ_SLOT(102) RENDOBJ_SLOT(103) RENDOBJ_SLOT(104) RENDOBJ_SLOT(105) RENDOBJ_SLOT(106)
	RENDOBJ_SLOT(107) RENDOBJ_SLOT(108) RENDOBJ_SLOT(109) RENDOBJ_SLOT(110) RENDOBJ_SLOT(111)
	RENDOBJ_SLOT(112) RENDOBJ_SLOT(113) RENDOBJ_SLOT(114) RENDOBJ_SLOT(115) RENDOBJ_SLOT(116)
	RENDOBJ_SLOT(117) RENDOBJ_SLOT(118) RENDOBJ_SLOT(119) RENDOBJ_SLOT(120) RENDOBJ_SLOT(121)
	RENDOBJ_SLOT(122) RENDOBJ_SLOT(123) RENDOBJ_SLOT(124) RENDOBJ_SLOT(125) RENDOBJ_SLOT(126)
	RENDOBJ_SLOT(127) RENDOBJ_SLOT(128) RENDOBJ_SLOT(129) RENDOBJ_SLOT(130) RENDOBJ_SLOT(131)
	RENDOBJ_SLOT(132) RENDOBJ_SLOT(133) RENDOBJ_SLOT(134) RENDOBJ_SLOT(135) RENDOBJ_SLOT(136)
	RENDOBJ_SLOT(137) RENDOBJ_SLOT(138)
	virtual RenderObjClass *Peek_Lod_Model(int lod, int model) const;
};
#undef RENDOBJ_SLOT

#define MAX_SHADOW_CASTER_MESHES 160	// ZH W3DVolumetricShadow.h

// A 0x34-byte mesh record; the ZH twin reads m_meshRobjIndex for the same Peek_Lod_Model
// index (BFME moved it to +0xc). +0x30 is an unmodelled BFME flag.
struct W3DShadowGeometryMesh
{
	char m_unmodelled00[0xc];
	int m_meshRobjIndex;
	char m_unmodelled10[0x20];
	unsigned char m_unmodelled30;
	char m_unmodelled31[3];
};

class W3DShadowGeometry
{
public:
	W3DShadowGeometryMesh *getMesh(int index) { return &m_meshList[index]; }

private:
	char m_unmodelled00[0x14];
	W3DShadowGeometryMesh m_meshList[MAX_SHADOW_CASTER_MESHES];
};

class W3DVolumetricShadow
{
protected:
	enum { SHADOW_DYNAMIC = 0x1 };	// ZH twin

	void RenderVolume(int meshIndex, int lightIndex);
	void RenderMeshVolume(int meshIndex, int lightIndex, const Matrix3D *meshXform);
	void RenderDynamicMeshVolume(int meshIndex, int lightIndex, const Matrix3D *meshXform);

	char m_unmodelled00[0x6c];
	W3DShadowGeometry *m_geometry;	// ZH twin order: m_next, m_geometry, m_robj
	RenderObjClass *m_robj;
	char m_unmodelled74[0xc];
	void *m_shadowVolume[MAX_SHADOW_CASTER_MESHES];	// ZH: Geometry *m_shadowVolume[lights][meshes]; flags byte at +0x18
};

static inline unsigned char shadowVolumeFlags(const void *geometry)
{
	return *((const unsigned char *)geometry + 0x18);
}

static inline unsigned char drawableByte3b1(const Drawable *draw)
{
	return *((const unsigned char *)draw + 0x3b1);
}

void W3DVolumetricShadow::RenderVolume(int meshIndex, int lightIndex)
{
	HLodClass *hlod = (HLodClass *)m_robj;
	RenderObjClass *mesh = 0;

	if (m_robj && m_robj->Get_User_Data())
	{
		Drawable *draw = ((DrawableInfo *)m_robj->Get_User_Data())->m_drawable;
		if (draw && !drawableByte3b1(draw))
			m_robj->Set_Transform(*draw->getTransformMatrix());
	}

	W3DShadowGeometryMesh *meshInfo = m_geometry->getMesh(meshIndex);
	int meshRobjIndex = meshInfo->m_meshRobjIndex;
	if (meshRobjIndex >= 0)
		mesh = hlod->Peek_Lod_Model(0, meshRobjIndex);
	else
		mesh = m_robj;

	const Matrix3D *meshXform = &mesh->Get_Transform();
	if (meshInfo->m_unmodelled30 && mesh->Class_ID() == RenderObjClass::CLASSID_MESH)
		meshXform = &Rva00ED6848IdentityMatrix;

	if (shadowVolumeFlags(m_shadowVolume[meshIndex]) & SHADOW_DYNAMIC)
		RenderDynamicMeshVolume(meshIndex, lightIndex, meshXform);
	else
		RenderMeshVolume(meshIndex, lightIndex, meshXform);
}
