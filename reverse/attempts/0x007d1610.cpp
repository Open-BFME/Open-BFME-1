// ?postRender@ScreenBWFilterDOT3@@UAE_NW4FilterModes@@AAUCoord2D@@AA_NPAU3@@Z
// partial score=0.88 date=2026-09-07
// cl: /DNDEBUG /MD
// Retail 0x007D1610: ScreenBWFilterDOT3::postRender.
// The fourth virtual argument is the display-size Coord2D* forwarded by the
// W3DShaderManager filter wrapper.

#include "d3dx8math.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

extern const Real g_bfmeK1253;
extern Real g_bfmeDefaultBU;

struct Coord2D
{
	Real x;
	Real y;
};

enum FilterModes
{
	FM_NULL_MODE = 0
};

struct BfmeDevice;

struct BfmeDeviceVt
{
	char pad000[0x104];
	int (__stdcall *SetTexture)(BfmeDevice *, unsigned int, void *);
	char pad108[4];
	int (__stdcall *SetTextureStageState)(BfmeDevice *, unsigned int,
		unsigned int, unsigned int);
	char pad110[0x3c];
	int (__stdcall *DrawPrimitiveUP)(BfmeDevice *, unsigned int,
		unsigned int, const void *, unsigned int);
	char pad150[0x14];
	int (__stdcall *SetVertexShader)(BfmeDevice *, unsigned int);
};

struct BfmeDevice
{
	BfmeDeviceVt *vt;
};

#define BfmeDeviceGlobal (*(BfmeDevice **)0x01340534)
#define BfmeCurrentCaps (*(unsigned char **)0x01340578)
#define BfmeFadeValue (*(Real *)0x013071A8)
#define BfmeFadeScale (*(Real *)0x01084068)
#define BfmeShaderDirty (*(Bool *)0x012D6DFC)

class BfmeTacticalView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual Int getWidth() = 0;
	virtual void slot16() = 0;
	virtual Int getHeight() = 0;
	virtual void slot18() = 0;
	virtual void getOrigin(Int *, Int *) = 0;
};

#define TheTacticalView (*(BfmeTacticalView **)0x012F1600)

void *__cdecl bfmeEndRenderToTexture(void);

class ShaderClass;

class DX8Wrapper
{
public:
	static void Set_Shader(const ShaderClass &);
	static void Set_DX8_Render_State(unsigned long, unsigned int);
	static void Set_DX8_Texture_Stage_State(unsigned int, unsigned long,
		unsigned int);
	static void Apply_Render_State_Changes(void);
};

class ShaderClass
{
public:
	static ShaderClass _PresetAlphaShader;

	unsigned int bits;

	static void Invalidate(void)
	{
		BfmeShaderDirty = true;
	}

	void Set_Depth_Compare(int)
	{
		bits |= 7;
	}
};

class ScreenBWFilterDOT3
{
public:
	virtual Int init();
	virtual Int shutdown();
	virtual Bool preRender(Bool &, Int &);
	virtual Bool postRender(FilterModes, Coord2D &, Bool &, Coord2D *);
	virtual Bool setup(FilterModes);
	virtual Int set(FilterModes);
	virtual void reset();
};

Bool ScreenBWFilterDOT3::postRender(FilterModes mode, Coord2D &scrollDelta,
	Bool &doExtraRender, Coord2D *displaySize)
{
	void *tex = bfmeEndRenderToTexture();
	if (!tex)
		return false;
	if (!set(mode))
		return false;

	BfmeDevice *pDev = BfmeDeviceGlobal;
	struct _TRANS_LIT_TEX_VERTEX
	{
		D3DXVECTOR4 p;
		unsigned int color;
		Real u;
		Real v;
	} v[4];

	{
	Int xpos, ypos, width, height;

	TheTacticalView->getOrigin(&xpos, &ypos);
	width = TheTacticalView->getWidth();
	height = TheTacticalView->getHeight();

	// bottom right
	v[0].p = D3DXVECTOR4(xpos + width - g_bfmeK1253,
		ypos + height - g_bfmeK1253, 0.0f, 1.0f);
	v[0].u = (g_bfmeDefaultBU / displaySize->x) *
		(Real)(xpos + width);
	v[0].v = (g_bfmeDefaultBU / displaySize->y) *
		(Real)(ypos + height);
	// top right
	v[1].p = D3DXVECTOR4(xpos + width - g_bfmeK1253,
		ypos - g_bfmeK1253, 0.0f, 1.0f);
	v[1].u = (g_bfmeDefaultBU / displaySize->x) *
		(Real)(xpos + width);
	v[1].v = (g_bfmeDefaultBU / displaySize->y) * (Real)ypos;
	// bottom left
	v[2].p = D3DXVECTOR4(xpos - g_bfmeK1253,
		ypos + height - g_bfmeK1253, 0.0f, 1.0f);
	v[2].u = (g_bfmeDefaultBU / displaySize->x) * (Real)xpos;
	v[2].v = (g_bfmeDefaultBU / displaySize->y) *
		(Real)(ypos + height);

	// top left
	v[3].p = D3DXVECTOR4(xpos - g_bfmeK1253,
		ypos - g_bfmeK1253, 0.0f, 1.0f);
	v[3].u = (g_bfmeDefaultBU / displaySize->x) * (Real)xpos;
	v[3].v = (g_bfmeDefaultBU / displaySize->y) * (Real)ypos;

	unsigned int currentFade =
		((Int)((g_bfmeDefaultBU - BfmeFadeValue) * BfmeFadeScale) << 24) |
		0x00ffffff;
	v[0].color = currentFade;
	v[1].color = currentFade;
	v[2].color = currentFade;
	v[3].color = currentFade;
	}

	pDev->vt->SetVertexShader(pDev,
		D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	// Draw the grayscale pass first.
	if (BfmeCurrentCaps[0x272])
	{
		DX8Wrapper::Set_DX8_Render_State(60, 0x80A5CA8E);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 26, 35);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 2, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 3, 35);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 25);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 2, 1);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 3, 3);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, 1, 24);
	}
	else
	{
		DX8Wrapper::Set_DX8_Render_State(60, 0x60606060);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 2, 2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 3, 3);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 4);
	}

	BfmeDeviceGlobal->vt->SetTexture(BfmeDeviceGlobal, 0, tex);
	pDev->vt->DrawPrimitiveUP(pDev, D3DPT_TRIANGLESTRIP, 2, v,
		sizeof(_TRANS_LIT_TEX_VERTEX));

	{
		ShaderClass shader;
		ShaderClass::Invalidate();
		shader = *(ShaderClass *)0x012D6E14;
		shader.Set_Depth_Compare(0);
		DX8Wrapper::Set_Shader(shader);
	}
	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 3);
	pDev->vt->DrawPrimitiveUP(pDev, D3DPT_TRIANGLESTRIP, 2, v,
		sizeof(_TRANS_LIT_TEX_VERTEX));

	reset();
	return true;
}
