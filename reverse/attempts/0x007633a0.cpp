// ?d_007633a0@@YAXXZ
// partial score=0.9571 date=2026-09-24
// 0x007633A0: address-qualified W3DModelDraw-family vtable slot 16.
// Seven constructor-installed tables route through ILT 0x0004A9FD; the method name is unproven.
// Near match: 303/303 bytes, one aligned relocation, 13 non-relocation differences.
// The only mismatch is VC7.1 scheduling the manager load/test before the final
// template offsetY load; retail loads offsetY, tests manager, then stores offsetY.
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef float Real;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vptr;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled008[0x3c8 - 8];
	Real m_shadowSizeX;
	Real m_shadowSizeY;
	Real m_shadowOffsetX;
	Real m_shadowOffsetY;
};

class BfmeOverrideView
{
public:
	Overridable *getNonOverloadedPointer() const { return m_value; }
	Overridable *volatile m_value;
};

class BfmeDrawableView
{
public:
	Overridable *getTemplate() const
	{
		return m_template.getNonOverloadedPointer();
	}

	void *m_vptr;
	BfmeOverrideView m_template;
};

class RenderObjClass {};

struct BfmeDecalInfo
{
	char m_name[128];
	int m_type;
	Bool m_allowUpdates;
	Bool m_allowWorldAlign;
	unsigned char m_pad086[2];
	Real m_sizeX;
	Real m_sizeY;
	Real m_offsetX;
	Real m_offsetY;
	int m_unmodelled098;
	Real m_defaultScale;
	Bool m_reserved;
	unsigned char m_pad09d[3];

	BfmeDecalInfo() : m_defaultScale(20.0f), m_reserved(false) {}
};

struct Rva007633A0Spec
{
	unsigned char m_00[4];
	unsigned short m_04;
	unsigned char m_06[2];
	char m_08[1];
};

struct Rva007633A0Input
{
	Rva007633A0Spec *m_00;
};

class Shadow
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void release();

	Bool m_isEnabled;
	Bool m_isInvisibleEnabled;

	void enableShadowRender(Bool value) { m_isEnabled = value; }
};

class BfmeProjectedShadowManager
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual Shadow *addDecal(RenderObjClass *, BfmeDecalInfo *, int, int);
};

// The source global TheProjectedShadowManager lives at VA 0x01306DEC.
static BfmeProjectedShadowManager *bfmeProjectedShadowManagerAt01306DEC()
{
	return *(BfmeProjectedShadowManager **)0x01306DEC;
}

class W3DModelDraw
{
public:
	virtual void rva007633A0(Rva007633A0Input *input);

	unsigned char m_unmodelled004[4];
	BfmeDrawableView *m_drawable;
	unsigned char m_unmodelled00c[0x2d - 0x0c];
	Bool m_fullyObscuredByShroud;
	Bool m_flag02e;
	Bool m_flag02f;
	unsigned char m_unmodelled030[0x34 - 0x30];
	RenderObjClass *m_renderObject;
	unsigned char m_unmodelled038[0x40 - 0x38];
	Shadow *m_terrainDecal;
};

// W3DModelDraw vtable slot 16, descriptive address name only.
void W3DModelDraw::rva007633A0(Rva007633A0Input *input)
{
	if (m_terrainDecal)
		m_terrainDecal->release();
	m_terrainDecal = 0;
	Rva007633A0Spec *spec = input->m_00;
	if (!spec || !spec->m_04)
		return;

	Overridable *raw = m_drawable->getTemplate();
	ThingTemplate *thing;
	if (raw == 0) {
		thing = 0;
	} else {
		if (raw->m_nextOverride != 0)
			raw = (Overridable *)raw->m_nextOverride->getFinalOverride();
		thing = (ThingTemplate *)raw;
	}

	BfmeDecalInfo info;
	info.m_allowUpdates = false;
	info.m_allowWorldAlign = true;
	info.m_type = 0x20;
	const char *from = spec->m_08;
	char *to = info.m_name;
	char c;
	do { c = *from++; *to++ = c; } while (c);
	info.m_sizeX = thing->m_shadowSizeX;
	info.m_sizeY = thing->m_shadowSizeY;
	info.m_offsetX = thing->m_shadowOffsetX;
	BfmeProjectedShadowManager *manager =
		bfmeProjectedShadowManagerAt01306DEC();
	info.m_offsetY = thing->m_shadowOffsetY;
	if (manager)
		m_terrainDecal = manager->addDecal(m_renderObject, &info, 1, 0);
	if (m_terrainDecal) {
		m_terrainDecal->m_isInvisibleEnabled = m_fullyObscuredByShroud;
		m_terrainDecal->enableShadowRender(m_flag02e && !m_flag02f);
	}
}
