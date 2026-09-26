// cl: /DNDEBUG /MD /EHsc
// W3DModelDraw vtable slot 16 at 0x007633A0 (method name unproven; address-qualified).
// Seven constructor-installed W3DModelDraw-family tables, including the primary
// 0x01123D38, route slot 16 through ILT 0x0004A9FD to this body.
// Shape follows the sibling setTerrainDecal (0x00763230) and the Zero Hour twin:
// OVERRIDE-style template access and a real TheProjectedShadowManager global
// (VA 0x01306DEC), which lets the offsetY store schedule after the manager test.

typedef bool Bool;
typedef float Real;

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
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
	operator const Overridable *() const
	{
		if (!m_overridable)
			return 0;
		return m_overridable->getFinalOverride();
	}

	const Overridable *m_overridable;
};

class BfmeDrawableView
{
public:
	const Overridable *getTemplate() const { return m_template; }

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
	Real m_unmodelled9c;
	Bool m_unmodelleda0;
	unsigned char m_pad09d[3];

	BfmeDecalInfo() : m_unmodelled9c(20.0f), m_unmodelleda0(false) {}
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

class ProjectedShadowManager
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual Shadow *addDecal(RenderObjClass *, BfmeDecalInfo *, int, int);
};

// The source global TheProjectedShadowManager lives at VA 0x01306DEC.
extern ProjectedShadowManager *TheProjectedShadowManager;

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

	const ThingTemplate *thing = (const ThingTemplate *)m_drawable->getTemplate();

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
	info.m_offsetY = thing->m_shadowOffsetY;
	if (TheProjectedShadowManager)
		m_terrainDecal = TheProjectedShadowManager->addDecal(m_renderObject, &info, 1, 0);
	if (m_terrainDecal) {
		m_terrainDecal->m_isInvisibleEnabled = m_fullyObscuredByShroud;
		m_terrainDecal->enableShadowRender(m_flag02e && !m_flag02f);
	}
}
