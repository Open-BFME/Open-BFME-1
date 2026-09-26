// ?allocateShadows@W3DModelDraw@@UAEXXZ
// partial score=0.75 date=2026-09-16
// Byte reconstruction of W3DModelDraw::allocateShadows.
// Identity: primary W3DModelDraw vtable slot 12 -> ILT 0x00038393 -> 0x007626F0.
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

struct BfmeOverrideView
{
	Overridable *volatile m_value;
};

struct BfmeDrawableView
{
	void *m_vptr;
	BfmeOverrideView m_template;
};

struct BfmeAsciiString
{
	const char *str() const
	{
		return m_data ? (const char *)(m_data + 8)
			: (const char *)0x0107388B;
	}
	int m_data;
};

struct ThingTemplate : public Overridable
{
	const BfmeAsciiString &getShadowTextureName() const
	{
		return m_shadowTextureName;
	}

	unsigned char m_unmodelled008[0x4c - 8];
	BfmeAsciiString m_shadowTextureName;
	unsigned char m_unmodelled050[0x3c8 - 0x50];
	Real m_shadowSizeX;
	Real m_shadowSizeY;
	Real m_shadowOffsetX;
	Real m_shadowOffsetY;
	unsigned char m_unmodelled3d8[0x3e0 - 0x3d8];
	Real m_shadowUnmodelled3e0;
	Real m_shadowUnmodelled3e4;
	unsigned char m_unmodelled3e8[0x482 - 0x3e8];
	unsigned short m_shadowType;
	unsigned char m_unmodelled484[0x48d - 0x484];
	Bool m_shadowFlag48d;
	Bool m_shadowFlag48e;
	Bool m_shadowFlag48f;
};

struct BfmeShadowTypeInfo
{
	char m_shadowName[128];
	int m_type;
	Bool m_allowUpdates;
	Bool m_allowWorldAlign;
	unsigned char m_padding086[2];
	Real m_sizeX;
	Real m_sizeY;
	Real m_offsetX;
	Real m_offsetY;
	Real m_unmodelled98;
	Real m_unmodelled9c;
	Bool m_unmodelleda0;

	BfmeShadowTypeInfo() : m_unmodelled9c(20.0f), m_unmodelleda0(false) {}
};

class RenderObjClass
{
public:
	#define TEN_SLOTS(P) \
		virtual void P##0(); virtual void P##1(); virtual void P##2(); \
		virtual void P##3(); virtual void P##4(); virtual void P##5(); \
		virtual void P##6(); virtual void P##7(); virtual void P##8(); \
		virtual void P##9()
	TEN_SLOTS(a); TEN_SLOTS(b); TEN_SLOTS(c); TEN_SLOTS(d); TEN_SLOTS(e);
	TEN_SLOTS(f); TEN_SLOTS(g); TEN_SLOTS(h); TEN_SLOTS(i);
	virtual void s90(); virtual void s91(); virtual void s92();
	virtual void s93(); virtual void s94(); virtual void s95();
	virtual void s96(); virtual void s97(); virtual void s98();
	virtual int isHidden();
	#undef TEN_SLOTS
};

class Shadow
{
public:
	void applyDrawable(void *value);

	unsigned char m_unmodelled000[4];
	Bool m_enabled;
	Bool m_invisible;
	unsigned char m_unmodelled006[0x30 - 6];
	Bool m_flag030;
};

class BfmeShadowManager
{
public:
	Shadow *addShadow(RenderObjClass *, BfmeShadowTypeInfo *, void *);
};

typedef Shadow *(BfmeShadowManager::*BfmeAddShadowFn)(
	RenderObjClass *, BfmeShadowTypeInfo *, void *);
typedef void (Shadow::*BfmeApplyDrawableFn)(void *);

extern void j_000022bb();
extern void j_0002dca4();
extern void j_0002b526();
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")

extern "C" char *__cdecl strcpy(char *, const char *);

class W3DModelDraw
{
public:
	virtual void allocateShadows();

	unsigned char m_unmodelled004[4];
	BfmeDrawableView *m_drawable;
	unsigned char m_unmodelled00c[0x24 - 0x0c];
	void *m_drawableArgument;
	unsigned char m_unmodelled028[0x2d - 0x28];
	Bool m_fullyObscuredByShroud;
	Bool m_shadowsEnabled;
	unsigned char m_unmodelled02f[0x34 - 0x2f];
	RenderObjClass *m_renderObject;
	unsigned char m_unmodelled038[0x3c - 0x38];
	Shadow *m_shadow;
};

void W3DModelDraw::allocateShadows()
{
	Overridable *raw = m_drawable->m_template.m_value;
	ThingTemplate *thing;
	if (raw == 0) {
		thing = 0;
	} else {
		if (raw->m_nextOverride != 0)
			raw = (Overridable *)raw->m_nextOverride->getFinalOverride();
		thing = (ThingTemplate *)raw;
	}

	if (m_shadow == 0 && m_renderObject != 0 &&
		*(BfmeShadowManager **)0x01306EEC != 0 && thing->m_shadowType != 0)
	{
		BfmeShadowTypeInfo info;
		const char *src = thing->getShadowTextureName().str();
		char *dst = info.m_shadowName;
		char value;
		do {
			value = *src++;
			*dst++ = value;
		} while (value != 0);
		info.m_allowUpdates = false;
		info.m_allowWorldAlign = true;
		info.m_type = thing->m_shadowType;
		info.m_sizeX = thing->m_shadowSizeX;
		info.m_sizeY = thing->m_shadowSizeY;
		info.m_offsetX = thing->m_shadowOffsetX;
		info.m_offsetY = thing->m_shadowOffsetY;
		info.m_unmodelled98 = thing->m_shadowUnmodelled3e0;
		info.m_unmodelled9c = thing->m_shadowUnmodelled3e4;
		info.m_unmodelleda0 = thing->m_shadowFlag48d;

		union { void *asVoid; BfmeAddShadowFn asMember; } addShadow;
		addShadow.asVoid = (void *)j_0002dca4;
		m_shadow = ((*(BfmeShadowManager **)0x01306EEC)->*addShadow.asMember)(
			m_renderObject, &info, 0);
		if (m_shadow != 0) {
			m_shadow->m_flag030 = thing->m_shadowFlag48f;
			if (thing->m_shadowFlag48e) {
				union { void *asVoid; BfmeApplyDrawableFn asMember; } apply;
				apply.asVoid = (void *)j_0002b526;
				(m_shadow->*apply.asMember)(m_drawableArgument);
			}
			m_shadow->m_invisible = m_fullyObscuredByShroud;
			if (m_renderObject->isHidden() || !m_shadowsEnabled)
				m_shadow->m_enabled = false;
		}
	}
}
