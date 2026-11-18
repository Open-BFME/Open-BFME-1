// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME: W3DModelDraw::allocateShadows, retail 0x007626F0 (363 bytes).
// Identity: primary W3DModelDraw vtable slot 12 -> ILT 0x00038393, and the
// Zero Hour twin (W3DModelDraw.cpp): build a Shadow::ShadowTypeInfo from the
// template's shadow fields and register it with TheW3DShadowManager. BFME
// adds two template floats (+0x3E0/+0x3E4) and three flags (+0x48D..+0x48F),
// passes no drawable to addShadow, and may hand the shadow the colour at
// +0x24. Fields without a witnessed name keep their offsets.

#include "ascii_string.h"

#include "../../../../../../GameEngine/Include/Common/ScalarTypes.h"



extern "C" char *__cdecl strcpy(char *, const char *);
#pragma intrinsic(strcpy)

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	void *m_vptr;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	const AsciiString &getShadowTextureName() const { return m_shadowTextureName; }
	unsigned short getShadowType() const { return m_shadowType; }
	Real getShadowSizeX() const { return m_shadowSizeX; }
	Real getShadowSizeY() const { return m_shadowSizeY; }
	Real getShadowOffsetX() const { return m_shadowOffsetX; }
	Real getShadowOffsetY() const { return m_shadowOffsetY; }

	unsigned char m_pad008[0x4c - 8];
	AsciiString m_shadowTextureName;	///< +0x4C
	unsigned char m_pad050[0x3c8 - 0x50];
	Real m_shadowSizeX;	///< +0x3C8
	Real m_shadowSizeY;	///< +0x3CC
	Real m_shadowOffsetX;	///< +0x3D0
	Real m_shadowOffsetY;	///< +0x3D4
	unsigned char m_pad3d8[0x3e0 - 0x3d8];
	Real m_shadowUnmodelled3e0;
	Real m_shadowUnmodelled3e4;
	unsigned char m_pad3e8[0x482 - 0x3e8];
	unsigned short m_shadowType;	///< +0x482
	unsigned char m_pad484[0x48d - 0x484];
	Bool m_shadowFlag48d;
	Bool m_shadowFlag48e;
	Bool m_shadowFlag48f;
};

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
template <class T>
class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable)
			return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
	operator const T *() const { return operator->(); }

private:
	const T *m_overridable;
};

class Drawable
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }

private:
	void *m_vptr;
	OVERRIDE<ThingTemplate> m_template;	///< +4
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
#undef TEN_SLOTS
	virtual void s90(); virtual void s91(); virtual void s92();
	virtual void s93(); virtual void s94(); virtual void s95();
	virtual void s96(); virtual void s97(); virtual void s98();
	virtual Int Is_Hidden();
};

class Shadow
{
public:
	struct ShadowTypeInfo
	{
		char m_ShadowName[128];
		Int m_type;
		Bool allowUpdates;
		Bool allowWorldAlign;
		Real m_sizeX;
		Real m_sizeY;
		Real m_offsetX;
		Real m_offsetY;
		Real m_field98;
		Real m_field9C;
		Bool m_fieldA0;

		ShadowTypeInfo() : m_field9C(20.0f), m_fieldA0(false) {}
	};

	void enableShadowRender(Bool enable) { m_isEnabled = enable; }
	void enableShadowInvisible(Bool invisible) { m_isInvisibleEnabled = invisible; }

	unsigned char m_pad000[4];
	Bool m_isEnabled;		///< +4
	Bool m_isInvisibleEnabled;	///< +5
	unsigned char m_pad006[0x30 - 6];
	Bool m_flag030;
};

// 0x00459880: packed-colour setter (ledger placeholder name).
class BfmeColourABK
{
public:
	void bfmeSetABK(Int colour);
};

class W3DShadowManager
{
public:
	Shadow *addShadow(RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);
};
extern W3DShadowManager *TheW3DShadowManager;

class W3DModelDraw
{
public:
	virtual void allocateShadows();

private:
	const Drawable *getDrawable() const { return m_drawable; }

	unsigned char m_pad004[4];
	Drawable *m_drawable;
	unsigned char m_pad00c[0x24 - 0x0c];
	Int m_drawableArgument;
	unsigned char m_pad028[0x2d - 0x28];
	Bool m_fullyObscuredByShroud;	///< +0x2D
	Bool m_shadowsEnabled;
	unsigned char m_pad02f[0x34 - 0x2f];
	RenderObjClass *m_renderObject;	///< +0x34
	unsigned char m_pad038[0x3c - 0x38];
	Shadow *m_shadow;		///< +0x3C
};

void W3DModelDraw::allocateShadows()
{
	const ThingTemplate *tmplate = getDrawable()->getTemplate();

	if (m_shadow == 0 && m_renderObject && TheW3DShadowManager && tmplate->getShadowType() != 0)
	{
		Shadow::ShadowTypeInfo shadowInfo;
		strcpy(shadowInfo.m_ShadowName, tmplate->getShadowTextureName().str());
		shadowInfo.allowUpdates = false;
		shadowInfo.allowWorldAlign = true;
		shadowInfo.m_type = tmplate->getShadowType();
		shadowInfo.m_sizeX = tmplate->getShadowSizeX();
		shadowInfo.m_sizeY = tmplate->getShadowSizeY();
		shadowInfo.m_offsetX = tmplate->getShadowOffsetX();
		shadowInfo.m_offsetY = tmplate->getShadowOffsetY();
		shadowInfo.m_field98 = tmplate->m_shadowUnmodelled3e0;
		shadowInfo.m_field9C = tmplate->m_shadowUnmodelled3e4;
		shadowInfo.m_fieldA0 = tmplate->m_shadowFlag48d;
		m_shadow = TheW3DShadowManager->addShadow(m_renderObject, &shadowInfo, 0);
		if (m_shadow)
		{
			m_shadow->m_flag030 = tmplate->m_shadowFlag48f;
			if (tmplate->m_shadowFlag48e)
				((BfmeColourABK *)m_shadow)->bfmeSetABK(m_drawableArgument);
			m_shadow->enableShadowInvisible(m_fullyObscuredByShroud);
			if (m_renderObject->Is_Hidden() || !m_shadowsEnabled)
				m_shadow->enableShadowRender(false);
		}
	}
}
