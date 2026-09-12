// cl: /DNDEBUG /MD
// Retail 0x007D2D30: ScreenBWFilterDOT3::postRender.
// The BFME filter wrapper forwards a fourth Coord2D* display-size argument;
// the ZH ScreenBWFilterDOT3 body is the semantic source for this method.

#include "d3dx8math.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

extern const Real g_bfmeK1253;
extern Real g_bfmeDefaultBU;
extern Real g_bfmeScaleB3;

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

struct BfmeDeviceVtable
{
	char pad000[0x104];
	long (__stdcall *SetTexture)(BfmeDevice *, unsigned int, void *);
	char pad108[0x44];
	long (__stdcall *DrawPrimitiveUP)(BfmeDevice *, unsigned int,
		unsigned int, const void *, unsigned int);
	char pad150[0x14];
	long (__stdcall *SetVertexShader)(BfmeDevice *, unsigned int);
};

struct BfmeDevice
{
	BfmeDeviceVtable *v;
};

#define BfmeDeviceGlobal (*(BfmeDevice **)0x01340534)
#define BfmeTacticalViewGlobal (*(class BfmeTacticalView **)0x012F1600)
#define BfmeCurrentCapsGlobal (*(struct BfmeCaps **)0x01340578)
/* ScreenBWFilter::m_curFadeValue is declared below. */
extern char g_rva007A2330Flag;
/* ShaderClass::_PresetAlphaShader is declared below. */

class BfmeTacticalView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual Int getWidth();
	virtual void slot16();
	virtual Int getHeight();
	virtual void slot18();
	virtual void getOrigin(Int *, Int *);
};

struct BfmeCaps
{
	char pad[0x272];
	Bool dot3;
};

class ShaderClass
{
public:
	static ShaderClass _PresetAlphaShader;
	unsigned int bits;
	ShaderClass(unsigned int value) : bits(value) {}
};

// This is the call-site ILT retained by retail.  Its body is the named
// DX8Wrapper::Set_Shader target behind that thunk.
void BaseHeightMapScorchSetShader(const ShaderClass &);

class DX8Wrapper
{
public:
	static void Set_DX8_Render_State(unsigned long, unsigned int);
	static void Set_DX8_Texture_Stage_State(unsigned int, unsigned long,
		unsigned int);
	static void Apply_Render_State_Changes();
};

void *__cdecl bfmeEndRenderToTexture();

class ScreenBWFilter
{
public:
	virtual Int init();
	virtual Int shutdown();
	virtual Bool preRender(Bool &, Int &);
	virtual Bool postRender(FilterModes, Coord2D &, Bool &, Coord2D *);
	virtual Bool setup(FilterModes);
	static Real m_curFadeValue;
	protected:
	virtual Int set(FilterModes);
	virtual void reset();
};

class ScreenBWFilterDOT3 : public ScreenBWFilter
{
public:
	virtual Int init();
	virtual Int shutdown();
	virtual Bool preRender(Bool &, Int &);
	virtual Bool postRender(FilterModes, Coord2D &, Bool &, Coord2D *);
	virtual Bool setup(FilterModes);
};

// ?postRender@ScreenBWFilterDOT3@@UAE_NW4FilterModes@@AAUCoord2D@@AA_NPAU3@@Z
Bool ScreenBWFilterDOT3::postRender(FilterModes mode, Coord2D &scrollDelta,
	Bool &doExtraRender, Coord2D *displaySize)
{
	void *tex = bfmeEndRenderToTexture();
	if (!tex)
		return false;
	if (!set(mode))
		return false;

	BfmeDevice *pDev = BfmeDeviceGlobal;
	Int xpos, ypos, width, height;
	struct Vertex
	{
		D3DXVECTOR4 p;
		unsigned int color;
		Real u;
		Real v;
	} v[4];

	BfmeTacticalViewGlobal->getOrigin(&xpos, &ypos);
	width = BfmeTacticalViewGlobal->getWidth();
	height = BfmeTacticalViewGlobal->getHeight();

	v[0].p = D3DXVECTOR4(xpos + width - g_bfmeK1253,
		ypos + height - g_bfmeK1253, 0.0f, 1.0f);
	v[0].u = (g_bfmeDefaultBU / displaySize->x) *
		(Real)(xpos + width);
	v[0].v = (g_bfmeDefaultBU / displaySize->y) *
		(Real)(ypos + height);
	v[1].p = D3DXVECTOR4(xpos + width - g_bfmeK1253,
		ypos - g_bfmeK1253, 0.0f, 1.0f);
	v[1].u = (g_bfmeDefaultBU / displaySize->x) *
		(Real)(xpos + width);
	v[1].v = (g_bfmeDefaultBU / displaySize->y) * (Real)ypos;
	v[2].p = D3DXVECTOR4(xpos - g_bfmeK1253,
		ypos + height - g_bfmeK1253, 0.0f, 1.0f);
	v[2].u = (g_bfmeDefaultBU / displaySize->x) * (Real)xpos;
	v[2].v = (g_bfmeDefaultBU / displaySize->y) *
		(Real)(ypos + height);
	v[3].p = D3DXVECTOR4(xpos - g_bfmeK1253,
		ypos - g_bfmeK1253, 0.0f, 1.0f);
	v[3].u = (g_bfmeDefaultBU / displaySize->x) * (Real)xpos;
	v[3].v = (g_bfmeDefaultBU / displaySize->y) * (Real)ypos;
	unsigned int currentFade =
		((Int)((g_bfmeDefaultBU - ScreenBWFilter::m_curFadeValue) * g_bfmeScaleB3) << 24) |
		0x00ffffff;
	v[0].color = currentFade;
	v[1].color = currentFade;
	v[2].color = currentFade;
	v[3].color = currentFade;

	pDev->v->SetVertexShader(pDev, 0x144);
	if (BfmeCurrentCapsGlobal->dot3)
	{
		DX8Wrapper::Set_DX8_Render_State(60, 0x80a5ca8e);
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

	BfmeDeviceGlobal->v->SetTexture(BfmeDeviceGlobal, 0, tex);
	pDev->v->DrawPrimitiveUP(pDev, 5, 2, v,
		sizeof(Vertex));

	g_rva007A2330Flag = 1;
	BaseHeightMapScorchSetShader(
		ShaderClass(ShaderClass::_PresetAlphaShader.bits | 7));
	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 3);
	pDev->v->DrawPrimitiveUP(pDev, 5, 2, v,
		sizeof(Vertex));
	reset();
	return true;
}
