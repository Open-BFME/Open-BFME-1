// cl: /DNDEBUG /MD
// Retail 0x007D0CE0: ScreenBWFilter::postRender.
// The BFME filter wrapper forwards a fourth caller-stack word containing the
// display dimensions; the old Zero Hour declaration omitted that ABI word.

#include "d3dx8math.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

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

class ScreenBWFilter
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

Bool ScreenBWFilter::postRender(FilterModes mode, Coord2D &scrollDelta,
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

	Int xpos, ypos, width, height;

	BfmeDeviceGlobal->vt->SetTexture(BfmeDeviceGlobal, 0, tex);
	TheTacticalView->getOrigin(&xpos, &ypos);
	width = TheTacticalView->getWidth();
	height = TheTacticalView->getHeight();

	// bottom right
	v[0].p = D3DXVECTOR4(xpos + width - 0.5f,
		ypos + height - 0.5f, 0.0f, 1.0f);
	v[0].u = (Real)(xpos + width) / displaySize->x;
	v[0].v = (Real)(ypos + height) / displaySize->y;
	// top right
	v[1].p = D3DXVECTOR4(xpos + width - 0.5f,
		ypos - 0.5f, 0.0f, 1.0f);
	v[1].u = (Real)(xpos + width) / displaySize->x;
	v[1].v = (Real)ypos / displaySize->y;
	// bottom left
	v[2].p = D3DXVECTOR4(xpos - 0.5f,
		ypos + height - 0.5f, 0.0f, 1.0f);
	v[2].u = (Real)xpos / displaySize->x;
	v[2].v = (Real)(ypos + height) / displaySize->y;
	// top left
	v[3].p = D3DXVECTOR4(xpos - 0.5f,
		ypos - 0.5f, 0.0f, 1.0f);
	v[3].u = (Real)xpos / displaySize->x;
	v[3].v = (Real)ypos / displaySize->y;
	v[0].color = 0xffffffff;
	v[1].color = 0xffffffff;
	v[2].color = 0xffffffff;
	v[3].color = 0xffffffff;

	pDev->vt->SetVertexShader(pDev,
		D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDev->vt->DrawPrimitiveUP(pDev, D3DPT_TRIANGLESTRIP, 2, v,
		sizeof(_TRANS_LIT_TEX_VERTEX));

	reset();
	return true;
}
