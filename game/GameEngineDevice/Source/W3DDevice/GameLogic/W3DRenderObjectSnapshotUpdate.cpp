// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// Open-BFME BFME-layout reconstruction of W3DRenderObjectSnapshot::update.

class Matrix3D
{
public:
	float m_values[12];
};

class HAnimClass;

class RenderObjClass
{
public:
	virtual void Delete_This();
	virtual void slot01();
	virtual RenderObjClass *Clone() const;
	virtual int Class_ID() const;

#define BFME_RENDER_SLOT(n) virtual void slot##n();
	BFME_RENDER_SLOT(04)
	BFME_RENDER_SLOT(05)
	BFME_RENDER_SLOT(06)
	BFME_RENDER_SLOT(07)
	BFME_RENDER_SLOT(08)
	BFME_RENDER_SLOT(09)
	BFME_RENDER_SLOT(10)
	BFME_RENDER_SLOT(11)
	BFME_RENDER_SLOT(12)
	BFME_RENDER_SLOT(13)
	BFME_RENDER_SLOT(14)
	BFME_RENDER_SLOT(15)
	virtual void Remove();
	BFME_RENDER_SLOT(17)
	BFME_RENDER_SLOT(18)
	BFME_RENDER_SLOT(19)
	virtual const Matrix3D &Get_Transform() const;
	virtual void Set_Transform(const Matrix3D &transform);
	BFME_RENDER_SLOT(22)
	BFME_RENDER_SLOT(23)
	BFME_RENDER_SLOT(24)
	BFME_RENDER_SLOT(25)
	BFME_RENDER_SLOT(26)
	BFME_RENDER_SLOT(27)
	BFME_RENDER_SLOT(28)
	BFME_RENDER_SLOT(29)
	BFME_RENDER_SLOT(30)
	BFME_RENDER_SLOT(31)
	BFME_RENDER_SLOT(32)
	BFME_RENDER_SLOT(33)
	BFME_RENDER_SLOT(34)
	BFME_RENDER_SLOT(35)
	BFME_RENDER_SLOT(36)
	BFME_RENDER_SLOT(37)
	BFME_RENDER_SLOT(38)
	BFME_RENDER_SLOT(39)
	BFME_RENDER_SLOT(40)
	BFME_RENDER_SLOT(41)
	BFME_RENDER_SLOT(42)
	BFME_RENDER_SLOT(43)
	virtual void Set_Animation(HAnimClass *animation, float frame, int mode = 0);
	BFME_RENDER_SLOT(45)
	BFME_RENDER_SLOT(46)
	BFME_RENDER_SLOT(47)
	BFME_RENDER_SLOT(48)
	BFME_RENDER_SLOT(49)
	BFME_RENDER_SLOT(50)
	BFME_RENDER_SLOT(51)
	BFME_RENDER_SLOT(52)
	BFME_RENDER_SLOT(53)
	BFME_RENDER_SLOT(54)
	BFME_RENDER_SLOT(55)
	BFME_RENDER_SLOT(56)
	BFME_RENDER_SLOT(57)
	BFME_RENDER_SLOT(58)
	BFME_RENDER_SLOT(59)
	BFME_RENDER_SLOT(60)
	BFME_RENDER_SLOT(61)
	BFME_RENDER_SLOT(62)
	BFME_RENDER_SLOT(63)
	BFME_RENDER_SLOT(64)
	BFME_RENDER_SLOT(65)
	BFME_RENDER_SLOT(66)
	BFME_RENDER_SLOT(67)
	BFME_RENDER_SLOT(68)
	BFME_RENDER_SLOT(69)
	BFME_RENDER_SLOT(70)
	BFME_RENDER_SLOT(71)
	BFME_RENDER_SLOT(72)
	BFME_RENDER_SLOT(73)
	BFME_RENDER_SLOT(74)
	BFME_RENDER_SLOT(75)
	BFME_RENDER_SLOT(76)
	BFME_RENDER_SLOT(77)
	BFME_RENDER_SLOT(78)
	BFME_RENDER_SLOT(79)
	BFME_RENDER_SLOT(80)
	BFME_RENDER_SLOT(81)
	BFME_RENDER_SLOT(82)
	BFME_RENDER_SLOT(83)
	BFME_RENDER_SLOT(84)
	virtual void Set_User_Data(void *data, bool recursive = false);
	BFME_RENDER_SLOT(86)
	BFME_RENDER_SLOT(87)
	BFME_RENDER_SLOT(88)
	BFME_RENDER_SLOT(89)
	BFME_RENDER_SLOT(90)
	BFME_RENDER_SLOT(91)
	BFME_RENDER_SLOT(92)
	BFME_RENDER_SLOT(93)
	BFME_RENDER_SLOT(94)
	BFME_RENDER_SLOT(95)
	BFME_RENDER_SLOT(96)
	BFME_RENDER_SLOT(97)
	BFME_RENDER_SLOT(98)
	BFME_RENDER_SLOT(99)
	BFME_RENDER_SLOT(100)
	BFME_RENDER_SLOT(101)
	BFME_RENDER_SLOT(102)
	BFME_RENDER_SLOT(103)
	BFME_RENDER_SLOT(104)
	BFME_RENDER_SLOT(105)
	BFME_RENDER_SLOT(106)
	BFME_RENDER_SLOT(107)
	BFME_RENDER_SLOT(108)
	BFME_RENDER_SLOT(109)
	BFME_RENDER_SLOT(110)
	BFME_RENDER_SLOT(111)
	BFME_RENDER_SLOT(112)
	BFME_RENDER_SLOT(113)
	BFME_RENDER_SLOT(114)
	BFME_RENDER_SLOT(115)
	BFME_RENDER_SLOT(116)
	BFME_RENDER_SLOT(117)
	BFME_RENDER_SLOT(118)
	BFME_RENDER_SLOT(119)
	BFME_RENDER_SLOT(120)
	BFME_RENDER_SLOT(121)
	BFME_RENDER_SLOT(122)
	BFME_RENDER_SLOT(123)
	BFME_RENDER_SLOT(124)
	BFME_RENDER_SLOT(125)
	BFME_RENDER_SLOT(126)
	BFME_RENDER_SLOT(127)
	BFME_RENDER_SLOT(128)
	BFME_RENDER_SLOT(129)
	BFME_RENDER_SLOT(130)
	virtual HAnimClass *Peek_Animation_And_Info(float &frame, int &numFrames, int &mode,
		float &multiplier);
#undef BFME_RENDER_SLOT

	unsigned int m_refCount;
	unsigned char m_pad08[0x10];
	Matrix3D m_transform;
	unsigned char m_pad48[4];
	unsigned int m_objectColor;

	void Release_Ref()
	{
		if (--m_refCount == 0)
			Delete_This();
	}

	unsigned int Get_ObjectColor() const
	{
		return m_objectColor;
	}

	void Set_ObjectColor(unsigned int color)
	{
		m_objectColor = color;
	}
};

struct DrawableInfo;

class Snapshot
{
public:
	virtual void anchor();
};

class W3DRenderObjectSnapshot : public Snapshot
{
void update(RenderObjClass *robj, DrawableInfo *drawInfo, bool cloneParentRobj);

public:
	RenderObjClass *m_robj;
};

extern void j_00030576();

void W3DRenderObjectSnapshot::update(RenderObjClass *robj, DrawableInfo *drawInfo,
	bool cloneParentRobj)
{
	W3DRenderObjectSnapshot *snapshot = this;
	RenderObjClass *parent = robj;

	if (snapshot->m_robj)
	{
		snapshot->m_robj->Remove();
		if (snapshot->m_robj)
		{
			snapshot->m_robj->Release_Ref();
			snapshot->m_robj = 0;
		}
	}

	if (cloneParentRobj == true)
	{
		snapshot->m_robj = parent->Clone();
		snapshot->m_robj->Set_ObjectColor(parent->Get_ObjectColor());
		parent->Get_Transform();
		snapshot->m_robj->Set_Transform(parent->m_transform);
		if (parent->Class_ID() == 0x19)
		{
			float frame;
			float multiplier;
			int mode;
			int numFrames;
			HAnimClass *animation = parent->Peek_Animation_And_Info(frame, numFrames, mode,
				multiplier);
			snapshot->m_robj->Set_Animation(animation, frame);
			reinterpret_cast<void (*)(RenderObjClass *)>(j_00030576)(snapshot->m_robj);
		}
	}
	else
		snapshot->m_robj = parent;

	snapshot->m_robj->Set_User_Data(drawInfo);
}
