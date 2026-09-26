// cl: /DNDEBUG /MD
// Retail 0x007D38B0: ScreenCrossFadeFilter::postRender.
// The constructor at 0x007D3740 installs vtable 0x01128A50; this is slot 3,
// with the matched CrossFade preRender at slot 2 and the separate set body at
// slot 5.  BFME forwards a fourth Coord2D* display-size argument through the
// filter wrapper, and the fade mask is the address-backed one-pointer handle
// at g_bfmeCurrentCZ rather than a raw TextureClass*.

#include "d3dx8math.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord2D
{
	Real x;
	Real y;
};

struct IDirect3DBaseTexture8;
struct IDirect3DTexture8;

enum FilterModes
{
	FM_NULL_MODE = 0,
	FM_VIEW_CROSSFADE_CIRCLE = 4
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
#define BfmeSkipRender (*(Bool *)0x01307210)

class DX8Wrapper
{
public:
	// ?_Get_D3D_Device8@DX8Wrapper@@SAPAUBfmeDevice@@XZ present-unmatched
	static BfmeDevice *_Get_D3D_Device8(void)
	{
		return BfmeDeviceGlobal;
	}
};

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

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture(void) const;
};

extern TextureBaseClass g_bfmeCurrentCZ;

class ScreenCrossFadeFilterUpdateFadeLevelShim
{
public:
	static Real m_curFadeValue;
};

void *__cdecl bfmeEndRenderToTexture(void);

class W3DShaderManager
{
public:
	static IDirect3DTexture8 *getRenderTexture(void);
};

class ScreenCrossFadeFilter
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

// ?postRender@ScreenCrossFadeFilter@@UAE_NW4FilterModes@@AAUCoord2D@@AA_NPAU3@@Z
Bool ScreenCrossFadeFilter::postRender(FilterModes mode, Coord2D &scrollDelta,
	Bool &doExtraRender, Coord2D *displaySize)
{
	IDirect3DTexture8 *tex;

	if (BfmeSkipRender)
	{
		BfmeSkipRender = false;
		doExtraRender = true;
		tex = (IDirect3DTexture8 *)bfmeEndRenderToTexture();
		return true;
	}

	tex = W3DShaderManager::getRenderTexture();
	if (!tex)
		return false;
	if (!set(mode))
		return false;

	BfmeDevice *pDev = DX8Wrapper::_Get_D3D_Device8();
	struct _TRANS_LIT_TEX_VERTEX
	{
		D3DXVECTOR4 p;
		unsigned int color;
		Real u;
		Real v;
		Real u1;
		Real v1;
	} v[4];

	Int xpos, ypos, width, height;
	Real radius = 0.0f;

	// ?_Get_D3D_Device8@DX8Wrapper@@SAPAUBfmeDevice@@XZ present-unmatched
	DX8Wrapper::_Get_D3D_Device8()->vt->SetTexture(
		DX8Wrapper::_Get_D3D_Device8(), 0, tex);
	if (mode == FM_VIEW_CROSSFADE_CIRCLE)
	{
		// ?_Get_D3D_Device8@DX8Wrapper@@SAPAUBfmeDevice@@XZ present-unmatched
		DX8Wrapper::_Get_D3D_Device8()->vt->SetTexture(
			// ?_Get_D3D_Device8@DX8Wrapper@@SAPAUBfmeDevice@@XZ present-unmatched
			DX8Wrapper::_Get_D3D_Device8(), 1,
			g_bfmeCurrentCZ.Peek_D3D_Base_Texture());
		radius = (1.0f - ScreenCrossFadeFilterUpdateFadeLevelShim::m_curFadeValue) * 2.0f;
		if (radius <= 0)
			radius = 0.01f;
		radius = 0.5f / radius;
	}

	TheTacticalView->getOrigin(&xpos, &ypos);
	width = TheTacticalView->getWidth();
	height = TheTacticalView->getHeight();

	// bottom right
	v[0].p = D3DXVECTOR4(xpos + width - 0.5f,
		ypos + height - 0.5f, 0.0f, 1.0f);
	v[0].u = (Real)(xpos + width) / displaySize->x;
	v[0].v = (Real)(ypos + height) / displaySize->y;
	v[0].u1 = 0.5f + radius;
	v[0].v1 = 0.5f + radius;
	// top right
	v[1].p = D3DXVECTOR4(xpos + width - 0.5f,
		ypos - 0.5f, 0.0f, 1.0f);
	v[1].u = (Real)(xpos + width) / displaySize->x;
	v[1].v = (Real)ypos / displaySize->y;
	v[1].u1 = 0.5f + radius;
	v[1].v1 = 0.5f - radius;
	// bottom left
	v[2].p = D3DXVECTOR4(xpos - 0.5f,
		ypos + height - 0.5f, 0.0f, 1.0f);
	v[2].u = (Real)xpos / displaySize->x;
	v[2].v = (Real)(ypos + height) / displaySize->y;
	v[2].u1 = 0.5f - radius;
	v[2].v1 = 0.5f + radius;
	// top left
	v[3].p = D3DXVECTOR4(xpos - 0.5f,
		ypos - 0.5f, 0.0f, 1.0f);
	v[3].u = (Real)xpos / displaySize->x;
	v[3].v = (Real)ypos / displaySize->y;
	v[3].u1 = 0.5f - radius;
	v[3].v1 = 0.5f - radius;

	unsigned int diffuse = 0xffffffff;
	v[0].color = diffuse;
	v[1].color = diffuse;
	v[2].color = diffuse;
	v[3].color = diffuse;

	pDev->vt->SetVertexShader(pDev,
		D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2);
	pDev->vt->DrawPrimitiveUP(pDev, D3DPT_TRIANGLESTRIP, 2, v,
		sizeof(_TRANS_LIT_TEX_VERTEX));

	reset();
	return true;
}
