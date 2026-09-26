// ?d_007d9aa0@@YAXXZ
// partial score=0.5 date=2026-09-04
// ?d_007d9aa0@@YAXXZ
// partial score=0.5 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#define HEAP_ZERO_MEMORY 8
extern "C" __declspec(dllimport) void * __stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void * __stdcall HeapAlloc(void *, unsigned long, unsigned long);
extern "C" __declspec(dllimport) int __stdcall HeapFree(void *, unsigned long, void *);

#define protected public
#include "dx8wrapper.h"
#undef protected
#include "Lib/BaseType.h"
#include "Common/File.h"
#include "Common/FileSystem.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "GameClient/view.h"
#include "GameClient/display.h"
#include "GameLogic/GameLogic.h"
#include "d3dx8tex.h"

// BFME retail keeps the ZH control flow, but replaces DrawPrimitiveUP with a
// DynamicVBAccessClass/DynamicIBAccessClass quad.  This banked body preserves
// the complete source-level algorithm and exposes that first structural wall.
Bool ScreenMotionBlurFilter::postRender(enum FilterModes mode, Coord2D &scrollDelta, Bool &doExtraRender)
{
	IDirect3DTexture8 *tex = W3DShaderManager::endRenderToTexture();
	if (!tex) return false;
	if (!set(mode)) return false;

	LPDIRECT3DDEVICE8 pDev = DX8Wrapper::_Get_D3D_Device8();
	Bool continueEffect = true;
	struct Vertex {
		D3DXVECTOR4 p;
		DWORD color;
		float u;
		float v;
	} v[4];

	Int xpos, ypos, width, height;
	pDev->SetTexture(0, tex);
	TheTacticalView->getOrigin(&xpos, &ypos);
	width = TheTacticalView->getWidth();
	height = TheTacticalView->getHeight();

	v[0].p = D3DXVECTOR4(xpos + width - 0.5f, ypos + height - 0.5f, 0.0f, 1.0f);
	v[0].u = (Real)(xpos + width) / (Real)TheDisplay->getWidth();
	v[0].v = (Real)(ypos + height) / (Real)TheDisplay->getHeight();
	v[1].p = D3DXVECTOR4(xpos + width - 0.5f, ypos - 0.5f, 0.0f, 1.0f);
	v[1].u = (Real)(xpos + width) / (Real)TheDisplay->getWidth();
	v[1].v = (Real)ypos / (Real)TheDisplay->getHeight();
	v[2].p = D3DXVECTOR4(xpos - 0.5f, ypos + height - 0.5f, 0.0f, 1.0f);
	v[2].u = (Real)xpos / (Real)TheDisplay->getWidth();
	v[2].v = (Real)(ypos + height) / (Real)TheDisplay->getHeight();
	v[3].p = D3DXVECTOR4(xpos - 0.5f, ypos - 0.5f, 0.0f, 1.0f);
	v[3].u = (Real)xpos / (Real)TheDisplay->getWidth();
	v[3].v = (Real)ypos / (Real)TheDisplay->getHeight();
	v[0].color = v[1].color = v[2].color = v[3].color = 0xffffffff;

	if (m_additive) {
		DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_ONE);
	} else {
		DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, false);
	DX8Wrapper::Apply_Render_State_Changes();
	pDev->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	Coord2D center;
	center.x = 0.5f;
	center.y = 0.5f;
	Bool pan = false;
	if (mode >= (FilterModes)16) {
		Real len = sqrt(scrollDelta.x * scrollDelta.x + scrollDelta.y * scrollDelta.y);
		center.y -= 0.5f;
		m_decrement = false;
		m_maxCount = (len * 200 * m_panFactor / (Real)DEFAULT_PAN_FACTOR);
		if (m_maxCount < m_panFactor / 2) m_maxCount = m_panFactor / 2;
		if (m_maxCount > m_panFactor) m_maxCount = m_panFactor;
		pan = true;
		m_priorDelta = scrollDelta;
	} else if (mode == (FilterModes)13) {
		Real len = sqrt(m_priorDelta.x * m_priorDelta.x + m_priorDelta.y * m_priorDelta.y);
		center.x += 0.5f * (m_priorDelta.x / len);
		center.y -= 0.5f * (m_priorDelta.y / len);
		m_decrement = false;
		m_maxCount--;
		if (m_maxCount < 2) continueEffect = false;
		pan = true;
	}

	m_skipRender = false;
	if (!pan && m_lastFrame != TheGameLogic->getFrame()) {
		if (m_decrement) {
			m_maxCount -= COUNT_STEP;
			if (m_maxCount < 1) {
				m_decrement = false;
				continueEffect = false;
			} else m_skipRender = true;
		} else {
			m_maxCount += COUNT_STEP;
			if (m_maxCount >= MAX_COUNT) {
				m_decrement = true;
				if (m_doZoomTo && m_zoomToValid) TheTacticalView->lookAt(&m_zoomToPos);
				else continueEffect = false;
			} else m_skipRender = true;
		}
	}

	Int i, j;
	if (!pan) {
		for (i = 0; i < 4; i++) {
			Real factor = 1.0f - (m_maxCount / (Real)MAX_COUNT) * 0.90f;
			factor = sqrt(factor);
			v[i].u = ((v[i].u - center.x) * factor) + center.x;
			v[i].v = ((v[i].v - center.y) * factor) + center.y;
		}
	}
	pDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
	pDev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	pDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex));
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, true);
	DX8Wrapper::Apply_Render_State_Changes();

	Int limit = m_maxCount;
	if (m_maxCount > 30) limit = 30;
	for (j = 0; j < limit; j++) {
		for (i = 0; i < 4; i++) {
			Real factor = m_additive ? 0.98f : 0.99f;
			Int alpha = 0x15;
			if (m_additive) {
				alpha = 0x09;
				if (m_maxCount > limit) alpha += (m_maxCount - limit) / 5;
				if (m_maxCount == MAX_COUNT) alpha += 60;
			}
			v[i].color = (alpha << 24) | 0x00ffffff;
			if (pan) {
				v[i].u = ((v[i].u - center.x) * (factor + .006f)) + center.x;
				v[i].v = ((v[i].v - center.y) * factor) + center.y;
			} else {
				v[i].u = ((v[i].u - center.x) * factor) + center.x;
				v[i].v = ((v[i].v - center.y) * factor) + center.y;
			}
		}
		pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex));
	}
	m_lastFrame = TheGameLogic->getFrame();
	if (pan) m_skipRender = false;
	reset();
	if (!continueEffect) m_zoomToValid = false;
	return continueEffect;
}
