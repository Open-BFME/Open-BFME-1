// ?RenderVolume@W3DVolumetricShadow@@IAEXHH@Z
// partial score=0.9 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/volumetricshadow /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath

class Matrix3D;

struct DrawableInfo
{
	unsigned int m_shroudStatusObjectID;
	class Drawable *m_drawable;
};

class Drawable
{
public:
	const Matrix3D *getTransformMatrix(void) const;
};

#define RVO_DUMMY(n) virtual void v##n(void);
class RvaRenderObj
{
public:
	RVO_DUMMY(0)
	RVO_DUMMY(1)
	RVO_DUMMY(2)
	virtual int Class_ID(void) const;
	RVO_DUMMY(4)
	RVO_DUMMY(5)
	RVO_DUMMY(6)
	RVO_DUMMY(7)
	RVO_DUMMY(8)
	RVO_DUMMY(9)
	RVO_DUMMY(10)
	RVO_DUMMY(11)
	RVO_DUMMY(12)
	RVO_DUMMY(13)
	RVO_DUMMY(14)
	RVO_DUMMY(15)
	RVO_DUMMY(16)
	RVO_DUMMY(17)
	RVO_DUMMY(18)
	RVO_DUMMY(19)
	virtual void Validate_Transform(void) const;
	virtual void Set_Transform(const Matrix3D &transform);
	RVO_DUMMY(22)
	RVO_DUMMY(23)
	RVO_DUMMY(24)
	RVO_DUMMY(25)
	RVO_DUMMY(26)
	RVO_DUMMY(27)
	RVO_DUMMY(28)
	RVO_DUMMY(29)
	RVO_DUMMY(30)
	RVO_DUMMY(31)
	RVO_DUMMY(32)
	RVO_DUMMY(33)
	RVO_DUMMY(34)
	RVO_DUMMY(35)
	RVO_DUMMY(36)
	RVO_DUMMY(37)
	RVO_DUMMY(38)
	RVO_DUMMY(39)
	RVO_DUMMY(40)
	RVO_DUMMY(41)
	RVO_DUMMY(42)
	RVO_DUMMY(43)
	RVO_DUMMY(44)
	RVO_DUMMY(45)
	RVO_DUMMY(46)
	RVO_DUMMY(47)
	RVO_DUMMY(48)
	RVO_DUMMY(49)
	RVO_DUMMY(50)
	RVO_DUMMY(51)
	RVO_DUMMY(52)
	RVO_DUMMY(53)
	RVO_DUMMY(54)
	RVO_DUMMY(55)
	RVO_DUMMY(56)
	RVO_DUMMY(57)
	RVO_DUMMY(58)
	RVO_DUMMY(59)
	RVO_DUMMY(60)
	RVO_DUMMY(61)
	RVO_DUMMY(62)
	RVO_DUMMY(63)
	RVO_DUMMY(64)
	RVO_DUMMY(65)
	RVO_DUMMY(66)
	RVO_DUMMY(67)
	RVO_DUMMY(68)
	RVO_DUMMY(69)
	RVO_DUMMY(70)
	RVO_DUMMY(71)
	RVO_DUMMY(72)
	RVO_DUMMY(73)
	RVO_DUMMY(74)
	RVO_DUMMY(75)
	RVO_DUMMY(76)
	RVO_DUMMY(77)
	RVO_DUMMY(78)
	RVO_DUMMY(79)
	RVO_DUMMY(80)
	RVO_DUMMY(81)
	RVO_DUMMY(82)
	RVO_DUMMY(83)
	RVO_DUMMY(84)
	RVO_DUMMY(85)
	virtual void *Get_User_Data(void);
	RVO_DUMMY(87)
	RVO_DUMMY(88)
	RVO_DUMMY(89)
	RVO_DUMMY(90)
	RVO_DUMMY(91)
	RVO_DUMMY(92)
	RVO_DUMMY(93)
	RVO_DUMMY(94)
	RVO_DUMMY(95)
	RVO_DUMMY(96)
	RVO_DUMMY(97)
	RVO_DUMMY(98)
	RVO_DUMMY(99)
	RVO_DUMMY(100)
	RVO_DUMMY(101)
	RVO_DUMMY(102)
	RVO_DUMMY(103)
	RVO_DUMMY(104)
	RVO_DUMMY(105)
	RVO_DUMMY(106)
	RVO_DUMMY(107)
	RVO_DUMMY(108)
	RVO_DUMMY(109)
	RVO_DUMMY(110)
	RVO_DUMMY(111)
	RVO_DUMMY(112)
	RVO_DUMMY(113)
	RVO_DUMMY(114)
	RVO_DUMMY(115)
	RVO_DUMMY(116)
	RVO_DUMMY(117)
	RVO_DUMMY(118)
	RVO_DUMMY(119)
	RVO_DUMMY(120)
	RVO_DUMMY(121)
	RVO_DUMMY(122)
	RVO_DUMMY(123)
	RVO_DUMMY(124)
	RVO_DUMMY(125)
	RVO_DUMMY(126)
	RVO_DUMMY(127)
	RVO_DUMMY(128)
	RVO_DUMMY(129)
	RVO_DUMMY(130)
	RVO_DUMMY(131)
	RVO_DUMMY(132)
	RVO_DUMMY(133)
	RVO_DUMMY(134)
	RVO_DUMMY(135)
	RVO_DUMMY(136)
	RVO_DUMMY(137)
	RVO_DUMMY(138)
	virtual RvaRenderObj *Peek_Lod_Model(int lod, int model) const;

	__forceinline const Matrix3D &Get_Transform(void) const
	{
		Validate_Transform();
		return *(const Matrix3D *)((const char *)this + 0x18);
	}
};
#undef RVO_DUMMY

class RvaHlod : public RvaRenderObj
{
};

struct RvaShadowGeometryMesh
{
	void *m_mesh;
	char m_padding04[8];
	int m_meshRobjIndex;
	char m_padding10[0x34 - 0x10];
};

class RvaShadowGeometry
{
public:
	__forceinline RvaShadowGeometryMesh *getMesh(int index)
	{
		return &m_meshList[index];
	}

private:
	char m_padding[0x14];
	RvaShadowGeometryMesh m_meshList[160];
};

class Rva007B12F0Base
{
public:
	void *m_vtable;
	unsigned char m_isEnabled;
	unsigned char m_isInvisibleEnabled;
	char m_padding[0x52];
};

class W3DVolumetricShadow : public Rva007B12F0Base
{
protected:
	void RenderVolume(int meshIndex, int lightIndex);
	void RenderDynamicMeshVolume(int meshIndex, int lightIndex, const Matrix3D *meshXform);
	void RenderMeshVolume(int meshIndex, int lightIndex, const Matrix3D *meshXform);

private:
	int m_field58;
	int m_field5c;
	float m_field60;
	unsigned char m_field64;
	char m_padding65[3];
	W3DVolumetricShadow *m_next;
	RvaShadowGeometry *m_geometry;
	RvaRenderObj *m_robj;
	float m_shadowLengthScale;
	float m_robjExtent;
	float m_extraExtrusionPadding;
	void *m_shadowVolume[160];
};

void W3DVolumetricShadow::RenderVolume(int meshIndex, int lightIndex)
{
	RvaRenderObj *robj = m_robj;
	if (robj)
	{
		if (robj->Get_User_Data())
		{
			Drawable *draw = ((DrawableInfo *)robj->Get_User_Data())->m_drawable;
			if (draw && !*(unsigned char *)((char *)draw + 0x3b1))
				robj->Set_Transform(*draw->getTransformMatrix());
		}
	}

	RvaHlod *hlod = (RvaHlod *)m_robj;
	RvaRenderObj *mesh = 0;
	RvaShadowGeometry *geometry = m_geometry;
	RvaShadowGeometryMesh *meshInfo = geometry->getMesh(meshIndex);
	int meshRobjIndex = meshInfo->m_meshRobjIndex;
	const Matrix3D *meshXform = 0;
	if (meshRobjIndex >= 0)
		mesh = hlod->Peek_Lod_Model(0, meshRobjIndex);
		else
			mesh = m_robj;

	if (mesh)
	{
		meshXform = &mesh->Get_Transform();
		if (*(unsigned char *)((char *)meshInfo + 0x30) && !mesh->Class_ID())
			meshXform = (const Matrix3D *)0x012D6848;

		if (*(unsigned char *)((char *)m_shadowVolume[meshIndex] + 0x18) & 1)
			RenderDynamicMeshVolume(meshIndex, lightIndex, meshXform);
		else
			RenderMeshVolume(meshIndex, lightIndex, meshXform);
	}
}
