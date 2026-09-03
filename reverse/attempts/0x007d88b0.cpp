// ?postRender@ScreenMotionBlurFilter@@UAE_NW4FilterModes@@AAUCoord2D@@AA_NH@Z
// partial score=0.95 date=2026-09-03
// cl: /DNDEBUG /MD
//
// Retail 0x007D88B0: ScreenMotionBlurFilter::postRender.  BFME's caller
// forwards one caller-stack word after the normal filter arguments; retail
// uses it as the display-size pair when it builds the filter quad.

#include <math.h>
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
	FM_VIEW_MB_END_PAN_ALPHA = 13,
	FM_VIEW_MB_PAN_ALPHA = 16
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
	virtual void slot20() = 0;
	virtual void lookAt(void *) = 0;
};

#define TheTacticalView (*(BfmeTacticalView **)0x012F1600)

struct BfmeGameLogic
{
	char pad000[0x3c];
	Int frame;
};

#define TheGameLogic (*(BfmeGameLogic **)0x012F0898)
#define ZoomToValid (*(Bool *)0x013072F8)
#define ZoomToPosition ((void *)0x01307318)

class DX8Wrapper
{
public:
	static void Set_DX8_Render_State(unsigned long, unsigned int);
	static void Apply_Render_State_Changes(void);
};

extern "C" void *__cdecl bfmeEndRenderToTexture(void);

class ScreenMotionBlurFilter
{
public:
	virtual Int init();
	virtual Int shutdown();
	virtual Bool preRender(Bool &, Int &);
	virtual Bool postRender(FilterModes, Coord2D &, Bool &, Int);
	virtual Bool setup(FilterModes);
	virtual Int set(FilterModes);
	virtual void reset();

	Int m_maxCount;
	Int m_lastFrame;
	Bool m_decrement;
	Bool m_skipRender;
	Bool m_additive;
	Bool m_doZoomTo;
	Coord2D m_priorDelta;
	Int m_panFactor;
};

Bool ScreenMotionBlurFilter::postRender(FilterModes mode, Coord2D &scrollDelta,
	Bool &doExtraRender, Int callerStackWord)
{
	void *tex = bfmeEndRenderToTexture();
	if (!tex)
		return false;
	if (!set(mode))
		return false;

	BfmeDevice *pDev = BfmeDeviceGlobal;
	Bool continueEffect = true;
	struct _TRANS_LIT_TEX_VERTEX
	{
		D3DXVECTOR4 p;
		unsigned int color;
		Real u;
		Real v;
	} v[4];

	Int xpos, ypos, width, height;

	BfmeDevice *textureDevice = BfmeDeviceGlobal;
	textureDevice->vt->SetTexture(textureDevice, 0, tex);
	BfmeTacticalView *originView = TheTacticalView;
	originView->getOrigin(&xpos, &ypos);
	BfmeTacticalView *widthView = TheTacticalView;
	width = widthView->getWidth();
	height = TheTacticalView->getHeight();

	Coord2D *displaySize = (Coord2D *)callerStackWord;
	// bottom right
	v[0].p = D3DXVECTOR4(xpos + width - 0.5f, ypos + height - 0.5f,
		0.0f, 1.0f);
	v[0].u = (Real)(xpos + width) / displaySize->x;
	v[0].v = (Real)(ypos + height) / displaySize->y;
	// top right
	v[1].p = D3DXVECTOR4(xpos + width - 0.5f, ypos - 0.5f,
		0.0f, 1.0f);
	v[1].u = (Real)(xpos + width) / displaySize->x;
	v[1].v = (Real)ypos / displaySize->y;
	// bottom left
	v[2].p = D3DXVECTOR4(xpos - 0.5f,
		ypos + height - 0.5f,
		0.0f, 1.0f);
	v[2].u = (Real)xpos / displaySize->x;
	v[2].v = (Real)(ypos + height) / displaySize->y;
	// top left
	v[3].p = D3DXVECTOR4(xpos - 0.5f, ypos - 0.5f,
		0.0f, 1.0f);
	v[3].u = (Real)xpos / displaySize->x;
	v[3].v = (Real)ypos / displaySize->y;
	v[0].color = 0xffffffff;
	v[1].color = 0xffffffff;
	v[2].color = 0xffffffff;
	v[3].color = 0xffffffff;

	if (m_additive) {
		DX8Wrapper::Set_DX8_Render_State(0x13, 5);
		DX8Wrapper::Set_DX8_Render_State(0x14, 2);
	} else {
		DX8Wrapper::Set_DX8_Render_State(0x13, 5);
		DX8Wrapper::Set_DX8_Render_State(0x14, 6);
	}
	DX8Wrapper::Set_DX8_Render_State(0x1b, false);
	DX8Wrapper::Apply_Render_State_Changes();
	pDev->vt->SetVertexShader(pDev, 0x144);

	Coord2D center;
	center.x = 0.5f;
	center.y = 0.5f;
	Bool pan = false;
	if (mode >= FM_VIEW_MB_PAN_ALPHA) {
		Real len = sqrt(scrollDelta.x * scrollDelta.x +
			scrollDelta.y * scrollDelta.y);
		center.y -= 0.5f;
		m_decrement = false;
		m_maxCount = (len * 200 * m_panFactor / (Real)30);
		if (m_maxCount < m_panFactor / 2)
			m_maxCount = m_panFactor / 2;
		if (m_maxCount > m_panFactor)
			m_maxCount = m_panFactor;
		pan = true;
		m_priorDelta = scrollDelta;
	} else if (mode == FM_VIEW_MB_END_PAN_ALPHA) {
		Real len = sqrt(m_priorDelta.x * m_priorDelta.x +
			m_priorDelta.y * m_priorDelta.y);
		center.x += 0.5f * (m_priorDelta.x / len);
		center.y -= 0.5f * (m_priorDelta.y / len);
		m_decrement = false;
		m_maxCount--;
		if (m_maxCount < 2)
			continueEffect = false;
		pan = true;
	}

	m_skipRender = false;
	if (!pan && m_lastFrame != TheGameLogic->frame) {
		if (m_decrement) {
			m_maxCount -= 5;
			if (m_maxCount < 1) {
				m_decrement = false;
				continueEffect = false;
			} else {
				m_skipRender = true;
			}
		} else {
			m_maxCount += 5;
			if (m_maxCount >= 60) {
				m_decrement = true;
				if (m_doZoomTo && ZoomToValid) {
					TheTacticalView->lookAt(ZoomToPosition);
				} else {
					continueEffect = false;
				}
			} else {
				m_skipRender = true;
			}
		}
	}

	Int i;
	Int j;
	if (!pan) {
		for (i = 0; i < 4; i++) {
			Real factor = 1.0f - (m_maxCount / (Real)60) * 0.90f;
			factor = sqrt(factor);
			v[i].u = ((v[i].u - center.x) * factor) + center.x;
			v[i].v = ((v[i].v - center.y) * factor) + center.y;
		}
	}
	pDev->vt->SetTextureStageState(pDev, 0, 5, 1);
	pDev->vt->SetTextureStageState(pDev, 0, 6, 2);
	pDev->vt->SetTextureStageState(pDev, 0, 4, 2);
	pDev->vt->DrawPrimitiveUP(pDev, 5, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));
	DX8Wrapper::Set_DX8_Render_State(0x1b, true);

	DX8Wrapper::Apply_Render_State_Changes();
	{
		Int limit = m_maxCount;
		if (m_maxCount > 30)
			limit = 30;
		for (j = 0; j < limit; j++) {
			for (i = 0; i < 4; i++) {
				Real factor = 0.99f;
				if (m_additive)
					factor = 0.98f;
				Int alpha = 0x15;
				if (m_additive) {
					alpha = 0x09;
					if (m_maxCount > limit)
						alpha += (m_maxCount - limit) / 5;
					if (m_maxCount == 60)
						alpha += 60;
				}
				v[i].color = (alpha << 24) | 0x00ffffff;
				if (pan) {
					v[i].u = ((v[i].u - center.x) * (factor + .006)) + center.x;
					v[i].v = ((v[i].v - center.y) * factor) + center.y;
				} else {
					v[i].u = ((v[i].u - center.x) * factor) + center.x;
					v[i].v = ((v[i].v - center.y) * factor) + center.y;
				}
			}
			pDev->vt->DrawPrimitiveUP(pDev, 5, 2, v,
				sizeof(_TRANS_LIT_TEX_VERTEX));
		}
	}
	m_lastFrame = TheGameLogic->frame;
	if (pan)
		m_skipRender = false;
	reset();
	if (!continueEffect)
		ZoomToValid = false;
	return continueEffect;
}
