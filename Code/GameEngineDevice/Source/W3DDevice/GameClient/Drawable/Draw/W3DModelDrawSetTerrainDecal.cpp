// Byte-exact BFME reconstruction of W3DModelDraw::setTerrainDecal.
// Identity is established by the constructor-installed W3DModelDraw vtable:
// its DrawModule terrain-decal slot routes through ILT 0x000400CF to 0x00763230.
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef float Real;

enum TerrainDecalType
{
	BFME_TERRAIN_DECAL_LIMIT = 7
};

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
	Real m_unmodelled9c;
	Bool m_unmodelleda0;
	unsigned char m_pad09d[3];

	BfmeDecalInfo() : m_unmodelled9c(20.0f), m_unmodelleda0(false) {}
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
	virtual Shadow *addDecal(RenderObjClass *, BfmeDecalInfo *, void *, int);
};

// Retail directly indexes the seven-entry decal-name table at VA 0x012BB604.
static const char *const *bfmeTerrainDecalNamesAt012BB604()
{
	return (const char *const *)0x012BB604;
}

// The source global TheProjectedShadowManager lives at VA 0x01306DEC.
static BfmeProjectedShadowManager *bfmeProjectedShadowManagerAt01306DEC()
{
	return *(BfmeProjectedShadowManager **)0x01306DEC;
}

extern "C" char *__cdecl strcpy(char *, const char *);

class W3DModelDraw
{
public:
	virtual void setTerrainDecal(TerrainDecalType type);

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

// ?setTerrainDecal@W3DModelDraw@@UAEXW4TerrainDecalType@@@Z
void W3DModelDraw::setTerrainDecal(TerrainDecalType type)
{
	if (m_terrainDecal)
		m_terrainDecal->release();
	m_terrainDecal = 0;
	if (type >= BFME_TERRAIN_DECAL_LIMIT)
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
	strcpy(info.m_name, bfmeTerrainDecalNamesAt012BB604()[type]);
	info.m_sizeX = thing->m_shadowSizeX;
	info.m_sizeY = thing->m_shadowSizeY;
	info.m_offsetX = thing->m_shadowOffsetX;
	info.m_offsetY = thing->m_shadowOffsetY;

	BfmeProjectedShadowManager *manager =
		bfmeProjectedShadowManagerAt01306DEC();
	if (manager)
		m_terrainDecal = manager->addDecal(m_renderObject, &info, 0, 0);
	if (m_terrainDecal) {
		m_terrainDecal->m_isInvisibleEnabled = m_fullyObscuredByShroud;
		m_terrainDecal->enableShadowRender(m_flag02e && !m_flag02f);
	}
}
